#pragma once

#include "CAEWaterCannonAudioEntity.h"

class CVector;

class CWaterCannon {
public:
    static constexpr uint32 SECTIONS_COUNT = 32;
    static constexpr uint32 NUM_INDICES = 18;

    uint32               m_nId;
    int32                        m_nSectionsCount;
    uint32               m_nCreationTime;
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
    void Update_OncePerFrame(int16);
    void Update_NewInput(CVector* start, CVector* end);
    void PushPeds();
    void Render();
};

VALIDATE_SIZE(CWaterCannon, 0x3CC);
