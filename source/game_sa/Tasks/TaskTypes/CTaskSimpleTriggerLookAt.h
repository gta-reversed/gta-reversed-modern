/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"
#include "CEntity.h"


class CTaskSimpleTriggerLookAt : public CTaskSimple {
public:
    CEntity*	m_pEntity;
    int32		m_time;
    int32		m_offsetBoneTag;
    RwV3d		m_offsetPos;
    bool m_bUseTorso;
private:
    char _pad[3];
public:
    float m_fSpeed;
    int32 m_BlendTime;
    bool m_bEntityExist;
    char m_priority;
private:
    char _pad2[2];
public:

    CTaskSimpleTriggerLookAt(CEntity* pEntity, int32 time, int32 offsetBoneTag, RwV3d offsetPos,
        bool bUseTorso = true, float speed = 0.25f, int32 blendTime = 1000, int32 priority = 3);

};

VALIDATE_SIZE(CTaskSimpleTriggerLookAt, 0x30);
