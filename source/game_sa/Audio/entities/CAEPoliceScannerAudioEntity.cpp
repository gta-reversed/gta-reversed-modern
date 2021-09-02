#include "StdInc.h"

void CAEPoliceScannerAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    plugin::CallMethod<0x4E7590, CAEPoliceScannerAudioEntity*, CAESound*, int16>(this, sound, curPlayPos);
}
