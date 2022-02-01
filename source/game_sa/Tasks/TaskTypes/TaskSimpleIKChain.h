/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
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
    int32		m_time;
    int32		m_blendTime;
    void* 	m_pIKChain;
    int16		m_slotID;
    int16 		m_pivotBoneTag;
    int16 		m_effectorBoneTag;
private:
    char _pad[2];
public:
    RwV3d		m_effectorVec;
    CEntity*	m_pEntity;
    int32		m_offsetBoneTag;
    RwV3d		m_offsetPos;
    float 		m_speed;
    bool		m_bEntityExist;
private:
    char _pad2[3];
public:
    // blending info
    float		m_blend;
    int32		m_endTime;
    float		m_targetBlend;
    int32		m_targetTime;
    int32		m_isBlendingOut;

    CTaskSimpleIKChain(char* _IGNORED_ idString ,int32 effectorBoneTag,RwV3d effectorVec,int32 pivotBoneTag,
        CEntity* pEntity,int32 offsetBoneTag, RwV3d offsetPos,float speed,int32 time,int32 blendTime);
};

VALIDATE_SIZE(CTaskSimpleIKChain, 0x58);
