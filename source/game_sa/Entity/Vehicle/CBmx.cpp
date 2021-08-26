#include "StdInc.h"

void CBmx::InjectHooks() {

}

CBmx::CBmx(int modelIndex, eVehicleCreatedBy createdBy) : CBike(plugin::dummy)
{
    plugin::CallMethod<0x6BF820, CBmx*, int, eVehicleCreatedBy>(this, modelIndex, createdBy);
}
