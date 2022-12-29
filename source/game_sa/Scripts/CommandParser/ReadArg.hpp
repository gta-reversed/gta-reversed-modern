#pragma once

#include <type_traits>
#include <assert.h>

#include "RunningScript.h"
#include "app_debug.h"
#include "World.h"
#include "TheScripts.h"
#include "Utility.hpp"
#include "Rect.h"

namespace notsa {
namespace script {
// Script thing stuff
namespace detail {
template<typename T>
inline auto GetScriptThing(uint32 index) -> T& = delete;

template<>
inline auto GetScriptThing(uint32 index) -> tScriptSphere& {
    return CTheScripts::ScriptSphereArray[index];
}

template<>
inline auto GetScriptThing(uint32 index) -> tScriptEffectSystem& {
    return CTheScripts::ScriptEffectSystemArray[index];
}

template<typename T>
concept ScriptThing = requires(uint32 index) {
    GetScriptThing<std::decay_t<T>>(index);
};

template<typename T>
inline uint16 GetScriptThingID(T& thing) {
    return thing.GetId();
}
};

namespace detail {
inline auto ReadArrayInfo(CRunningScript* S) {
    uint16 offset{};
    int32 idx{};
    S->ReadArrayInformation(true, &offset, &idx);
    return std::make_tuple(offset, idx);
}

template<typename T>
concept PooledType =
    requires { detail::PoolOf<T>(); };
};

namespace detail {
//! Safely cast one arithmetic type to another (Checks for under/overflow in debug mode only), then casts to `T`
template<typename T, typename F>
inline T safe_arithmetic_cast(F value) {
#ifdef NOTSA_DEBUG
    if constexpr (std::numeric_limits<F>::lowest() < std::numeric_limits<T>::lowest()) { // Underflow
        assert(value >= static_cast<F>(std::numeric_limits<T>::lowest())); 
    }
    if constexpr (std::numeric_limits<F>::max() >= std::numeric_limits<T>::max()) { // Overflow
        assert(value <= static_cast<F>(std::numeric_limits<T>::max())); 
    }
#endif
    return static_cast<T>(value); // In release mode just a simple, regular cast
}

//! Check if `Derived` is derived from `Base` but isn't `Base`
template<typename Base, typename Derived>
constexpr auto is_derived_from_but_not_v = std::is_base_of_v<Base, Derived> && !std::is_same_v<Base, Derived>;
};

//! Read a value (Possibly from script => increases IP, or return a value (w/o increasing IP)
template<typename T>
inline T Read(CRunningScript* S) {
    using Y = std::remove_pointer_t<std::remove_cvref_t<T>>;

    // First of all, deal with references
    // References are a way to express that a valud (non-null) value must be present
    // While simple pointers are a way to express that "it's okay if it's null, I can handle it".
    // This check here also means that all other branches must either return by-value or a pointer (not a refernce)
    if constexpr (std::is_reference_v<T>) {
        const auto ptr = Read<std::remove_reference_t<T>*>(S);
        assert(ptr);
        return *ptr;
    } else if constexpr (std::is_same_v<Y, CVector>) {
        return { Read<float>(S), Read<float>(S), Read<float>(S) };
    } else if constexpr (std::is_same_v<Y, CVector2D>) {
        return { Read<float>(S), Read<float>(S) };
    } else if constexpr (std::is_same_v<Y, CRect>) {
        return { Read<CVector2D>(S), Read<CVector2D>(S) };
    } else if constexpr (std::is_same_v<Y, std::string_view>) { 
        auto& IP = S->m_IP;

        const auto FromScriptSpace = [](const auto offset) -> std::string_view {
            return { (const char*)&CTheScripts::ScriptSpace[offset] };
        };

        const auto FromGlobalArray = [&](uint8 elemsz) -> std::string_view {
            const auto [idx, offset] = detail::ReadArrayInfo(S);
            return FromScriptSpace(elemsz * idx + offset);
        };

        const auto FromLocalArray = [&](uint8 elemsz) -> std::string_view {
            const auto [idx, offset] = detail::ReadArrayInfo(S);
            return { (const char*)S->GetPointerToLocalArrayElement(offset, idx, elemsz) };
        };

        const auto FromStaticString = [&](size_t strsz) -> std::string_view {
            const auto str = (const char*)(IP);
            IP += strsz;
            return str;
        };

        switch (const auto ptype = (eScriptParameterType)S->ReadAtIPAs<int8>()) {
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

        case SCRIPT_PARAM_LOCAL_LONG_STRING_VARIABLE:
        case SCRIPT_PARAM_STATIC_SHORT_STRING:
            return FromStaticString(SHORT_STRING_SIZE);
        case SCRIPT_PARAM_STATIC_LONG_STRING:
        case SCRIPT_PARAM_GLOBAL_LONG_STRING_VARIABLE:
            return FromStaticString(LONG_STRING_SIZE);
        case SCRIPT_PARAM_STATIC_PASCAL_STRING: {
            const auto sz = S->ReadAtIPAs<int8>(); // sign extension. max size = 127, not 255
            assert(sz >= 0);
            const auto str = (const char*)(IP);
            IP += (ptrdiff_t)(sz);
            return std::string_view{ str, (size_t)(sz) };
        }
        default:
            NOTSA_UNREACHABLE("Unknown param type: {}", (int32)(ptype));
        }
    } else if constexpr (std::is_same_v<T, const char*>) { // Read C-style string (Hacky)
        const auto sv = Read<std::string_view>(S);
        assert(sv.data()[sv.size()] == 0); // Check if str is 0 terminated - Not using `str[]` here as it would assert.
        return sv.data();
    } else if constexpr (std::is_arithmetic_v<Y>) { // Simple arithmetic types (After reading a string, because `const char*` with cv and pointer removed is just `char` which is an arithmetic type)
        const auto ptype = S->ReadAtIPAs<eScriptParameterType>();
        if constexpr (std::is_pointer_v<T>) { // This is a special case, as some basic ops need a reference instead of a value
            switch (ptype) {
            case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
                return reinterpret_cast<Y*>(&CTheScripts::ScriptSpace[S->ReadAtIPAs<int16>()]);
            case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
                return reinterpret_cast<Y*>(S->GetPointerToLocalVariable(S->ReadAtIPAs<int16>()));
            case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY: {
                const auto [offset, idx] = detail::ReadArrayInfo(S);
                return reinterpret_cast<Y*>(&CTheScripts::ScriptSpace[offset + sizeof(tScriptParam) * idx]);
            }
            case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY: {
                const auto [offset, idx] = detail::ReadArrayInfo(S);
                return reinterpret_cast<Y*>(S->GetPointerToLocalArrayElement(offset, idx, 1));
            }
            }
        } else { // Regular by-value
            switch (ptype) {
            case SCRIPT_PARAM_STATIC_INT_32BITS:
                return detail::safe_arithmetic_cast<T>(S->ReadAtIPAs<int32>());
            case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
                return *reinterpret_cast<T*>(&CTheScripts::ScriptSpace[S->ReadAtIPAs<int16>()]);
            case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
                return *reinterpret_cast<T*>(S->GetPointerToLocalVariable(S->ReadAtIPAs<int16>()));
            case SCRIPT_PARAM_STATIC_INT_8BITS:
                return detail::safe_arithmetic_cast<T>(S->ReadAtIPAs<int8>());
            case SCRIPT_PARAM_STATIC_INT_16BITS:
                return detail::safe_arithmetic_cast<T>(S->ReadAtIPAs<int16>());
            case SCRIPT_PARAM_STATIC_FLOAT: {
                if constexpr (!std::is_floating_point_v<T>) {
                    DebugBreak(); // Possibly unintended truncation of `float` to integeral type! Check your call stack and change the function argument type to a float.
                }
                return detail::safe_arithmetic_cast<T>(S->ReadAtIPAs<float>());
            }
            case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY: {
                const auto [offset, idx] = detail::ReadArrayInfo(S);
                return *reinterpret_cast<T*>(&CTheScripts::ScriptSpace[offset + sizeof(tScriptParam) * idx]);
            }
            case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY: {
                const auto [offset, idx] = detail::ReadArrayInfo(S);
                return *reinterpret_cast<T*>(S->GetPointerToLocalArrayElement(offset, idx, 1));
            }
            }
        }
        NOTSA_UNREACHABLE("Unknown param type: {}", (int32)(ptype));
    } else if constexpr (std::is_enum_v<Y>) { // Read underlaying arithmetic type and cast (then profit)
        return static_cast<Y>(Read<std::underlying_type_t<Y>>(S));
    } else if constexpr (std::is_same_v<Y, CPlayerPed>) { // Special case for `CPlayerPed` (As the IDs for it aren't from the pool)
        return FindPlayerPed(Read<int32>(S));
    } else if constexpr (detail::PooledType<Y>)  { // Pooled types (CVehicle, CPed, etc)
        T ptr = static_cast<T>(detail::PoolOf<Y>().GetAtRef(Read<int32>(S)));

    #ifdef NOTSA_DEBUG
        if (ptr) {
            if constexpr (detail::is_derived_from_but_not_v<CVehicle, Y>) {
                assert(Y::Type == ptr->m_nVehicleType);
            } else if constexpr (detail::is_derived_from_but_not_v<CTask, Y>) {
                assert(Y::Type == ptr->GetTaskType());
            } // TODO: Eventually add this for `CEvent` too
        }
    #endif

        return ptr;
    } else if constexpr (std::is_same_v<Y, CRunningScript>) { // Just return the script from where this command was invoked from
        return S;
    } else if constexpr (std::is_same_v<Y, CPlayerInfo>) {
        return &FindPlayerInfo(Read<int32>(S));
    } else if constexpr (detail::ScriptThing<Y>) {
        // Read information (packed 2x16 int)
        const auto info = Read<uint32>(S);
        if (info == (uint32)(-1)) {
            return nullptr; // Not quite sure how normal this is, but okay
        }

        // Extract index and (expected) ID of the object
        const auto index = (uint16)(HIWORD(info)), id = (uint16)(LOWORD(info));

        // Get the object, and check if it's ID is what we expect
        Y& thing = detail::GetScriptThing<Y>(index);
        if (detail::GetScriptThingID(thing) != id) {
            return nullptr; // ID changed, totally normal, object was reused
        }

        return &thing;
    }
    // If there's an error like "function must return a value" here,
    // that means that no suitable branch was found for `T`
    // You have 2 options: Either add a branch for that type,
    // or check and make sure you didn't try taking some object by-value
    // that you shouldn't have (Like `CPed`, `CVehicle`, or such)
}

}; // namespace script
}; // namespace notsa
