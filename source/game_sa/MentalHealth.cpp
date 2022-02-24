#include "StdInc.h"
#include "MentalHealth.h"

void CMentalHealth::IncrementAnger() {
    plugin::CallMethod<0x421050>(this);
}

void CMentalHealth::Process() {
    plugin::CallMethod<0x6008A0>(this);
}
