#include "StdInc.h"

#include "PedAttractorManager.h"

#include "PedAttractor.h"

#include "PedAtmAttractor.h"
#include "PedSeatAttractor.h"
#include "PedStopAttractor.h"
#include "PedPizzaAttractor.h"
#include "PedShelterAttractor.h"
#include "PedTriggerScriptAttractor.h"
#include "PedLookAtAttractor.h"
#include "PedScriptedAttractor.h"
#include "PedParkAttractor.h"
#include "PedStepAttractor.h"

CPedAttractorManager* GetPedAttractorManager() {
    return plugin::CallAndReturn<CPedAttractorManager*, 0x5EE190>();
}

bool CPedAttractorManager::HasEmptySlot(const C2dEffect* effect, const CEntity* entity) {
    return plugin::CallMethodAndReturn<bool, 0x5EBB00, CPedAttractorManager*, C2dEffect const*, CEntity const*>(this, effect, entity);
}

CPedAttractor* CPedAttractorManager::RegisterPed(CPed* ped, C2dEffect* attr, CEntity* entity, int a4, void* attrAry) {
    assert(0);
    return nullptr;
}
