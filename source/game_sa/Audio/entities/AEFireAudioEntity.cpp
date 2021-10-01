#include "StdInc.h"

#include "AEFireAudioEntity.h"
#include "AEAudioHardware.h"

void CAEFireAudioEntity::StaticInitialise() {
    AEAudioHardware.LoadSoundBank(52, 4);
}
