#pragma once

#include "CAEWaterCannonAudioEntity.h"

class CVector;

class CWaterCannon {
public:
    static constexpr unsigned int SECTIONS_COUNT = 32;
    static constexpr unsigned int NUM_INDICES = 18;

    unsigned int               m_nId;
    int                        m_nSectionsCount;
    unsigned int               m_nCreationTime;
    CVector                    m_sectionPoint[SECTIONS_COUNT];
    CVector                    m_sectionMoveSpeed[SECTIONS_COUNT];
    char                       m_anSectionState[SECTIONS_COUNT];
    CAEWaterCannonAudioEntity  m_audio;
    char                       field_3BC[16];

    static RxVertexIndex (&m_auRenderIndices)[NUM_INDICES];

public:
    static void InjectHooks();

    CWaterCannon();
    CWaterCannon* Constructor();

    ~CWaterCannon();
    CWaterCannon* Destructor();

    void Init();
    bool HasActiveSection() const;
    void Update_OncePerFrame(short);
    void Update_NewInput(CVector* start, CVector* end);
    void PushPeds();
    void Render();

private:
    // NOTSA
    bool IsSectionActive(size_t idx) const;
    CVector GetSectionPosn(size_t idx) const;
    CVector GetSectionMoveSpeed(size_t idx) const;
    CBoundingBox GetBounding() const;
};

VALIDATE_SIZE(CWaterCannon, 0x3CC);
