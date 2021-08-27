#pragma once

#include "CTaskSimple.h"
#include "CAccident.h"

class CTaskSimpleGiveCPR : public CTaskSimple {
public:
    union {
        struct {
            unsigned int bNoHealthValue : 1;
            unsigned int bAnimationFinished : 1;
        };
        unsigned int m_nFlags;
    };
    CAccident* m_pAccident;
    CAnimBlendAssociation* m_pAnim;
    float m_fInitialHealth;

public:
    CTaskSimpleGiveCPR(CAccident* pAccident);
    ~CTaskSimpleGiveCPR() override;

    eTaskType GetId() override { return TASK_SIMPLE_GIVE_CPR; }

    CTask* Clone() override;
    bool ProcessPed(CPed* ped) override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override;

    void ReviveDeadPed(CPed* ped);
    static void FinishGiveCPRAnimCB(CAnimBlendAssociation* pAnim, void* priv);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleGiveCPR* Constructor(CAccident* pAccident);

    CTask* Clone_Reversed();
    bool ProcessPed_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event);
};

VALIDATE_SIZE(CTaskSimpleGiveCPR, 0x18);
