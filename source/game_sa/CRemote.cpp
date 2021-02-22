#include "StdInc.h"

void CRemote::TakeRemoteControlledCarFromPlayer(bool bCreateRemoteVehicleExplosion)
{
    return plugin::Call<0x45AE80, bool>(bCreateRemoteVehicleExplosion);
}
