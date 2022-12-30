#pragma once

#include "Base.h"
#include "Vector.h"

class CEntity;

struct InteriorInfo_t {
    int8     m_actionType;             // 0x0
    bool     m_goToInfoTaskCreated;    // 0x1
    int8     m_field_2;                // 0x2
    int8     m_field_3;                // 0x3
    CVector  m_position;               // 0x4
    CVector  m_targetPoint;            // 0x10
    CEntity* m_entityIgnoredCollision; // 0x1C
};
VALIDATE_SIZE(InteriorInfo_t, 0x20);
