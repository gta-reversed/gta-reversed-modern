#pragma once

//! Fixed point number (With implicit conversion to float)
template<std::integral T, float CompressValue>
class FixedFloat {
    T value{};

public:
    constexpr FixedFloat() = default;
    constexpr FixedFloat(float v) : value(static_cast<T>(v * CompressValue)) {}
    template<std::integral Y>
    constexpr FixedFloat(Y x) : value(x) {}

    constexpr operator float() const { return static_cast<float>(value) / CompressValue; }
};
