#pragma once

#include "Base.h"
#include <rwplcore.h>
#include <span>

#include "ListItem_c.h"
#include "BoneNode_c.h"
#include "Vector.h"

class CEntity;
class CPed;

class IKChain_c : public ListItem_c {
public:
    static void InjectHooks();

    IKChain_c() = default;
    ~IKChain_c() = default;

    bool Init(const char* name, int32 indexInList, CPed* ped, ePedBones bone, RwV3d bonePosn, ePedBones bone2, CEntity* entity, int32 offsetBoneTag, RwV3d posn, float a11, int8 priority);
    void Exit();
    void Update(float unused);
    bool IsAtTarget(float a2, float& outDist);
    bool IsFacingTarget();
    void UpdateTarget(uint8 target);
    void UpdateOffset(int32 offsetBoneTag, RwV3d offsetPosn);
    void ClampLimits(int32 boneTag, bool LimitX, bool LimitY, bool LimitZ, bool UseCurrentLimits);
    void UpdateEntity(CEntity* entity);
    BoneNode_c* GetBoneNodeFromTag(int32 a2);
    int8 GetPriority();
    void SetOffsetPos(RwV3d value);
    void SetOffsetBoneTag(int32 value);
    void SetBlend(float value);
    void MoveBonesToTarget();
    void SetupBones(ePedBones boneTag, RwV3d posn, ePedBones bone, AnimBlendFrameData* a7);
    void GetLimits(int32 boneTag, eRotationAxis axis, float& outMin, float& outMax);

    auto GetBones() { return std::span{ m_bones, (size_t)m_count }; }

public:
    CPed* m_ped;
    int32 m_count;
    BoneNode_c** m_bones; // BoneNode_c*[m_count] -> Array
    RwMatrix* m_matrix;
    float m_blend;
    uint16 m_bone1;
    RwV3d m_bonePosn;
    ePedBones m_bone;
    CEntity* m_entity;
    int32 m_offsetBoneTag; // ePedBones.. Just that we have to use int32 here... :D
    CVector m_offsetPos;
    float m_speed;
    CVector m_offset; //< `m_offsetPos` transformed with `m_entity`'s modelling matrix. See `MoveBonesToTarget`
    uint8 m_targetMB;
    uint8 m_indexInList;
    int8 m_priority;
};
VALIDATE_SIZE(IKChain_c, 0x58);
