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
    SWIM_TREAD,
    SWIM_SPRINT,
    SWIM_SPRINTING,
    SWIM_DIVE_UNDERWATER,
    SWIM_UNDERWATER_SPRINTING,
    SWIM_BACK_TO_SURFACE
};

class CPed;

class  CTaskSimpleSwim : public CTaskSimple {
protected:
    CTaskSimpleSwim(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    bool m_bFinishedBlending;
    bool m_bAnimBlockRefAdded;
    eSwimState m_nSwimState;
    int m_AnimID;
    float m_fAnimSpeed;
    CVector m_vecPos;
    CPed *m_pPed;
    float flt_24; // initialized with 0.0f
    float flt_28; // and used 
    float flt_2C; // for
    float flt_30; // internal
    float flt_34; //calculations
    CEntity *m_pEntity;
    CVector m_pClimbPos;
    float m_fAngle;
    unsigned char m_nSurfaceType;
private:
    char _pad[3];
public:
    float flt_50; // initialized with 0.0f
    float flt_54; // and used  for internal calculations
    int m_nProcessTimeCounter;
    FxSystem_c *m_pFxSystem;
    bool m_bTriggerWaterSplash;
    char pad2[3];
    
    CTaskSimpleSwim(CVector const* pPosn, CPed* pPed);
};

VALIDATE_SIZE(CTaskSimpleSwim, 0x64);
