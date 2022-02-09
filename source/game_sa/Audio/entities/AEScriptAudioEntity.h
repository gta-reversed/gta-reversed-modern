#pragma once

#include "eAudioEvents.h"
#include "AEExplosionAudioEntity.h"
#include "AEDoorAudioEntity.h"

class CEntity;
class CVector;

struct CAudioLink {
    CVector  m_vPosition;
    CEntity* m_pEntity;
    int32    m_field_10;
    int32    m_nAudioEvent;
    int32    m_nBankId;
    int32    m_nBankSlotId;

    void Init() {
        m_nAudioEvent = -1;
        m_nBankId     = -1;
        m_nBankSlotId = -1;
        m_pEntity     =  nullptr;
        m_field_10    =  0;
        m_vPosition   = CVector(-1000.0f, -1000.0f, -1000.0f);
    }
};

VALIDATE_SIZE(CAudioLink, 0x20);

class CAEScriptAudioEntity : public CAEAudioEntity {
public:
    static constexpr auto MISSION_AUDIO_COUNT = 4;

public:
    uint8                   field_7C;
    uint8                   field_7D;
    uint8                   field_7E;
    uint8                   field_7F;
    int32                   m_nLastTimeHornPlayed;
    float                   m_fVolume;
    float                   m_fSpeed;
    float                   field_8C;
    CAudioLink              wavLinks[MISSION_AUDIO_COUNT];
    CPhysical*              m_Physical;
    CAEDoorAudioEntity      m_GarageAudio;
    CAEExplosionAudioEntity m_explosionAudio;

public:
    CAEScriptAudioEntity();

    void Initialise();
    void Reset();

    void AddAudioEvent(int32);
    CVector* AttachMissionAudioToPhysical(uint8 sampleId, CPhysical* physical);

    void ClearMissionAudio(uint8 id);

    bool IsMissionAudioSampleFinished(uint8 sampleId);
    int8 GetMissionAudioLoadingStatus(uint8 sampleId);
    int32 GetMissionAudioEvent(uint8 sampleId);
    void SetMissionAudioPosition(uint8 sampleId, CVector& posn);
    CVector* GetMissionAudioPosition(uint8);

    void PlayMissionBankSound(uint8 sampleId, CVector& posn, CPhysical* physical, int16 a4, uint8 a5, uint8 a6, float a7, float a8, float a9);
    void PlayResidentSoundEvent(int16 a1, int16 a2, int16 a3, uint16 a4, CVector& posn, CPhysical* physical, float a7, float a8, int16 a9, float a10);
    void PlayLoadedMissionAudio(uint8);
    void PreloadMissionAudio(uint8, int32);

    void ProcessMissionAudioEvent(eAudioEvents eventId, CVector& posn, CPhysical* physical, float a6, float a7);
    void ReportMissionAudioEvent(eAudioEvents eventId, CPhysical* physical, float a4, float a5);
    void ReportMissionAudioEvent(eAudioEvents eventId, CVector& posn);

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;
    void Service();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEScriptAudioEntity* Constructor();
    void UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos);
};

VALIDATE_SIZE(CAEScriptAudioEntity, 0x21C);
