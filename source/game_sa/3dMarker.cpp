#include "StdInc.h"

#include "3dMarker.h"
#include "3dMarkers.h"

void C3dMarker::InjectHooks() {
    RH_ScopedClass(C3dMarker);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(AddMarker, 0x722230);
    RH_ScopedInstall(DeleteMarkerObject, 0x722390);
    RH_ScopedInstall(IsZCoordinateUpToDate, 0x7226A0);
    RH_ScopedInstall(Render, 0x7223D0);
    RH_ScopedInstall(SetZCoordinateIfNotUpToDate, 0x724E10);
    // RH_ScopedInstall(UpdateZCoordinate, 0x724D40);
}

// uint8 r, uint8 g, uint8 b, uint8 a -> CRGBA
// 0x722230
bool C3dMarker::AddMarker(uint32 id, uint16 type, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate) {
    const CRGBA color = { red, green, blue, alpha };

    m_nIdentifier = id;
    m_mat.SetUnity();

    RpClump* clump;
    switch (type) {
    case MARKER3D_TUBE:
        clump = C3dMarkers::m_pRpClumpArray[1]; // black cylinder
        break;
    case MARKER3D_ARROW2:
        clump = C3dMarkers::m_pRpClumpArray[0]; // diamond_3
        break;
    default:
        clump = C3dMarkers::m_pRpClumpArray[type];
    }
    uint32 atomicPtr = 0;
    RpClumpForAllAtomics(clump, MarkerAtomicCB, &atomicPtr);

    assert(atomicPtr != 0);
    auto atomic = RpAtomicClone((RpAtomic*)atomicPtr);
    auto frame = RwFrameCreate();
    RpAtomicSetFrame(atomic, frame);
    CVisibilityPlugins::SetAtomicRenderCallback(atomic, nullptr);
    RpGeometrySetFlags(atomic->geometry, RpGeometryGetFlags(atomic->geometry) | rpGEOMETRYMODULATEMATERIALCOLOR); // v14->geometry->flags |= 0x40u;
    m_pAtomic = atomic;

    m_mat.Attach(&frame->modelling, false);
    m_pMaterial = RpGeometryGetMaterial(atomic->geometry, 0);
    m_fSize = size;
    m_fStdSize = size;
    m_colour = color;
    m_nPulsePeriod = pulsePeriod;
    m_fPulseFraction = pulseFraction;
    m_nRotateRate = rotateRate;
    m_nStartTime = CTimer::GetTimeInMS();
    m_vecLastPosition = CVector{};
    m_nType = static_cast<e3dMarkerType>(type);
    m_fRoofHeight = 65535.0f;
    m_nOnScreenTestTime = CTimer::GetTimeInMS();
    return m_pAtomic != nullptr;
}

// 0x722390
void C3dMarker::DeleteMarkerObject() {
    // plugin::CallMethod<0x722390, C3dMarker*>(this);

    m_nIdentifier = 0;
    m_nStartTime = 0;
    m_bIsUsed = false;
    m_bMustBeRenderedThisFrame = false;
    m_nType = MARKER3D_NA;
    auto* frame = RpAtomicGetFrame(m_pAtomic);
    RpAtomicDestroy(m_pAtomic);
    RwFrameDestroy(frame);
    m_pAtomic = nullptr;
}

// 0x7226A0
bool C3dMarker::IsZCoordinateUpToDate() {
    return m_nLastMapReadX == static_cast<uint16>(m_mat.GetPosition().x)
        && m_nLastMapReadY == static_cast<uint16>(m_mat.GetPosition().y);
}

// 0x7223D0
void C3dMarker::Render() {
    static uint8& s_SavedAlpha = *(uint8*)0x8D5E44;

    if (!m_pAtomic)
        return;

    if (m_nType == MARKER3D_CYLINDER)
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));
    else
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLBACK));

    CMatrix mat_1;
    m_mat.UpdateRW();
    mat_1.Attach(m_mat.m_pAttachMatrix, false);
    if (m_nType == MARKER3D_TORUS || m_nType == MARKER3D_ARROW2) {
        CMatrix mat;
        mat.SetUnity();
        CVector v13 = { 0.0f, 0.0f, 1.0f };
        if (m_vecNormal != v13) {
            auto right = CrossProduct(&v13, &m_vecNormal);
            right.Normalise();

            auto forward = CrossProduct(&m_vecNormal, &right);
            forward.Normalise();

            mat.GetRight().x = right.x;
            mat.GetRight().z = right.z;
            mat.GetForward().x = forward.x;
            mat.GetForward().z = forward.z;
            mat.GetUp() = m_vecNormal;
        }
        mat_1 *= mat;
    }
    mat_1.Scale(m_fSize);
    if (m_nType == MARKER3D_TUBE)
        mat_1.ScaleXYZ(1.0f, 1.0f, 20.0f);
    mat_1.UpdateRW();

    RwFrameUpdateObjects(RpAtomicGetFrame(m_pAtomic));

    if (!m_nType || m_nType == MARKER3D_CONE || m_nType == MARKER3D_CONE_NO_COLLISION)
        m_colour.a = -1;

    if (m_colour.a == s_SavedAlpha) {
        if (m_colour.a <= 127u)
            m_colour.a += 1;
        else
            m_colour.a -= 1;
    }
    s_SavedAlpha = m_colour.a;

    const auto color = m_colour.ToRwRGBA();
    RpMaterialSetColor(m_pMaterial, &color);
    SetBrightMarkerColours(m_fBrightness);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(FALSE));
    if (m_nType == MARKER3D_ARROW2)
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));
    m_pAtomic->renderCallBack(m_pAtomic);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(TRUE));
    ReSetAmbientAndDirectionalColours();
}

// 0x724E10
void C3dMarker::SetZCoordinateIfNotUpToDate(float coordinate) {
    if (IsZCoordinateUpToDate())
        return;

    m_mat.GetPosition().z = coordinate;
}

// 0x724D40
void C3dMarker::UpdateZCoordinate(CVector point, float zDistance) {
    return plugin::CallMethod<0x724D40, C3dMarker*, CVector, float>(this, point, zDistance);

    if (IsZCoordinateUpToDate())
        return;

    auto& pos = m_mat.GetPosition();
    if (DistanceBetweenPointsSquared2D(pos, point) >= sq(100.0f))
        return;

    if (CColStore::HasCollisionLoaded(pos, AREA_CODE_NORMAL_WORLD)) {
        bool found{};
        auto height = CWorld::FindGroundZFor3DCoord({ pos.x, pos.y, pos.z + 1.0f }, &found, nullptr); // todo: Add OG version FindGroundZFor3DCoord(float x, float y, float z)?
        if (found) {
            pos.z = height - zDistance / 20.0f;
        }

        m_nLastMapReadX = static_cast<uint16>(pos.x);
        m_nLastMapReadY = static_cast<uint16>(pos.y);
    }
}
