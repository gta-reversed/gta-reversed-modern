#include "StdInc.h"

void CDarkel::DrawMessages()
{
    ((void(__cdecl*)())0x43CEC0)();
}

void CDarkel::RegisterCarBlownUpByPlayer(CVehicle* pVehicle, int arg2)
{
    plugin::Call<0x43DF20, CVehicle*, int>(pVehicle, arg2);
}
