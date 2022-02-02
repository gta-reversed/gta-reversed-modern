/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CEntity;
class CObject;

// TODO: Find out what CRANE_MAGNET1/2/3/4 is exactly..
enum class eRopeType : uint8 {
    NONE,
    CRANE_MAGNET1,
    CRANE_HARNESS,
    MAGNET,
    CRANE_MAGNET2,
    WRECKING_BALL,
    CRANE_MAGNET3,
    CRANE_MAGNET4
};

constexpr auto NUM_ROPE_SEGMENTS{ 32u };

class CRope {
public:
    CVector    m_aSegments[NUM_ROPE_SEGMENTS];
    CVector    m_aSegmentsReleased[NUM_ROPE_SEGMENTS];
    int32      m_nId;
    float      m_fGroundZ;
    float      m_fMass;
    float      m_fTotalLength;
    CEntity*   m_pRopeHolder;
    CEntity*   m_pAttachedEntity; // CPhysical?
    CPhysical* m_pRopeAttachObject;
    float      m_fSegmentLength;
    uint32     m_nTime;
    uint8      m_nSegments;
    eRopeType  m_nType;
    uint8      m_nFlags1;
    uint8      m_nFlags2;

public:
    static void InjectHooks();

    void ReleasePickedUpObject();
    ModelIndex GetModelForType() const;
    void CreateHookObjectForRope();
    int8 UpdateWeightInRope(float a2, float a3, float a4, int32 a5, float* a6);
    void Remove();
    void Render();
    void PickUpObject(CPhysical* obj);
    void Update();
};

VALIDATE_SIZE(CRope, 0x328);
