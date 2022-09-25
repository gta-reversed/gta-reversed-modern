#include "StdInc.h"

#include <extensions/enumerate.hpp>

#include "3dMarkers.h"
#include "PostEffects.h"

void C3dMarkers::InjectHooks() {
    RH_ScopedClass(C3dMarkers);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x724E40);
    RH_ScopedInstall(Update, 0x7227B0);
    RH_ScopedInstall(Shutdown, 0x722710);
    RH_ScopedInstall(Render, 0x725040);
    RH_ScopedInstall(DirectionArrowFindFirstFreeSlot, 0x721120);
    RH_ScopedInstall(DirectionArrowSet, 0x721140);
    RH_ScopedInstall(DirectionArrowsDraw, 0x7211F0, {.reversed = false});
    RH_ScopedInstall(DirectionArrowsInit, 0x721100);
    RH_ScopedInstall(ForceRender, 0x722870);
    RH_ScopedInstall(PlaceMarker, 0x725120, {.reversed = false});
    RH_ScopedInstall(PlaceMarkerCone, 0x726D40);
    RH_ScopedInstall(PlaceMarkerSet, 0x725BA0);
    RH_ScopedInstall(User3dMarkerAtomicCB, 0x7210D0);
    RH_ScopedInstall(User3dMarkerDelete, 0x721090);
    RH_ScopedInstall(User3dMarkerDeleteAll, 0x7210B0);
    RH_ScopedInstall(User3dMarkerFindFirstFreeSlot, 0x720FB0);
    RH_ScopedInstall(User3dMarkerSet, 0x720FD0);
    RH_ScopedInstall(User3dMarkersDraw, 0x723240);
    RH_ScopedInstall(LoadUser3dMarkers, 0x5D42E0);
    RH_ScopedInstall(SaveUser3dMarkers, 0x5D4300);
}

// 0x724E40
void C3dMarkers::Init() {
    for (auto& marker : m_aMarkerArray) {
        marker.Init();
    }

    memset(&m_pRpClumpArray, 0, sizeof(m_pRpClumpArray));

    NumActiveMarkers = 0;
    m_angleDiamond = 0.0f;

    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(CTxdStore::FindTxdSlot("particle"));
    CFileMgr::ChangeDir("\\");

    m_pRpClumpArray[1] = LoadMarker("cylinder"); // black cylinder
    m_pRpClumpArray[4] = LoadMarker("hoop");     // black hoop
    auto clump         = LoadMarker("diamond_3");
    m_pRpClumpArray[0] = clump;
    m_pRpClumpArray[6] = clump;
    m_pRpClumpArray[5] = clump;

    CTxdStore::PopCurrentTxd();
}

// 0x7227B0
void C3dMarkers::Update() {
    m_angleDiamond += CTimer::GetTimeStep() * 5.0f;

    for (auto& marker : m_aMarkerArray) {
        if (marker.m_bIsUsed) {
            marker.m_mat.UpdateRW();
            RwFrameUpdateObjects(RpAtomicGetFrame(marker.m_pAtomic));
            marker.m_bMustBeRenderedThisFrame = true;
        }
    }
}

// 0x722710
void C3dMarkers::Shutdown() {
    for (auto& marker : m_aMarkerArray) {
        if (!marker.m_pAtomic)
            continue;

        marker.DeleteMarkerObject();
    }

    // WTF?
    for (auto i = 0; auto& clump : m_pRpClumpArray) {
        if (clump) {
            RpClumpForAllAtomics(clump, RemoveRefsCB, nullptr);
            RpClumpDestroy(clump);
            for (auto j = 0; auto& clump1 : m_pRpClumpArray) {
                if (i != j && m_pRpClumpArray[j] == clump)
                    m_pRpClumpArray[j] = nullptr;
            }
            clump = nullptr;
        }
    }
}

