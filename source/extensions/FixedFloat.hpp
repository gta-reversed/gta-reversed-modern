#pragma once

template<typename T, float CompressValue> requires std::is_integral_v<T>
class FixedFloat {
    T value{};

public:
    constexpr FixedFloat() = default;
    constexpr FixedFloat(float X) : value(X * CompressValue) {}
    explicit constexpr FixedFloat(T X) : value(X) {}

    constexpr operator float() const {
        return value / CompressValue;
    }
};
