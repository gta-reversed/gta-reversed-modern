/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CTaskComplex.h"
#include "eWeaponType.h"
#include "CVehicle.h"

class CTaskComplexDie : public CTaskComplex {
public:
    eWeaponType m_nWeaponType; // Means Of Death
    int32 m_animGroup;
    int32 m_animID;
    float m_fBlendDelta;
    float  m_fAnimSpeed;

    union
    {
        uint32 m_nFlags;
        struct
        {
            uint32 bBeingKilledByStealth : 1;
            uint32 bFallingToDeath : 1;
            uint32 bFallToDeathOverRailing : 1;

        };
    };
    int32 nFallToDeathDir;


    CTaskComplexDie(eWeaponType nWeaponType/*=WEAPONTYPE_UNARMED*/, int32 animGroup/*ANIM_STD_PED*/, int32 animID/*ANIM_STD_KO_FRONT*/,
        float fBlendDelta, float fAnimSpeed, bool bBeingKilledByStealth, bool bFallingToDeath, int32 nFallToDeathDir, bool bFallToDeathOverRailing);

};

VALIDATE_SIZE(CTaskComplexDie, 0x28);

