#include "StdInc.h"

void CAEPedAudioEntity::AddAudioEvent(int32 audioEventVolumeIndex, float arg2, float arg3, int32 arg4, int32 arg5, int32 arg7, int32 arg8) {
    plugin::CallMethod<0x4E2BB0, CAEPedAudioEntity*, int32, float, float, int32, int32, int32, int32>(this, audioEventVolumeIndex, arg2, arg3, arg4, arg5, arg7, arg8);
}