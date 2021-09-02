#pragma once

#include "ListItem_c.h"
#include "CObject.h"

#ifdef GetObject
#undef GetObject
#endif

enum eWaterCreatureType : uint8 {
    FISH1,
    FISH2,
    FISH3,
    JELLYFISH1,
    JELLYFISH2,
    TURTLE,
    DOLPHIN
};

class WaterCreature_c : public ListItem_c
{
public:
    WaterCreature_c() : ListItem_c(), m_pObject(nullptr) {}
    ~WaterCreature_c() = default;
public:
    CObject*         m_pObject;
    uint8            m_nCreatureType; // see eWaterCreatureType
    uint8            m_bShouldBeDeleted;
    uint8            m_ucTargetSwimSpeed;
    unsigned __int8  pad;
    int16_t          m_wSpeedChangeCurTime;
    int16_t          m_wSpeedChangeTotalTime;
    float            m_fDefaultSpeed;
    float            m_fCurSpeed;
    WaterCreature_c* m_pFollowedCreature;
    CVector          m_vecOffsetFromFollowed;
    float            m_fHeading;
    bool             m_bChangedDir;

public:
    static void InjectHooks();

    bool Init(int32 nType, CVector* pVecPos, WaterCreature_c* pParent, float fWaterLevel, float fWaterDepth);
    void Exit();
    void Update(float fTimeStep);

public:
    CObject* GetObject() const { return m_pObject; }
    bool IsJellyfish() const { return m_nCreatureType == JELLYFISH1 || m_nCreatureType == JELLYFISH2; }
    bool IsSmallFish() const {
        return m_nCreatureType == FISH1
            || m_nCreatureType == FISH2
            || m_nCreatureType == FISH3;
    }
};
VALIDATE_SIZE(WaterCreature_c, 0x34);
