/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CVector.h"
#include "FxSystem_c.h"

enum eSwimState : unsigned short
{
    SWIM_TREAD = 0,
    SWIM_SPRINT = 1,
    SWIM_SPRINTING = 2,
    SWIM_DIVE_UNDERWATER = 3,
    SWIM_UNDERWATER_SPRINTING = 4,
    SWIM_BACK_TO_SURFACE = 5
};

class CPed;
class CPlayerPed;

class  CTaskSimpleSwim : public CTaskSimple {
public:
    bool m_bFinishedBlending;
    bool m_bAnimBlockRefAdded;
    eSwimState m_nSwimState;
    int m_AnimID; 
    float m_fAnimSpeed;
    CVector m_vecPos;
    CPed *m_pPed; 
    float m_fRotationX;  // updated all the time. 
    float m_fTurningRotationY; // updated when ped is turning.
    float m_fUpperTorsoRotationX; //  updated when ped diving or coming back to surface
    float m_fAimingRotation; // The direction that the ped is facing. Updated all the time.
    float m_fStateChanger; // It is is normally 0, but updated when changing swimming states. 
    CEntity *m_pEntity;
    CVector m_pClimbPos;
    float m_fAngle;
    unsigned char m_nSurfaceType;
private:
    char _pad[3]; 
public:
    float m_fRandomMoveBlendRatio; // Used in CTaskSimpleSwim::ProcessControlAI
    float m_fSwimStopTime;
    unsigned int m_nTimeStep;
    FxSystem_c *m_pFxSystem; 
    bool m_bTriggerWaterSplash;
    char pad2[3];

    static float &SWIM_DIVE_UNDER_ANGLE;
    static float &SWIM_STOP_TIME;

    static void InjectHooks();
    CTaskSimpleSwim(CVector* pPosition, CPed* pPed);
    ~CTaskSimpleSwim();
private:
    CTaskSimpleSwim* Constructor(CVector* pPosition, CPed* pPed);
public:
    // original virtual functions
    CTask* Clone() override;
    eTaskType GetId() override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed *pPed) override;

    // reversed virtual functions
    CTask* Clone_Reversed();
    eTaskType GetId_Reversed() { return TASK_SIMPLE_SWIM; };
    bool ProcessPed_Reversed(CPed* pPed);
    bool MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event);

    void ApplyRollAndPitch(CPed* pPed);
    void ProcessSwimAnims(CPed *pPed);
    void ProcessSwimmingResistance(CPed*pPed);
    void ProcessEffects(CPed*pPed);
    void ProcessControlAI(CPed*pPed);
    void ProcessControlInput(CPlayerPed* pPed);
    void CreateFxSystem(CPed* pPed, RwMatrixTag* pRwMatrix);
    void DestroyFxSystem();
};

VALIDATE_SIZE(CTaskSimpleSwim, 0x64);
