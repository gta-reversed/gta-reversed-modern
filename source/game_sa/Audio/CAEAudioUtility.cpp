#include "StdInc.h" // TODO: Remove

#include <chrono>
#include <cmath>
#include <cstdlib>

#include "CAEAudioUtility.h"

constexpr float RAND_MAX_RECIPROCAL = 1.0 / double(RAND_MAX);

std::int64_t &CAEAudioUtility::startTimeMs = *reinterpret_cast<std::int64_t *> (0xb610f8);
float (&CAEAudioUtility::m_sfLogLookup)[50][2] = *reinterpret_cast<float(*)[50][2]> (0xb61100);

std::int32_t CAEAudioUtility::GetRandomNumberInRange(std::int32_t a, std::int32_t b)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<std::int32_t, 0x4d9c10, std::int32_t, std::int32_t>(a, b);
#else
    // TODO: Use better RNG
    return a + std::int32_t(rand() * (b - a + 1) * RAND_MAX_RECIPROCAL);
#endif
}

float CAEAudioUtility::GetRandomNumberInRange(float a, float b)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<float, 0x4d9c50, float, float>(a, b);
#else
    // TODO: Use better RNG
    return a + rand() * (b - a) * RAND_MAX_RECIPROCAL;
#endif
}

bool CAEAudioUtility::ResolveProbability(float p)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallAndReturn<bool, 0x4d9c80, float>(p);
#else
    return p >= 1.0f || (rand() * RAND_MAX_RECIPROCAL) < p;
#endif
}

float CAEAudioUtility::GetPiecewiseLinear(float x, short dataCount, float (*data)[2])
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<float, 0x4d9d90, float, short, float (*)[2]>(x, dataCount, data);
#else
    if (x <= data[0][0])
        return data[0][1];
    else if (x >= data[dataCount - 1][0])
        return data[dataCount - 1][1];
    else
    {
        int i = -1;

        for (int j = 0; j < dataCount; j++)
        {
            if (x < data[j][0])
            {
                i = j - 1;
                break;
            }
        }

        assert(i >= 0);

        // Perform linear interpolation
        float t = (x - data[i][0]) / (data[i + 1][0] - data[i][0]);
        return data[i][1] * (1.0f - t) + data[i + 1][1] * t;
    }
#endif
}

float CAEAudioUtility::AudioLog10(float p)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<float, 0x4d9e50, float>(p);
#else
    return 0.00001f <= p ? log10f(p) : -5.0f;
#endif
}

std::int64_t CAEAudioUtility::GetCurrentTimeInMilliseconds()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<std::int64_t, 0x4d9e80>();
#else
    auto nowMs = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(nowMs.time_since_epoch());
    return static_cast<std::int64_t> (value.count());
#endif
}

std::uint32_t CAEAudioUtility::ConvertFromBytesToMS(std::uint32_t a, std::uint32_t b, std::uint16_t c)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<std::uint32_t, 0x4d9ef0, std::uint32_t, std::uint32_t, std::uint16_t>(a, b, c);
#else
    return (std::uint32_t) floorf(a / (b * c / 500.0f));
#endif
}

std::uint32_t CAEAudioUtility::ConvertFromMSToBytes(std::uint32_t a, std::uint32_t b, std::uint16_t c)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<std::uint32_t, 0x4d9f40, std::uint32_t, std::uint32_t, std::uint16_t>(a, b, c);
#else
    std::uint32_t value = (std::uint32_t) floorf(a * b * c / 500.0f);
    return value + value % (2 * c);
#endif
}

void CAEAudioUtility::StaticInitialise(void)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x5b97f0>();
#else
    constexpr size_t LOOKUP_SIZE = sizeof(CAEAudioUtility::m_sfLogLookup) / sizeof(float) / 2;

    m_sfLogLookup[0][0] = 0.0f;
    m_sfLogLookup[0][1] = -100.0f;
    m_sfLogLookup[1][0] = 0.00001f;

    for (size_t i = 2; i < LOOKUP_SIZE; i++)
    {
        float v = 10.0f / powf(1.2f, float(LOOKUP_SIZE - i - 1));
        m_sfLogLookup[i][0] = v;
        m_sfLogLookup[1][1] = log10f(v);
    }

    startTimeMs = GetCurrentTimeInMilliseconds();
#endif
}

void CAEAudioUtility::InjectHooks()
{
#ifndef USE_DEFAULT_FUNCTIONS
    HookInstall(0x4d9c10, (std::int32_t(*)(std::int32_t, std::int32_t)) CAEAudioUtility::GetRandomNumberInRange);
    HookInstall(0x4d9c50, (float(*)(float, float)) CAEAudioUtility::GetRandomNumberInRange);
    HookInstall(0x4d9c80, &CAEAudioUtility::ResolveProbability);
    HookInstall(0x4d9d90, &CAEAudioUtility::GetPiecewiseLinear);
    HookInstall(0x4d9e50, &CAEAudioUtility::AudioLog10);
    HookInstall(0x4d9e80, &CAEAudioUtility::GetCurrentTimeInMilliseconds);
    HookInstall(0x4d9ef0, &CAEAudioUtility::ConvertFromBytesToMS);
    HookInstall(0x4d9f40, &CAEAudioUtility::ConvertFromMSToBytes);
    HookInstall(0x5b97f0, &CAEAudioUtility::StaticInitialise);
#endif
}
