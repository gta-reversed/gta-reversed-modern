#pragma once

#include "Base.h"
#include "Vector.h"

class CEntity;

struct InteriorInfo_t {
    int8     m_actionType;
    bool     m_goToInfoTaskCreated;
    CVector  m_position;
    CVector  m_targetPoint;
    CEntity* m_entityIgnoredCollision;
};
VALIDATE_SIZE(InteriorInfo_t, 0x20);
