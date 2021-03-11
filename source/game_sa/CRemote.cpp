#include "StdInc.h"

void CRemote::TakeRemoteControlledCarFromPlayer(bool bCreateRemoteVehicleExplosion)
{
    return plugin::Call<0x45AE80, bool>(bCreateRemoteVehicleExplosion);
}

void CRemote::GivePlayerRemoteControlledCar(CVector pos, float rotation, int16_t modelId)
{
    return plugin::Call<0x45AB10, CVector, float, int16_t>(pos, rotation, modelId);
}
