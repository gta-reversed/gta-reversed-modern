#include "StdInc.h"

void CAEPedAudioEntity::AddAudioEvent(int audioEventVolumeIndex, float arg2, float arg3, int arg4, int arg5, int arg7, int arg8)
{
    plugin::CallMethod<0x4E2BB0, CAEPedAudioEntity*, int, float, float, int, int, int, int> (this, audioEventVolumeIndex, arg2, arg3, arg4, arg5, arg7, arg8);
}