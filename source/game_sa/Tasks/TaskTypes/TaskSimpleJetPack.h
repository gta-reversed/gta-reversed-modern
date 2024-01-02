/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "Vector.h"
class CAnimBlendAssociation;
class CFxSystem;

class CPed;
class CPlayerPed;

class CTaskSimpleJetPack : public CTaskSimple {
public:
    bool m_bIsFinished;
    bool m_bAddedIdleAnim;
    bool m_bAnimsReferenced;
    bool m_bAttackButtonPressed;
    bool m_bSwitchedWeapons;

    char  m_nThrustStop;
    char  m_nThrustFwd;
    float m_fThrustStrafe;
    float m_fThrustAngle;

    float m_fLegSwingFwd;
    float m_fLegSwingSide;
    float m_fLegTwist;

    float m_fLegSwingFwdSpeed;
    float m_fLegSwingSideSpeed;
    float m_fLegTwistSpeed;

    CVector m_vecOldSpeed;
    float   m_fOldHeading;

    RpClump*               m_pJetPackClump;
    CAnimBlendAssociation* m_pAnim;

    CVector      m_vecTargetPos;
    float        m_fCruiseHeight;
    int32        m_nHoverTime;
    uint32       m_nStartHover;
    CEntity*     m_pTargetEnt;

    FxSystem_c* m_pFxSysL;
    FxSystem_c* m_pFxSysR;
    float       m_fxKeyTime;

    static float& THRUST_NOMINAL;         // 0.8f
    static float& THRUST_FULL;            // 0.6f
    static float& THRUST_STRAFE;          // 0.3f
    static float& THRUST_STOP;            // 0.5f
    static float& THRUST_MAX_ANGLE;       // 1.309f
    static float& THRUST_MOVE_DAMPING;    // 0.02f
    static float& JETPACK_TURN_RATE;      // -0.05f
    static float& JETPACK_ANGLE_RATE;     // 0.9f
    static float& LEG_SWING_MAX_ANGLE;    // 0.7854f
    static float& LEG_SWING_DELTA_V_MULT; // -0.2f
    static float& LEG_SWING_GRAVITY_MULT; // 0.01f
    static float& LEG_SWING_DAMP_FRAC;    // 0.98f

public:
    static constexpr auto Type = TASK_SIMPLE_JETPACK;


    CTaskSimpleJetPack(const CVector* pVecTargetPos = nullptr, float fCruiseHeight = 10.0f, int32 nHoverTime = 0, CEntity* entity = nullptr);
    CTaskSimpleJetPack* Constructor(const CVector* pVecTargetPos, float fCruiseHeight, int32 nHoverTime, CEntity* entity);
    ~CTaskSimpleJetPack() override;

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;

    void RenderJetPack(CPed* ped);
    void ProcessThrust(CPed* ped);
    void ProcessAnims(CPed* ped);
    void ProcessControlInput(CPlayerPed* player);
    void ApplyRollAndPitch(CPed* ped);
    void DropJetPack(CPed* ped);
    void DoJetPackEffect(CPed* ped);

    static void InjectHooks();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    CTask*  Clone_Reversed() const;
};
VALIDATE_SIZE(CTaskSimpleJetPack, 0x70);

static constexpr CVector JETPACK_POS_OFFSET = { 0.1f, 0.08f, 0.0f };
static constexpr CVector JETPACK_ROT_AXIS   = { 0.0f, 1.0f, 0.0f };
