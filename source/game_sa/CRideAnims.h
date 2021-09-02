#pragma once

#include "AnimationEnums.h"

enum eRideAnim : unsigned char {
    RIDE_IDLE = 0,
    RIDE_LOOK_LEFT = 1,
    RIDE_LOOK_RIGHT = 2,
    RIDE_LOOK_BACK = 3
};

class CRideAnims {
public:
    AnimationId m_aAnims[4]; // Access with eRideAnim index
};

extern CRideAnims& aDriveAnimIdsLow;     // {ANIM_ID_CAR_LSIT, ANIM_ID_DRIVE_LO_L, ANIM_ID_DRIVE_LO_R, ANIM_ID_CAR_LB}
extern CRideAnims& aDriveAnimIdsBoat;    // {ANIM_ID_DRIVE_BOAT, ANIM_ID_DRIVE_BOAT_L, ANIM_ID_DRIVE_BOAT_R, ANIM_ID_DRIVE_BOAT_BACK}
extern CRideAnims& aDriveAnimIdsBad;     // {ANIM_ID_CAR_SIT_WEAK, ANIM_ID_DRIVE_L_WEAK, ANIM_ID_DRIVE_R_WEAK, ANIM_ID_CAR_LB_WEAK}
extern CRideAnims& aDriveAnimIdsBadSlow; // {ANIM_ID_CAR_SIT_WEAK, ANIM_ID_DRIVE_L_WEAK_SLOW, ANIM_ID_DRIVE_R_WEAK_SLOW, ANIM_ID_CAR_LB_WEAK}
extern CRideAnims& aDriveAnimIdsStd;     // {ANIM_ID_CAR_SIT, ANIM_ID_DRIVE_L, ANIM_ID_DRIVE_R, ANIM_ID_CAR_LB}
extern CRideAnims& aDriveAnimIdsStdSlow; // {ANIM_ID_CAR_SIT, ANIM_ID_DRIVE_L_SLOW, ANIM_ID_DRIVE_R_SLOW, ANIM_ID_CAR_LB}
extern CRideAnims& aDriveAnimIdsPro;     // {ANIM_ID_CAR_SIT_PRO, ANIM_ID_DRIVE_L_PRO, ANIM_ID_DRIVE_R_PRO, ANIM_ID_CAR_LB_PRO}
extern CRideAnims& aDriveAnimIdsProSlow; // {ANIM_ID_CAR_SIT_PRO, ANIM_ID_DRIVE_L_PRO_SLOW, ANIM_ID_DRIVE_R_PRO_SLOW, ANIM_ID_CAR_LB_PRO}
extern CRideAnims& aDriveAnimIdsTruck;   // {ANIM_ID_DRIVE_TRUCK, ANIM_ID_DRIVE_TRUCK_L, ANIM_ID_DRIVE_TRUCK_R, ANIM_ID_DRIVE_TRUCK_BACK}
extern CRideAnims& aDriveAnimIdsKart;    // {ANIM_ID_KART_DRIVE, ANIM_ID_KART_L, ANIM_ID_KART_R, ANIM_ID_KART_LB}
