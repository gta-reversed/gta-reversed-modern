#include "StdInc.h"

#include "CMotionBlurStreaks.h"

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

// 0x721D90
void CMotionBlurStreaks::Init()
{
    for (CRegisteredMotionBlurStreak& streak : CMotionBlurStreaks::aStreaks) {
        streak.m_nId = 0;
    }
}

// 0x7240C0
void CMotionBlurStreaks::Update()
{
    for (CRegisteredMotionBlurStreak& streak : CMotionBlurStreaks::aStreaks) {
        if (streak.m_nId)
            streak.Update();
    }
}

// 0x7240E0
void CMotionBlurStreaks::Render()
{
    bool bRenderParamsSet = false;
    for (CRegisteredMotionBlurStreak& streak : CMotionBlurStreaks::aStreaks) {
        if (streak.m_nId) {
            if (!bRenderParamsSet) {
                bRenderParamsSet = true;
                RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void*)FALSE);
                RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
                RwRenderStateSet(rwRENDERSTATEFOGENABLE,         (void*)TRUE);
                RwRenderStateSet(rwRENDERSTATEFOGCOLOR,          (void*)CTimeCycle::GetCurrentSkyBottomColor().ToIntARGB());
                RwRenderStateSet(rwRENDERSTATESRCBLEND,          (void*)rwBLENDSRCALPHA);
                RwRenderStateSet(rwRENDERSTATEDESTBLEND,         (void*)rwBLENDINVSRCALPHA);
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     (void*)nullptr);
            }
            streak.Render();
        }
    }

    if (bRenderParamsSet) {
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
    }
}

// 0x721DC0
void CMotionBlurStreaks::RegisterStreak(uint32 id, uint8 red, uint8 green, uint8 blue, uint8 alpha, CVector leftPoint, CVector rightPoint)
{
    for (CRegisteredMotionBlurStreak& streak : CMotionBlurStreaks::aStreaks) {
        if (streak.m_nId != id)
            continue;

        streak.m_color.Set(red, green, blue, alpha);
        streak.m_avecLeftPoints[0] = leftPoint;
        streak.m_avecRightPoints[0] = rightPoint;
        streak.m_acRenderHistory[0] = true;
        return;
    }


    for (CRegisteredMotionBlurStreak& streak : CMotionBlurStreaks::aStreaks) {
        if (streak.m_nId)
            continue;

        streak.m_nId = id;
        streak.m_color.Set(red, green, blue, alpha);
        streak.m_avecLeftPoints[0] = leftPoint;
        streak.m_avecRightPoints[0] = rightPoint;
        streak.m_acRenderHistory[0] = true;
        streak.m_acRenderHistory[1] = false;
        return;
    }
}
