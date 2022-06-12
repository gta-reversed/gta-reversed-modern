#pragma once

class C2dEffect;

struct CScriptedEffectPairs {
    int32 dword0;
    int32 dword4;
    int32 dword8;
    int32 dwordC;
    int32 dword10;
    int32 dword14;
    int32 dword18;
    int8  gap1C[4];
    int32 dword20;
    int8  byte24;
    int8  gap25[3];
    int32 dword28;
    int32 dword2C;
    int32 dword30;
    int32 dword34;
    int32 dword38;
    int32 dword3C;
    int8  gap40[4];
    int32 dword44;
    int8  byte48;
    int8  gap49[3];
    int32 dword4C;
    int32 dword50;
    int32 dword54;
    int32 dword58;
    int32 dword5C;
    int32 dword60;
    int8  gap64[4];
    int32 dword68;
    int8  byte6C;
    int8  gap6D[3];
    int32 dword70;
    int32 dword74;
    int32 dword78;
    int32 dword7C;
    int32 dword80;
    int32 dword84;
    int8  gap88[4];
    int32 dword8C;
    int8  byte90;

    void Flush() {
        dword4  = -1;
        dword8  = -1;
        dword10 = -1;
        dword14 = -1;
        dwordC  = -1;
        dword18 = -1;
        dword20 = -1;
        byte24  = 0;

        dword28 = -1;
        dword2C = -1;
        dword34 = -1;
        dword38 = -1;
        dword30 = -1;
        dword3C = -1;
        dword44 = -1;
        byte48  = 0;

        dword4C = -1;
        dword50 = -1;
        dword58 = -1;
        dword5C = -1;
        dword54 = -1;
        dword60 = -1;
        dword68 = -1;
        byte6C  = 0;

        dword70 = -1;
        dword74 = -1;
        dword7C = -1;
        dword80 = -1;
        dword78 = -1;
        dword84 = -1;
        dword8C = -1;
        byte90  = 0;

        dword0  = 0;
    }
};
VALIDATE_SIZE(CScriptedEffectPairs, 0x94);

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
    static inline std::array<const C2dEffect, 64>&      ms_effects               = *(std::array<const C2dEffect, 64>*)0xC3AB00; // class maybe
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

    static void Load() { } // NOP
    static void Save() { } // NOP
};
