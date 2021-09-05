#include "StdInc.h"

CCivilianPed::CCivilianPed(ePedType pedType, uint32 modelIndex) : CPed(plugin::dummy) {
    ((void(__thiscall*)(CCivilianPed*, ePedType, uint32))0x5DDB70)(this, pedType, modelIndex);
}
