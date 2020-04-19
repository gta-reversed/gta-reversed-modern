#pragma once
#include "CTaskSimple.h"
#include "CVector.h"

class CTaskSimpleGoTo : public CTaskSimple
{
public:
    int     m_moveState;
    CVector m_vecTargetPoint;
    float   m_fRadius;
    union {
        struct 
        {
            unsigned char m_b01 : 1;
            unsigned char m_b02 : 1;
            unsigned char m_b03 : 1;
            unsigned char m_b04 : 1;
            unsigned char m_bIsIKChainSet : 1;
            unsigned char m_bTargetPointUpdated : 1;
        } gotoFlags;
        unsigned char m_GoToFlags;
    };
private:
    unsigned char field_1D[3]; // padding
public:
    static float& ms_fLookAtThresholdDotProduct;
    static void InjectHooks();

    CTaskSimpleGoTo(int moveState, const CVector& targetPoint, float fRadius);
    CTaskSimpleGoTo* Constructor(int moveState, const CVector& targetPoint, float fRadius);
    ~CTaskSimpleGoTo();

    bool HasCircledTarget(CPed* pPed);
    void SetUpIK(CPed* pPed);
    void QuitIK(CPed* pPed);
};

VALIDATE_SIZE(CTaskSimpleGoTo, 0x20);