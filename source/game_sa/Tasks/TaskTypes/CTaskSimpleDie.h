#include "CTaskSimple.h"

class CAnimBlendHierarchy;
class CAnimBlendAssociation;

class CTaskSimpleDie : public CTaskSimple
{
    std::int32_t m_animGroupId;
    std::int32_t m_animId;
    CAnimBlendHierarchy* m_animHierarchy;
    std::uint32_t m_animFlags;
    float m_blendDelta;
    float m_animSpeed;
    std::uint8_t m_flags;
private:
    std::uint8_t padding[3];
public:
    CAnimBlendAssociation* m_animAssociation;
};

VALIDATE_SIZE(CTaskSimpleDie, 0x28);
