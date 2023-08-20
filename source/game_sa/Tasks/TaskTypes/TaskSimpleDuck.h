/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "Vector2D.h"
class CAnimBlendAssociation;

enum eDuckControlTypes : uint8 {
    DUCK_STANDALONE = 0,           // duck anim removed when task removed
    DUCK_STANDALONE_WEAPON_CROUCH, // duck anim removed when task removed
    DUCK_TASK_CONTROLLED,          // duck directly linked to a controlling task
    DUCK_ANIM_CONTROLLED,          // duck linked to duck anim (make duck partial?)
    DUCK_SCRIPT_CONTROLLED,
};

class CTaskSimpleDuck : public CTaskSimple {
public:
    uint32                 m_nStartTime;
    uint16                 m_nLengthOfDuck;
    int16                  m_nShotWhizzingCounter;
    CAnimBlendAssociation* m_pDuckAnim;
    CAnimBlendAssociation* m_pMoveAnim;

    bool m_bIsFinished;
    bool m_bIsAborting;
    bool m_bNeedToSetDuckFlag;  // in case bIsDucking flag gets cleared elsewhere, so we know to stop duck task
    bool m_bIsInControl;        // if duck task is being controlled by another task then it requires continuous control

    CVector2D         m_vecMoveCommand;
    eDuckControlTypes m_nDuckControlType;
    uint8             m_nCountDownFrames;

public:
    static constexpr auto Type = TASK_SIMPLE_DUCK;

    CTaskSimpleDuck(eDuckControlTypes DuckControlType, uint16 nLengthOfDuck, int16 nUseShotsWhizzingEvents = -1);
    ~CTaskSimpleDuck() override;

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override { return new CTaskSimpleDuck(m_nDuckControlType, m_nLengthOfDuck, m_nShotWhizzingCounter); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;

    static bool CanPedDuck(CPed* ped);

    bool ControlDuckMove(float moveSpeedX, float moveSpeedY);
    bool ControlDuckMove(CVector2D moveSpeed) { return ControlDuckMove(moveSpeed.x, moveSpeed.y); }
    bool IsTaskInUseByOtherTasks();
    void ForceStopMove();
    void SetDuckTimer(uint16 lengthOfDuck); // 0x692530

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleDuck* Constructor(eDuckControlTypes DuckControlType, uint16 nLengthOfDuck, int16 nUseShotsWhizzingEvents = -1);
    CTaskSimpleDuck* Destructor();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};
VALIDATE_SIZE(CTaskSimpleDuck, 0x28);
