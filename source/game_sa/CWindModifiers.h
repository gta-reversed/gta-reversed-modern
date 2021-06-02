#pragma once

struct CWindModifier {
    CVector m_vecPos;
    int     m_iActive;
    float   m_fPower;
};

class CWindModifiers {
public:
    static constexpr int MAX_NUM_MODIFIERS = 16;

    static int& Number;
    static CWindModifier (&Array)[MAX_NUM_MODIFIERS];

public:
    static void InjectHooks();

    static void FindWindModifier(CVector vecPos, float* pOutX, float* pOutY);
    static void RegisterOne(CVector vecPos, int iActive, float fPower);
};
