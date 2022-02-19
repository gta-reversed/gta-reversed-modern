#pragma once

#include "Base.h"

#include "Vector.h"

class CEntity;

struct InteriorObject {
    CEntity* m_pObject;
    int32    m_nModelId;
    int32    m_nInteriorId;
    CVector  m_vPosition;
    bool     m_bIsStolen;
    int8     m_field_19[3];
};
