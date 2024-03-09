#pragma once

#include <type_traits>
#include <cstdint>

namespace notsa {
//! Store enums (of type `Enum`) in a given integral type.
//! Useful in cases where the class originally used a width
//! different to the enums underlaying type.
//! WEnum just sounded like a cool name... Venom.. WEnum, idk
template<typename Enum, typename StoreAs>
    requires(std::is_integral_v<StoreAs>)
struct WEnum {
    StoreAs m_Value;

    //! Implicitly convert from the enum value
    WEnum(Enum e = {}) : m_Value{static_cast<StoreAs>(e)} { }

    //! Implicitly convert from another WEnum for the same enum
    template<typename Y>
    WEnum(WEnum<Enum, Y> other) : WEnum{static_cast<Enum>(other)} { }

    //! Implicitly convert back to the underlaying `Enum` type
    operator Enum() const { return static_cast<Enum>(m_Value); }

    //! Use this in cases you want to cast to an int (for cout or something)
    Enum get() const { return static_cast<Enum>(m_Value); }
};

template<typename E>
using WEnumU8 = WEnum<E, std::uint8_t>;
template<typename E>
using WEnumS8 = WEnum<E, std::int8_t>;

template<typename E>
using WEnumU16 = WEnum<E, std::uint16_t>;
template<typename E>
using WEnumS16 = WEnum<E, std::int16_t>;

template<typename E>
using WEnumU32 = WEnum<E, std::uint32_t>;
template<typename E>
using WEnumS32 = WEnum<E, std::int32_t>;
};
