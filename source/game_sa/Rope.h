/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CEntity;
class CObject;

class CRope {
public:
    CVector  m_avecRopeSegments[32];
    CVector  m_avecRopeSegmentsReleased[32];
    int32    m_nId;
    float    field_304;
    float    m_fMass;
    float    m_fRopeTotalLength;
    CEntity* m_pRopeHolder;
    CObject* m_pRopeAttachObject;
    CEntity* m_pAttachedEntity;
    float    m_fRopeSegmentLength;
    uint32   m_nTime;
    uint8    m_nNumSegments;
    uint8    m_nRopeType;
    uint8    m_nFlags1;
    uint8    m_nFlags2;

    void CreateHookObjectForRope();
    void PickUpObject(CEntity* object);
    void ReleasePickedUpObject();
    void Remove();
    void Render();
    void Update();
    void UpdateWeightInRope(CVector a1, float a2, CVector* a3);
};

VALIDATE_SIZE(CRope, 0x328);
