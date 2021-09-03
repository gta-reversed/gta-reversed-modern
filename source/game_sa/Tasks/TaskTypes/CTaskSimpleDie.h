#include "CTaskSimple.h"

class CAnimBlendHierarchy;
class CAnimBlendAssociation;

class CTaskSimpleDie : public CTaskSimple
{
    int32 m_animGroupId;
    int32 m_animId;
    CAnimBlendHierarchy* m_animHierarchy;
    uint32 m_animFlags;
    float m_blendDelta;
    float m_animSpeed;
    uint8 m_flags;
private:
    uint8 padding[3];
public:
    CAnimBlendAssociation* m_animAssociation;
};

VALIDATE_SIZE(CTaskSimpleDie, 0x28);
