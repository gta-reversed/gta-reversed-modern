#include "StdInc.h"

#include "AEPedlessSpeechAudioEntity.h"

// 0x4E6070
CAEPedlessSpeechAudioEntity::CAEPedlessSpeechAudioEntity() : CAEPedSpeechAudioEntity() {
    // NOP
}

// 0x4E4E10
void CAEPedlessSpeechAudioEntity::Initialise() {
    m_pEntity                    = nullptr;
    m_Entity                     = nullptr;
    m_Sound                      = nullptr;
    m_EventVolume                = -100.0f;
    m_LastGCtx                   = GCTX_UNK;
    m_IsPlayingSpeech            = false;
    m_IsSpeechDisabled           = false;
    m_IsSpeechForScriptsDisabled = false;
    m_IsFrontend                 = 0;
    m_IsForcedAudible            = 0;
    m_IsFemale                   = 0;
    m_PedAudioType               = PED_TYPE_GFD;
    m_IsInitialized              = true;
    m_NextTimeCanSayPain.fill(0);
}

// 0x4E4E80
void CAEPedlessSpeechAudioEntity::StopCurrentSpeech() {
    plugin::CallMethod<0x4E4E80, CAEPedlessSpeechAudioEntity*>(this);
}

// 0x4E60D0
int16 CAEPedlessSpeechAudioEntity::AddSayEvent(int32 a1, int16 a2, CEntity* entity, uint32 playOffset, float a6, bool a3, bool a8, bool a9) {
    return plugin::CallMethodAndReturn<int16, 0x4E60D0, CAEPedlessSpeechAudioEntity*, int32, int16, CEntity*, uint32, float, bool, bool, bool>(this, a1, a2, entity, playOffset, a6, a3, a8, a9);
}

// 0x4E6080
void CAEPedlessSpeechAudioEntity::AddScriptSayEvent(int32, int32, uint8, uint8, uint8) {
    // NOP
}

// 0x4E4D10
void CAEPedlessSpeechAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    plugin::CallMethod<0x4E4D10, CAEPedlessSpeechAudioEntity*, CAESound*, int16>(this, sound, curPlayPos);
}

// 0x4E6300
void CAEPedlessSpeechAudioEntity::Terminate() {
    plugin::CallMethod<0x4E6300, CAEPedlessSpeechAudioEntity*>(this);
}

// 0x4E6380
void CAEPedlessSpeechAudioEntity::PlayLoadedSound() {
    plugin::CallMethod<0x4E6380, CAEPedlessSpeechAudioEntity*>(this);
}

// 0x4E6090
int16 CAEPedlessSpeechAudioEntity::GetAllocatedVoice() {
    return -1;
}

// 0x4E60A0
bool CAEPedlessSpeechAudioEntity::WillPedChatAboutTopic(int16) {
    return false;
}

// 0x4E60B0
int16 CAEPedlessSpeechAudioEntity::GetPedType() {
    return -1;
}

// 0x4E60C0
bool CAEPedlessSpeechAudioEntity::IsPedFemaleForAudio() {
    return false;
}

void CAEPedlessSpeechAudioEntity::InjectHooks() {
    RH_ScopedVirtualClass(CAEPedlessSpeechAudioEntity, 0x85F330, 8);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Constructor, 0x4E6070, { .reversed = false });
    RH_ScopedInstall(GetPedType, 0x4E60B0);
    RH_ScopedInstall(IsPedFemaleForAudio, 0x4E60C0);
    RH_ScopedInstall(Initialise, 0x4E4E10, { .reversed = false });
    RH_ScopedInstall(StopCurrentSpeech, 0x4E4E80, { .reversed = false });
    RH_ScopedInstall(AddSayEvent, 0x4E60D0, { .reversed = false });
    RH_ScopedVMTInstall(UpdateParameters, 0x4E4D10, { .reversed = false });
    RH_ScopedVMTInstall(Terminate, 0x4E6300, { .reversed = false });
    RH_ScopedVMTInstall(PlayLoadedSound, 0x4E6380, { .reversed = false });
    RH_ScopedVMTInstall(GetAllocatedVoice, 0x4E6090);
    RH_ScopedVMTInstall(WillPedChatAboutTopic, 0x4E60A0);
}

CAEPedlessSpeechAudioEntity* CAEPedlessSpeechAudioEntity::Constructor() {
    this->CAEPedlessSpeechAudioEntity::CAEPedlessSpeechAudioEntity();
    return this;
}

CAEPedlessSpeechAudioEntity* CAEPedlessSpeechAudioEntity::Destructor() {
    this->CAEPedlessSpeechAudioEntity::~CAEPedlessSpeechAudioEntity();
    return this;
}
