#pragma once

#include "Base.h"

#include "Vector.h"

class C2dEffect;
class CEntity;

struct InteriorEffectInfo_t {
    CEntity*   m_pEntity;
    int32      m_nEffectCount;
    C2dEffect* m_pEffects[8];
    int32      m_nEffectIndicesInModelInfo[8];
    int32      m_field_48;
    bool       m_field_4C;
    int8       m_field_4D[3];
};
VALIDATE_SIZE(InteriorEffectInfo_t, 0x50);
