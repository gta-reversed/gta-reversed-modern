#pragma once

struct CWindModifier {
    CVector m_vecPos;
    int32   m_iActive;
    float   m_fPower;
};

class CWindModifiers {
public:
    static constexpr int32 MAX_NUM_MODIFIERS = 16;

    static int32& Number;
    static CWindModifier (&Array)[MAX_NUM_MODIFIERS];

public:
    static void InjectHooks();

    static void FindWindModifier(CVector vecPos, float* pOutX, float* pOutY);
    static void RegisterOne(CVector vecPos, int32 iActive, float fPower);
};
