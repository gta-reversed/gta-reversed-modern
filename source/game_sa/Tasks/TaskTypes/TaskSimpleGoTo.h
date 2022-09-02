#pragma once

#include "TaskSimple.h"
#include "Vector.h"

class CTaskSimpleGoTo : public CTaskSimple {
public:
    int32   m_moveState;
    CVector m_vecTargetPoint;
    float   m_fRadius;
    union {
        struct 
        {
            uint8 m_b01 : 1;
            uint8 m_b02 : 1;
            uint8 m_b03 : 1;
            uint8 m_b04 : 1;
            uint8 m_bIsIKChainSet : 1;
            uint8 m_bTargetPointUpdated : 1;
        } gotoFlags;
        uint8 m_GoToFlags;
    };

    static float& ms_fLookAtThresholdDotProduct;

public:
    CTaskSimpleGoTo(int32 moveState, const CVector& targetPoint, float fRadius);
    ~CTaskSimpleGoTo() override = default; // 0x667A00

    bool HasCircledTarget(CPed* ped);
    void SetUpIK(CPed* ped);
    void QuitIK(CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    // 0x6679C0
    auto Constructor(eMoveState moveState, const CVector& targetPoint, float fRadius) {
        this->CTaskSimpleGoTo::CTaskSimpleGoTo(moveState, targetPoint, fRadius);
        return this;
    }
};

VALIDATE_SIZE(CTaskSimpleGoTo, 0x20);