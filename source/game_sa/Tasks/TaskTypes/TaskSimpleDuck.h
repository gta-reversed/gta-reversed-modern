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

enum eDuckControlType : uint8
{
    DUCK_STANDALONE = 0,	        // duck anim removed when task removed
    DUCK_STANDALONE_WEAPON_CROUCH,  // duck anim removed when task removed
    DUCK_TASK_CONTROLLED,	        // duck directly linked to a controlling task
    DUCK_ANIM_CONTROLLED,	        // duck linked to duck anim (make duck partial?)
    DUCK_SCRIPT_CONTROLLED,
};

class CTaskSimpleDuck : public CTaskSimple {
public:
    uint32 m_nStartTime = {};                 // 8
    uint16 m_nLengthOfDuck = {};              // 0xC
    int16 m_nShotWhizzingCounter = {};        // 0xE
    CAnimBlendAssociation* m_pDuckAnim = {};  // 0x10
    CAnimBlendAssociation* m_pMoveAnim = {};  // 0x14
    int8 m_bIsFinished = {};                  // 0x18
    int8 m_bIsAborting = {};                  // 0x19
    bool m_bNeedToSetDuckFlag = {true};       // 0x1A - In case ped->bIsDucking flag gets cleared elsewhere, so we know to stop duck task
    int8 m_bIsInControl = {true};             // 0x1B - If duck task is being controlled by another task then it requires continuous control
    CVector2D m_vecMoveCommand = {0.f, 0.f};  // 0x1C
    eDuckControlType m_nDuckControlType = {}; // 0x24
    int8 m_nCountDownFrames = {-1};           // 0x25

public:
    static constexpr auto Type = TASK_SIMPLE_DUCK;

    static void InjectHooks();

    CTaskSimpleDuck(eDuckControlType duckControlType, uint16 lengthOfDuck, int16 showWhizzingCounter);
    CTaskSimpleDuck(const CTaskSimpleDuck&); // NOTSA: `Clone()` helper
    ~CTaskSimpleDuck();

    static void DeleteDuckAnimCB(CAnimBlendAssociation* assoc, void* task);
    static bool CanPedDuck(CPed* ped);

    bool IsTaskInUseByOtherTasks();
    void AbortBecauseOfOtherDuck(CPed* ped); // May've been returning bool originally, unsure.
    void RestartTask(CPed* ped);
    void ControlDuckMove(CVector2D moveSpeed = {});
    void SetMoveAnim(CPed*);

    CTask* Clone() override { return new CTaskSimpleDuck{ *this }; }
    eTaskType GetTaskType() override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    bool ProcessPed(CPed* ped) override;

private: // Wrappers for hooks

// 0x691FC0
    CTaskSimpleDuck* Constructor(eDuckControlType duckControlType, int16 lengthOfDuck, int16 showWhizzingCounter) {
        this->CTaskSimpleDuck::CTaskSimpleDuck(duckControlType, lengthOfDuck, showWhizzingCounter);
        return this;
    }

    // 0x692030
    CTaskSimpleDuck* Destructor() {
        this->CTaskSimpleDuck::~CTaskSimpleDuck();
        return this;
    }

    CTask* Clone_Reversed() { return CTaskSimpleDuck::Clone(); }
    int32 GetTaskType_Reversed() { return CTaskSimpleDuck::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleDuck::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed* ped) { return CTaskSimpleDuck::ProcessPed(ped); }
}; 
VALIDATE_SIZE(CTaskSimpleDuck, 0x28);
