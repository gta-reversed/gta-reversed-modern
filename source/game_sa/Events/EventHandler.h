/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "EventHandlerHistory.h"

class CPed;

class CTask;
class CTaskInteriorUseInfo;

class CEvent;
class CEventCarUpsideDown;
class CEventDamage;
class CEventAreaCodes;
class CEventAttractor;
class CEventBuildingCollision;
class CEventChatPartner;
class CEventCopCarBeingStolen;
class CEventCreatePartnerTask;
class CEventDanger;
class CEventDeadPed;
class CEventDeath;
class CEventDontJoinPlayerGroup;
class CEventDraggedOutCar;
class CEventFireNearby;
class CEventDamage;
class CEventGotKnockedOverByCar;
class CEventGunAimedAt;
class CEventHighAngerAtPlayer;
class CEventInWater;
class CEventInteriorUseInfo;
class CEventLowAngerAtPlayer;
class CEventHealthLow;
class CEventPotentialWalkIntoObject;
class CEventObjectCollision;
class CEventOnFire;
class CEventPassObject;
class CEventAcquaintancePed;
class CEventSoundQuiet;
class CEventAcquaintancePedHateBadlyLit;

class CEventHandler {
public:
    CPed*                m_ped{};
    CEventHandlerHistory m_history{};
    CTask*               m_physicalResponseTask{};
    CTask*               m_eventResponseTask{};
    CTask*               m_attackTask{};
    CTask*               m_sayTask{};
    CTask*               m_partialAnimTask{};

public:
    static void InjectHooks();

    explicit CEventHandler(CPed* ped);
    ~CEventHandler() = default;

    void Flush();
    void FlushImmediately();

    eEventType GetCurrentEventType() const;
    void HandleEvents();
    bool IsKillTaskAppropriate(CPed* ped1, CPed* ped2, const CEvent& event);
    static bool IsTemporaryEvent(const CEvent& event);
    void RecordActiveEvent(const CEvent& event);
    void RecordPassiveEvent(const CEvent& event);
    static void RegisterKill(const CPed* ped, const CEntity* entity, eWeaponType weaponType, bool a4);
    void SetEventResponseTask(const CEvent& event);

    void ComputeAreaCodesResponse(CEventAreaCodes* e, CTask* tactive, CTask* tsimplest);
    void ComputeAttractorResponse(CEventAttractor* e, CTask* tactive, CTask* tsimplest);
    void ComputeBuildingCollisionPassiveResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeBuildingCollisionResponse(CEventBuildingCollision* e, CTask* tactive, CTask* tsimplest);
    void ComputeCarUpsideDownResponse(CEventCarUpsideDown* e, CTask* tactive, CTask* tsimplest);
    void ComputeChatPartnerResponse(CEventChatPartner* e, CTask* tactive, CTask* tsimplest);
    void ComputeCopCarBeingStolenResponse(CEventCopCarBeingStolen* e, CTask* tactive, CTask* tsimplest);
    void ComputeCreatePartnerTaskResponse(CEventCreatePartnerTask* e, CTask* tactive, CTask* tsimplest);
    void ComputeDamageResponse(CEventDamage* e, CTask* tactive, CTask* tsimplest, CTask* abortedTaskEventResponse);
    void ComputeDangerResponse(CEventDanger* e, CTask* tactive, CTask* tsimplest);
    void ComputeDeadPedResponse(CEventDeadPed* e, CTask* tactive, CTask* tsimplest);
    void ComputeDeathResponse(CEventDeath* e, CTask* tactive, CTask* tsimplest);
    void ComputeDontJoinGroupResponse(CEventDontJoinPlayerGroup* e, CTask* tactive, CTask* tsimplest);
    void ComputeDraggedOutCarResponse(CEventDraggedOutCar* e, CTask* tactive, CTask* tsimplest);
    void ComputeFireNearbyResponse(CEventFireNearby* e, CTask* tactive, CTask* tsimplest);
    void ComputeGotKnockedOverByCarResponse(CEventGotKnockedOverByCar* e, CTask* tactive, CTask* tsimplest);
    void ComputeGunAimedAtResponse(CEventGunAimedAt* e, CTask* tactive, CTask* tsimplest);
    void ComputeHighAngerAtPlayerResponse(CEventHighAngerAtPlayer* e, CTask* tactive, CTask* tsimplest);
    void ComputeInWaterResponse(CEventInWater* e, CTask* tactive, CTask* tsimplest);
    void ComputeInteriorUseInfoResponse(CEventInteriorUseInfo* e, CTaskInteriorUseInfo* tactive, CTask* tsimplest);
    void ComputeKnockOffBikeResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeLowAngerAtPlayerResponse(CEventLowAngerAtPlayer* e, CTask* tactive, CTask* tsimplest);
    void ComputeLowHealthResponse(CEventHealthLow* e, CTask* tactive, CTask* tsimplest);
    void ComputeObjectCollisionPassiveResponse(CEventPotentialWalkIntoObject* e, CTask* tactive, CTask* tsimplest);
    void ComputeObjectCollisionResponse(CEventObjectCollision* e, CTask* tactive, CTask* tsimplest);
    void ComputeOnEscalatorResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeOnFireResponse(CEventOnFire* e, CTask* tactive, CTask* tsimplest);
    void ComputePassObjectResponse(CEventPassObject* e, CTask* tactive, CTask* tsimplest);
    void ComputePedCollisionWithPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputePedCollisionWithPlayerResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputePedEnteredVehicleResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputePedFriendResponse(CEventAcquaintancePed* e, CTask* tactive, CTask* tsimplest);
    void ComputePedSoundQuietResponse(CEventSoundQuiet* e, CTask* tactive, CTask* tsimplest);
    void ComputePedThreatBadlyLitResponse(CEventAcquaintancePedHateBadlyLit* e, CTask* tactive, CTask* tsimplest);
    void ComputePedThreatResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputePedToChaseResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputePedToFleeResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputePersonalityResponseToDamage(CEventDamage* damageEvent, CEntity* entity);
    void ComputePlayerCollisionWithPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputePlayerWantedLevelResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputePotentialPedCollideResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputePotentialWalkIntoFireResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeReallyLowHealthResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeReviveResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeScriptCommandResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeSeenCopResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeSeenPanickedPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeSexyPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeSexyVehicleResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeShotFiredResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeShotFiredWhizzedByResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeSignalAtPedResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeSpecialResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeVehicleCollisionResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeVehicleDamageResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeVehicleDiedResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeVehicleHitAndRunResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeVehicleOnFireResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeVehiclePotentialCollisionResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeVehiclePotentialPassiveCollisionResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeVehicleToStealResponse(CEvent* e, CTask* tactive, CTask* tsimplest);
    void ComputeWaterCannonResponse(CEvent* e, CTask* tactive, CTask* tsimplest);

    void ComputeEventResponseTask(CEvent* event, CTask* task);
    static CTask* ComputeEventResponseTask(const CPed& ped, const CEvent& e);

    auto& GetHistory() { return m_history; }

private:
    // 0x4C3E80
    CEventHandler* Constructor(CPed * ped) {
        this->CEventHandler::CEventHandler(ped);
        return this;
    }

    // 0x4C3EC0
    CEventHandler* Destructor() {
        this->CEventHandler::~CEventHandler();
        return this;
    }
};

VALIDATE_SIZE(CEventHandler, 0x34);
