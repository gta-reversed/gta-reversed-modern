#include "StdInc.h"

bool CPedGroupIntelligence::AddEvent(CEvent* event) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CPedGroupIntelligence*, CEvent*>(0x5F7470, this, event);
}
