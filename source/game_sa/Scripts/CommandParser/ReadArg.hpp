#pragma once

#include <type_traits>

#include "RunningScript.h"
#include "TheScripts.h"
#include "Utility.hpp"
#include "Rect.h"

namespace notsa {
namespace script {

template<typename T, typename Y = T>
Y Read(CRunningScript* S);

auto ReadArrayInfo(CRunningScript* S) {
    uint16 offset{};
    int32 idx{};
    S->ReadArrayInformation(true, &offset, &idx);
    return std::make_tuple(offset, idx);
}

/*!
* @notsa
* @brief Read one POD parameter from the script at the current IP and increment the IP. Non-POD parameters can be read using `notsa::script::ReadParam`
* @return The value read casted to the required type. The value will be read correctly,
*         even if the original type was wider or narrower then the
*         requested one (eg.: originally it was `int8`, but `T = int32`)
*/
template<typename T>
T Read(CRunningScript* S) requires(std::is_arithmetic_v<T> || std::is_enum_v<T>) {
    auto& ip = S->m_pCurrentIP;

    switch (CTheScripts::Read1ByteFromScript(ip)) {
    case SCRIPT_PARAM_STATIC_INT_32BITS:
        return static_cast<T>(CTheScripts::Read4BytesFromScript(ip));
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        return *reinterpret_cast<T*>(&CTheScripts::ScriptSpace[CTheScripts::Read2BytesFromScript(ip)]);
    case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
        return *reinterpret_cast<T*>(S->GetPointerToLocalVariable(CTheScripts::Read2BytesFromScript(ip)));
    case SCRIPT_PARAM_STATIC_INT_8BITS:
        return static_cast<T>(CTheScripts::Read1ByteFromScript(ip));
    case SCRIPT_PARAM_STATIC_INT_16BITS:
        return static_cast<T>(CTheScripts::Read2BytesFromScript(ip));
    case SCRIPT_PARAM_STATIC_FLOAT:
        return static_cast<T>(CTheScripts::ReadFloatFromScript(ip));
    case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY: {
        const auto [offset, idx] = ReadArrayInfo(S);
        return *reinterpret_cast<T*>(CTheScripts::ScriptSpace[offset + 4 * idx]);
    }
    case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY: {
        const auto [offset, idx] = ReadArrayInfo(S);
        return *reinterpret_cast<T*>(S->GetPointerToLocalArrayElement(offset, idx, 1));
    }
    default:
        NOTSA_UNREACHABLE();
    }
}

/*!
* @brief Read variable as T&. Useful when to modify local/global variables.
*/
template <typename T, typename Y = std::decay_t<T>> requires(std::is_reference_v<T> && std::is_arithmetic_v<Y>)
T Read(CRunningScript* S) {
    auto& ip = S->m_pCurrentIP;

    switch (auto t = CTheScripts::Read1ByteFromScript(ip)) {
    case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
        return *reinterpret_cast<Y*>(&CTheScripts::ScriptSpace[CTheScripts::Read2BytesFromScript(ip)]);
    case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE:
        return *reinterpret_cast<Y*>(S->GetPointerToLocalVariable(CTheScripts::Read2BytesFromScript(ip)));
    case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY: {
        const auto [offset, idx] = ReadArrayInfo(S);
        return *reinterpret_cast<Y*>(&CTheScripts::ScriptSpace[offset + 4 * idx]);
    }
    case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY: {
        const auto [offset, idx] = ReadArrayInfo(S);
        return *reinterpret_cast<Y*>(S->GetPointerToLocalArrayElement(offset, idx, 1));
    }
    default:
        NOTSA_UNREACHABLE("Bad reference value read! type: {}", t);
    }
}

/*!
* @brief  Special overload for stuff in pools.
* @return Always a reference to the object `T`
*/
template<typename T>
concept PooledType = requires {
    detail::PoolOf<std::decay_t<T>>();
};

template<PooledType T, typename Y = std::decay_t<T>>
Y& Read(CRunningScript* S) {
    return *detail::PoolOf<Y>().GetAtRef(Read<int32>(S));
}

/*!
 * @brief Read a vehicle as specialized type.
 */
template<typename T, typename Y = std::decay_t<T>> requires(!std::is_same_v<CVehicle, Y> && std::is_base_of_v<CVehicle, Y>)
Y& Read(CRunningScript* S) {
    DEV_LOG("hello :333");
    auto& vehicle = Read<CVehicle&>(S);
    assert(Y::Type == vehicle.m_nVehicleType);
    return *reinterpret_cast<Y*>(&vehicle);
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
    auto& IP = S->m_pCurrentIP;

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

    const auto type = (eScriptParameterType)CTheScripts::Read1ByteFromScript(IP); // As a variable so can inspect it in debugger
    switch (type) {
    case SCRIPT_PARAM_LOCAL_LONG_STRING_VARIABLE:
    case SCRIPT_PARAM_STATIC_SHORT_STRING:
        return FromStaticString(SHORT_STRING_SIZE);
    case SCRIPT_PARAM_STATIC_LONG_STRING:
    case SCRIPT_PARAM_GLOBAL_LONG_STRING_VARIABLE:
        return FromStaticString(LONG_STRING_SIZE);
    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_VARIABLE:
        return FromScriptSpace(CTheScripts::Read2BytesFromScript(IP));
    case SCRIPT_PARAM_LOCAL_SHORT_STRING_VARIABLE:
        return { (const char*)S->GetPointerToLocalVariable(CTheScripts::Read2BytesFromScript(IP)) };
    case SCRIPT_PARAM_GLOBAL_SHORT_STRING_ARRAY:
        return FromGlobalArray(SHORT_STRING_SIZE);
    case SCRIPT_PARAM_GLOBAL_LONG_STRING_ARRAY:
        return FromGlobalArray(LONG_STRING_SIZE);
    case SCRIPT_PARAM_LOCAL_SHORT_STRING_ARRAY:
        return FromLocalArray(2);
    case SCRIPT_PARAM_LOCAL_LONG_STRING_ARRAY:
        return FromLocalArray(4);
    case SCRIPT_PARAM_STATIC_PASCAL_STRING: {
        const auto sz = CTheScripts::Read1ByteFromScript(IP); // sign extension. max size = 127, not 255
        assert(sz >= 0);
        IP += sz;
        return { (const char*)(IP - sz), (size_t)sz };
    }
    default:
        NOTSA_UNREACHABLE();
    }
}

template<>
const char* Read<const char*>(CRunningScript* S) {
    return Read<std::string_view>(S).data();
}

}; // namespace script
}; // namespace notsa
