/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"
#include "CTaskSimpleIKChain.h"


class  CTaskSimpleIKLookAt : public CTaskSimpleIKChain {
protected:
    CTaskSimpleIKLookAt(plugin::dummy_func_t a) : CTaskSimpleIKChain(a) {}
public:
    bool    m_bUseTorso;
    char     m_priority;

    CTaskSimpleIKLookAt(char* idString _IGNORED_ ,CEntity* pEntity,int time,int offsetBoneTag, RwV3d offsetPos,
        bool bUseTorso,float speed,int blendTime,int m_priority);
};

VALIDATE_SIZE(CTaskSimpleIKLookAt, 0x5C);
