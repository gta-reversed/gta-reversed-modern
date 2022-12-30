#pragma once

// https://gtamods.com/wiki/Item_Definition#IDE_Flags
enum eItemDefinitionFlags {
    IS_ROAD                     = 0x1,
    PAD1_                       = 0x2,
    DRAW_LAST                   = 0x4,
    ADDITIVE                    = 0x8,
    PAD2_                       = 0x10,
    ANIM_SOMETHING              = 0x20,
    NO_ZBUFFER_WRITE            = 0x40,
    DONT_RECEIVE_SHADOWS        = 0x80,
    PAD3                        = 0x100,
    IS_GLASS_TYPE_1             = 0x200,
    IS_GLASS_TYPE_2             = 0x400,
    IS_GARAGE_DOOR              = 0x800,
    IS_DAMAGEABLE               = 0x1000,
    IS_TREE                     = 0x2000,
    IS_PALM                     = 0x4000,
    DOES_NOT_COLLIDE_WITH_FLYER = 0x8000,
    IS_EXPLOSIVE_UNUSED         = 0x10000,
    IS_COP_BODYPART_UNUSED      = 0x20000,
    PAD6                        = 0x40000,
    IS_UNKNOWN                  = 0x80000,
    IS_TAG                      = 0x100000,
    DISABLE_BACKFACE_CULLING    = 0x200000,
    IS_BREAKABLE_STATUE         = 0x400000
};

struct sItemDefinitionFlags {
    union {
        uint32 dwFlags;
        struct {
            uint32 bIsRoad             : 1;
            uint32 bPad1               : 1;
            uint32 bDrawLast           : 1;
            uint32 bAdditive           : 1;
            uint32 bPad2               : 1;
            uint32 bAnimSomething      : 1;
            uint32 bNoZBufferWrite     : 1;
            uint32 bDontReceiveShadows : 1;

            uint32 bPad3                    : 1;
            uint32 bIsGlassType1            : 1;
            uint32 bIsGlassType2            : 1;
            uint32 bIsGarageDoor            : 1;
            uint32 bIsDamageable            : 1;
            uint32 bIsTree                  : 1;
            uint32 bIsPalm                  : 1;
            uint32 bDoesNotCollideWithFlyer : 1;

            uint32 bIsExplosive_Unused     : 1;
            uint32 bIsCopBodyPart_Unused   : 1;
            uint32 bPad4                   : 1;
            uint32 bIsUnknown              : 1;
            uint32 bIsTag                  : 1;
            uint32 bDisableBackfaceCulling : 1;
            uint32 bisBreakableStatue      : 1;
        };
    };

    inline sItemDefinitionFlags(uint32 flags) : dwFlags(flags) {}
};
VALIDATE_SIZE(sItemDefinitionFlags, 0x4);
