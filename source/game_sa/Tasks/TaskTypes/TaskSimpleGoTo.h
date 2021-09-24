#pragma once
#include "CTaskSimple.h"
#include "CVector.h"

class CTaskSimpleGoTo : public CTaskSimple
{
public:
    int32     m_moveState;
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
private:
    uint8 field_1D[3]; // padding
public:
    static float& ms_fLookAtThresholdDotProduct;
    static void InjectHooks();

    CTaskSimpleGoTo(int32 moveState, const CVector& targetPoint, float fRadius);
    CTaskSimpleGoTo* Constructor(int32 moveState, const CVector& targetPoint, float fRadius);
    ~CTaskSimpleGoTo();

    bool HasCircledTarget(CPed* pPed);
    void SetUpIK(CPed* pPed);
    void QuitIK(CPed* pPed);
};

VALIDATE_SIZE(CTaskSimpleGoTo, 0x20);