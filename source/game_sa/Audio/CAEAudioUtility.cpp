#include "StdInc.h" // TODO: Remove

#include <chrono>
#include <cmath>
#include <cstdlib>

#include "CAEAudioUtility.h"

constexpr float RAND_MAX_RECIPROCAL = 1.0f / static_cast<float>(RAND_MAX);

std::int64_t &CAEAudioUtility::startTimeMs = *reinterpret_cast<std::int64_t *> (0xb610f8);
float (&CAEAudioUtility::m_sfLogLookup)[50][2] = *reinterpret_cast<float(*)[50][2]> (0xb61100);

void CAEAudioUtility::InjectHooks()
{
    
    ReversibleHooks::Install("CAEAudioUtility", "GetRandomNumberInRange_int", 0x4d9c10, (std::int32_t(*)(std::int32_t, std::int32_t)) CAEAudioUtility::GetRandomNumberInRange);
    ReversibleHooks::Install("CAEAudioUtility", "GetRandomNumberInRange_float", 0x4d9c50, (float(*)(float, float)) CAEAudioUtility::GetRandomNumberInRange);
    ReversibleHooks::Install("CAEAudioUtility", "ResolveProbability", 0x4d9c80, &CAEAudioUtility::ResolveProbability);
    ReversibleHooks::Install("CAEAudioUtility", "GetPiecewiseLinear", 0x4d9d90, &CAEAudioUtility::GetPiecewiseLinear);
    ReversibleHooks::Install("CAEAudioUtility", "AudioLog10", 0x4d9e50, &CAEAudioUtility::AudioLog10);
    ReversibleHooks::Install("CAEAudioUtility", "ConvertFromBytesToMS", 0x4d9ef0, &CAEAudioUtility::ConvertFromBytesToMS);
    ReversibleHooks::Install("CAEAudioUtility", "ConvertFromMSToBytes", 0x4d9f40, &CAEAudioUtility::ConvertFromMSToBytes);

    // Those 2 change logic of the functions, and shouldn't be toggled on/off
    HookInstall(0x4d9e80, &CAEAudioUtility::GetCurrentTimeInMilliseconds);
    HookInstall(0x5b97f0, &CAEAudioUtility::StaticInitialise);
}

// Exactly the same as CGeneral::GetRandomNumberInRange
std::int32_t CAEAudioUtility::GetRandomNumberInRange(std::int32_t a, std::int32_t b)
{
    // TODO: Use better RNG
    return a + static_cast<std::int32_t>(rand() * RAND_MAX_RECIPROCAL * (b - a + 1) );
}

// Exactly the same as CGeneral::GetRandomNumberInRange
float CAEAudioUtility::GetRandomNumberInRange(float a, float b)
{
    // TODO: Use better RNG
    return a + (b - a) * rand() * RAND_MAX_RECIPROCAL;
}

bool CAEAudioUtility::ResolveProbability(float p)
{
    return p >= 1.0f || (rand() * RAND_MAX_RECIPROCAL) < p;
}

float CAEAudioUtility::GetPiecewiseLinear(float x, short dataCount, float (*data)[2])
{
    if (x >= data[dataCount - 1][0])
        return data[dataCount - 1][1];

    if (x <= data[0][0])
        return data[0][1];

    int i = 0;
    for (; i < dataCount; i++)
    {
        if (data[i][0] >= x)
            break;
    }
    // Perform linear interpolation
    float t = (x - data[i - 1][0]) / (data[i][0] - data[i - 1][0]);
    return t * (data[i][1] - data[i - 1][1]) + data[i - 1][1];
}

float CAEAudioUtility::AudioLog10(float p)
{
    return 0.00001f <= p ? log10f(p) : -5.0f;
}

std::int64_t CAEAudioUtility::GetCurrentTimeInMilliseconds()
{
    auto nowMs = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(nowMs.time_since_epoch());
    return static_cast<std::int64_t> (value.count());
}

std::uint32_t CAEAudioUtility::ConvertFromBytesToMS(std::uint32_t a, std::uint32_t frequency, std::uint16_t frequencyMult)
{
    return static_cast<std::uint32_t>(floorf(a / (frequency * frequencyMult / 500.0f)));
}

std::uint32_t CAEAudioUtility::ConvertFromMSToBytes(std::uint32_t a, std::uint32_t frequency, std::uint16_t frequencyMult)
{
    const auto value = static_cast<uint32_t>(floorf(a * frequency * frequencyMult / 500.0f));
    return value + value % (2 * frequencyMult);
}

void CAEAudioUtility::StaticInitialise(void)
{
    constexpr size_t LOOKUP_SIZE = sizeof(CAEAudioUtility::m_sfLogLookup) / sizeof(float) / 2;

    m_sfLogLookup[0][0] = 0.0f;
    m_sfLogLookup[0][1] = -100.0f;
    m_sfLogLookup[1][0] = 0.00001f;

    for (size_t i = 2; i < LOOKUP_SIZE; i++)
    {
        float v = 10.0f / powf(1.2f, static_cast<float>(LOOKUP_SIZE - i - 1));
        m_sfLogLookup[i][0] = v;
        m_sfLogLookup[1][1] = log10f(v);
    }

    startTimeMs = GetCurrentTimeInMilliseconds();
}
