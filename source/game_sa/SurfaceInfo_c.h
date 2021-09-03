#pragma once

enum eAdhesionGroup {
    ADHESION_GROUP_RUBBER = 0,
    ADHESION_GROUP_HARD,
    ADHESION_GROUP_ROAD,
    ADHESION_GROUP_LOOSE,
    ADHESION_GROUP_SAND,
    ADHESION_GROUP_WET,
};

enum eFrictionEffect {
    FRICTION_EFFECT_NONE = 0,
    FRICTION_EFFECT_SPARKS,
    FRICTION_EFFECT_MORE // not sure what this is, but it's probably not used
};

#pragma pack(push, 1)
class SurfaceInfo_c {
public:
    char tyreGrip;
    char wetGrip;
    char _pad[2];
    union {
        struct {
            uint32 ucAdhesionGroup : 3;
            uint32 ucSkidmarkType : 2;
            uint32 ucFrictionEffect : 3;

            uint32 ucBulletFX : 3;
            uint32 bIsSoftLand : 1;
            uint32 bIsSeeThrough : 1;
            uint32 bIsShootThrough : 1;
            uint32 bIsSand : 1;
            uint32 bIsWater : 1;

            uint32 bIsShallowWater : 1;
            uint32 bIsBeach : 1;
            uint32 bIsSteepSlope : 1;
            uint32 bIsGlass : 1;
            uint32 bIsStairs : 1;
            uint32 bIsSkateable : 1;
            uint32 bIsPavement : 1;
            uint32 ucRoughness : 2;
            uint32 ucFlammability : 2;
            uint32 bCreatesSparks : 1;
            uint32 bCantSprintOn : 1;
            uint32 bLeavesFootsteps : 1;
            uint32 bProducesFootDust : 1;
            uint32 bMakesCarDirty : 1;

            uint32 bMakesCarClean : 1;
            uint32 bCreatesWheelGrass : 1;
            uint32 bCreatesWheelGravel : 1;
            uint32 bCreatesWheelMud : 1;
            uint32 bCreatesWheelDust : 1;
            uint32 bCreatesWheelSand : 1;
            uint32 bCreatesWheelSpray : 1;
            uint32 bCreatesPlants : 1;

            uint32 bCreatesObjects : 1;
            uint32 bCanClimb : 1;
            uint32 bIsAudioConcrete : 1;
            uint32 bIsAudioGrass : 1;
            uint32 bIsAudioSand : 1;
            uint32 bIsAudioGravel : 1;
            uint32 bIsAudioWood : 1;
            uint32 bIsAudioWater : 1;

            uint32 bIsAudioMetal : 1;
            uint32 bIsAudioLongGrass : 1;
            uint32 bIsAudioTile : 1;
            uint32 bPad : 13;
        };
        uint32 m_nFlags1;
        uint32 m_nFlags2;
    };
};
#pragma pack(pop)

VALIDATE_SIZE(SurfaceInfo_c, 0xC);
