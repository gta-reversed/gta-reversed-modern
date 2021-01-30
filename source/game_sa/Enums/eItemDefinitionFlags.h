#pragma once

// https://gtamods.com/wiki/Item_Definition#IDE_Flags
enum eItemDefinitionFlags {
    IS_ROAD                     = 0x1,
    PAD1                        = 0x2,
    DRAW_LAST                   = 0x4,
    ADDITIVE                    = 0x8,
    PAD2                        = 0x10,
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
        unsigned int dwFlags;
        struct {
            unsigned int bIsRoad             : 1;
            unsigned int bPad1               : 1;
            unsigned int bDrawLast           : 1;
            unsigned int bAdditive           : 1;
            unsigned int bPad2               : 1;
            unsigned int bAnimSomething      : 1;
            unsigned int bNoZBufferWrite     : 1;
            unsigned int bDontReceiveShadows : 1;

            unsigned int bPad3                    : 1;
            unsigned int bIsGlassType1            : 1;
            unsigned int bIsGlassType2            : 1;
            unsigned int bIsGarageDoor            : 1;
            unsigned int bIsDamageable            : 1;
            unsigned int bIsTree                  : 1;
            unsigned int bIsPalm                  : 1;
            unsigned int bDoesNotCollideWithFlyer : 1;

            unsigned int bIsExplosive_Unused     : 1;
            unsigned int bIsCopBodyPart_Unused   : 1;
            unsigned int bPad4                   : 1;
            unsigned int bIsUnknown              : 1;
            unsigned int bIsTag                  : 1;
            unsigned int bDisableBackfaceCulling : 1;
            unsigned int bisBreakableStatue      : 1;
        };
    };

    inline sItemDefinitionFlags(unsigned int flags) : dwFlags(flags) {}
};
VALIDATE_SIZE(sItemDefinitionFlags, 0x4);
