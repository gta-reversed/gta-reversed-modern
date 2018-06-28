/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "FxSystem_c.h"

class  CObjectInfo {
public:
	float          m_fMass;
	float          m_fTurnMass;
	float          m_fAirResistance;
	float          m_fElasticity;
	float          m_fBuoyancyConstant;
	float          m_fUprootLimit;
	float          m_fColDamageMultiplier;
	unsigned char  m_nColDamageEffect;
	unsigned char  m_nSpecialColResponseCase;
	unsigned char  m_nCameraAvoidObject;
	unsigned char  m_bCausesExplosion;
	unsigned char  m_nFxType;
	CVector        m_vFxOffset;
    FxSystem_c    *m_pFxSystem;
	float          m_fSmashMultiplier;
	CVector        m_vecBreakVelocity;
	float          m_fBreakVelocityRand;
	unsigned int   m_nGunBreakMode;
	unsigned int   m_nSparksOnImpact;
};

VALIDATE_SIZE(CObjectInfo, 0x50);