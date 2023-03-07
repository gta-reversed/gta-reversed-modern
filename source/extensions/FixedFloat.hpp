#pragma once

//! Fixed point number (With implicit conversion to float)
template<typename T, float CompressValue>
    requires std::is_integral_v<T>
class FixedFloat {
    T value{};

public:
    constexpr FixedFloat() = default;
    constexpr FixedFloat(float X) : value(static_cast<T>(X * CompressValue)) {}
    explicit constexpr FixedFloat(T X) : value(X) {}

    constexpr operator float() const {
        return static_cast<float>(value) / CompressValue;
    }
};
