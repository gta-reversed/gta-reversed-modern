#include "StdInc.h"
#include "CWaterCannons.h"

void CWaterCannons::Init()
{
    plugin::Call<0x728C80>();
}

void CWaterCannons::UpdateOne(uint32_t id, CVector* start, CVector* end)
{
    plugin::Call<0x728CB0, uint32_t, CVector*, CVector*>(id, start, end);
}
