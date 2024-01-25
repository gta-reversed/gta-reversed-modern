#pragma once

#include "EventEditableResponse.h"

#include "EventEditableResponse.h"
#include "Vector.h"
#include "EventAcquaintancePed.h"


class NOTSA_EXPORT_VTABLE CEventAcquaintancePed : public CEventEditableResponse {
public:
    CPed* m_AcquaintancePed;

public:
    explicit CEventAcquaintancePed(CPed* ped, eTaskType taskType = TASK_NONE/*notsa arg*/);
    ~CEventAcquaintancePed() override;

    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEntity* GetSourceEntity() const override { return reinterpret_cast<CEntity*>(m_AcquaintancePed); }
    bool TakesPriorityOver(const CEvent& refEvent) override;
    bool CanBeInterruptedBySameEvent() override { return true; }

public:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventAcquaintancePed* Constructor(CPed* ped);

    bool AffectsPed_Reversed(CPed* ped);
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
};
VALIDATE_SIZE(CEventAcquaintancePed, 0x18);
