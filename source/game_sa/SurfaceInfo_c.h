#pragma once
#include "PluginBase.h"

enum eAdhesionGroup
{
    ADHESION_GROUP_RUBBER = 0,
    ADHESION_GROUP_HARD,
    ADHESION_GROUP_ROAD,
    ADHESION_GROUP_LOOSE,
    ADHESION_GROUP_SAND,
    ADHESION_GROUP_WET,
};

enum eFrictionEffect
{
    FRICTION_EFFECT_NONE = 0,
    FRICTION_EFFECT_SPARKS,
    FRICTION_EFFECT_MORE // not sure what this is, but it's probably not used
};

#pragma pack(push, 1)
class SurfaceInfo_c {
public:
    char tyreGrip;
    char wetGrip;
    __int16 pad;
    union {
        struct {
            unsigned int ucAdhesionGroup : 3;
            unsigned int ucSkidmarkType : 2;
            unsigned int ucFrictionEffect : 3;

            unsigned int ucBulletFX : 3;
            unsigned int bIsSoftLand : 1;
            unsigned int bIsSeeThrough : 1;
            unsigned int bIsShootThrough : 1;
            unsigned int bIsSand : 1;
            unsigned int bIsWater : 1;

            unsigned int bIsShallowWater : 1;
            unsigned int bIsBeach : 1;
            unsigned int bIsSteepSlope : 1;
            unsigned int bIsGlass : 1;
            unsigned int bIsStairs : 1;
            unsigned int bIsSkateable : 1;
            unsigned int bIsPavement : 1;
            unsigned int ucRoughness : 2;
            unsigned int ucFlammability : 2;
            unsigned int bCreatesSparks : 1;
            unsigned int bCantSprintOn : 1;
            unsigned int bLeavesFootsteps : 1;
            unsigned int bProducesFootDust : 1;
            unsigned int bMakesCarDirty : 1;

            unsigned int bMakesCarClean : 1;
            unsigned int bCreatesWheelGrass : 1;
            unsigned int bCreatesWheelGravel : 1;
            unsigned int bCreatesWheelMud : 1;
            unsigned int bCreatesWheelDust : 1;
            unsigned int bCreatesWheelSand : 1;
            unsigned int bCreatesWheelSpray : 1;
            unsigned int bCreatesPlants : 1;

            unsigned int bCreatesObjects : 1;
            unsigned int bCanClimb : 1;
            unsigned int bIsAudioConcrete : 1;
            unsigned int bIsAudioGrass : 1;
            unsigned int bIsAudioSand : 1;
            unsigned int bIsAudioGravel : 1;
            unsigned int bIsAudioWood : 1;
            unsigned int bIsAudioWater : 1;

            unsigned int bIsAudioMetal : 1;
            unsigned int bIsAudioLongGrass : 1;
            unsigned int bIsAudioTile : 1;
            unsigned int bPad : 13;
        };
        unsigned int m_nFlags1;
        unsigned int m_nFlags2;
    };
};
#pragma pack(pop)

VALIDATE_SIZE(SurfaceInfo_c, 0xC);
