/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

#include "AnimationEnums.h"
#include "eWeaponFlags.h"
#include "eWeaponType.h"
#include "eWeaponSkill.h"
#include "eWeaponFire.h"

#define MAX_WEAPON_INFOS 80
#define MAX_WEAPON_NAMES 50

#define WEAPONINFO_NUM_WEAPONS_WITH_SKILLS 11
#define WEAPONINFO_NUM_WEAPONS 46

class CWeaponInfo {
public:
    /* some info here https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CWeaponInfoSA.h */
    eWeaponFire m_nWeaponFire;  // see eWeaponFire
    float       m_fTargetRange; // max targeting range
    float       m_fWeaponRange; // absolute gun range / default melee attack range
    int32       m_nModelId1;    // modelinfo id
    int32       m_nModelId2;    // second modelinfo id
    uint32      m_nSlot;
    union {
        struct {
            uint32 bCanAim : 1;
            uint32 bAimWithArm : 1;
            uint32 b1stPerson : 1;
            uint32 bOnlyFreeAim : 1;
            uint32 bMoveAim : 1;  // can move when aiming
            uint32 bMoveFire : 1; // can move when firing
            uint32 b07 : 1;       // this bitfield is not used
            uint32 b08 : 1;       // this bitfield is not used

            uint32 bThrow : 1;
            uint32 bHeavy : 1; // can't run fast with this weapon
            uint32 bContinuosFire : 1;
            uint32 bTwinPistol : 1;
            uint32 bReload : 1;       // this weapon can be reloaded
            uint32 bCrouchFire : 1;   // can reload when crouching
            uint32 bReload2Start : 1; // reload directly after firing
            uint32 bLongReload : 1;

            uint32 bSlowdown : 1;
            uint32 bRandSpeed : 1;
            uint32 bExpands : 1;
        } flags;
        uint32 m_nFlags;
    };
    AssocGroupId m_eAnimGroup;      // instead of storing pointers directly to anims, use anim association groups
    uint16       m_nAmmoClip;       // ammo in one clip
    uint16       m_nDamage;         // damage inflicted per hit
    CVector      m_vecFireOffset;   // offset from weapon origin to projectile starting point
    uint32       m_nSkillLevel;     // what's the skill level of this weapontype
    uint32       m_nReqStatLevel;   // what stat level is required for this skill level
    float        m_fAccuracy;       // modify accuracy of weapon
    float        m_fMoveSpeed;      // how fast can move with weapon
    float        m_fAnimLoopStart;  // start of animation loop
    float        m_fAnimLoopEnd;    // end of animation loop
    uint32       m_nAnimLoopFire;   // time in animation when weapon should be fired
    uint32       m_nAnimLoop2Start; // start of animation2 loop
    uint32       m_nAnimLoop2End;   // end of animation2 loop
    uint32       m_nAnimLoop2Fire;  // time in animation2 when weapon should be fired
    float        m_fBreakoutTime;   // time after which player can break out of attack and run off
    float        m_fSpeed;          // speed of projectile
    float        m_fRadius;         // radius affected
    float        m_fLifespan;       // time taken for shot to dissipate
    float        m_fSpread;         // angle inside which shots are created
    uint16       m_nAimOffsetIndex; // index into array of aiming offsets
    uint8        m_nBaseCombo;      // base combo for this melee weapon
    uint8        m_nNumCombos;      // how many further combos are available

public:
    static void InjectHooks();

    // functions
    CWeaponInfo();
    ~CWeaponInfo();

    // static variables

    // weapon names array. Count: MAX_WEAPON_NAMES(50)
    static char **ms_aWeaponNames;

    AnimationId GetCrouchReloadAnimationID();

    // static functions

    // load weapon data file
    static void LoadWeaponData();
    // get weapon info for this type and with this skill
    static CWeaponInfo *GetWeaponInfo(eWeaponType weaponType, eWeaponSkill skill);
    // get weapon type by name
    static eWeaponType FindWeaponType(char *name);
    // get weapon fire type by name
    static eWeaponFire FindWeaponFireType(char *name);
    // initialisation
    static void Initialise();
    // closing
    static void Shutdown();

    static int32 GetSkillStatIndex(int32 weaponType);
};

VALIDATE_SIZE(CWeaponInfo, 0x70);

// list of weapon infos. Count: MAX_WEAPON_INFOS (80)
extern CWeaponInfo *aWeaponInfo;
