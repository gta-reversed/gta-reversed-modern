/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CObject.h"

class  CCutsceneObject : public CObject {
public:
    union {
        RwFrame *m_pAttachTo;
        unsigned int m_nAttachBone; // this one if m_pAttachmentObject != 0
    };
    CObject *m_pAttachmentObject;
    CVector m_vWorldPosition;
    CVector m_vForce;
};

VALIDATE_SIZE(CCutsceneObject, 0x19C);