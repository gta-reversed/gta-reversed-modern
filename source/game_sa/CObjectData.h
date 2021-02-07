/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

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

enum eObjectFxType : unsigned char
{
    NO_FX,
    PLAY_ON_HIT,
    PLAY_ON_DESTROYED,
    PLAY_ON_HIT_DESTROYED
};

enum eObjectBreakMode : unsigned int
{
    NOT_BY_GUN,
    BY_GUN,
    SMASHABLE,
};

enum eObjectCameraAvoidType : unsigned char
{
    CAMERA_IGNORE = 0,
    CAMERA_COLLIDE = 1,
    CAMERA_UNKNOWN = 2,
};

class  CObjectData {
public:
	float         m_fMass;
	float         m_fTurnMass;
	float         m_fAirResistance;
	float         m_fElasticity;
	float         m_fBuoyancyConstant;
	float         m_fUprootLimit;
	float         m_fColDamageMultiplier;
	unsigned char m_nColDamageEffect; // see eObjectColDamageEffect
	unsigned char m_nSpecialColResponseCase; // see eObjectSpecialColResponseCases
	unsigned char m_nCameraAvoidObject; // see eObjectCameraAvoidType
	unsigned char m_bCausesExplosion;
    unsigned char m_nFxType; // see eObjectFxType
	CVector       m_vFxOffset;
    FxSystemBP_c *m_pFxSystemBP;
	float         m_fSmashMultiplier;
	CVector       m_vecBreakVelocity;
	float         m_fBreakVelocityRand;
    unsigned int  m_nGunBreakMode; // see eObjectBreakMode
	unsigned int  m_nSparksOnImpact;

public:
    static constexpr int NUM_OBJECT_INFOS = 160;
    static CObjectData(&ms_aObjectInfo)[NUM_OBJECT_INFOS];

public:
    static void InjectHooks();

    static void Initialise(char* fileName, bool bUnused);
    static void SetObjectData(int dwModelIndex, CObject& pObject);

    bool operator==(CObjectData const& right) const;

public:
    inline static CObjectData& GetAtIndex(int dwIndex) { return ms_aObjectInfo[dwIndex]; }
    inline static constexpr CObjectData& GetDefault() { return ms_aObjectInfo[0]; }
};

VALIDATE_SIZE(CObjectData, 0x50);
