#include "StdInc.h"

eReplayMode &CReplay::Mode = *reinterpret_cast<eReplayMode*>(0xA43088);

void CReplay::Display()
{
    plugin::Call<0x45C210>();
}

void CReplay::RecordVehicleDeleted(CVehicle* vehicle)
{
    plugin::Call<0x45EBB0, CVehicle*>(vehicle);
}
