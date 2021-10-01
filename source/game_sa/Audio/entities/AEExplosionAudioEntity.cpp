#include "StdInc.h"

#include "AEExplosionAudioEntity.h"
#include "AEAudioHardware.h"

void CAEExplosionAudioEntity::StaticInitialise() {
    AEAudioHardware.LoadSoundBank(52, 4);
}
