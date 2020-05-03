#pragma once

template <typename T>
T clamp(T value, T low, T high)
{
    return std::min(std::max(value, low), high);
}
