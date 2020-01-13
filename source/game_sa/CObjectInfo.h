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

enum eObjectColDamageEffect : unsigned char
{
    COL_DAMAGE_EFFECT_NONE = 0,
    COL_DAMAGE_EFFECT_CHANGE_MODEL = 1,
    COL_DAMAGE_EFFECT_SMASH_COMPLETELY = 20,
    COL_DAMAGE_EFFECT_CHANGE_THEN_SMASH = 21,
    COL_DAMAGE_EFFECT_BREAKABLE = 200,
    COL_DAMAGE_EFFECT_BREAKABLE_REMOVED = 202 // (ie.never regenerated after destroyed)
};

enum eObjectSpecialColResponseCases : unsigned char
{
    COL_SPECIAL_RESPONSE_NONE = 0,
    COL_SPECIAL_RESPONSE_LAMPOST,
    COL_SPECIAL_RESPONSE_SMALLBOX,
    COL_SPECIAL_RESPONSE_BIGBOX,
    COL_SPECIAL_RESPONSE_FENCEPART,
    COL_SPECIAL_RESPONSE_GRENADE,
    COL_SPECIAL_RESPONSE_SWINGDOOR,
    COL_SPECIAL_RESPONSE_LOCKDOOR,
    COL_SPECIAL_RESPONSE_HANGING,
    COL_SPECIAL_RESPONSE_OB_COL_POOLBALL,
};

class  CObjectInfo {
public:
	float          m_fMass;
	float          m_fTurnMass;
	float          m_fAirResistance;
	float          m_fElasticity;
	float          m_fBuoyancyConstant;
	float          m_fUprootLimit;
	float          m_fColDamageMultiplier;
	unsigned char  m_nColDamageEffect; // see eObjectColDamageEffect
	unsigned char  m_nSpecialColResponseCase; // see eObjectSpecialColResponseCases
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