// 0x725040
void C3dMarkers::Render() {
    static RwRGBAReal& ambient = *(RwRGBAReal*)0xC80444;
    static RwRGBAReal& directional = *(RwRGBAReal*)0xC80434;

    NumActiveMarkers = 0;
    ActivateDirectional();
    SetAmbientColours(&ambient);
    SetDirectionalColours(&directional);
    User3dMarkersDraw();

    for (auto& marker : m_aMarkerArray) {
        if (marker.m_bMustBeRenderedThisFrame) {
            if (TheCamera.IsSphereVisible(&marker.m_mat.GetPosition(), 2.0f, reinterpret_cast<RwMatrix*>(&TheCamera.m_mMatInverse))) {
                if (marker.m_fCameraRange < 150.0f || IgnoreRenderLimit || marker.m_nType == MARKER3D_TORUS) {
                    marker.Render();
                }
            }
            marker.m_bIsUsed = false;
            marker.m_bMustBeRenderedThisFrame = false;
            NumActiveMarkers += 1;
        } else {
            if (marker.m_pAtomic) {
                marker.DeleteMarkerObject();
            }
        }
    }
    DirectionArrowsDraw();
}

// Returns slot index; -1 if not found
// 0x721120
int32 C3dMarkers::DirectionArrowFindFirstFreeSlot() {
    for (const auto& [index, arrow] : notsa::enumerate(ms_directionArrows)) {
        if (!arrow.m_bIsUsed) {
            return index;
        }
    }
    return -1;
}

// 0x721140
void C3dMarkers::DirectionArrowSet(CVector posn, float size, int32 red, int32 green, int32 blue, int32 alpha, float dirX, float dirY, float dirZ) {
    auto arrowIndex = DirectionArrowFindFirstFreeSlot();
    if (arrowIndex == -1)
        return; // -1 where? see User3dMarkerSet

    auto& arrow = ms_directionArrows[arrowIndex];
    arrow.m_vecPosition.Set(posn.x, posn.y, posn.z + 3.0f);
    arrow.m_vecDirection.Set(dirX, dirY, dirZ);
    arrow.m_fSize = size;
    arrow.m_nRed = red;
    arrow.m_nGreen = green;
    arrow.m_nBlue = blue;
    arrow.m_nAlpha = alpha;
    arrow.m_bIsUsed = true;
}

// 0x7211F0
void C3dMarkers::DirectionArrowsDraw() {
    // return plugin::Call<0x7211F0>();

    auto bRenderParamsSet = false;
    for (auto& arrow : ms_directionArrows) {
        if (!arrow.m_bIsUsed)
            continue;

        if (!bRenderParamsSet) {
            RwRenderStateGet(rwRENDERSTATECULLMODE,          &gStoredRenderStateCullMode);
            RwRenderStateGet(rwRENDERSTATEZTESTENABLE,       &gStoredRenderStateZTestEnable);
            RwRenderStateGet(rwRENDERSTATEZWRITEENABLE,      &gStoredRenderStateZWriteEnable);
            RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &gStoredRenderStateVertexAlphaEnable);

            RwRenderStateSet(rwRENDERSTATECULLMODE,          RWRSTATE(rwCULLMODECULLNONE));
            RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(TRUE));
            RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
            bRenderParamsSet = true;
        }

        auto& clump = m_pRpClumpArray[5];
        auto frame = RpClumpGetFrame(clump);
        RwFrameSetIdentity(frame);
        RwFrameTranslate(frame, &arrow.m_vecPosition, rwCOMBINEREPLACE);

        CMatrix matrix1(&frame->modelling, false);
        matrix1.UpdateRW();

        CMatrix matrix2;
        matrix2.SetUnity();

        CVector vec = { 0.0f, 0.0f, 1.0f };
        if (arrow.m_vecDirection != vec) {
            auto right = CrossProduct(&vec, &arrow.m_vecDirection);
            right.Normalise();

            auto forward = CrossProduct(&arrow.m_vecDirection, &right);
            forward.Normalise();

            matrix2.GetRight()   = right;
            matrix2.GetForward() = forward;
            matrix2.GetUp()      = arrow.m_vecDirection;
        }
        matrix1 *= matrix2;

        // 0x7214DF useless loop

        matrix1.UpdateRW();
        RwFrameUpdateObjects(frame);
        m_user3dMarkerColor = CRGBA(0, 0, 0, -1);
        RpClumpForAllAtomics(clump, User3dMarkerAtomicCB, nullptr);
        RpClumpRender(clump);

        // 0x721552 useless loop

        matrix1.UpdateRW();
        RwFrameUpdateObjects(frame);
        m_user3dMarkerColor = CRGBA(arrow.m_nRed, arrow.m_nGreen, arrow.m_nBlue, arrow.m_nAlpha);
        RpClumpForAllAtomics(clump, User3dMarkerAtomicCB, nullptr);
        RpClumpRender(clump);
        arrow.m_bIsUsed = false;
    }

    if (bRenderParamsSet) {
        RwRenderStateSet(rwRENDERSTATECULLMODE,          RWRSTATE(gStoredRenderStateCullMode));
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(gStoredRenderStateZTestEnable));
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(gStoredRenderStateZWriteEnable));
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(gStoredRenderStateVertexAlphaEnable));
    }
}

