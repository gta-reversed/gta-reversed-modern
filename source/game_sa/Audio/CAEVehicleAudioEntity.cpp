#include "StdInc.h"

CAEVehicleAudioEntity::CAEVehicleAudioEntity() : CAEAudioEntity(), m_skidSound()
{
    m_bEnabled = false;
    m_pEntity = nullptr;
}

CAEVehicleAudioEntity::~CAEVehicleAudioEntity()
{
    if (m_bEnabled)
        CAEVehicleAudioEntity::Terminate();
}

void CAEVehicleAudioEntity::AddAudioEvent(int audioEvent, float fVolume)
{
    plugin::CallMethod<0x4F6420, CAEVehicleAudioEntity*, int, float>(this, audioEvent, fVolume);
}

void CAEVehicleAudioEntity::Service()
{
    plugin::CallMethod<0x502280, CAEVehicleAudioEntity*>(this);
}

void CAEVehicleAudioEntity::Initialise(CVehicle* vehicle)
{
    plugin::CallMethod<0x4F7670, CAEVehicleAudioEntity*, CVehicle*>(this, vehicle);
}

void CAEVehicleAudioEntity::Terminate()
{
    plugin::CallMethod<0x4FB8C0, CAEVehicleAudioEntity*>(this);
}
