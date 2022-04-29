#include "StdInc.h"

#include "AEPedAudioEntity.h"
#include "AEAudioHardware.h"

void CAEPedAudioEntity::StaticInitialise() {
    AEAudioHardware.LoadSoundBank(0, 41);
    AEAudioHardware.LoadSoundBank(128, 32);
}

// (CEntity* entity)
// 0x4E0E80
void CAEPedAudioEntity::Initialise(CPed* ped) {
    plugin::CallMethod<0x4E0E80>(this, ped);
}

// 0x4E1360
void CAEPedAudioEntity::Terminate() {
    plugin::CallMethod<0x4E1360>(this);
    /*
    field_7C = 0;
    m_pPed   = nullptr;
    StopJetPackSound();
    AESoundManager.CancelSoundsOwnedByAudioEntity(this, true);
    if (m_sTwinLoopSoundEntity.m_bIsInitialised)
        m_sTwinLoopSoundEntity.StopSoundAndForget();
    */
}

void CAEPedAudioEntity::AddAudioEvent(int32 audioEventVolumeIndex, float arg2, float arg3, CPhysical* physical, uint8 arg5, int32 arg7, uint32 arg8) {
    plugin::CallMethod<0x4E2BB0, CAEPedAudioEntity*, int32, float, float, CPhysical*, uint8, int32, uint32>(this, audioEventVolumeIndex, arg2, arg3, physical, arg5, arg7, arg8);
}
