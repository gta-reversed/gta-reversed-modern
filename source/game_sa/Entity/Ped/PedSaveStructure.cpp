#include "StdInc.h"
#include "PedSaveStructure.h"

void CPedSaveStructure::Extract(CPed* ped) {
    plugin::CallMethod<0x5D44B0, CPedSaveStructure*, CPed*>(this, ped);
}

void CPedSaveStructure::Construct(CPed* ped) {
    plugin::CallMethod<0x5D43D0, CPedSaveStructure*, CPed*>(this, ped);
}
