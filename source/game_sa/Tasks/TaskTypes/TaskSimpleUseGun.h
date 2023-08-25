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
    bool m_bIsFinished;
    bool m_bIsInControl;
    bool m_bMoveControl;
    bool m_bFiredGun;
    bool m_bBlockedLOS;
    union {
        uint8 m_nFireGunThisFrame;
        struct {
            uint8 bRightHand : 1;
            uint8 bLefttHand : 1;
        };
    };
    bool m_bSkipAim;

    eGunCommand m_nNextCommand;
    eGunCommand m_nLastCommand; // active command
    CVector2D m_vecMoveCommand;
    CEntity* m_pTarget;
    CVector m_vecTarget;

    CAnimBlendAssociation* m_pAnim;

    CWeaponInfo* m_pWeaponInfo;
    uint16 m_nBurstLength;
    uint16 m_nBurstShots;

    uint8 m_nCountDownFrames;
    bool m_ArmIKInUse;
    bool m_LookIKInUse;
    bool m_bAimImmediate;

public:
    static constexpr auto Type = TASK_SIMPLE_USE_GUN;

    CTaskSimpleUseGun(CEntity* targetEntity, CVector vecTarget = {}, eGunCommand nCommand = eGunCommand::AIM, uint16 nBurstLength = 1, bool bAimImmediate = false);
    ~CTaskSimpleUseGun() override;

    CTask* Clone() const override { return new CTaskSimpleUseGun(m_pTarget, m_vecTarget, m_nLastCommand, m_nBurstLength, m_bAimImmediate); }
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

    auto GetLastGunCommand() const { return (eGunCommand)m_nLastCommand; }

#if ANDROID
    void CreateTask();
    void Serialize();
#endif

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleUseGun* Constructor(CEntity* targetEntity, CVector vecTarget, eGunCommand nCommand, uint16 nBurstLength = 1, bool bAimImmediate = false);
};

VALIDATE_SIZE(CTaskSimpleUseGun, 0x3C);

