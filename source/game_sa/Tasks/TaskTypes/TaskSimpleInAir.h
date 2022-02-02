/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimple.h"
#include "TaskTimer.h"
#include "Vector.h"
#include "AnimBlendAssociation.h"
#include "Entity.h"

class CTaskSimpleInAir : public CTaskSimple {
public:
    CVector m_vecPosn;
    float m_fAngle;
    uint8 m_nSurfaceType;
    char _pad[3];
    CAnimBlendAssociation* m_pAnim;
    float m_fMinZSpeed;
    union {
        uint8 m_nFlags;
        struct
        {
            uint8 bUsingJumpGlide : 1;
            uint8 bUsingFallGlide : 1;
            uint8 bUsingClimbJump : 1;
        };
    };
    char _pad2[3];
    uint32 m_nProcessCounter;
    CTaskTimer m_timer;
    CEntity* m_pClimbEntity;
private:
    CTaskSimpleInAir* Constructor(bool bUsingJumpGlide, bool bUsingFallGlide, bool bUsingClimbJump);
public:
    CTaskSimpleInAir(bool bUsingJumpGlide, bool bUsingFallGlide, bool bUsingClimbJump);
    ~CTaskSimpleInAir() override;

    static void InjectHooks();

    CTask* Clone() override { return new CTaskSimpleInAir(bUsingJumpGlide, bUsingFallGlide, bUsingClimbJump); }
    eTaskType GetTaskType() override { return TASK_SIMPLE_IN_AIR; }
    bool ProcessPed(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

    bool ProcessPed_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);

    static void DeleteAnimCB(CAnimBlendAssociation* pAnim, void* data);

    static float ms_fSlowFallThreshold; // 0x8D2EFC
    static uint32 ms_nMaxSlowFallFrames; // 0x8D2EF8
};

VALIDATE_SIZE(CTaskSimpleInAir, 0x3C);
