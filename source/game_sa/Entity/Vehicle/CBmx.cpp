#include "StdInc.h"

void CBmx::InjectHooks() {

}

CBmx::CBmx(int32 modelIndex, eVehicleCreatedBy createdBy) : CBike(plugin::dummy)
{
    plugin::CallMethod<0x6BF820, CBmx*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
}
