/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"

enum class eVehicleComponentFlags : unsigned int {
    IS_VEH_STRUCT_PART = 0x00000001,
    IS_DAMAGEABLE = 0x00000002,
    IS_WHEEL = 0x00000004,
    IS_DUMMY = 0x00000008,
    IS_DOOR = 0x00000010,
    COMP_IS_LEFT = 0x00000020,
    COMP_IS_RIGHT = 0x00000040,
    COMP_IS_FRONT = 0x00000080,

    COMP_IS_REAR = 0x00000100,
    IS_EXTRA = 0x00000200,
    COMP_HAS_ALPHA = 0x00000400,
    COMP_IS_GLASS = 0x00000800,
    COMP_CULL = 0x00001000,
    COMP_IS_REAR_DOOR = 0x00002000,
    COMP_IS_FRONT_DOOR = 0x00004000,
    COMP_SWINGING = 0x00008000,

    IS_MAIN_WHEEL = 0x00010000,
    IS_UPGRADE = 0x00020000,
    COMP_DISABLE_REFLECTIONS = 0x00040000,
    TRAIN_FRONT_BOGIE = 0x00100000,
    TRAIN_REAR_BOGIE = 0x00200000,
    COMP_RENDER_ALWAYS = 0x00400000,
    UNKN_4 = 0x20000000,
};
struct tVehicleComponentFlagsUnion {
    union {
        unsigned int m_nFlags;
        struct {
            unsigned int bIsVehStructPart : 1;
            unsigned int bIsDamageable : 1;
            unsigned int bIsWheel : 1;
            unsigned int bIsDummy : 1;
            unsigned int bIsDoor : 1;
            unsigned int bIsLeft : 1;
            unsigned int bIsRight : 1;
            unsigned int bIsFront : 1;

            unsigned int bIsRear : 1;
            unsigned int bIsExtra : 1;
            unsigned int bHasAlpha : 1;
            unsigned int bIsGlass : 1;
            unsigned int bCull : 1;
            unsigned int bIsRearDoor : 1;
            unsigned int bIsFrontDoor : 1;
            unsigned int bSwinging : 1;

            unsigned int bIsMainWheel : 1;
            unsigned int bIsUpgrade : 1;
            unsigned int bDisableReflections : 1;
            unsigned int : 1;
            unsigned int bIsTrainFrontBogie : 1;
            unsigned int bIsTrainRearBogie : 1;
            unsigned int bRenderAlways : 1;
            unsigned int : 1;

            unsigned int : 5;
            unsigned int bUnkn4 : 1;
            unsigned int : 2;
        };
    };
};
VALIDATE_SIZE(tVehicleComponentFlagsUnion, 0x4);

struct  RwObjectNameIdAssocation
{
	char *m_pName;
	unsigned int m_dwHierarchyId;
	unsigned int m_dwFlags; // see eVehicleComponentFlags

public:
    inline tVehicleComponentFlagsUnion AsFlagsUnion() {
        tVehicleComponentFlagsUnion flags;
        flags.m_nFlags = m_dwFlags;
        return flags;
    }
};

VALIDATE_SIZE(RwObjectNameIdAssocation, 0xC);
