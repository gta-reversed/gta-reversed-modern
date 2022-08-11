#pragma once

#include "AnimationEnums.h"

struct CRideAnims {
    AnimationId idle;
    AnimationId left;
    AnimationId right;
    AnimationId back;
};

static inline CRideAnims aDriveAnimIdsLow     = { ANIM_ID_CAR_LSIT,     ANIM_ID_DRIVE_LO_L,        ANIM_ID_DRIVE_LO_R,        ANIM_ID_CAR_LB           }; // 0x8D3514
static inline CRideAnims aDriveAnimIdsBoat    = { ANIM_ID_DRIVE_BOAT,   ANIM_ID_DRIVE_BOAT_L,      ANIM_ID_DRIVE_BOAT_R,      ANIM_ID_DRIVE_BOAT_BACK  }; // 0x8D3524
static inline CRideAnims aDriveAnimIdsBad     = { ANIM_ID_CAR_SIT_WEAK, ANIM_ID_DRIVE_L_WEAK,      ANIM_ID_DRIVE_R_WEAK,      ANIM_ID_CAR_LB_WEAK      }; // 0x8D3534
static inline CRideAnims aDriveAnimIdsBadSlow = { ANIM_ID_CAR_SIT_WEAK, ANIM_ID_DRIVE_L_WEAK_SLOW, ANIM_ID_DRIVE_R_WEAK_SLOW, ANIM_ID_CAR_LB_WEAK      }; // 0x8D3544
static inline CRideAnims aDriveAnimIdsStd     = { ANIM_ID_CAR_SIT,      ANIM_ID_DRIVE_L,           ANIM_ID_DRIVE_R,           ANIM_ID_CAR_LB           }; // 0x8D3554
static inline CRideAnims aDriveAnimIdsStdSlow = { ANIM_ID_CAR_SIT,      ANIM_ID_DRIVE_L_SLOW,      ANIM_ID_DRIVE_R_SLOW,      ANIM_ID_CAR_LB           }; // 0x8D3564
static inline CRideAnims aDriveAnimIdsPro     = { ANIM_ID_CAR_SIT_PRO,  ANIM_ID_DRIVE_L_PRO,       ANIM_ID_DRIVE_R_PRO,       ANIM_ID_CAR_LB_PRO       }; // 0x8D3574
static inline CRideAnims aDriveAnimIdsProSlow = { ANIM_ID_CAR_SIT_PRO,  ANIM_ID_DRIVE_L_PRO_SLOW,  ANIM_ID_DRIVE_R_PRO_SLOW,  ANIM_ID_CAR_LB_PRO       }; // 0x8D3584
static inline CRideAnims aDriveAnimIdsTruck   = { ANIM_ID_DRIVE_TRUCK,  ANIM_ID_DRIVE_TRUCK_L,     ANIM_ID_DRIVE_TRUCK_R,     ANIM_ID_DRIVE_TRUCK_BACK }; // 0x8D3594
static inline CRideAnims aDriveAnimIdsKart    = { ANIM_ID_KART_DRIVE,   ANIM_ID_KART_L,            ANIM_ID_KART_R,            ANIM_ID_KART_LB          }; // 0x8D35A4
