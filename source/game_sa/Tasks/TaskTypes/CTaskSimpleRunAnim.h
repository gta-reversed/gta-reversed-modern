/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimpleAnim.h"
#include "CAnimBlendAssociation.h"

class  CTaskSimpleRunAnim : public CTaskSimpleAnim {
protected:
    CTaskSimpleRunAnim(plugin::dummy_func_t a) : CTaskSimpleAnim(a) {}
public:

    unsigned int m_nAnimGroup;
    unsigned int m_nAnimId;
    float m_fBlendDelta;
    unsigned short m_nTaskType;
private:
    short __pad;
public:

    CTaskSimpleRunAnim(unsigned int animGroup, unsigned int animID, float fBlendDelta, bool bHoldLastFrame);
    CTaskSimpleRunAnim(unsigned int animGroup, unsigned int animID, float fBlendDelta, unsigned int nTaskType,
        char* pTaskName _IGNORED_, bool bHoldLastFrame);

};

VALIDATE_SIZE(CTaskSimpleRunAnim, 0x20);
