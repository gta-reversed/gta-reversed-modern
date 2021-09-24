/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimple.h"
#include "AnimBlendAssociation.h"
#include "Vector2D.h"

enum eDuckControlTypes : uint8
{
    DUCK_STANDALONE = 0,	// duck anim removed when task removed
    DUCK_STANDALONE_WEAPON_CROUCH,// duck anim removed when task removed
    DUCK_TASK_CONTROLLED,	// duck directly linked to a controlling task
    DUCK_ANIM_CONTROLLED,	// duck linked to duck anim (make duck partial?)
    DUCK_SCRIPT_CONTROLLED,
};

class CTaskSimpleDuck : public CTaskSimple {
public:
    uint32 m_nStartTime;
    uint16 m_nLengthOfDuck;
    int16 m_nShotWhizzingCounter;
    CAnimBlendAssociation *m_pDuckAnim; 
    CAnimBlendAssociation *m_pMoveAnim;
  
    bool m_bIsFinished;

    bool m_bIsAborting;
    bool m_bNeedToSetDuckFlag; // incase bIsDucking flag gets cleared elsewhere, so we know to stop duck task
    bool m_bIsInControl;	// if duck task is being controlled by another task then it requires continuous control
  
    CVector2D m_vecMoveCommand; 
    uint8 m_nDuckControlType;
    uint8 m_nCountDownFrames;

    CTaskSimpleDuck * Constructor (eDuckControlTypes DuckControlType, uint16 nLengthOfDuck, int16 nUseShotsWhizzingEvents = -1);
    static bool CanPedDuck(CPed* pPed);
    bool ControlDuckMove(float moveSpeedX, float moveSpeedY);
    bool IsTaskInUseByOtherTasks(); 
};

VALIDATE_SIZE(CTaskSimpleDuck, 0x28);
