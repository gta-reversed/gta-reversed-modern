#pragma once

#include <stdint.h>

class CTimeInfo {
public:
    uint8 m_nTimeOn;
    uint8 m_nTimeOff;
    int16 m_nOtherTimeModel = -1;

public:
    static void InjectHooks();

public:
    CTimeInfo* FindOtherTimeModel(const char* modelName);

    int32 GetOtherTimeModel() const { return m_nOtherTimeModel; }

    void SetOtherTimeModel(int16 otherTimeModel) { m_nOtherTimeModel = otherTimeModel; }

    uint8 GetTimeOn() const { return m_nTimeOn; }

    uint8 GetTimeOff() const { return m_nTimeOff; }

    void SetTimes(uint8 timeOn, uint8 timeOff) { m_nTimeOn = timeOn; m_nTimeOff = timeOff; }
};

VALIDATE_SIZE(CTimeInfo, 0x4);
