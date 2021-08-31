#include "StdInc.h"

RxVertexIndex (&CSkidmarks::m_aIndices)[96] = *reinterpret_cast<unsigned short (*)[96]>(0xC799C8);
RwTexture*& CSkidmarks::m_pTexture = *reinterpret_cast<RwTexture**>(0xC79A88);
CSkidmark (&CSkidmarks::m_aSkidmarks)[SKIDMARKS_COUNT] = *reinterpret_cast<CSkidmark (*)[SKIDMARKS_COUNT]>(0xC79AA8);

void CSkidmarks::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CSkidmarks", "Clear", 0x720590, &CSkidmarks::Clear);
    Install("CSkidmarks", "Init", 0x7204E0, &CSkidmarks::Init);
    Install("CSkidmarks", "RegisterOne_EC0", 0x720EC0, (void (*)(uint32_t, const CVector&, float, float, const bool*, bool&, float))(&CSkidmarks::RegisterOne));
    Install("CSkidmarks", "RegisterOne", 0x720930, (void (*)(uint32_t, const CVector&, float, float, eSkidMarkType, bool&, float))(&CSkidmarks::RegisterOne));
    Install("CSkidmarks", "Render", 0x720640, &CSkidmarks::Render);
    Install("CSkidmarks", "Shutdown", 0x720570, &CSkidmarks::Shutdown);
    Install("CSkidmarks", "Update", 0x7205C0, &CSkidmarks::Update);
}

// 0x720590
void CSkidmarks::Clear() {
    for (CSkidmark& mark : m_aSkidmarks) {
        mark.m_nState = eSkidmarkState::INACTIVE;
        mark.m_bActive = 0;
    }
}

// 0x7204E0
void CSkidmarks::Init() {
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(CTxdStore::FindTxdSlot("particle"));
    m_pTexture = RwTextureRead("particleskid", 0);
    CTxdStore::PopCurrentTxd();

    Clear();

    for (unsigned i = 0; i < SKIDMARK_NUM_PARTS; i++) { // todo fix
        constexpr unsigned indicesRelative[] = { 0, 2, 1, 1, 2, 3 };
        for (unsigned v = 0; v < 6; v++) {
            m_aIndices[6 * i + v] = (RxVertexIndex)(2 * i + indicesRelative[v]);
        }
    }
}

// 0x720EC0
void CSkidmarks::RegisterOne(uint32_t index, const CVector& posn, float dirX, float dirY, const bool* isSandy, bool& bloodState, float length) {
    if (bloodState)
        CSkidmarks::RegisterOne(index, posn, dirX, dirY, eSkidMarkType::BLOODY, bloodState, length);
    else
        CSkidmarks::RegisterOne(index, posn, dirX, dirY, *isSandy ? eSkidMarkType::SANDY : eSkidMarkType::DEFALT, bloodState, length);
}

CSkidmark* CSkidmarks::FindById(uint32_t id) {
    for (CSkidmark& mark : m_aSkidmarks)
        if (mark.m_nState == eSkidmarkState::JUST_UPDATED && mark.m_id == id)
            return &mark;
    return nullptr;
}

// Try get an unsued slot/forcefully reuse one that isn't visible
CSkidmark* CSkidmarks::GetNextFree(bool forceFree) {
    for (CSkidmark& mark : m_aSkidmarks)
        if (mark.m_nState == eSkidmarkState::INACTIVE)
            return &mark;

    if (forceFree) {
        auto mostRecentlyUpdatedMs = std::numeric_limits<uint32>::max();
        CSkidmark* mostRecentlyUpdatedMark{};
        for (CSkidmark& mark : m_aSkidmarks) {
            if (mark.m_bActive)
                continue;
            if (mark.m_lastDisappearTimeUpdateMs >= mostRecentlyUpdatedMs)
                continue;
            if (!TheCamera.IsSphereVisible(mark.GetBoundingSphere())) {
                mostRecentlyUpdatedMs = mark.m_lastDisappearTimeUpdateMs;
                mostRecentlyUpdatedMark = &mark;
            }
        }
        return mostRecentlyUpdatedMark;
    }

    return nullptr;
}

// 0x720930
void CSkidmarks::RegisterOne(uint32_t index, const CVector& posn, float dirX, float dirY, eSkidMarkType type, bool& bloodState, float length) {
    if (CSkidmark* markById = FindById(index)) {
        markById->RegisterNewPart(posn, { dirX, dirY }, length, bloodState);
    } else if (CSkidmark* mark = GetNextFree(true)) {
        mark->Init(index, posn, type, bloodState);
    }
}

// 0x720640
void CSkidmarks::Render() {
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     (void*)RwTextureGetRaster(m_pTexture));

    for (CSkidmark& mark : m_aSkidmarks) {
        mark.Render();
    }

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       (void*)TRUE);
}

// 0x720570
void CSkidmarks::Shutdown() {
    RwTextureDestroy(CSkidmarks::m_pTexture);
    CSkidmarks::m_pTexture = nullptr;
}

// 0x7205C0
void CSkidmarks::Update() {
    for (CSkidmark& mark : m_aSkidmarks) {
        mark.Update();
    }
}
