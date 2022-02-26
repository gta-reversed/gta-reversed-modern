#pragma once

#include "Base.h"
#include <rwplcore.h>

#include "ListItem_c.h"
#include "BoneNode_c.h"
#include "Vector.h"

class CEntity;
class CPed;

class IKChain_c : public ListItem_c {
public:
    void Update();
public:
  CPed *m_ped;
  int32 m_count;
  BoneNode_c *m_bones; // BoneNode_c[m_count] -> Array
  RwMatrix *m_matrix;
  float m_blend;
  uint16 m_animId;
  CVector m_bonePosn;
  int32 gap2C;
  CEntity *m_entity;
  int32 m_offsetBoneTag;
  CVector m_offsetPos;
  float float44;
  CVector m_vec;
  uint8 m_targetMB;
  uint8 m_indexInList;
  int8  m_priority;
};
VALIDATE_SIZE(IKChain_c, 0x58);
