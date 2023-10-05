#pragma once

class C2dEffect;

struct CScriptedEffectPair {
    int32 dword0;
    int32 dword4;
    int32 dword8;
    int32 dwordC;
    int32 dword10;
    int32 dword14;
    int32 dword18;
    int32 dword1C;
    int8  byte20;

    void Flush() {
        dword0  = -1;
        dword4  = -1;
        dwordC  = -1;
        dword10 = -1;
        dword8  = -1;
        dword14 = -1;
        dword1C = -1;
        byte20  = 0;
    }
};

struct CScriptedEffectPairs {
    int32 m_nCurrentPairIndex;
    CScriptedEffectPair pair1[4];
    CScriptedEffectPair pair2[4];

    void Flush() {
        std::ranges::for_each(pair1, [](auto& pair) { pair.Flush(); });
        m_nCurrentPairIndex  = 0;
    }
};
VALIDATE_SIZE(CScriptedEffectPairs, 0x124);

struct tUserList_Child {
    int32 m_Id;      // eModelID
    int32 m_PedType; // ePedType
};
VALIDATE_SIZE(tUserList_Child, 0x8);

struct tUserList {
    tUserList_Child* arr[8];
    bool             m_b20;
    int8             pad[3];
};
VALIDATE_SIZE(tUserList, 0x24);

class CScripted2dEffects {
public:
    static inline std::array<C2dEffect, 64>&            ms_effects               = *(std::array<C2dEffect, 64>*)0xC3AB00; // class maybe
    static inline std::array<CScriptedEffectPairs, 64>& ms_effectPairs           = *(std::array<CScriptedEffectPairs, 64>*)0xC3BB00;
    static inline std::array<tUserList, 64>&            ms_userLists             = *(std::array<tUserList, 64>*)0xC3A200; // class maybe
    static inline std::array<bool, 64>&                 ms_activated             = *(std::array<bool, 64>*)0xC3A1A0;
    static inline std::array<uint16, 64>&               ScriptReferenceIndex     = *(std::array<uint16, 64>*)0xC3A120;
    static inline std::array<int32, 64>&                ms_effectSequenceTaskIDs = *(std::array<int32, 64>*)0xC3A020;
    static inline std::array<bool, 64>&                 ms_useAgainFlags         = *(std::array<bool, 64>*)0xC39FE0;
    static inline std::array<float, 64>&                ms_radii                 = *(std::array<float, 64>*)0xC39EE0;

public:
    static void InjectHooks();

    static void Init();

    static CScriptedEffectPairs* GetEffectPairs(const C2dEffect* effect);
    static int32 GetIndex(const C2dEffect* effect);

    static int32 AddScripted2DEffect(float radius);
    static void ReturnScripted2DEffect(int32 index);

    /// Index of the effect if it's from `ms_effects` `nullopt` otherwise.
    static auto IndexOfEffect(const C2dEffect* effect) ->std::optional<size_t>;

    static void Load() { } // NOP
    static void Save() { } // NOP
};
