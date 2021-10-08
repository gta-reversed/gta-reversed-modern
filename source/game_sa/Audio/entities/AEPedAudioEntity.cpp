#include "StdInc.h"

#include "AEPedAudioEntity.h"
#include "AEAudioHardware.h"

void CAEPedAudioEntity::StaticInitialise() {
    AEAudioHardware.LoadSoundBank(0, 41);
    AEAudioHardware.LoadSoundBank(128, 32);
}

void CAEPedAudioEntity::AddAudioEvent(int32 audioEventVolumeIndex, float arg2, float arg3, CPhysical* physical, uint8 arg5, int32 arg7, uint32 arg8) {
    plugin::CallMethod<0x4E2BB0, CAEPedAudioEntity*, int32, float, float, CPhysical*, uint8, int32, uint32>(this, audioEventVolumeIndex, arg2, arg3, physical, arg5, arg7, arg8);
}
