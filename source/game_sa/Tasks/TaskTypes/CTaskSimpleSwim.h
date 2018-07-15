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

class  CTaskSimpleSwim : public CTaskSimple {
protected:
    CTaskSimpleSwim(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    bool m_bFinishedBlending; // 8
    bool m_bAnimBlockRefAdded; // 9
    eSwimState m_nSwimState; // 10
    int m_AnimID; // pThis + 12
    float m_fAnimSpeed;// 16
    CVector m_vecPos; // 20
    CPed *m_pPed; // 32
    float flt_24; // initialized with 0.0f 36
    float flt_28; // and used 40
    float flt_2C; // for 44
    float flt_30; // internal 48
    float flt_34; //calculations 52
    CEntity *m_pEntity; // pThis + 56
    CVector m_pClimbPos;// pThis + 60
    float m_fAngle; // 72
    unsigned char m_nSurfaceType; // 76
private:
    char _pad[3]; // 77
public:
    float flt_50; // initialized with 0.0f  |  pThis+80
    float flt_54; // and used  for internal calculations | pThis+84
    int m_nProcessTimeCounter; // 88
    FxSystem_c *m_pFxSystem; // 92
    bool m_bTriggerWaterSplash; // 96
    char pad2[3]; // 97
    // 100 = 0x64

    static bool &CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE;
    CTaskSimpleSwim(CVector const* pPosn, CPed* pPed);
    void ProcessSwimAnims(CPed *pPed);
};

VALIDATE_SIZE(CTaskSimpleSwim, 0x64);
