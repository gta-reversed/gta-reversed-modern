#pragma once

#include "PedDamageResponse.h"
#include "Entity.h"
#include "Enums\eWeaponType.h"
#include "Enums\eEventType.h"
#include "Event.h"

enum ePedPieceTypes;
class CPedDamageResponseCalculator;

class NOTSA_EXPORT_VTABLE CEventDamage : public CEventEditableResponse {
public:
    CEntity*       m_pSourceEntity;
    uint32         m_nStartTime;
    eWeaponType    m_weaponType;
    ePedPieceTypes m_pedPieceType;
    uint8          m_ucDirection;
    union {
        struct {
            uint8 m_b01 : 1;
            uint8 m_bKnockOffPed : 1; // If true, the victim falls on the ground when damaged
            uint8 m_b03 : 1;
            uint8 m_bPedInVehicle : 1;
            uint8 m_b05 : 1;
        };
        uint8 m_ucFlags;
    };
    bool               m_unk26;
    bool               m_unk27;
    uint32             m_nAnimGroup;
    int32              m_nAnimID;
    float              m_fAnimBlend;
    float              m_fAnimSpeed;
    CPedDamageResponse m_damageResponse;

public:
    static constexpr auto Type = eEventType::EVENT_DAMAGE;

    CEventDamage(const CEventDamage& event);
    CEventDamage(CEntity* source, uint32 startTime, eWeaponType weaponType, ePedPieceTypes pieceHit, uint8 direction, bool a7, bool bPedInVehicle);
    ~CEventDamage() override;

    eEventType GetEventType() const override;
    int32 GetEventPriority() const override;
    int32 GetLifeTime() override;
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

    void From(const CEventDamage& event);
    void ProcessDamage(CPed* ped);
    void ComputeBodyPartToRemove(int32& boneFrameId);
    void ComputeDeathAnim(CPed* ped, bool bMakeActiveTaskAbortable);
    void ComputeDamageAnim(CPed* ped, bool bMakeActiveTaskAbortable);
    void ComputeAnim(CPed* ped, bool bMakeActiveTaskAbortable = true);

    //! Either computes the damage, or sets it as computed (Without computing it) - Very common logic in the code
    void ComputeDamageResponseIfAffectsPed(CPed* ped, CPedDamageResponseCalculator calculator, bool bSpeak);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventDamage* Constructor(const CEventDamage& event);
    CEventDamage* Constructor(CEntity * source, uint32 startTime, eWeaponType weaponType, ePedPieceTypes pieceHit, uint8 direction, bool a7, bool bPedInVehicle);

    eEventType GetEventType_Reversed() const { return EVENT_DAMAGE; }
    int32 GetEventPriority_Reversed() const { return 65; }
    int32 GetLifeTime_Reversed() { return 0; }
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
