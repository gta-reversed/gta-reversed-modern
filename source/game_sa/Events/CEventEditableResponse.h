#pragma once
#include "CEvent.h"

class CEventEditableResponse : public CEvent {
public:
    bool m_bAddToEventGroup;
    bool field_D;
    short m_taskId;
    short field_10;
    unsigned short field_12;

    static void InjectHooks();

    CEventEditableResponse();
    ~CEventEditableResponse();
private:
    CEventEditableResponse* Constructor();
public:
    CEvent* Clone() override;
    bool HasEditableResponse() override;
    virtual CEventEditableResponse* CloneEditable() = 0;

    CEvent* Clone_Reversed();
    bool HasEditableResponse_Reversed() { return true; }

    bool WillRespond();
    void InformVehicleOccupants(CPed* ped);
    void InformRespectedFriends(CPed* ped);
    void InformGroup(CPed* ped);
    void TriggerLookAt(CPed* ped);
    void ComputeResponseTaskType(CPed* ped, bool bDecisionMakerTypeInGroup);
    void ComputeResponseTaskType(CPedGroup* pedGroup);
    bool ComputeResponseTaskOfType(CPed* ped, int taskId);
};

VALIDATE_SIZE(CEventEditableResponse, 0x14);