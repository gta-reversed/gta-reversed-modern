#include "StdInc.h"

void CAEPoliceScannerAudioEntity::UpdateParameters(CAESound* sound, short curPlayPos)
{
    plugin::CallMethod<0x4E7590, CAEPoliceScannerAudioEntity*, CAESound*, short>(this, sound, curPlayPos);
}
