#pragma once

#include "AEWaterCannonAudioEntity.h"

class CVector;

class CWaterCannon {
public:
    static constexpr uint32 SECTIONS_COUNT = 32;

    uint32                    m_nId;
    int32                     m_nSectionsCount;
    uint32                    m_nCreationTime;
    CVector                   m_sectionPoint[SECTIONS_COUNT];
    CVector                   m_sectionMoveSpeed[SECTIONS_COUNT];
    bool                      m_abUsed[SECTIONS_COUNT];
    CAEWaterCannonAudioEntity m_Audio;
    char                      field_3BC[16];

    static inline std::array<RxVertexIndex, 18>& m_auRenderIndices = *(std::array<RxVertexIndex, 18>*)0xC80700;

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

private:
    // NOTSA
    bool IsSectionActive(size_t idx) const;
    CVector GetSectionPosn(size_t idx) const;
    CVector GetSectionMoveSpeed(size_t idx) const;
    CBoundingBox GetSectionsBoundingBox() const;
};

VALIDATE_SIZE(CWaterCannon, 0x3CC);
