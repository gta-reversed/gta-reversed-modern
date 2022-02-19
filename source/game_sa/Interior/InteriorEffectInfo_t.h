#pragma once

#include "Base.h"

#include "Vector.h"

class C2dEffect;
class CEntity;

struct InteriorEffectInfo_t {
    CEntity* m_entity;
    int32 m_effectCount;
    C2dEffect* m_effect[8];
    int32 m_effectIndicesInModelInfo[8];
    int32 m_field_48;
    bool m_field_4C;
    int8 m_field_4D[3];
};
VALIDATE_SIZE(InteriorEffectInfo_t, 0x50);
