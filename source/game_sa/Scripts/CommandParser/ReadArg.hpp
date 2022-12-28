#pragma once

#include <type_traits>
#include <assert.h>
#include <app_debug.h>
#include "RunningScript.h"
#include "TheScripts.h"
#include "Utility.hpp"
#include "Rect.h"

namespace notsa {
namespace script {
namespace detail {
//! Base exception for argument reader stuff
class ArgReaderException : public std::exception {
    /* nothing */
};

//! Exception that can be ignored by the command parser
class ArgReaderIgnorableException : public ArgReaderException {
    /* nothing */
};

//! Exception for when a script thing is invalid (dead) - This is completely normal
class ArgReaderInvalidScriptThingException : public ArgReaderIgnorableException {
    /* nothing */
};
};

//! Check if `Derived` is derived from `Base` but isn't `Base`
template<typename Base, typename Derived>
constexpr auto is_derived_from_but_not_v = std::is_base_of_v<Base, Derived> && !std::is_same_v<Base, Derived>;

auto ReadArrayInfo(CRunningScript* S) {
    uint16 offset{};
    int32 idx{};
    S->ReadArrayInformation(true, &offset, &idx);
    return std::make_tuple(offset, idx);
}


template<typename T, typename Y = T>
Y Read(CRunningScript* S);

/*!
* @notsa
* @brief Read one POD parameter's value from the script at the current IP and increment the IP.
* @return The value read casted to `T`. The value will be read correctly,
*         even if the original type was wider or narrower then the
*         requested one (ex.: originally it was `int8`, but `T = int32`)
*/
template<typename T>
T Read(CRunningScript* S)
    requires(!std::is_reference_v<T> && (std::is_arithmetic_v<T> || std::is_enum_v<T>))
{
    auto& ip = S->m_IP;

    switch (const auto type = S->ReadAtIPAs<eScriptParameterType>()) {
    case SCRIPT_PARAM_STATIC_INT_32BITS:
        return static_cast<T>(S->ReadAtIPAs<int32>());
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        return *reinterpret_cast<T*>(&CTheScripts::ScriptSpace[S->ReadAtIPAs<int16>()]);
    case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
        return *reinterpret_cast<T*>(S->GetPointerToLocalVariable(S->ReadAtIPAs<int16>()));
    case SCRIPT_PARAM_STATIC_INT_8BITS:
        return static_cast<T>(S->ReadAtIPAs<int8>());
    case SCRIPT_PARAM_STATIC_INT_16BITS:
        return static_cast<T>(S->ReadAtIPAs<int16>());
    case SCRIPT_PARAM_STATIC_FLOAT: {
        if constexpr (!std::is_floating_point_v<T>) {
            DebugBreak(); // Possibly unintended truncation of `float` to integeral type! Check your call stack and change the function argument type to a float.
        }
        return static_cast<T>(S->ReadAtIPAs<float>());
    }
    case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY: {
        const auto [offset, idx] = ReadArrayInfo(S);
        return *reinterpret_cast<T*>(&CTheScripts::ScriptSpace[offset + sizeof(tScriptParam) * idx]);
    }
    case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY: {
        const auto [offset, idx] = ReadArrayInfo(S);
        return *reinterpret_cast<T*>(S->GetPointerToLocalArrayElement(offset, idx, 1));
    }
    default:
        NOTSA_UNREACHABLE("Unknown type: {}", (int32)(type));
    }
}

/*!
* @brief Read variable as T&. Used for writing to local/global variables.
*/
template <typename T, typename Y = std::remove_reference_t<T>>
    requires std::is_reference_v<T> && std::is_arithmetic_v<Y>
T Read(CRunningScript* S) {
    auto& ip = S->m_IP;

    switch (const auto type = S->ReadAtIPAs<eScriptParameterType>()) {
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        return *reinterpret_cast<Y*>(&CTheScripts::ScriptSpace[S->ReadAtIPAs<int16>()]);
    case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
        return *reinterpret_cast<Y*>(S->GetPointerToLocalVariable(S->ReadAtIPAs<int16>()));
    case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY: {
        const auto [offset, idx] = ReadArrayInfo(S);
        return *reinterpret_cast<Y*>(&CTheScripts::ScriptSpace[offset + sizeof(tScriptParam) * idx]);
    }
    case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY: {
        const auto [offset, idx] = ReadArrayInfo(S);
        return *reinterpret_cast<Y*>(S->GetPointerToLocalArrayElement(offset, idx, 1));
    }
    default:
        NOTSA_UNREACHABLE("Bad reference value read: {}", (int32)(type));
    }
}

/*!
* @brief  Special overload for stuff in pools.
* @return Always a reference to the object `T`
*/
template<typename T>
concept PooledType = requires {
    detail::PoolOf<std::remove_reference_t<T>>();
};

template<PooledType RefT, typename T = std::remove_reference_t<RefT>>
    requires std::is_class_v<T> // Make sure RefT is something like `CVehicle&` and not some abnomination like `CVehicle*&` (or `CVehicle` in which case a copy would be made)
T& Read(CRunningScript* S) {
    T& obj = *static_cast<T*>(detail::PoolOf<T>().GetAtRef(Read<int32>(S)));

    // Special debug type checks
    if constexpr (is_derived_from_but_not_v<CVehicle, T>) {
        assert(T::Type == obj.m_nVehicleType);
    } else if constexpr (is_derived_from_but_not_v<CTask, T>) {
        assert(T::Type == obj.GetTaskType());
    } // TODO: Eventually add this for `CEvent` too

    return obj;
}

/*!
* Allow taking the current script as a parameter.
* This isn't an actual script parameter, so reading
* it doesn't increase the IP.
*/
template<>
CRunningScript& Read<CRunningScript&>(CRunningScript* S) {
    return *S;
}

// Same as above, but returns a pointer instead
template<>
CRunningScript* Read<CRunningScript*>(CRunningScript* S) {
    return S;
}

template<>
CVector Read<CVector>(CRunningScript* S) {
    return { Read<float>(S), Read<float>(S), Read<float>(S) };
}

template<>
CVector2D Read<CVector2D>(CRunningScript* S) {
    return { Read<float>(S), Read<float>(S) };
}

template<>
CRect Read<CRect>(CRunningScript* S) {
    return { Read<CVector2D>(S), Read<CVector2D>(S) };
}
template<>
CPlayerInfo& Read<CPlayerInfo&>(CRunningScript* S) {
    return FindPlayerInfo(Read<int32>(S));
}

template<>
CPlayerPed& Read<CPlayerPed&>(CRunningScript* S) {
    return *FindPlayerPed(Read<int32>(S));
}

template<>
std::string_view Read<std::string_view>(CRunningScript* S) {
    auto& IP = S->m_IP;

    const auto FromScriptSpace = [](const auto offset) -> std::string_view {
        return { (const char*)&CTheScripts::ScriptSpace[offset] };
    };

    const auto FromGlobalArray = [&](uint8 elemsz) -> std::string_view {
        const auto [idx, offset] = ReadArrayInfo(S);
        return FromScriptSpace(elemsz * idx + offset);
    };

    const auto FromLocalArray = [&](uint8 elemsz) -> std::string_view {
        const auto [idx, offset] = ReadArrayInfo(S);
        return { (const char*)S->GetPointerToLocalArrayElement(offset, idx, elemsz) };
    };

    const auto FromStaticString = [&](size_t buffsz) -> std::string_view {
        IP += buffsz;
        return { (const char*)(IP - buffsz) };
    };

    const auto type = (eScriptParameterType)S->ReadAtIPAs<int8>(); // As a variable so can inspect it in debugger
    switch (type) {
    case SCRIPT_PARAM_LOCAL_LONG_STRING_VARIABLE:
    case SCRIPT_PARAM_STATIC_SHORT_STRING:
        return FromStaticString(SHORT_STRING_SIZE);
    case SCRIPT_PARAM_STATIC_LONG_STRING:
    case SCRIPT_PARAM_GLOBAL_LONG_STRING_VARIABLE:
        return FromStaticString(LONG_STRING_SIZE);
    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_VARIABLE:
        return FromScriptSpace(S->ReadAtIPAs<int16>());
    case SCRIPT_PARAM_LOCAL_SHORT_STRING_VARIABLE:
        return { (const char*)S->GetPointerToLocalVariable(S->ReadAtIPAs<int16>()) };
    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY:
        return FromGlobalArray(SHORT_STRING_SIZE);
    case SCRIPT_PARAM_GLOBAL_LONG_STRING_ARRAY:
        return FromGlobalArray(LONG_STRING_SIZE);
    case SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY:
        return FromLocalArray(2);
    case SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY:
        return FromLocalArray(4);
    case SCRIPT_PARAM_STATIC_PASCAL_STRING: {
        const auto sz = S->ReadAtIPAs<int8>(); // sign extension. max size = 127, not 255
        assert(sz >= 0);
        IP += sz;
        return { (const char*)(IP - sz), (size_t)(sz) };
    }
    default:
        NOTSA_UNREACHABLE();
    }
}

//! Read a `const char*` - This is hacky, but we know all strings are null-terminated, so it's fine
template<>
const char* Read<const char*>(CRunningScript* S) {
    const auto str = Read<std::string_view>(S);
    assert(str.data()[str.size()] == 0); // Check if str is 0 terminated - Not using `str[]` here as it would assert.
    return str.data();
}

//
// SCRIPT THING
//

namespace detail {
struct ScriptThingInfo {
    uint16 arrayIdx; // Index in the array of script things
    uint16 id;       // Array of the script thing 
};

auto ReadScriptThingInfo(CRunningScript* S) {
    const auto info = Read<uint32>(S);
    if (info == (uint32)(-1)) {
        throw ::notsa::script::detail::ArgReaderInvalidScriptThingException{};
    }
    return detail::ScriptThingInfo{ (uint16)(HIWORD(info)), (uint16)(LOWORD(info)) };
}

template<typename T>
auto GetScriptThingAtIndex(uint32 index);

template<>
auto GetScriptThingAtIndex<tScriptSphere>(uint32 index) {
    return &CTheScripts::ScriptSphereArray[index];
}

template<>
auto GetScriptThingAtIndex<tScriptEffectSystem>(uint32 index) {
    return &CTheScripts::ScriptEffectSystemArray[index];
}
};

//! Generic implementation of reading a script thing
template<typename T>
    requires (detail::GetScriptThingAtIndex<T>())
T Read(CRunningScript* S) {
    const auto [index, id] = detail::ReadScriptThingInfo(S);
    T* thing = detail::GetScriptThingAtIndex<T>(index);
    if (!thing || thing->GetId() != id) {
        throw detail::ArgReaderInvalidScriptThingException{};
    }
    return *thing;
}

}; // namespace script
}; // namespace notsa
