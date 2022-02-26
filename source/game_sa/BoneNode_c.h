#pragma once

#include "Base.h"

#include "List_c.h"
#include "ListItem_c.h"
#include <rwplcore.h>
#include <rtquat.h>

class BoneNode_c : public ListItem_c {
public:
    int32 m_boneTag;
    RtQuat* m_interpFrame;
    RtQuat m_orientation;
    RwV3d m_pos;
    BoneNode_c* m_parent;
    TList_c<BoneNode_c> m_childs;
    RwMatrix m_worldMat;
    float min_0;
    float min_1;
    float min_2;
    float max_0;
    float max_1;
    float max_2;
    float m_speed;
};
