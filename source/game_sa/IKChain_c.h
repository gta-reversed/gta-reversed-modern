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
    static void InjectHooks();

    void Exit();
    void Update(float unused);
    bool Init(const char* name, int32 indexInList, CPed* ped, int32 animId, RwV3d bonePosn, int32 animId1, CEntity* entity, int32 offsetBoneTag, RwV3d posn, float a11, int32 priority);
    bool IsAtTarget(float a2, float* a3);
    bool IsFacingTarget();
    void UpdateTarget(uint8 target);
    void UpdateOffset(int32 offsetBoneTag, RwV3d offsetPosn);
    void ClampLimits(int32 a1, uint8 a2, uint8 a3, uint8 a4, int32 a5);
    void UpdateEntity(CEntity* entity);
    BoneNode_c* GetBoneNodeFromTag(int32 a2);
    int8 GetPriority();
    void SetOffsetPos(RwV3d value);
    void SetOffsetBoneTag(int32 value);
    void SetBlend(float value);
    void MoveBonesToTarget();
    void SetupBones(int32 a2, RwV3d posn, int32 animId, AnimBlendFrameData* a7);
    void GetLimits(int32 a2, int32 type, float* a3, float* a4);

public:
    CPed* m_ped;
    int32 m_count;
    BoneNode_c* m_bones; // BoneNode_c[m_count] -> Array
    RwMatrix* m_matrix;
    float m_blend;
    uint16 m_animId;
    CVector m_bonePosn;
    int32 gap2C;
    CEntity* m_entity;
    int32 m_offsetBoneTag;
    CVector m_offsetPos;
    float float44;
    CVector m_vec;
    uint8 m_targetMB;
    uint8 m_indexInList;
    int8 m_priority;
};
VALIDATE_SIZE(IKChain_c, 0x58);
