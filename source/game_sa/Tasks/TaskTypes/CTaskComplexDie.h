/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplex.h"
#include "eWeaponType.h"
#include "CVehicle.h"

class  CTaskComplexDie : public CTaskComplex {
public:
    eWeaponType m_nWeaponType; // Means Of Death
    int m_animGroup;
    int m_animID;
    float m_fBlendDelta;
    float  m_fAnimSpeed;

    union
    {
        unsigned int m_nFlags;
        struct
        {
            unsigned int bBeingKilledByStealth : 1;
            unsigned int bFallingToDeath : 1;
            unsigned int bFallToDeathOverRailing : 1;

        };
    };
    int nFallToDeathDir;


    CTaskComplexDie(eWeaponType nWeaponType/*=WEAPONTYPE_UNARMED*/, int animGroup/*ANIM_STD_PED*/, int animID/*ANIM_STD_KO_FRONT*/,
        float fBlendDelta, float fAnimSpeed, bool bBeingKilledByStealth, bool bFallingToDeath, int nFallToDeathDir, bool bFallToDeathOverRailing);

};

VALIDATE_SIZE(CTaskComplexDie, 0x28);

