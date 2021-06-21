#include "StdInc.h"

void CBmx::InjectHooks() {

}

CBmx::CBmx(int modelIndex, unsigned char createdBy) : CBike(plugin::dummy)
{
    plugin::CallMethod<0x6BF820, CBmx*, int, unsigned char>(this, modelIndex, createdBy);
}
