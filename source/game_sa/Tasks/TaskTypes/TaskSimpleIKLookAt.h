/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimple.h"
#include "AnimBlendAssociation.h"
#include "TaskSimpleIKChain.h"


class CTaskSimpleIKLookAt : public CTaskSimpleIKChain {
public:
    bool    m_bUseTorso;
    char     m_priority;

    CTaskSimpleIKLookAt(char* idString _IGNORED_ ,CEntity* pEntity,int32 time,int32 offsetBoneTag, RwV3d offsetPos,
        bool bUseTorso,float speed,int32 blendTime,int32 m_priority);
};

VALIDATE_SIZE(CTaskSimpleIKLookAt, 0x5C);
