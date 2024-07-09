#pragma once

#include <extensions/WEnum.hpp>

// TODO: Make this an enum class
enum eGlobalSpeechContext : int32 {
    GCTX_UNKNOWN                        = -1,
    GCTX_NO_SPEECH                      = 0, // 0x0
    GCTX_ABUSE_GANG_BALLAS              = 1, // 0x1
    GCTX_ABUSE_GANG_LSV                 = 2, // 0x2
    GCTX_ABUSE_GANG_VLA                 = 3, // 0x3
    GCTX_ABUSE_GANG_FAMILIES            = 4, // 0x4
    GCTX_ABUSE_TRIAD                    = 5, // 0x5
    GCTX_ABUSE_MAFIA                    = 6, // 0x6
    GCTX_ABUSE_RIFA                     = 7, // 0x7
    GCTX_ABUSE_DA_NANG                  = 8, // 0x8
    GCTX_ACCEPT_DATE_CALL               = 9, // 0x9
    GCTX_ACCEPT_DATE_REQUEST            = 10, // 0xA
    GCTX_AFTER_SEX                      = 11, // 0xB
    GCTX_APOLOGY                        = 12, // 0xC
    GCTX_ARREST                         = 13, // 0xD
    GCTX_ARREST_CRIM                    = 14, // 0xE
    GCTX_ARRESTED                       = 15, // 0xF
    GCTX_ATTACK_BY_PLAYER_LIKE          = 16, // 0x10
    GCTX_ATTACK_GANG_BALLAS             = 17, // 0x11
    GCTX_ATTACK_GANG_LSV                = 18, // 0x12
    GCTX_ATTACK_GANG_VLA                = 19, // 0x13
    GCTX_ATTACK_PLAYER                  = 20, // 0x14
    GCTX_BAR_CHAT                       = 21, // 0x15
    GCTX_BLOCKED                        = 22, // 0x16
    GCTX_BOOZE_RECEIVE                  = 23, // 0x17
    GCTX_BOOZE_REQUEST                  = 24, // 0x18
    GCTX_BUM_BACK_OFF                   = 25, // 0x19
    GCTX_BUM_BACK_OFF_2                 = 26, // 0x1A
    GCTX_BUM_LATCH                      = 27, // 0x1B
    GCTX_BUMP                           = 28, // 0x1C
    GCTX_CAR_CRASH                      = 29, // 0x1D
    GCTX_CAR_DRIVEBY_BURN_RUBBER        = 30, // 0x1E
    GCTX_CAR_DRIVEBY_TOO_FAST           = 31, // 0x1F
    GCTX_CAR_FAST                       = 32, // 0x20
    GCTX_CAR_FIRE                       = 33, // 0x21
    GCTX_CAR_FLIPPED                    = 34, // 0x22
    GCTX_CAR_GET_IN                     = 35, // 0x23
    GCTX_CAR_HIT_PED                    = 36, // 0x24
    GCTX_CAR_JUMP                       = 37, // 0x25
    GCTX_CAR_POLICE_PURSUIT             = 38, // 0x26
    GCTX_CAR_SLOW                       = 39, // 0x27
    GCTX_CAR_WAIT_FOR_ME                = 40, // 0x28
    GCTX_CAR_SINGALONG                  = 41, // 0x29
    GCTX_CB_CHAT                        = 42, // 0x2A
    GCTX_CHASE_FOOT                     = 43, // 0x2B
    GCTX_CHASED                         = 44, // 0x2C
    GCTX_CHAT                           = 45, // 0x2D
    GCTX_COFFEE_ACCEPT                  = 46, // 0x2E
    GCTX_COFFEE_DECLINE                 = 47, // 0x2F
    GCTX_CONV_DISL_CAR                  = 48, // 0x30
    GCTX_CONV_DISL_CLOTHES              = 49, // 0x31
    GCTX_CONV_DISL_HAIR                 = 50, // 0x32
    GCTX_CONV_DISL_PHYS                 = 51, // 0x33
    GCTX_CONV_DISL_SHOES                = 52, // 0x34
    GCTX_CONV_DISL_SMELL                = 53, // 0x35
    GCTX_CONV_DISL_TATTOO               = 54, // 0x36
    GCTX_CONV_DISL_WEATHER              = 55, // 0x37
    GCTX_CONV_IGNORED                   = 56, // 0x38
    GCTX_CONV_LIKE_CAR                  = 57, // 0x39
    GCTX_CONV_LIKE_CLOTHES              = 58, // 0x3A
    GCTX_CONV_LIKE_HAIR                 = 59, // 0x3B
    GCTX_CONV_LIKE_PHYS                 = 60, // 0x3C
    GCTX_CONV_LIKE_SHOES                = 61, // 0x3D
    GCTX_CONV_LIKE_SMELL                = 62, // 0x3E
    GCTX_CONV_LIKE_TATTOO               = 63, // 0x3F
    GCTX_CONV_LIKE_WEATHER              = 64, // 0x40
    GCTX_COVER_ME                       = 65, // 0x41
    GCTX_CRASH_BIKE                     = 66, // 0x42
    GCTX_CRASH_CAR                      = 67, // 0x43
    GCTX_CRASH_GENERIC                  = 68, // 0x44
    GCTX_CRIMINAL_PLEAD                 = 69, // 0x45
    GCTX_DANCE_IMPR_HIGH                = 70, // 0x46
    GCTX_DANCE_IMPR_LOW                 = 71, // 0x47
    GCTX_DANCE_IMPR_MED                 = 72, // 0x48
    GCTX_DANCE_IMPR_NOT                 = 73, // 0x49
    GCTX_DODGE                          = 74, // 0x4A
    GCTX_DRUG_AGGRESSIVE_HIGH           = 75, // 0x4B
    GCTX_DRUG_AGGRESSIVE_LOW            = 76, // 0x4C
    GCTX_DRUG_DEALER_DISLIKE            = 77, // 0x4D
    GCTX_DRUG_DEALER_HATE               = 78, // 0x4E
    GCTX_DRUG_REASONABLE_HIGH           = 79, // 0x4F
    GCTX_DRUG_REASONABLE_LOW            = 80, // 0x50
    GCTX_DRUGGED_CHAT                   = 81, // 0x51
    GCTX_DRUGGED_IGNORE                 = 82, // 0x52
    GCTX_DRUGS_BUY                      = 83, // 0x53
    GCTX_DRUGS_SELL                     = 84, // 0x54
    GCTX_DUCK                           = 85, // 0x55
    GCTX_EYEING_PED                     = 86, // 0x56
    GCTX_EYEING_PED_THREAT              = 87, // 0x57
    GCTX_EYEING_PLAYER                  = 88, // 0x58
    GCTX_FIGHT                          = 89, // 0x59
    GCTX_FOLLOW_ARRIVE                  = 90, // 0x5A
    GCTX_FOLLOW_CONSTANT                = 91, // 0x5B
    GCTX_FOLLOW_REPLY                   = 92, // 0x5C
    GCTX_GAMB_BJ_HIT                    = 93, // 0x5D
    GCTX_GAMB_BJ_LOSE                   = 94, // 0x5E
    GCTX_GAMB_BJ_STAY                   = 95, // 0x5F
    GCTX_GAMB_BJ_WIN                    = 96, // 0x60
    GCTX_GAMB_BJ_STICK                  = 97, // 0x61
    GCTX_GAMB_BJ_DOUBLE                 = 98, // 0x62
    GCTX_GAMB_BJ_SPLIT                  = 99, // 0x63
    GCTX_GAMB_CASINO_WIN                = 100, // 0x64
    GCTX_GAMB_CASINO_LOSE               = 101, // 0x65
    GCTX_GAMB_CONGRATS                  = 102, // 0x66
    GCTX_GAMB_ROUL_CHAT                 = 103, // 0x67
    GCTX_GAMB_SLOT_WIN                  = 104, // 0x68
    GCTX_GANG_FULL                      = 105, // 0x69
    GCTX_GANGBANG_NO                    = 106, // 0x6A
    GCTX_GANGBANG_YES                   = 107, // 0x6B
    GCTX_GENERIC_HI_MALE                = 108, // 0x6C
    GCTX_GENERIC_HI_FEMALE              = 109, // 0x6D
    GCTX_GENERIC_INSULT_MALE            = 110, // 0x6E
    GCTX_GENERIC_INSULT_FEMALE          = 111, // 0x6F
    GCTX_GIVING_HEAD                    = 112, // 0x70
    GCTX_GOOD_CITIZEN                   = 113, // 0x71
    GCTX_GUN_COOL                       = 114, // 0x72
    GCTX_GUN_RUN                        = 115, // 0x73
    GCTX_HAVING_SEX                     = 116, // 0x74
    GCTX_HAVING_SEX_MUFFLED             = 117, // 0x75
    GCTX_JACKED_CAR                     = 118, // 0x76
    GCTX_JACKED_GENERIC                 = 119, // 0x77
    GCTX_JACKED_ON_STREET               = 120, // 0x78
    GCTX_JACKING_BIKE                   = 121, // 0x79
    GCTX_JACKING_CAR_FEM                = 122, // 0x7A
    GCTX_JACKING_CAR_MALE               = 123, // 0x7B
    GCTX_JACKING_GENERIC                = 124, // 0x7C
    GCTX_JOIN_GANG_NO                   = 125, // 0x7D
    GCTX_JOIN_GANG_YES                  = 126, // 0x7E
    GCTX_JOIN_ME_ASK                    = 127, // 0x7F
    GCTX_JOIN_ME_REJECTED               = 128, // 0x80
    GCTX_LIKE_CAR_REPLY                 = 129, // 0x81
    GCTX_LIKE_CLOTHES_REPLY             = 130, // 0x82
    GCTX_LIKE_DISMISS_FEMALE            = 131, // 0x83
    GCTX_LIKE_DISMISS_MALE              = 132, // 0x84
    GCTX_LIKE_DISMISS_REPLY             = 133, // 0x85
    GCTX_LIKE_HAIR_REPLY                = 134, // 0x86
    GCTX_LIKE_NEGATIVE_FEMALE           = 135, // 0x87
    GCTX_LIKE_NEGATIVE_MALE             = 136, // 0x88
    GCTX_LIKE_PHYS_REPLY                = 137, // 0x89
    GCTX_LIKE_SHOES_REPLY               = 138, // 0x8A
    GCTX_LIKE_SMELL_REPLY               = 139, // 0x8B
    GCTX_LIKE_TATTOO_REPLY              = 140, // 0x8C
    GCTX_MEET_GFRIEND_AGAIN_MAYBE       = 141, // 0x8D
    GCTX_MEET_GFRIEND_AGAIN_NO          = 142, // 0x8E
    GCTX_MEET_GFRIEND_AGAIN_YES         = 143, // 0x8F
    GCTX_MOVE_IN                        = 144, // 0x90
    GCTX_MUGGED                         = 145, // 0x91
    GCTX_MUGGING                        = 146, // 0x92
    GCTX_ORDER_ATTACK_MANY              = 147, // 0x93
    GCTX_ORDER_ATTACK_SINGLE            = 148, // 0x94
    GCTX_ORDER_DISBAND_MANY             = 149, // 0x95
    GCTX_ORDER_DISBAND_ONE              = 150, // 0x96
    GCTX_ORDER_FOLLOW_FAR_MANY          = 151, // 0x97
    GCTX_ORDER_FOLLOW_FAR_ONE           = 152, // 0x98
    GCTX_ORDER_FOLLOW_NEAR_MANY         = 153, // 0x99
    GCTX_ORDER_FOLLOW_NEAR_ONE          = 154, // 0x9A
    GCTX_ORDER_FOLLOW_VNEAR_MANY        = 155, // 0x9B
    GCTX_ORDER_FOLLOW_VNEAR_ONE         = 156, // 0x9C
    GCTX_ORDER_KEEP_UP_MANY             = 157, // 0x9D
    GCTX_ORDER_KEEP_UP_ONE              = 158, // 0x9E
    GCTX_ORDER_WAIT_MANY                = 159, // 0x9F
    GCTX_ORDER_WAIT_ONE                 = 160, // 0xA0
    GCTX_PCONV_AGREE_BAD                = 161, // 0xA1
    GCTX_PCONV_AGREE_GOOD               = 162, // 0xA2
    GCTX_PCONV_ANS_NO                   = 163, // 0xA3
    GCTX_PCONV_DISMISS                  = 164, // 0xA4
    GCTX_PCONV_GREET_FEM                = 165, // 0xA5
    GCTX_PCONV_GREET_MALE               = 166, // 0xA6
    GCTX_PCONV_PART_FEM                 = 167, // 0xA7
    GCTX_PCONV_PART_MALE                = 168, // 0xA8
    GCTX_PCONV_QUESTION                 = 169, // 0xA9
    GCTX_PCONV_STATE_BAD                = 170, // 0xAA
    GCTX_PCONV_STATE_GOOD               = 171, // 0xAB
    GCTX_PICKUP_CASH                    = 172, // 0xAC
    GCTX_POLICE_BOAT                    = 173, // 0xAD
    GCTX_POLICE_HELICOPTER              = 174, // 0xAE
    GCTX_POLICE_OVERBOARD               = 175, // 0xAF
    GCTX_PULL_GUN                       = 176, // 0xB0
    GCTX_ROPE                           = 177, // 0xB1
    GCTX_RUN_FROM_FIGHT                 = 178, // 0xB2
    GCTX_SAVED                          = 179, // 0xB3
    GCTX_SEARCH                         = 180, // 0xB4
    GCTX_SHOCKED                        = 181, // 0xB5
    GCTX_SHOOT                          = 182, // 0xB6
    GCTX_SHOOT_BALLAS                   = 183, // 0xB7
    GCTX_SHOOT_GENERIC                  = 184, // 0xB8
    GCTX_SHOOT_LSV                      = 185, // 0xB9
    GCTX_SHOOT_VLA                      = 186, // 0xBA
    GCTX_SHOOT_FAMILIES                 = 187, // 0xBB
    GCTX_SHOP_BROWSE                    = 188, // 0xBC
    GCTX_SHOP_BUY                       = 189, // 0xBD
    GCTX_SHOP_SELL                      = 190, // 0xBE
    GCTX_SHOP_LEAVE                     = 191, // 0xBF
    GCTX_SOLICIT                        = 192, // 0xC0
    GCTX_SOLICIT_GEN_NO                 = 193, // 0xC1
    GCTX_SOLICIT_GEN_YES                = 194, // 0xC2
    GCTX_SOLICIT_PRO_NO                 = 195, // 0xC3
    GCTX_SOLICIT_PRO_YES                = 196, // 0xC4
    GCTX_SOLICIT_THANKS                 = 197, // 0xC5
    GCTX_SOLICIT_UNREASONABLE           = 198, // 0xC6
    GCTX_SOLO                           = 199, // 0xC7
    GCTX_SPLIFF_RECEIVE                 = 200, // 0xC8
    GCTX_SPLIFF_REQUEST                 = 201, // 0xC9
    GCTX_STEALTH_ALERT_SOUND            = 202, // 0xCA
    GCTX_STEALTH_ALERT_SIGHT            = 203, // 0xCB
    GCTX_STEALTH_ALERT_GENERIC          = 204, // 0xCC
    GCTX_STEALTH_DEF_SIGHTING           = 205, // 0xCD
    GCTX_STEALTH_NOTHING_THERE          = 206, // 0xCE
    GCTX_SURROUNDED                     = 207, // 0xCF
    GCTX_TAKE_TURF_LAS_COLINAS          = 208, // 0xD0
    GCTX_TAKE_TURF_LOS_FLORES           = 209, // 0xD1
    GCTX_TAKE_TURF_EAST_BEACH           = 210, // 0xD2
    GCTX_TAKE_TURF_EAST_LS              = 211, // 0xD3
    GCTX_TAKE_TURF_JEFFERSON            = 212, // 0xD4
    GCTX_TAKE_TURF_GLEN_PARK            = 213, // 0xD5
    GCTX_TAKE_TURF_IDLEWOOD             = 214, // 0xD6
    GCTX_TAKE_TURF_GANTON               = 215, // 0xD7
    GCTX_TAKE_TURF_LITTLE_MEXICO        = 216, // 0xD8
    GCTX_TAKE_TURF_WILLOWFIELD          = 217, // 0xD9
    GCTX_TAKE_TURF_PLAYA_DEL_SEVILLE    = 218, // 0xDA
    GCTX_TAKE_TURF_TEMPLE               = 219, // 0xDB
    GCTX_TARGET                         = 220, // 0xDC
    GCTX_TAXI_BAIL                      = 221, // 0xDD
    GCTX_TAXI_HAIL                      = 222, // 0xDE
    GCTX_TAXI_HIT_PED                   = 223, // 0xDF
    GCTX_TAXI_START                     = 224, // 0xE0
    GCTX_TAXI_SUCCESS                   = 225, // 0xE1
    GCTX_TAXI_TIP                       = 226, // 0xE2
    GCTX_TRAPPED                        = 227, // 0xE3
    GCTX_VALET_BAD                      = 228, // 0xE4
    GCTX_VALET_GOOD                     = 229, // 0xE5
    GCTX_VALET_PARK_CAR                 = 230, // 0xE6
    GCTX_VAN                            = 231, // 0xE7
    GCTX_VICTIM                         = 232, // 0xE8
    GCTX_WEATHER_DISL_REPLY             = 233, // 0xE9
    GCTX_WEATHER_LIKE_REPLY             = 234, // 0xEA
    GCTX_WHERE_YOU_FROM_NEG             = 235, // 0xEB
    GCTX_WHERE_YOU_FROM_POS             = 236, // 0xEC
    GCTX_SPANKED                        = 237, // 0xED
    GCTX_SPANKING                       = 238, // 0xEE
    GCTX_SPANKING_MUFFLED               = 239, // 0xEF
    GCTX_GREETING_GFRIEND               = 240, // 0xF0
    GCTX_PARTING_GFRIEND                = 241, // 0xF1
    GCTX_UH_HUH                         = 242, // 0xF2
    GCTX_CLEAR_ATTACHED_PEDS            = 243, // 0xF3
    GCTX_AGREE_TO_DO_DRIVEBY            = 244, // 0xF4
    GCTX_AGREE_TO_LET_DRIVE             = 245, // 0xF5
    GCTX_MICHELLE_TAKE_CAR              = 246, // 0xF6
    GCTX_ACCEPT_SEX                     = 247, // 0xF7
    GCTX_DECLINE_SEX                    = 248, // 0xF8
    GCTX_GIVE_NUMBER_YES                = 249, // 0xF9
    GCTX_GIVE_NUMBER_NO                 = 250, // 0xFA
    GCTX_WHERE_YOU_FROM                 = 251, // 0xFB
    GCTX_GANGBANG                       = 252, // 0xFC
    GCTX_WHERE_YOU_FROM_POS_REPLY       = 253, // 0xFD
    GCTX_DRIVE_THROUGH_TAUNT            = 254, // 0xFE
    GCTX_ATTACK_CAR                     = 255, // 0xFF
    GCTX_TIP_CAR                        = 256, // 0x100
    GCTX_CHASE_CAR                      = 257, // 0x101
    GCTX_ENEMY_GANG_WASTED              = 258, // 0x102
    GCTX_PLAYER_WASTED                  = 259, // 0x103
    GCTX_CHASE                          = 260, // 0x104
    GCTX_GFRIEND_REQ_DATE_DESPERATE     = 261, // 0x105
    GCTX_GFRIEND_REQ_DATE_NORMAL        = 262, // 0x106
    GCTX_GFRIEND_REQ_MEAL_DESPERATE     = 263, // 0x107
    GCTX_GFRIEND_REQ_MEAL_NORMAL        = 264, // 0x108
    GCTX_GFRIEND_REQ_DRIVE_DESPERATE    = 265, // 0x109
    GCTX_GFRIEND_REQ_DRIVE_NORMAL       = 266, // 0x10A
    GCTX_GFRIEND_REQ_DANCE_DESPERATE    = 267, // 0x10B
    GCTX_GFRIEND_REQ_DANCE_NORMAL       = 268, // 0x10C
    GCTX_GFRIEND_REQ_SEX_DESPERATE      = 269, // 0x10D
    GCTX_GFRIEND_REQ_SEX_NORMAL         = 270, // 0x10E
    GCTX_GFRIEND_BORED_1                = 271, // 0x10F
    GCTX_GFRIEND_BORED_2                = 272, // 0x110
    GCTX_GFRIEND_STORY                  = 273, // 0x111
    GCTX_GFRIEND_LIKE_MEAL_DEST         = 274, // 0x112
    GCTX_GFRIEND_LIKE_CLUB_DEST         = 275, // 0x113
    GCTX_GFRIEND_OFFER_DANCE            = 276, // 0x114
    GCTX_GFRIEND_ENJOYED_MEAL_HIGH      = 277, // 0x115
    GCTX_GFRIEND_ENJOYED_EVENT_LOW      = 278, // 0x116
    GCTX_GFRIEND_ENJOYED_CLUB_HIGH      = 279, // 0x117
    GCTX_GFRIEND_TAKE_HOME_HAPPY        = 280, // 0x118
    GCTX_GFRIEND_TAKE_HOME_ANGRY        = 281, // 0x119
    GCTX_GFRIEND_COFFEE                 = 282, // 0x11A
    GCTX_GFRIEND_MOAN                   = 283, // 0x11B
    GCTX_GFRIEND_MOAN_MUFFLED           = 284, // 0x11C
    GCTX_GFRIEND_HEAD                   = 285, // 0x11D
    GCTX_GFRIEND_CLIMAX_HIGH            = 286, // 0x11E
    GCTX_GFRIEND_CLIMAX_HIGH_MUFFLED    = 287, // 0x11F
    GCTX_GFRIEND_CLIMAX_LOW             = 288, // 0x120
    GCTX_GFRIEND_SEX_GOOD               = 289, // 0x121
    GCTX_GFRIEND_SEX_GOOD_MUFFLED       = 290, // 0x122
    GCTX_GFRIEND_SEX_BAD                = 291, // 0x123
    GCTX_GFRIEND_MEET_AGAIN             = 292, // 0x124
    GCTX_GFRIEND_JEALOUS                = 293, // 0x125
    GCTX_GFRIEND_JEALOUS_REPLY          = 294, // 0x126
    GCTX_GFRIEND_GOODBYE_HAPPY          = 295, // 0x127
    GCTX_GFRIEND_GOODBYE_ANGRY          = 296, // 0x128
    GCTX_GFRIEND_LEFT_BEHIND            = 297, // 0x129
    GCTX_GFRIEND_HELLO                  = 298, // 0x12A
    GCTX_GFRIEND_GOODBYE                = 299, // 0x12B
    GCTX_GFRIEND_PICKUP_LOCATION        = 300, // 0x12C
    GCTX_GFRIEND_PARK_UP                = 301, // 0x12D
    GCTX_GFRIEND_PARK_LOCATION_HATE     = 302, // 0x12E
    GCTX_GFRIEND_GIFT_LIKE              = 303, // 0x12F
    GCTX_GFRIEND_CHANGE_RADIO_FAVE      = 304, // 0x130
    GCTX_GFRIEND_CHANGE_RADIO_BACK      = 305, // 0x131
    GCTX_GFRIEND_DO_A_DRIVEBY           = 306, // 0x132
    GCTX_GFRIEND_START_A_FIGHT          = 307, // 0x133
    GCTX_GFRIEND_REJECT_DATE            = 308, // 0x134
    GCTX_GFRIEND_REQUEST_TO_DRIVE_CAR   = 309, // 0x135
    GCTX_GFRIEND_DROP_PLAYER_DRIVE_AWAY = 310, // 0x136
    GCTX_GFRIEND_DISLIKE_CURRENT_ZONE   = 311, // 0x137
    GCTX_GFRIEND_LIKE_CURRENT_ZONE      = 312, // 0x138
    GCTX_GFRIEND_HIT_BY_PLAYER_WARNING  = 313, // 0x139
    GCTX_GFRIEND_DUMP_PLAYER_LIVE       = 314, // 0x13A
    GCTX_GFRIEND_DUMP_PLAYER_PHONE      = 315, // 0x13B
    GCTX_GFRIEND_SEX_APPEAL_TOO_LOW     = 316, // 0x13C
    GCTX_GFRIEND_PHYSIQUE_CRITIQUE      = 317, // 0x13D
    GCTX_GFRIEND_INTRO                  = 318, // 0x13E
    GCTX_GFRIEND_NEG_RESPONSE           = 319, // 0x13F
    GCTX_GFRIEND_POS_RESPONSE           = 320, // 0x140
    GCTX_BOXING_CHEER                   = 321, // 0x141
    GCTX_BOUGHT_ENOUGH                  = 322, // 0x142
    GCTX_GIVE_PRODUCT                   = 323, // 0x143
    GCTX_NO_MONEY                       = 324, // 0x144
    GCTX_PLAYER_SICK                    = 325, // 0x145
    GCTX_REMOVE_TATTOO                  = 326, // 0x146
    GCTX_SHOP_CLOSED                    = 327, // 0x147
    GCTX_SHOW_CHANGINGROOM              = 328, // 0x148
    GCTX_SHOP_CHAT                      = 329, // 0x149
    GCTX_TAKE_A_SEAT                    = 330, // 0x14A
    GCTX_THANKS_FOR_CUSTOM              = 331, // 0x14B
    GCTX_WELCOME_TO_SHOP                = 332, // 0x14C
    GCTX_WHAT_WANT                      = 333, // 0x14D
    GCTX_PHOTO_CARL                     = 334, // 0x14E
    GCTX_PHOTO_CHEESE                   = 335, // 0x14F
    GCTX_SINGING                        = 336, // 0x150
    GCTX_STOMACH_RUMBLE                 = 337, // 0x151
    GCTX_BREATHING                      = 338, // 0x152
    GCTX_PAIN_START                     = 339, // 0x153
    GCTX_PAIN_COUGH                     = 340, // 0x154
    GCTX_PAIN_DEATH_DROWN               = 341, // 0x155
    GCTX_PAIN_DEATH_HIGH                = 342, // 0x156
    GCTX_PAIN_DEATH_LOW                 = 343, // 0x157
    GCTX_PAIN_HIGH                      = 344, // 0x158
    GCTX_PAIN_LOW                       = 345, // 0x159
    GCTX_PAIN_ON_FIRE                   = 346, // 0x15A
    GCTX_PAIN_PANIC                     = 347, // 0x15B
    GCTX_PAIN_SPRAYED                   = 348, // 0x15C
    GCTX_PAIN_CJ_BOXING                 = 349, // 0x15D
    GCTX_PAIN_CJ_GRUNT                  = 350, // 0x15E
    GCTX_PAIN_CJ_PANT_IN                = 351, // 0x15F
    GCTX_PAIN_CJ_PANT_OUT               = 352, // 0x160
    GCTX_PAIN_CJ_PUKE                   = 353, // 0x161
    GCTX_PAIN_CJ_STRAIN                 = 354, // 0x162
    GCTX_PAIN_CJ_STRAIN_EXHALE          = 355, // 0x163
    GCTX_PAIN_CJ_SWIM_GASP              = 356, // 0x164
    GCTX_PAIN_CJ_DROWNING               = 357, // 0x165
    GCTX_PAIN_CJ_HIGH_FALL              = 358, // 0x166
    GCTX_PAIN_END                       = 359, // 0x167
    GCTX_END                            = 360, // 0x168
};
NOTSA_WENUM_DEFS_FOR(eGlobalSpeechContext)
