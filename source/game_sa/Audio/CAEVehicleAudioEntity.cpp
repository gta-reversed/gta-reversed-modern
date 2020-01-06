#include "StdInc.h"

void CAEVehicleAudioEntity::AddAudioEvent(int audioEvent, float fVolume)
{
    plugin::CallMethod<0x4F6420, CAEVehicleAudioEntity*, int, float>(this, audioEvent, fVolume);
}

void CAEVehicleAudioEntity::Service()
{
    plugin::CallMethod<0x502280, CAEVehicleAudioEntity*>(this);
}