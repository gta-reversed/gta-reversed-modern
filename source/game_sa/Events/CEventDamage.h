#pragma once

#include "CPedDamageResponse.h"
#include "Entity\CEntity.h"
#include "Enums\eWeaponType.h"
#include "Enums\eEventType.h"
#include "CEvent.h"

enum ePedPieceTypes;

class CEventDamage : public CEventEditableResponse {
public:
    CEntity* m_pSourceEntity;
    unsigned int m_nStartTime;
    eWeaponType m_weaponType;
    ePedPieceTypes m_pedPieceType;
    char m_ucDirection;
    union {
        struct {
            unsigned char m_b01 : 1;
            unsigned char m_bKnockOffPed : 1; // If true, the victim falls on the ground when damaged
            unsigned char m_b03 : 1;
            unsigned char m_bPedInVehicle : 1;
            unsigned char m_b05 : 1;
        };
        unsigned char m_ucFlags;
    };
    bool m_unk26;
    bool m_unk27;
    unsigned int m_nAnimGroup;
    int m_nAnimID;
    float m_fAnimBlend;
    float m_fAnimSpeed;
    CPedDamageResponse m_damageResponse;

public:
    CEventDamage(CEventDamage* pCopyFrom);
    CEventDamage(CEntity* source, unsigned int startTime, eWeaponType weaponType, ePedPieceTypes pieceHit, unsigned char direction, bool a7, bool bPedInVehicle);
    ~CEventDamage();

    eEventType GetEventType() const override;
    int32_t GetEventPriority() const override;
    int GetLifeTime() override;
    bool AffectsPed(CPed* ped) override;
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    bool IsCriminalEvent() override;
    void ReportCriminalEvent(CPed* ped) override;
    CEntity* GetSourceEntity() const override;
    bool TakesPriorityOver(const CEvent& refEvent) override;
    float GetLocalSoundLevel() override;
    bool DoInformVehicleOccupants(CPed* ped) override;
    bool CanBeInterruptedBySameEvent() override;
    CEventEditableResponse* CloneEditable() override;

    void From(CEventDamage* pCopyFrom);
    void ProcessDamage(CPed* ped);
    void ComputeBodyPartToRemove(int* pBoneFrameId);
    void ComputeDeathAnim(CPed* ped, bool bMakeActiveTaskAbortable);
    void ComputeDamageAnim(CPed* ped, bool bMakeActiveTaskAbortable);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventDamage* Constructor(CEventDamage* pCopyFrom);
    CEventDamage* Constructor(CEntity * source, unsigned int startTime, eWeaponType weaponType, ePedPieceTypes pieceHit, unsigned char direction, bool a7, bool bPedInVehicle);

    eEventType GetEventType_Reversed() const { return EVENT_DAMAGE; }
    int32_t GetEventPriority_Reversed() const { return 65; }
    int GetLifeTime_Reversed() { return 0; }
    bool AffectsPed_Reversed(CPed* ped);
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
    bool IsCriminalEvent_Reversed();
    void ReportCriminalEvent_Reversed(CPed* ped);
    CEntity* GetSourceEntity_Reversed() const;
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
    float GetLocalSoundLevel_Reversed() { return 55.0f; }
    bool DoInformVehicleOccupants_Reversed(CPed* ped);
    bool CanBeInterruptedBySameEvent_Reversed() { return true; };
    CEventEditableResponse* CloneEditable_Reversed();
};

VALIDATE_SIZE(CEventDamage, 0x44);
