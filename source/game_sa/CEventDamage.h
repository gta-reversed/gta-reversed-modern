#pragma once
#include "CPedDamageResponse.h"
#include "Entity\CEntity.h"
#include "Enums\eWeaponType.h"
#include "Enums\ePedPieceTypes.h"

class CEventDamage
{
public:
    DWORD vmt;                                              // 0
    DWORD ticks;                                            // 4
    BYTE unk8;                                              // 8
    BYTE unk9;                                              // 9
    BYTE unkA;                                              // Ah
    BYTE unkB;                                              // Bh
    BYTE unkC;                                              // Ch
    BYTE unkD;                                              // Dh
    WORD unkE;                                              // Eh
    WORD unk10;                                             // 10h
    WORD unk12;                                             // 12h
    CEntity *                       pInflictor;             // 14h
    DWORD                           damageTime;             // 18h
    eWeaponType                     weaponUsed;             // 1Ch
    ePedPieceTypes                  pedPieceType;           // 20h
    BYTE                            ucDirection;            // 24h
    BYTE                            ucFlags;                // 25h
    BYTE unk26;                                             // 26h
    BYTE unk27;                                             // 27h
    DWORD                           dwAnimGroup;            // 28h
    DWORD                           dwAnimID;               // 2Ch
    float                           fAnimBlend;             // 30h
    float                           fAnimSpeed;             // 34h
    CPedDamageResponse              damageResponseData;     // 38h

    static void InjectHooks();
    CEventDamage* Constructor1(CEntity * pEntity, unsigned int i_1, eWeaponType weaponType, ePedPieceTypes hitZone, unsigned char uc_2, bool b_3, bool b_4);
    void Destructor1();

    bool AffectsPed(CPed * pPed);
};

VALIDATE_SIZE(CEventDamage, 0x44);