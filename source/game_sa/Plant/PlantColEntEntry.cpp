#include "StdInc.h"

#include "PlantColEntEntry.h"

// 0x5DB7D0
CPlantColEntEntry* CPlantColEntEntry::AddEntry(CEntity* entity) {
    return plugin::CallMethodAndReturn<CPlantColEntEntry*, 0x5DB7D0, CPlantColEntEntry*, CEntity*>(this, entity);
}

// 0x5DB8A0
void CPlantColEntEntry::ReleaseEntry() {
    plugin::CallMethod<0x5DB7D0, CPlantColEntEntry*>(this);
}
