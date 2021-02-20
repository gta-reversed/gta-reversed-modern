#include "StdInc.h"

CAETwinLoopSoundEntity::CAETwinLoopSoundEntity() : CAEAudioEntity()
{
    m_bIsInitialised = 0;
    for (size_t i = 0; i < 2; ++i)
        m_apSounds[i] = nullptr;
}

CAETwinLoopSoundEntity::CAETwinLoopSoundEntity(short wBankSlotId,
                                               short wSoundType1,
                                               short wSoundType2,
                                               CAEAudioEntity* pAudioEntity,
                                               short wPlayTimeMin,
                                               short wPlayTimeMax,
                                               short wStartingPlayPercent1,
                                               short wStartingPlayPercent2) : CAEAudioEntity()
{
    m_nBankSlotId = wBankSlotId;
    m_nSoundType[0] = wSoundType1;
    m_nSoundType[1] = wSoundType2;
    m_pBaseAudio = pAudioEntity;
    m_nPlayTimeMin = wPlayTimeMin;
    m_nPlayTimeMax = wPlayTimeMax;
    field_8A = -1;
    field_8C = -1;

    for (size_t i = 0; i <= 1; ++i)
        m_apSounds[i] = nullptr;

    m_bPlayingFirstSound = true;
    m_anStartingPlayPercentage[0] = wStartingPlayPercent1;
    m_anStartingPlayPercentage[1] = wStartingPlayPercent2;
    m_bIsInitialised = 1;
}

CAETwinLoopSoundEntity::~CAETwinLoopSoundEntity()
{
    if (!m_bIsInitialised)
        return;

    for (size_t i = 0; i <= 2; ++i) {
        if (!m_apSounds[i])
            continue;

        m_apSounds[i]->StopSoundAndForget();
        m_apSounds[i] = nullptr;
    }
    m_bIsInitialised = 0;
}
