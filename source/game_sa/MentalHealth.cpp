#include "StdInc.h"
#include "MentalHealth.h"

// 0x421050
void CMentalState::IncrementAnger(int32 anger) {
    plugin::CallMethod<0x421050, CMentalState*, int32>(this, anger);
}

// 0x6008A0
void CMentalState::Process(const CPed& ped) {
    plugin::CallMethod<0x6008A0>(this, &ped);
}
