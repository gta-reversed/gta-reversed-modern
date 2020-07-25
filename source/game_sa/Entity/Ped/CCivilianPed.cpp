#include "StdInc.h"

CCivilianPed::CCivilianPed(ePedType pedType, unsigned int modelIndex) : CPed(plugin::dummy) {
    ((void(__thiscall*)(CCivilianPed*, ePedType, unsigned int))0x5DDB70)(this, pedType, modelIndex);
}