// 0x721100
void C3dMarkers::DirectionArrowsInit() {
    for (auto& arrow : ms_directionArrows) {
        arrow.m_bIsUsed = false;
    }
}

// 0x722870
void C3dMarkers::ForceRender(bool ignore) {
    IgnoreRenderLimit = ignore;
}

// 0x722810
inline RpClump* C3dMarkers::LoadMarker(const char* modelName) {
    int32 modelId = MODEL_INVALID;
    auto mi = CModelInfo::GetModelInfo(modelName, &modelId);
    CStreaming::RequestModel(modelId, STREAMING_GAME_REQUIRED);
    CStreaming::LoadAllRequestedModels(false);
    RwObject* obj = mi->CreateInstance();
    mi->AddRef();
    auto* clump = RpClumpCreate();
    RwFrameSetIdentity(static_cast<RwFrame*>(obj->parent));
    RpClumpAddAtomic(clump, reinterpret_cast<RpAtomic*>(obj));
    RpClumpSetFrame(clump, obj->parent);
    return clump;
}

// 0x725120
C3dMarker* C3dMarkers::PlaceMarker(uint32 id, e3dMarkerType type, CVector& posn, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate, float nrm_x, float nrm_y, float nrm_z, bool zCheck) {
    return plugin::CallAndReturn<C3dMarker*, 0x725120, uint32, e3dMarkerType, CVector&, float, uint8, uint8, uint8, uint8, uint16, float, int16, float, float, float, bool>(id, type, posn, size, red, green, blue, alpha, pulsePeriod, pulseFraction, rotateRate, nrm_x, nrm_y, nrm_z, zCheck);
}

// 0x726D40
void C3dMarkers::PlaceMarkerCone(uint32 id, CVector& point, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate, bool bEnableCollision) {
    const auto& cameraPos = TheCamera.GetPosition();
    if ((point - cameraPos).Magnitude() < 1.6f)
        return;

    if (bEnableCollision)
        PlaceMarker(id, MARKER3D_CONE, point, size, red, green, blue, m_colDiamond, pulsePeriod, pulseFraction, 0, 0.0f, 0.0f, 0.0f, false);
    else
        PlaceMarker(id, MARKER3D_CONE_NO_COLLISION, point, size, red, green, blue, m_colDiamond, pulsePeriod, pulseFraction, 0, 0.0f, 0.0f, 0.0f, false);
}

// 0x725BA0
void C3dMarkers::PlaceMarkerSet(uint32 id, e3dMarkerType type, CVector& posn, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate) {
    PlaceMarker(id, type, posn, size, red, green, blue, static_cast<uint8>((float)alpha * 1.0f / 3.0f), pulsePeriod, pulseFraction, 1, 0.0f, 0.0f, 0.0f, false);
}

// only set material color (m_user3dMarkerColor) for first material in first atomic; 'data' is unused
// 0x7210D0
RpAtomic* C3dMarkers::User3dMarkerAtomicCB(RpAtomic* atomic, void* data) {
    UNUSED(data);
    const auto geometry = RpAtomicGetGeometry(atomic);
    const auto material = RpGeometryGetMaterial(geometry, 0);
    const auto color = m_user3dMarkerColor.ToRwRGBA();
    RpMaterialSetColor(material, &color);
    return nullptr;
}

