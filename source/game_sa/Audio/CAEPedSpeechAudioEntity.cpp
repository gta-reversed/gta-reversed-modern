#include "StdInc.h"

bool CAEPedSpeechAudioEntity::RequestPedConversation(CPed* ped1, CPed* ped2) {
    return plugin::CallAndReturn<bool, 0x4E50E0, CPed*, CPed*>(ped1, ped2);
}

bool CAEPedSpeechAudioEntity::ReleasePedConversation() {
    return plugin::CallAndReturn<bool, 0x4E52A0>();
}
