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
    RH_ScopedInstall(UpdateZCoordinate, 0x724D40);
}

RpAtomic* GetAtomicForMarkerType(e3dMarkerType type) {
    return GetFirstAtomic(
        [type]{
            switch (type) {
            case MARKER3D_TUBE:
                return C3dMarkers::m_pRpClumpArray[1]; // black cylinder
            case MARKER3D_ARROW2:
                return C3dMarkers::m_pRpClumpArray[0]; // diamond_3
            default:
                return C3dMarkers::m_pRpClumpArray[type];
            }
        }()
    );
}

// uint8 r, uint8 g, uint8 b, uint8 a -> CRGBA
// 0x722230
bool C3dMarker::AddMarker(uint32 id, uint16 type, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate) {
    const CRGBA color = { red, green, blue, alpha };

    m_pAtomic = RpAtomicClone(GetAtomicForMarkerType((e3dMarkerType)type));
    assert(m_pAtomic);

    const auto frame = RwFrameCreate();
    const auto geo   = RpAtomicGetGeometry(m_pAtomic);

    RpAtomicSetFrame(m_pAtomic, frame);
    CVisibilityPlugins::SetAtomicRenderCallback(m_pAtomic, nullptr);

    RpGeometrySetFlags(geo, RpGeometryGetFlags(geo) | rpGEOMETRYMODULATEMATERIALCOLOR);

    m_mat.SetUnity();
    m_mat.Attach(RwFrameGetMatrix(frame), false);

    m_nIdentifier       = id;
    m_pMaterial         = RpGeometryGetMaterial(geo, 0);
    m_fSize             = size;
    m_fStdSize          = size;
    m_colour            = color;
    m_nPulsePeriod      = pulsePeriod;
    m_fPulseFraction    = pulseFraction;
    m_nRotateRate       = rotateRate;
    m_nStartTime        = CTimer::GetTimeInMS();
    m_nOnScreenTestTime = CTimer::GetTimeInMS();
    m_vecLastPosition   = CVector{};
    m_nType             = static_cast<e3dMarkerType>(type);
    m_fRoofHeight       = 65535.0f;

    return m_pAtomic != nullptr;
}

// 0x722390
void C3dMarker::DeleteMarkerObject() {
    m_nIdentifier               = 0;
    m_nStartTime                = 0;
    m_bIsUsed                   = false;
    m_bMustBeRenderedThisFrame  = false;
    m_nType                     = MARKER3D_NA;

    // Destroy RW object
    const auto frame = RpAtomicGetFrame(m_pAtomic);
    RpAtomicDestroy(m_pAtomic);
    RwFrameDestroy(frame);
    m_pAtomic = nullptr;
}

// 0x7226A0
bool C3dMarker::IsZCoordinateUpToDate() {
    const auto& pos = m_mat.GetPosition();
    return m_nLastMapReadX == static_cast<uint16>(pos.x)
        && m_nLastMapReadY == static_cast<uint16>(pos.y);
}

// 0x7223D0
void C3dMarker::Render() {
    if (!m_pAtomic) {
        return;
    }

    RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(m_nType == MARKER3D_CYLINDER ? rwCULLMODECULLNONE : rwCULLMODECULLBACK));

    m_mat.UpdateRW();

    auto transform = CMatrix{ m_mat.m_pAttachMatrix };
    if (m_nType == MARKER3D_TORUS || m_nType == MARKER3D_ARROW2) {
        if (m_vecNormal != CVector{ 0.0f, 0.0f, 1.0f }) {
            transform *= CMatrix::WithUp(m_vecNormal);
        }
    }

    if (m_nType == MARKER3D_TUBE) {
        transform.ScaleXYZ(m_fSize, m_fSize, m_fSize * 20.0f);
    } else {
        transform.Scale(m_fSize);
    }

    transform.UpdateRW();

    RwFrameUpdateObjects(RpAtomicGetFrame(m_pAtomic));

    switch (m_nType) {
    case MARKER3D_ARROW:
    case MARKER3D_CONE:
    case MARKER3D_CONE_NO_COLLISION:
        m_colour.a = 255;
        break;
    }

    // TODO: What the fuck? I dont' think this does what they intended it to.
    static uint8& s_SavedAlpha = *(uint8*)0x8D5E44; // STATICREF
    if (m_colour.a == s_SavedAlpha) {
        m_colour.a += m_colour.a < 128u ? 1 : -1; // But then again, this doesn't make a lot more sense either
    }
    s_SavedAlpha = m_colour.a;

    const auto color = m_colour.ToRwRGBA();
    RpMaterialSetColor(m_pMaterial, &color);

    SetBrightMarkerColours(m_fBrightness);

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(FALSE));

    if (m_nType == MARKER3D_ARROW2)
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));

    // And now, render the atomic
    RpAtomicRender(m_pAtomic);

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(TRUE));

    ReSetAmbientAndDirectionalColours();
}

// 0x724E10
void C3dMarker::SetZCoordinateIfNotUpToDate(float coordinate) {
    if (!IsZCoordinateUpToDate()) {
        m_mat.GetPosition().z = coordinate;
    }
}

// 0x724D40
void C3dMarker::UpdateZCoordinate(CVector point, float zDistance) {
    if (IsZCoordinateUpToDate()) {
        return;
    }

    auto& pos = m_mat.GetPosition();

    if (DistanceBetweenPointsSquared2D(pos, point) >= sq(100.0f)) {
        return;
    }

    if (!CColStore::HasCollisionLoaded(pos, AREA_CODE_NORMAL_WORLD)) {
        return;
    }

    bool found{};
    auto height = CWorld::FindGroundZFor3DCoord({ pos.x, pos.y, pos.z + 1.0f }, &found, nullptr);
    if (found) {
        pos.z = height - zDistance / 20.0f;
    }

    m_nLastMapReadX = static_cast<uint16>(pos.x);
    m_nLastMapReadY = static_cast<uint16>(pos.y);
}

void C3dMarker::DeleteIfHasAtomic() {
    if (m_pAtomic) {
        DeleteMarkerObject();
    }
}
