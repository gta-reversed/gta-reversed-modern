#pragma once

//#include <array>

#include "Base.h"
#include "Utility.hpp"
#include "TheScripts.h"
#include "RunningScript.h" // ScriptParams
#include "Pools.h"

namespace notsa {
namespace script {
/*!
* Bool is a sepcial case, it isn't stored, but rather updates the compare flag.
* TODO: Actually verify this theory.
*/
void StoreArg(CRunningScript* S, bool arg) {
    S->UpdateCompareFlag(arg);
}
/*!
* @brief Store an argument of type. NOTE: Increments script's IP.
*
* @param S The S to which the values should be stored to
* @param arg    The argument to store
*/
template<typename T>
void StoreArg(CRunningScript* S, const T& arg) requires (std::is_arithmetic_v<T>) { // Add requirements to filter out possible mistakes (Like returning an unsupported type)
    tScriptParam* dest = [&] {
        auto& ip = S->m_pCurrentIP;

        // Helper
        const auto ReadArrayInfo = [S] {
            uint16 offset{};
            int32 idx{};
            S->ReadArrayInformation(true, &offset, &idx);
            return std::make_tuple(offset, idx);
        };

        switch (CTheScripts::Read1ByteFromScript(ip)) {
        case SCRIPT_PARAM_GLOBAL_NUMBER_VARIABLE:
            return reinterpret_cast<tScriptParam*>(&CTheScripts::ScriptSpace[CTheScripts::Read2BytesFromScript(ip)]);
        case SCRIPT_PARAM_LOCAL_NUMBER_VARIABLE: {
            return S->GetPointerToLocalVariable(CTheScripts::Read2BytesFromScript(ip));
        }
        case SCRIPT_PARAM_GLOBAL_NUMBER_ARRAY: {
            const auto [offset, idx] = ReadArrayInfo();
            return reinterpret_cast<tScriptParam*>(&CTheScripts::ScriptSpace[offset + 4 * idx]);
        }
        case SCRIPT_PARAM_LOCAL_NUMBER_ARRAY: {
            const auto [offset, idx] = ReadArrayInfo();
            return S->GetPointerToLocalArrayElement(offset, idx, 1);
        }
        default:
            NOTSA_UNREACHABLE("Variable type unknown");
        }
    }();
    static_assert(sizeof(T) <= sizeof(tScriptParam)); // Otherwise we'd be overwriting the script => bad

    memset((void*)dest, 0, sizeof(tScriptParam));  // Zero it all out
    memcpy((void*)dest, (void*)&arg, sizeof(arg)); // Now copy the value to it (Which might be less than 4 bytes)
}

// Vector overloads

void StoreArg(CRunningScript* script, const CVector& v3) {
    for (auto&& c : v3.GetComponents()) {
        StoreArg(script, c);
    }
}

void StoreArg(CRunningScript* S, const CVector2D& v2) {
    for (auto&& c : v2.GetComponents()) {
        StoreArg(S, c);
    }
}

// Below must be after the basic overloads, otherwise won't compile

/*!
* @brief Overload for MultiReturn => Stores each arg separately, in same order as they appear in the multireturn
*/
template<typename... Ts>
void StoreArg(CRunningScript* S, const MultiRet<Ts...>& ret) {
    std::apply([&](auto&& arg) { StoreArg(S, arg); }, ret);
}

void StoreArg(CRunningScript* S, CompareFlagUpdate flag) {
    S->UpdateCompareFlag(flag.state);
}

/*!
* @brief Arrays are pushed as arrays
*/
//template<typename T, size_t N>
//void StoreArg(CRunningScript* S, std::array<T, N>&& arr) {
//    for (const auto& arg : arr) {
//        StoreArg(S, arg);
//    }
//}

/*!
* @brief Overload for types that have a pool (thus we store a reference)
*/
template<typename T, typename Y = std::decay_t<T>>
void StoreArg(CRunningScript* S, T* arg) requires(detail::PoolOf<Y>()) {
    StoreArg(S, detail::PoolOf<Y>().GetRef(arg));
}

}; // namespace script
}; // namespace notsa
