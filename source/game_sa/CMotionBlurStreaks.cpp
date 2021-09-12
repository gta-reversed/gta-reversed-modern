#include "StdInc.h"

CRegisteredMotionBlurStreak(&CMotionBlurStreaks::aStreaks)[MAX_NUM_MOTIONBLUR_STREAKS] = *(CRegisteredMotionBlurStreak(*)[MAX_NUM_MOTIONBLUR_STREAKS])0xC7CA08;
RxObjSpace3DVertex(&CMotionBlurStreaks::aStreakVertices)[NUM_STREAK_VERTICES] = *(RxObjSpace3DVertex(*)[NUM_STREAK_VERTICES])0xC7C628;
RxVertexIndex(&CMotionBlurStreaks::aIndices)[NUM_STREAK_INDICES] = *(RxVertexIndex(*)[NUM_STREAK_INDICES])0xC7C6B8;

void CMotionBlurStreaks::InjectHooks()
{
    ReversibleHooks::Install("CMotionBlurStreaks", "Init", 0x721D90, &CMotionBlurStreaks::Init);
    ReversibleHooks::Install("CMotionBlurStreaks", "Update", 0x7240C0, &CMotionBlurStreaks::Update);
    ReversibleHooks::Install("CMotionBlurStreaks", "Render", 0x7240E0, &CMotionBlurStreaks::Render);
    ReversibleHooks::Install("CMotionBlurStreaks", "RegisterStreak", 0x721DC0, &CMotionBlurStreaks::RegisterStreak);
}

void CMotionBlurStreaks::Init()
{
    for (auto& pStreak : CMotionBlurStreaks::aStreaks)
        pStreak.m_nId = 0;
}

void CMotionBlurStreaks::Update()
{
    for (auto& pStreak : CMotionBlurStreaks::aStreaks) {
        if (pStreak.m_nId)
            pStreak.Update();
    }
}

void CMotionBlurStreaks::Render()
{
    bool bRenderParamsSet = false;
    for (auto& pStreak : CMotionBlurStreaks::aStreaks) {
        if (pStreak.m_nId) {
            if (!bRenderParamsSet) {
                bRenderParamsSet = true;
                RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
                RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
                RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);
                auto rwColor = RWRGBALONG(CTimeCycle::m_CurrentColours.m_nSkyBottomRed,
                                          CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
                                          CTimeCycle::m_CurrentColours.m_nSkyBottomBlue,
                                          255);
                RwRenderStateSet(rwRENDERSTATEFOGCOLOR, (void*)rwColor);
                RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
                RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
            }
            pStreak.Render();
        }
    }

    if (bRenderParamsSet) {
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
    }
}

void CMotionBlurStreaks::RegisterStreak(uint32 id, uint8 red, uint8 green, uint8 blue, uint8 alpha, CVector leftPoint, CVector rightPoint)
{
    for (auto& pStreak : CMotionBlurStreaks::aStreaks) {
        if (pStreak.m_nId != id)
            continue;

        pStreak.m_color.Set(red, green, blue, alpha);
        pStreak.m_avecLeftPoints[0] = leftPoint;
        pStreak.m_avecRightPoints[0] = rightPoint;
        pStreak.m_acRenderHistory[0] = true;
        return;
    }


    for (auto& pStreak : CMotionBlurStreaks::aStreaks) {
        if (pStreak.m_nId)
            continue;

        pStreak.m_nId = id;
        pStreak.m_color.Set(red, green, blue, alpha);
        pStreak.m_avecLeftPoints[0] = leftPoint;
        pStreak.m_avecRightPoints[0] = rightPoint;
        pStreak.m_acRenderHistory[0] = true;
        pStreak.m_acRenderHistory[1] = false;
        return;
    }
}
