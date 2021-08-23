#include "StdInc.h"
#include "C3dMarker.h"

void C3dMarker::InjectHooks() {
    ReversibleHooks::Install("C3dMarker", "C3dMarker", 0x720F60, &C3dMarker::Constructor);
    ReversibleHooks::Install("C3dMarker", "~C3dMarker", 0x720F70, &C3dMarker::Destructor);

    ReversibleHooks::Install("C3dMarker", "AddMarker", 0x722230, &C3dMarker::AddMarker);
    ReversibleHooks::Install("C3dMarker", "DeleteMarkerObject", 0x722390, &C3dMarker::DeleteMarkerObject);
    ReversibleHooks::Install("C3dMarker", "Render", 0x7223D0, &C3dMarker::Render);
    ReversibleHooks::Install("C3dMarker", "IsZCoordinateUpToDate", 0x7226A0, &C3dMarker::IsZCoordinateUpToDate);
    ReversibleHooks::Install("C3dMarker", "UpdateZCoordinate", 0x724D40, &C3dMarker::UpdateZCoordinate);
    ReversibleHooks::Install("C3dMarker", "SetZCoordinateIfNotUpToDate", 0x724E10, &C3dMarker::SetZCoordinateIfNotUpToDate);
}

// 0x720F60
C3dMarker::C3dMarker() {
    /* Compiler does it for us */
}

C3dMarker* C3dMarker::Constructor() {
    this->C3dMarker::C3dMarker();
    return this;
}

// 0x720F70
C3dMarker::~C3dMarker() {
    /* Compiler does it for us */
}

C3dMarker* C3dMarker::Destructor() {
    this->C3dMarker::~C3dMarker();
    return this;
}

// 0x722230
bool C3dMarker::AddMarker(uint32_t id, e3dMarkerType type, float size, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, uint16_t pulsePeriod,
 float pulseFraction,
                          int16_t rotateRate) {

    m_nIdentifier = id;
    m_mat.SetUnity();

    m_pAtomic = C3dMarkers::GetClonedAtomicForType(type);
    RpAtomicSetFrame(m_pAtomic, RwFrameCreate());

    CVisibilityPlugins::SetAtomicRenderCallback(m_pAtomic, nullptr);
    m_mat.Attach(RwFrameGetMatrix(RpAtomicGetFrame(m_pAtomic)), false);

    RpGeometry* geometry = RpAtomicGetGeometry(m_pAtomic);
    RpGeometryGetFlags(geometry) |= rpGEOMETRYMODULATEMATERIALCOLOR;
    m_pMaterial = RpGeometryGetMaterial(geometry, 0);

    m_fSize = size;
    m_fStdSize = size;

    m_colour = CRGBA(red, green, blue, alpha);

    m_nPulsePeriod = pulsePeriod;
    m_fPulseFraction = pulseFraction;
    m_nRotateRate = rotateRate;
    m_nStartTime = CTimer::m_snTimeInMilliseconds;
    m_vecLastPosition = CVector();
    m_nType = type;
    m_fRoofHeight = 65535;
    m_nOnScreenTestTime = CTimer::m_snTimeInMilliseconds;

    return (bool)m_pAtomic;
}

// 0x722390
void C3dMarker::DeleteMarkerObject() {
    m_nIdentifier = 0;
    m_nStartTime = 0;
    m_bIsUsed = 0;
    m_bMustBeRenderedThisFrame = 0;
    m_nType = e3dMarkerType::MARKER3D_NA;

    RwFrame* frame = RpAtomicGetFrame(m_pAtomic);
    RpAtomicDestroy(m_pAtomic);
    RwFrameDestroy(frame);
    m_pAtomic = nullptr;
}

// 0x7223D0
void C3dMarker::Render() {
    if (!m_pAtomic)
        return;

    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)(m_nType == e3dMarkerType::MARKER3D_CYLINDER ? rwCULLMODECULLNONE : rwCULLMODECULLBACK));

    m_mat.UpdateRW();

    CMatrix mat(m_mat.m_pAttachMatrix, false);

    switch (m_nType) {
    case e3dMarkerType::MARKER3D_TORUS:
    case e3dMarkerType::MARKER3D_ARROW2: {
        // These types need to have their matrices calculated based on `m_vecNormal`

        CMatrix normalMatrix;
        normalMatrix.SetUnity();

        // Check if normal isn't default
        if (m_vecNormal.x != 0.0f || m_vecNormal.y != 0.0f || m_vecNormal.z != 1.0f) {
            // Basic math stuff here (Check out: https://www.mathsisfun.com/algebra/vectors-cross-product.html)
            normalMatrix.GetRight() = Normalized(CrossProduct(CVector(0.0f, 0.0, 1.0f), m_vecNormal));
            normalMatrix.GetForward() = Normalized(CrossProduct(m_vecNormal, normalMatrix.GetRight()));
            normalMatrix.GetUp() = m_vecNormal;
        }
        mat *= normalMatrix;
        break;
    }
    }

    mat.Scale(m_fSize);
    if (m_nType == e3dMarkerType::MARKER3D_TUBE)
        mat.Scale(1.0f, 1.0f, 20.0f);
    mat.UpdateRW();
    RwFrameUpdateObjects(RpAtomicGetFrame(m_pAtomic));

    // Color stuff
    {
        switch (m_nType) {
        case e3dMarkerType::MARKER3D_ARROW:
        case e3dMarkerType::MARKER3D_CONE:
        case e3dMarkerType::MARKER3D_CONE_NO_COLLISION: {
            m_colour.a = 255;
            break;
        }
        }

        static uint8_t lastAlpha;
        uint8_t& a = m_colour.a;
        if (a == lastAlpha) {
            if (a <= 127)
                a++;
            else
                a--;
        }
        lastAlpha = a;

        RwRGBA color = m_colour.ToRwRGBA(); // Can't take address of temporary
        RpMaterialSetColor(m_pMaterial, &color);
        SetBrightMarkerColours(m_fBrightness);
    }

    // And finally.. render
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)false);
    if (m_nType == e3dMarkerType::MARKER3D_ARROW2)
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
    RpAtomicRender(m_pAtomic);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)true);
    ReSetAmbientAndDirectionalColours();
}

// 0x7226A0
bool C3dMarker::IsZCoordinateUpToDate() {
    const CVector BugStarDevFrom2003 = m_mat.GetPosition();
    return (uint16_t)BugStarDevFrom2003.x == m_nLastMapReadX && (uint16_t)BugStarDevFrom2003.y == m_nLastMapReadX;
}

// 0x724D40
void C3dMarker::UpdateZCoordinate(CVector newPos, float zDistance) {
    if (IsZCoordinateUpToDate())
        return;

    CVector pos = m_mat.GetPosition();
    if ((pos - newPos).SquaredMagnitude2D() >= 100.0f * 100.0f)
        return;

    if (!CColStore::HasCollisionLoaded(m_mat.GetPosition(), 0))
        return;

    bool hit = false;
    const float groundZ = CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z + 1.0f, &hit, nullptr);
    if (hit)
        m_mat.GetPosition().z = groundZ - zDistance / 20.0f;

    m_nLastMapReadX = (uint16_t)pos.x;
    m_nLastMapReadY = (uint16_t)pos.y;
}

// 0x724E10
void C3dMarker::SetZCoordinateIfNotUpToDate(float zCoord) {
    if (!IsZCoordinateUpToDate())
        m_mat.GetPosition().z = zCoord;
}
