/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "Vector.h"
#include "Vector2D.h"
#include "TaskSimpleGunControl.h"

class CWeaponInfo;
class CAnimBlendAssociation;
class CEntity;

class NOTSA_EXPORT_VTABLE CTaskSimpleUseGun : public CTaskSimple {
public:
    static constexpr auto Type = TASK_SIMPLE_USE_GUN;

    CTaskSimpleUseGun(CEntity* targetEntity, CVector vecTarget = {}, eGunCommand nCommand = eGunCommand::AIM, uint16 nBurstLength = 1, bool bAimImmediate = false);
    ~CTaskSimpleUseGun() override;

    CTask* Clone() const override { return new CTaskSimpleUseGun(m_TargetEntity, m_TargetPos, m_LastCmd, m_BurstLength, m_IsAimImmediate); }
    eTaskType GetTaskType() const override { return Type; };
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    void AbortIK(CPed* ped);
    void AimGun(CPed* ped);

    int32 SkipAim(CPed* ped);
    int32 ClearAnim(CPed* ped);

    bool ControlGun(CPed* ped, CEntity* target, eGunCommand cmd);
    bool ControlGunMove(const CVector2D& moveSpeed);

    void FinishGunAnimCB(CAnimBlendAssociation* anim, void* data);

    void FireGun(CPed* ped, bool);
    bool PlayerPassiveControlGun();
    void RemoveStanceAnims(CPed* ped, float);
    static bool RequirePistolWhip(CPed* ped, CEntity* entity);
    void Reset(CPed* ped, CEntity* entity, CVector posn, int8 unused, int16 burstAmmoCnt);

    void SetMoveAnim(CPed* ped);
    void StartAnim(CPed* ped);
    void StartCountDown(uint8, bool);

    auto GetLastGunCommand() const { return m_LastCmd; }

#if ANDROID
    void CreateTask();
    void Serialize();
#endif

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleUseGun* Constructor(CEntity* targetEntity, CVector vecTarget, eGunCommand nCommand, uint16 nBurstLength = 1, bool bAimImmediate = false);

public:
    bool m_IsFinished;
    bool m_IsInControl;
    bool m_HasMoveControl;
    bool m_HasFiredGun;
    bool m_IsLOSBlocked;

    union {
        uint8 m_FireGunThisFrame;
        struct {
            uint8 bRightHand : 1;
            uint8 bLefttHand : 1;
        };
    };

    bool m_SkipAim;

    eGunCommand  m_NextCmd;
    eGunCommand  m_LastCmd; // active command
    CVector2D    m_MoveCmd;
    CEntity::Ref m_TargetEntity;
    CVector      m_TargetPos;

    CAnimBlendAssociation* m_Anim;

    CWeaponInfo* m_WeaponInfo;
    uint16       m_BurstLength;
    uint16       m_BurstShots;

    uint8 m_CountDownFrames;
    bool  m_IsArmIKInUse;
    bool  m_IsLookIKInUse;
    bool  m_IsAimImmediate;
};
VALIDATE_SIZE(CTaskSimpleUseGun, 0x3C);
