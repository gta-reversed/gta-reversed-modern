#pragma once

#include <cstdint>

class CAEAudioUtility
{
public:
    static std::int32_t GetRandomNumberInRange(std::int32_t a, std::int32_t b);
    static float GetRandomNumberInRange(float a, float b);
    static bool ResolveProbability(float prob);
    // TODO: CAEAudioUtility::GetBankAndSoundFromScriptSlotAudioEvent(int *,int *,int *,int) @ 0x4D9CC0
    static float GetPiecewiseLinear(float x, short dataCount, float (*data)[2]);
    // TODO: CAEAudioUtility::FindVehicleOfPlayer(void) @ 0x4D9E10
    static float AudioLog10(float p);
    static std::int64_t CAEAudioUtility::GetCurrentTimeInMilliseconds();
    static std::uint32_t CAEAudioUtility::ConvertFromBytesToMS(std::uint32_t a, std::uint32_t frequency, std::uint16_t frequencyMult);
    static std::uint32_t CAEAudioUtility::ConvertFromMSToBytes(std::uint32_t a, std::uint32_t frequency, std::uint16_t frequencyMult);
    static void CAEAudioUtility::StaticInitialise();

private:
    static std::int64_t &startTimeMs;
    static float (&m_sfLogLookup)[50][2];

private:
    friend void InjectHooksMain();
    static void InjectHooks();
};
