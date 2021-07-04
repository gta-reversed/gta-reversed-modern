#pragma once

#include <cstdint>

class CVehicle;

class CAEAudioUtility {
public:
    static int GetRandomNumberInRange(const int min, const int max);
    static float GetRandomNumberInRange(float a, float b);
    static bool ResolveProbability(float prob);
    static bool GetBankAndSoundFromScriptSlotAudioEvent(int* a1, int* a2, int* a3, int a4);
    static float GetPiecewiseLinear(float x, short dataCount, float (*data)[2]);
    static CVehicle* FindVehicleOfPlayer();
    static float AudioLog10(float p);
    static std::int64_t GetCurrentTimeInMilliseconds();
    static std::uint32_t ConvertFromBytesToMS(std::uint32_t a, std::uint32_t frequency, std::uint16_t frequencyMult);
    static std::uint32_t ConvertFromMSToBytes(std::uint32_t a, std::uint32_t frequency, std::uint16_t frequencyMult);
    static void StaticInitialise();

private:
    static std::int64_t &startTimeMs;
    static float (&m_sfLogLookup)[50][2];

private:
    friend void InjectHooksMain();
    static void InjectHooks();
};
