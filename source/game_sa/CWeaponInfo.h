/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "eWeaponFlags.h"
#include "eWeaponType.h"
#include "eWeaponFire.h"
#include "CVector.h"

#define MAX_WEAPON_INFOS 80
#define MAX_WEAPON_NAMES 50

#define WEAPONINFO_NUM_WEAPONS_WITH_SKILLS 11
#define WEAPONINFO_NUM_WEAPONS 46

enum eWeaponSkill
{
	WEAPSKILL_POOR,
	WEAPSKILL_STD,
	WEAPSKILL_PRO,
	WEAPSKILL_COP
};

class CWeaponInfo {
public:
    /* some info here https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CWeaponInfoSA.h */
    unsigned int   m_nWeaponFire; // see eWeaponFire
    float          m_fTargetRange; // max targeting range
    float          m_fWeaponRange; // absolute gun range / default melee attack range
    int            m_nModelId1; // modelinfo id
    int            m_nModelId2; // second modelinfo id
    unsigned int   m_nSlot;
    struct {
        unsigned int bCanAim : 1;
        unsigned int bAimWithArm : 1;
        unsigned int b1stPerson : 1;
        unsigned int bOnlyFreeAim : 1;
        unsigned int bMoveAim : 1; // can move when aiming
        unsigned int bMoveFire : 1; // can move when firing
        unsigned int b06 : 1; // this bitfield is not used
        unsigned int b07 : 1; // this bitfield is not used
        unsigned int bThrow : 1;
        unsigned int bHeavy : 1; // can't run fast with this weapon
        unsigned int bContinuosFire : 1;
        unsigned int bTwinPistol : 1;
        unsigned int bReload : 1; // this weapon can be reloaded
        unsigned int bCrouchFire : 1; // can reload when crouching
        unsigned int bReload2Start : 1; // reload directly after firing
        unsigned int bLongReload : 1;
        unsigned int bSlowdown : 1;
        unsigned int bRandSpeed : 1;
        unsigned int bExpands : 1;
    }              m_nFlags;
	unsigned int   m_dwAnimGroup; // instead of storing pointers directly to anims, use anim association groups
	unsigned short m_nAmmoClip; // ammo in one clip
	unsigned short m_nDamage; // damage inflicted per hit
	CVector        m_vecFireOffset; // offset from weapon origin to projectile starting point
	unsigned int   m_nSkillLevel; // what's the skill level of this weapontype
	unsigned int   m_nReqStatLevel; // what stat level is required for this skill level
	float          m_fAccuracy; // modify accuracy of weapon
	float          m_fMoveSpeed; // how fast can move with weapon
	float          m_fAnimLoopStart; // start of animation loop
	float          m_fAnimLoopEnd; // end of animation loop
	unsigned int   m_nAnimLoopFire; // time in animation when weapon should be fired
	unsigned int   m_nAnimLoop2Start; // start of animation2 loop
	unsigned int   m_nAnimLoop2End; // end of animation2 loop
	unsigned int   m_nAnimLoop2Fire; // time in animation2 when weapon should be fired
	float          m_fBreakoutTime; // time after which player can break out of attack and run off
	float          m_fSpeed; // speed of projectile
	float          m_fRadius; // radius affected
	float          m_fLifespan; // time taken for shot to dissipate
	float          m_fSpread; // angle inside which shots are created
	unsigned short m_nAimOffsetIndex; // index into array of aiming offsets
	unsigned char  m_nBaseCombo; // base combo for this melee weapon
	unsigned char  m_nNumCombos; // how many further combos are available

	// functions
	CWeaponInfo();
	~CWeaponInfo();

	// static variables

	// weapon names array. Count: MAX_WEAPON_NAMES(50)
	static char **ms_aWeaponNames;

	// static functions

	// load weapon data file
	static void LoadWeaponData();
	// get weapon info for this type and with this skill
	static CWeaponInfo *GetWeaponInfo(eWeaponType weaponType, unsigned char skill);
	// get weapon type by name
	static eWeaponType FindWeaponType(char *name);
	// get weapon fire type by name
	static eWeaponFire FindWeaponFireType(char *name);
	// initialisation
	static void Initialise();
	// closing
	static void Shutdown();
};

VALIDATE_SIZE(CWeaponInfo, 0x70);

// list of weapon infos. Count: MAX_WEAPON_INFOS (80)
extern CWeaponInfo *aWeaponInfo;