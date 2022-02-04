#include "StdInc.h"

#include "ShotInfo.h"

void CShotInfo::Initialise() {
    plugin::Call<0x739B60>();
}

void CShotInfo::Shutdown() {
    plugin::Call<0x739C20>();
}

void CShotInfo::Update() {
    plugin::Call<0x739E60>();
}
