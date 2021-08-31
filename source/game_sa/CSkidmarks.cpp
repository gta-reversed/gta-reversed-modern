#include "StdInc.h"

RxVertexIndex (&CSkidmarks::m_aIndices)[96] = *reinterpret_cast<unsigned short (*)[96]>(0xC799C8);
RwTexture*& CSkidmarks::m_pTexture = *reinterpret_cast<RwTexture**>(0xC79A88);
CSkidmark (&CSkidmarks::m_aSkidmarks)[SKIDMARKS_COUNT] = *reinterpret_cast<CSkidmark (*)[SKIDMARKS_COUNT]>(0xC79AA8);

void CSkidmarks::InjectHooks() {
    ReversibleHooks::Install("CSkidmarks", "Clear", 0x720590, &CSkidmarks::Clear);
    ReversibleHooks::Install("CSkidmarks", "Init", 0x7204E0, &CSkidmarks::Init);
    ReversibleHooks::Install("CSkidmarks", "RegisterOne_EC0", 0x720EC0, (void (*)(uint32_t, const CVector&, float, float, const bool*, bool&, float))(&CSkidmarks::RegisterOne));
    ReversibleHooks::Install("CSkidmarks", "RegisterOne", 0x720930, (void (*)(uint32_t, const CVector&, float, float, eSkidMarkType, bool&, float))(&CSkidmarks::RegisterOne));
    // ReversibleHooks::Install("CSkidmarks", "Render", 0x720640, &CSkidmarks::Render);
    ReversibleHooks::Install("CSkidmarks", "Shutdown", 0x720570, &CSkidmarks::Shutdown);
    // ReversibleHooks::Install("CSkidmarks", "Update", 0x7205C0, &CSkidmarks::Update);
}

// 0x720590
void CSkidmarks::Clear() {
    for (CSkidmark& mark : m_aSkidmarks) {
        mark.m_nState = 0;
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

    for (unsigned i = 0; i < 16; i++) {
        constexpr unsigned indicesRelative[] = { 0, 2, 1, 1, 2, 3 };
        for (unsigned v = 0; v < 6; v++) {
            m_aIndices[i + v] = (RxVertexIndex)(2 * i + indicesRelative[v]);
        }
    }
}

// 0x720EC0
void CSkidmarks::RegisterOne(uint32_t index, const CVector& posn, float dirX, float dirY, const bool* isSandy, bool& bloodState, float length) {
    if (bloodState)
        CSkidmarks::RegisterOne(index, posn, dirX, dirY, (eSkidMarkType)3, bloodState, length); // TODO: Missing enum
    else
        CSkidmarks::RegisterOne(index, posn, dirX, dirY, *isSandy ? eSkidMarkType::SKIDMARK_SANDY : eSkidMarkType::SKIDMARK_DEFAULT, bloodState, length);
}

CSkidmark* CSkidmarks::FindById(uint32_t id) {
    for (CSkidmark& mark : m_aSkidmarks)
        if (mark.m_nState == 1 && mark.m_id == id)
            return &mark;
    return nullptr;
}

// Try get an unsued slot/forcefully reuse one that isn't visible
CSkidmark* CSkidmarks::GetNextFree(bool forceFree) {
    for (CSkidmark& mark : m_aSkidmarks)
        if (mark.m_nState == 0)
            return &mark;

    if (forceFree) {
        auto mostRecentlyUpdatedMs = std::numeric_limits<uint32>::max();
        CSkidmark* mostRecentlyUpdatedMark{};
        for (CSkidmark& mark : m_aSkidmarks) {
            if (mark.m_bActive)
                continue;
            if (mark.m_timeUpdatedMs > mostRecentlyUpdatedMs)
                continue;
            if (!TheCamera.IsSphereVisible(mark.GetBoundingSphere())) {
                mostRecentlyUpdatedMs = mark.m_timeUpdatedMs;
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
        markById->Update(posn, { dirX, dirY }, length, bloodState);
    } else if (CSkidmark* mark = GetNextFree(true)) {
        mark->Init(index, posn, type, bloodState);
    }
}

// 0x720640
void CSkidmarks::Render() {
    plugin::Call<0x720640>();
}

// 0x720570
void CSkidmarks::Shutdown() {
    RwTextureDestroy(CSkidmarks::m_pTexture);
    CSkidmarks::m_pTexture = nullptr;
}

// 0x7205C0
void CSkidmarks::Update() {
    plugin::Call<0x7205C0>();
}

void CSkidmark::Update(CVector posn, CVector2D dir, float length, bool& bloodState) {
    if ((unsigned)m_type == (unsigned)bloodState) { // TODO: Okaaay?!?
        m_bActive = true;
        if (CTimer::GetTimeInMilliseconds() - m_timeUpdatedMs <= 100) {
            m_vPosn[m_nNumParts] = posn; // Update existing, because of low delta time
        } else {
            if (m_nNumParts >= 15) {
                m_timeUpdatedMs = CTimer::GetTimeInMilliseconds();
                m_nState = 2;
                m_timeLow = CTimer::GetTimeInMilliseconds() + 10'000;
                m_timeHigh = CTimer::GetTimeInMilliseconds() + 20'000;
                bloodState = false;
            } else {
                m_nNumParts++;
                m_vPosn[m_nNumParts] = posn;

                const CVector prevPosn = m_vPosn[m_nNumParts - 1];
                CVector2D dirPrevPart = {
                    prevPosn.x - posn.x,
                    posn.y - prevPosn.y
                };

                if (dirPrevPart.Magnitude() > 0.0f)
                    dirPrevPart.Normalise();
                else
                    dirPrevPart.y = 1.0f;

                dir.Normalise();

                const float absSqMag = 1.0f + fabs(dirPrevPart.y * dir.x + dirPrevPart.x * dir.y);
                m_partDirY[m_nNumParts] = absSqMag * dirPrevPart.y * length / 2.0f;
                m_partDirX[m_nNumParts] = absSqMag * dirPrevPart.x * length / 2.0f;

                if (m_nNumParts == 1) {
                    m_partDirY[0] = m_partDirY[1];
                    m_partDirX[0] = m_partDirX[1];
                }

                if (m_nNumParts > 8)
                    bloodState = false;
            }
        }
    } else {
        m_nState = 2;
        m_timeLow = CTimer::GetTimeInMilliseconds() + 10'000;
        m_timeHigh = CTimer::GetTimeInMilliseconds() + 20'000;
    }
}

void CSkidmark::Init(uint32_t id, CVector posn, eSkidMarkType type, bool& bloodState) {
    m_id = id;
    m_vPosn[0] = posn;
    m_partDirX[0] = 0.0f;
    m_partDirY[0] = 0.0f;
    m_bActive = true;
    m_nState = 1;
    m_timeUpdatedMs = CTimer::GetTimeInMilliseconds() - 1'000;
    m_nNumParts = 0;
    m_type = bloodState ? (eSkidMarkType)3 : type; // TODO Missing enum..
}
