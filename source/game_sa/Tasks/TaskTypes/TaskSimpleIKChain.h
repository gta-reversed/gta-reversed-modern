/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimple.h"
#include "AnimBlendAssociation.h"
#include "Entity.h"


class CTaskSimpleIKChain : public CTaskSimple {
public:
    int32    m_nTime;
    int32    m_nBlendTime;
    void*    m_pIKChain;
    int16    m_nAlotId;
    int16    m_nPivotBoneTag;
    int16    m_nEffectorBoneTag;
    RwV3d    m_vecEffectorVec;
    CEntity* m_pEntity;
    int32    m_nOffsetBoneTag;
    RwV3d    m_vecOffsetPos;
    float    m_fSpeed;
    bool     m_bEntityExist;
    float    m_fBlend;
    int32    m_nEndTime;
    float    m_fTargetBlend;
    int32    m_nTargetTime;
    int32    m_bIsBlendingOut;

public:
    CTaskSimpleIKChain(char* idString,
                       int32 effectorBoneTag,
                       RwV3d effectorVec,
                       int32 pivotBoneTag,
                       CEntity* entity,
                       int32 offsetBoneTag,
                       RwV3d offsetPos,
                       float speed,
                       int32 time,
                       int32 blendTime);
};

VALIDATE_SIZE(CTaskSimpleIKChain, 0x58);
