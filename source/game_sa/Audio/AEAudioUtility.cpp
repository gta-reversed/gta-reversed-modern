#include "StdInc.h" // TODO: Remove

#include <chrono>

#include "CAEAudioUtility.h"

int64& CAEAudioUtility::startTimeMs = *reinterpret_cast<int64*>(0xb610f8);
float (&CAEAudioUtility::m_sfLogLookup)[50][2] = *reinterpret_cast<float (*)[50][2]>(0xb61100);

void CAEAudioUtility::InjectHooks() {
    ReversibleHooks::Install("CAEAudioUtility", "GetRandomNumberInRange_int", 0x4d9c10, (int32(*)(const int32, const int32))CAEAudioUtility::GetRandomNumberInRange);
    ReversibleHooks::Install("CAEAudioUtility", "GetRandomNumberInRange_float", 0x4d9c50, (float(*)(float, float))CAEAudioUtility::GetRandomNumberInRange);
    ReversibleHooks::Install("CAEAudioUtility", "ResolveProbability", 0x4d9c80, &CAEAudioUtility::ResolveProbability);
    ReversibleHooks::Install("CAEAudioUtility", "GetPiecewiseLinear", 0x4d9d90, &CAEAudioUtility::GetPiecewiseLinear);
    ReversibleHooks::Install("CAEAudioUtility", "AudioLog10", 0x4d9e50, &CAEAudioUtility::AudioLog10);
    ReversibleHooks::Install("CAEAudioUtility", "ConvertFromBytesToMS", 0x4d9ef0, &CAEAudioUtility::ConvertFromBytesToMS);
    ReversibleHooks::Install("CAEAudioUtility", "ConvertFromMSToBytes", 0x4d9f40, &CAEAudioUtility::ConvertFromMSToBytes);
    // ReversibleHooks::Install("CAEAudioUtility", "GetBankAndSoundFromScriptSlotAudioEvent", 0x4D9CC0, GetBankAndSoundFromScriptSlotAudioEvent);
    // ReversibleHooks::Install("CAEAudioUtility", "FindVehicleOfPlayer", 0x4D9E10, FindVehicleOfPlayer);

    // Those 2 change logic of the functions, and shouldn't be toggled on/off
    HookInstall(0x4d9e80, &CAEAudioUtility::GetCurrentTimeInMilliseconds);
    HookInstall(0x5b97f0, &CAEAudioUtility::StaticInitialise);
}

// 0x4d9c10
int32 CAEAudioUtility::GetRandomNumberInRange(const int32 min, const int32 max) {
    // This and CGeneral differs in that this function returns a number [min, max + 1], while
    // the other [min, max]. To solve this we do `max + 1`
    return CGeneral::GetRandomNumberInRange(min, max + 1);
}

// 0x4d9c50
float CAEAudioUtility::GetRandomNumberInRange(float a, float b) {
    return CGeneral::GetRandomNumberInRange(a, b);
}

// 0x4d9c80
bool CAEAudioUtility::ResolveProbability(float p) {
    return p >= 1.0f || (rand() * RAND_MAX_FLOAT_RECIPROCAL) < p;
}

// 0x4d9d90
float CAEAudioUtility::GetPiecewiseLinear(float x, int16 dataCount, float (*data)[2]) {
    if (x >= data[dataCount - 1][0])
        return data[dataCount - 1][1];

    if (x <= data[0][0])
        return data[0][1];

    int32 i = 0;
    for (; i < dataCount; i++) {
        if (data[i][0] >= x)
            break;
    }
    // Perform linear interpolation
    float t = (x - data[i - 1][0]) / (data[i][0] - data[i - 1][0]);
    return t * (data[i][1] - data[i - 1][1]) + data[i - 1][1];
}

// 0x4d9e50
float CAEAudioUtility::AudioLog10(float p) {
    return 0.00001f <= p ? log10f(p) : -5.0f;
}

// 0x4d9e80
int64 CAEAudioUtility::GetCurrentTimeInMilliseconds() {
    auto nowMs = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(nowMs.time_since_epoch());
    return static_cast<int64>(value.count());
}

// 0x4d9ef0
uint32 CAEAudioUtility::ConvertFromBytesToMS(uint32 a, uint32 frequency, uint16 frequencyMult) {
    return static_cast<uint32>(floorf(a / (frequency * frequencyMult / 500.0f)));
}

// 0x4d9f40
uint32 CAEAudioUtility::ConvertFromMSToBytes(uint32 a, uint32 frequency, uint16 frequencyMult) {
    const auto value = static_cast<uint32>(floorf(a * frequency * frequencyMult / 500.0f));
    return value + value % (2 * frequencyMult);
}

// 0x5B97F0
void CAEAudioUtility::StaticInitialise() {
    constexpr size_t LOOKUP_SIZE = sizeof(CAEAudioUtility::m_sfLogLookup) / sizeof(float) / 2;

    m_sfLogLookup[0][0] = 0.0f;
    m_sfLogLookup[0][1] = -100.0f;
    m_sfLogLookup[1][0] = 0.00001f;

    for (size_t i = 2; i < LOOKUP_SIZE; i++) {
        float v = 10.0f / powf(1.2f, static_cast<float>(LOOKUP_SIZE - i - 1));
        m_sfLogLookup[i][0] = v;
        m_sfLogLookup[1][1] = log10f(v);
    }

    startTimeMs = GetCurrentTimeInMilliseconds();
}

// 0x4D9CC0
bool CAEAudioUtility::GetBankAndSoundFromScriptSlotAudioEvent(int32* a1, int32* a2, int32* a3, int32 a4) {
    return plugin::CallAndReturn<bool, 0x4D9CC0, int32*, int32*, int32*, int32>(a1, a2, a3, a4);
}

// 0x4D9E10
CVehicle* CAEAudioUtility::FindVehicleOfPlayer() {
    return plugin::CallAndReturn<CVehicle*, 0x4D9E10>();
}
