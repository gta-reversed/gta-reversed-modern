#pragma once
#include "CPedDamageResponse.h"
#include "Entity\CEntity.h"
#include "Enums\eWeaponType.h"
#include "Enums\ePedPieceTypes.h"
#include "CEvent.h"

class CEventDamage : CEvent
{
public:
    unsigned int m_nTimeActive;
    bool m_bValid;
    bool m_unk9;
    bool m_unkA;
    bool m_unkB;
    bool m_bAddToEventGroup;
    bool m_unkD;
    unsigned short m_taskId;
    unsigned short unk10;
    unsigned short unk12;
    CEntity* m_pSourceEntity;
    unsigned int m_nStartTime;
    eWeaponType m_weaponType;
    ePedPieceTypes pedPieceType;
    bool m_ucDirection;
    union {
        struct {
            unsigned char m_b01 : 1;
            unsigned char m_b02 : 1;
            unsigned char m_b03 : 1;
            unsigned char m_bPedInVehicle : 1;
            unsigned char m_b05 : 1;
        };
        unsigned char m_ucFlags;
    };
    bool m_unk26;
    bool m_unk27;
    unsigned int m_nAnimGroup;
    unsigned int m_nAnimID;
    float m_fAnimBlend;
    float m_fAnimSpeed;
    CPedDamageResponse m_damageResponse;

    static void InjectHooks();
    CEventDamage* Constructor(CEntity * pEntity, unsigned int startTime, eWeaponType weaponType, ePedPieceTypes pieceHit, unsigned char direction, bool b_3, bool bPedInVehicle);
    void Destructor();

    bool AffectsPed(CPed * pPed);
};

VALIDATE_SIZE(CEventDamage, 0x44);