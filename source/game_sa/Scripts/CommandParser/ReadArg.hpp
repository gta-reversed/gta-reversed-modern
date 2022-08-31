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

    const auto ReadArrayInfo = [S] {
        uint16 offset{};
        int32 idx{};
        S->ReadArrayInformation(true, &offset, &idx);
        return std::make_tuple(offset, idx);
    };

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
        const auto [offset, idx] = ReadArrayInfo();
        return *reinterpret_cast<T*>(CTheScripts::ScriptSpace[offset + 4 * idx]);
    }
    case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY: {
        const auto [offset, idx] = ReadArrayInfo();
        return *reinterpret_cast<T*>(S->GetPointerToLocalArrayElement(offset, idx, 1));
    }
    default:
        NOTSA_UNREACHABLE();
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

}; // namespace script
}; // namespace notsa
