#pragma once
#include "CPedDamageResponse.h"
#include "Enums\eWeaponType.h"
#include "Enums\ePedPieceTypes.h"
#include "Entity\Ped\CPed.h"

#pragma pack(push, 1)
class CPedDamageResponseCalculator
{
public:
    CEntity *      pEntity;
    float          Damage;
    ePedPieceTypes bodyPart;
    eWeaponType    weaponType;
    bool           bSpeak;     // refers to a CPed::Say call (the dying scream?)

    static void InjectHooks();
    CPedDamageResponseCalculator* Constructor1(CEntity * pEntity, float fDamage, eWeaponType weaponType, ePedPieceTypes bodyPart, bool b_1);
    void Destructor1();

    void ComputeDamageResponse(CPed * pPed, CPedDamageResponse * pDamageResponse, bool bSpeak);
    
};
#pragma pack(pop)

VALIDATE_SIZE(CPedDamageResponseCalculator, 0x11);