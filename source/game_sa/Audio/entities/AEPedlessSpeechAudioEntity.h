#pragma once

#include "AEPedSpeechAudioEntity.h"

class NOTSA_EXPORT_VTABLE CAEPedlessSpeechAudioEntity : public CAEPedSpeechAudioEntity {
public:
    char     gap100[20];
    CEntity* m_Entity;

public:
    CAEPedlessSpeechAudioEntity();
    ~CAEPedlessSpeechAudioEntity() = default;

    void Initialise();
    void StopCurrentSpeech(); // OG moment: Function 'StopCurrentSpeech' hides a non-virtual function from class 'CAEPedSpeechAudioEntity'
    int16 AddSayEvent(int32 a1, int16 a2, CEntity* entity, uint32 playOffset, float a6, bool a3, bool a8, bool a9);

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;
    void AddScriptSayEvent(int32, int32, uint8, uint8, uint8) override;
    void Terminate() override;
    void PlayLoadedSound() override;
    int16 GetAllocatedVoice() override;
    bool WillPedChatAboutTopic(int16 topic) override;
    int16 GetPedType() override;
    bool IsPedFemaleForAudio() override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEPedlessSpeechAudioEntity* Constructor();
    CAEPedlessSpeechAudioEntity* Destructor();

};

VALIDATE_SIZE(CAEPedlessSpeechAudioEntity, 0x118);
