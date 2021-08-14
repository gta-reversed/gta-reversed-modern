#pragma once

#include <stdint.h>

class CTimeInfo {
public:
    uint8_t m_nTimeOn;
    uint8_t m_nTimeOff;
    int16_t m_nOtherTimeModel = -1;

public:
    static void InjectHooks();

public:
    CTimeInfo* FindOtherTimeModel(const char* modelName);

    int GetOtherTimeModel() const { return m_nOtherTimeModel; }

    void SetOtherTimeModel(int16_t otherTimeModel) { m_nOtherTimeModel = otherTimeModel; }

    uint8_t GetTimeOn() const { return m_nTimeOn; }

    uint8_t GetTimeOff() const { return m_nTimeOff; }

    void SetTimes(uint8_t timeOn, uint8_t timeOff) { m_nTimeOn = timeOn; m_nTimeOff = timeOff; }
};

VALIDATE_SIZE(CTimeInfo, 0x4);