// 0x721090
void C3dMarkers::User3dMarkerDelete(int32 slotIndex) {
    if (slotIndex < 0 || slotIndex > 4)
        return;

    ms_user3dMarkers[slotIndex].m_bIsUsed = false;
}

// 0x7210B0
void C3dMarkers::User3dMarkerDeleteAll() {
    for (auto& marker : ms_user3dMarkers) {
        marker.m_bIsUsed = false;
    }
}

// Returns slot index; -1 if not found
// 0x720FB0
int32 C3dMarkers::User3dMarkerFindFirstFreeSlot() {
    for (const auto& [index, marker] : notsa::enumerate(ms_user3dMarkers)) {
        if (!marker.m_bIsUsed) {
            return index;
        }
    }
    return -1;
}

// Returns slot index; -1 if not created; for 'color', see eHudColours
// 0x720FD0
int32 C3dMarkers::User3dMarkerSet(float x, float y, float z, int32 color) {
    const auto markerIndex = User3dMarkerFindFirstFreeSlot();
    if (markerIndex == -1)
        return -1;

    auto& marker = ms_user3dMarkers[markerIndex];

    marker.m_vecPosition.Set(x, y, z);
    const auto colour = HudColour.GetRGB((eHudColours)color);
    marker.m_nRed   = colour.r;
    marker.m_nGreen = colour.g;
    marker.m_nBlue  = colour.b;
    marker.m_bIsUsed = true;

    return markerIndex;
}

// 0x723240
void C3dMarkers::User3dMarkersDraw() {
    bool bRenderParamsSet = false;

    for (auto& marker : ms_user3dMarkers) {
        if (!marker.m_bIsUsed)
            continue;

        if (!bRenderParamsSet) {
            RwRenderStateGet(rwRENDERSTATECULLMODE,     &gStoredRenderStateCullMode);
            RwRenderStateGet(rwRENDERSTATEZTESTENABLE,  &gStoredRenderStateZTestEnable);
            RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &gStoredRenderStateZWriteEnable);

            RwRenderStateSet(rwRENDERSTATECULLMODE,     RWRSTATE(rwCULLMODECULLNONE));
            RwRenderStateSet(rwRENDERSTATEZTESTENABLE,  RWRSTATE(TRUE));
            RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(FALSE));
            bRenderParamsSet = true;
        }

        CVector translation = marker.m_vecPosition;
        translation.z = std::sin(m_angleDiamond * DegreesToRadians(1)) * 0.25f + translation.z;

        auto clump = m_pRpClumpArray[5]; // diamond_3
        auto frame = RpClumpGetFrame(clump);
        RwFrameSetIdentity(frame);
        RwFrameTranslate(frame, &translation, rwCOMBINEREPLACE);

        m_user3dMarkerColor.Set(marker.m_nRed, marker.m_nGreen, marker.m_nBlue, -1);
        RpClumpForAllAtomics(clump, User3dMarkerAtomicCB, nullptr);
        RpClumpRender(clump);
    }

    if (bRenderParamsSet) {
        RwRenderStateSet(rwRENDERSTATECULLMODE,     RWRSTATE(gStoredRenderStateCullMode));
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE,  RWRSTATE(gStoredRenderStateZTestEnable));
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(gStoredRenderStateZWriteEnable));
    }
}

// 0x5D42E0
bool C3dMarkers::LoadUser3dMarkers() {
    for (auto& marker : ms_user3dMarkers) {
        CGenericGameStorage::LoadDataFromWorkBuffer(&marker, sizeof(marker));
    }
    return true;
}

// 0x5D4300
bool C3dMarkers::SaveUser3dMarkers() {
    for (auto& marker : ms_user3dMarkers) {
        CGenericGameStorage::SaveDataToWorkBuffer(&marker, sizeof(marker));
    }
    return true;
}

// 'data' is a pointer to store atomic (RpAtomic **)
// 0x722220
RpAtomic* MarkerAtomicCB(RpAtomic* atomic, void* data) {
    return plugin::CallAndReturn<RpAtomic*, 0x722220, RpAtomic*, void*>(atomic, data);

    *static_cast<RpAtomic*>(data) = *atomic;
    return atomic;
}
