/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

enum class eVehicleComponentFlags : uint32 {
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
        uint32 m_nFlags;
        struct {
            uint32 bIsVehStructPart : 1;
            uint32 bIsDamageable : 1;
            uint32 bIsWheel : 1;
            uint32 bIsDummy : 1;
            uint32 bIsDoor : 1;
            uint32 bIsLeft : 1;
            uint32 bIsRight : 1;
            uint32 bIsFront : 1;

            uint32 bIsRear : 1;
            uint32 bIsExtra : 1;
            uint32 bHasAlpha : 1;
            uint32 bIsGlass : 1;
            uint32 bCull : 1;
            uint32 bIsRearDoor : 1;
            uint32 bIsFrontDoor : 1;
            uint32 bSwinging : 1;

            uint32 bIsMainWheel : 1;
            uint32 bIsUpgrade : 1;
            uint32 bDisableReflections : 1;
            uint32 : 1;
            uint32 bIsTrainFrontBogie : 1;
            uint32 bIsTrainRearBogie : 1;
            uint32 bRenderAlways : 1;
            uint32 : 1;

            uint32 : 5;
            uint32 bUnkn4 : 1;
            uint32 : 2;
        };
    };
};
VALIDATE_SIZE(tVehicleComponentFlagsUnion, 0x4);

struct RwObjectNameIdAssocation {
    char*  m_pName;
    uint32 m_dwHierarchyId;
    uint32 m_dwFlags; // see eVehicleComponentFlags

public:
    inline tVehicleComponentFlagsUnion AsFlagsUnion() {
        tVehicleComponentFlagsUnion flags;
        flags.m_nFlags = m_dwFlags;
        return flags;
    }
};

VALIDATE_SIZE(RwObjectNameIdAssocation, 0xC);
