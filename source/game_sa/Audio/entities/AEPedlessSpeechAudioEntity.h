#pragma once

#include "AEPedSpeechAudioEntity.h"

class CAEPedlessSpeechAudioEntity : public CAEPedSpeechAudioEntity {
public:
    char     gap100[20];
    CEntity* m_Entity;

public:
    CAEPedlessSpeechAudioEntity();
    ~CAEPedlessSpeechAudioEntity();

    void Initialise();
    void StopCurrentSpeech();
    int16 AddSayEvent(int32 a1, int16 a2, CEntity* entity, uint32 playOffset, float a6, bool a3, bool a8, bool a9);
    static int16 GetPedType();
    static bool IsPedFemaleForAudio();

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;
    void Terminate() override;
    void PlayLoadedSound() override;
    int16 GetAllocatedVoice() override;
    bool WillPedChatAboutTopic(int16 topic) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEPedlessSpeechAudioEntity* Constructor();
    CAEPedlessSpeechAudioEntity* Destructor();

    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos);
    void Terminate_Reversed();
    void PlayLoadedSound_Reversed();
    int16 GetAllocatedVoice_Reversed();
    bool WillPedChatAboutTopic_Reversed(int16 topic);
};

VALIDATE_SIZE(CAEPedlessSpeechAudioEntity, 0x118);
