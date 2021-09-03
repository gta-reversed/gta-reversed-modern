/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

// https://github.com/multitheftauto/mtasa-blue/blob/master/Client/sdk/game/CEntity.h
enum eEntityStatus : uint8 {
    STATUS_PLAYER = 0,
    STATUS_PLAYER_PLAYBACK_FROM_BUFFER,
    STATUS_SIMPLE,
    STATUS_PHYSICS,
    STATUS_ABANDONED,
    STATUS_WRECKED,
    STATUS_TRAIN_MOVING,
    STATUS_TRAIN_NOT_MOVING,
    STATUS_HELI,
    STATUS_PLANE,
    STATUS_REMOTE_CONTROLLED,
    STATUS_PLAYER_DISABLED,
    STATUS_TRAILER,                  // TODO: Check this. I can't reproduce that this is set for trailers
    STATUS_SIMPLE_TRAILER            // Same here
};
