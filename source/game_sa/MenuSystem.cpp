#include "StdInc.h"

#include "MenuSystem.h"

uint16& CMenuSystem::num_menus_in_use = *reinterpret_cast<uint16*>(0xBA82E3);

// 0x5822D0
void CMenuSystem::Initialise() {
    plugin::Call<0x5822D0>();
}
