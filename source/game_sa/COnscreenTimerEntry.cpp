#include "StdInc.h"

#include "COnscreenTimerEntry.h"

// 0x44CB10
void COnscreenTimerEntry::Process() {
    if (m_nVarId == 0)
        return;

    int32& timerPtr  = *CTheScripts::GetPointerToScriptVariable(m_nVarId);
    auto   deltaTime = (int32)CTimer::GetTimeStepInMS();

    switch (m_nTimerDirection) {
    case eTimerDirection::INCREASE:
        timerPtr += deltaTime;
    case eTimerDirection::DECREASE:
        timerPtr -= deltaTime;

        if (timerPtr >= 0) {
            auto seconds = timerPtr / 1000;
            if (seconds < m_nClockBeepCountdownSecs && !TheCamera.m_bWideScreenOn) {
                AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_TIMER_COUNT, 0.0f, 1.0f);
            }
        } else {
            timerPtr = 0;
            m_nVarId = 0;
            m_szDescriptionTextKey[0] = '\0';
            m_bEnabled = false;
        }
    }
    printf("%d\n", timerPtr);
}

// 0x44CA40
void COnscreenTimerEntry::ProcessForDisplayClock() {
    uint32 time = *CTheScripts::GetPointerToScriptVariable(m_nVarId);
    sprintf(
        m_szDisplayedText,
        "%02d:%02d",
        time / 1000 / 60 % 100,
        time / 1000 % 60
    );
}
