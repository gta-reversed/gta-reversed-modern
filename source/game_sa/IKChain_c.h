#pragma once

#include "Base.h"
#include <rwplcore.h>
#include <span>

#include "ListItem_c.h"
#include "BoneNode_c.h"
#include "Vector.h"

class CEntity;
class CPed;

class IKChain_c : public ListItem_c<IKChain_c> {
public:
    static void InjectHooks();

    IKChain_c() = default;
    ~IKChain_c() = default;

    bool Init(const char* name, int32 indexInList, CPed* ped, ePedBones bone, RwV3d bonePosn, ePedBones bone2, CEntity* entity, int32 offsetBoneTag, RwV3d posn, float speed, int8 priority);
    void Exit();
    void Update(float timeStep);
    bool IsAtTarget(float maxDist, float* outDist) const;
    bool IsFacingTarget();
    void UpdateTarget(bool target);
    void UpdateOffset(int32 offsetBoneTag, CVector offsetPosn);
    void ClampLimits(int32 boneTag, bool LimitX, bool LimitY, bool LimitZ, bool UseCurrentLimits);
    void UpdateEntity(CEntity* entity);
    BoneNode_c* GetBoneNodeFromTag(int32 tag);
    int8 GetPriority() const;
    void SetOffsetPos(CVector value);
    void SetOffsetBoneTag(int32 value);
    void SetBlend(float value);
    void MoveBonesToTarget();
    void SetupBones(ePedBones boneTag, CVector posn, ePedBones bone, AnimBlendFrameData* frames);
    void GetLimits(int32 boneTag, eRotationAxis axis, float& outMin, float& outMax);

    auto GetBones() { return std::span{ m_Bones, (size_t)m_Count }; }

public:
    CPed*        m_Ped;
    int32        m_Count;
    BoneNode_c** m_Bones; // BoneNode_c*[m_count] -> Array
    RwMatrix*    m_Matrix;
    float        m_Blend;
    uint16       m_Bone1;
    RwV3d        m_BonePosn;
    ePedBones    m_Bone;
    CEntity*     m_Entity;
    int32        m_OffsetBoneTag; // ePedBones.. Just that we have to use int32 here... :D
    CVector      m_OffsetPos;
    float        m_Speed;
    CVector      m_Offset;   //< `m_offsetPos` transformed with `m_entity`'s modelling matrix. See `MoveBonesToTarget`
    bool         m_TargetMB; // Mouse Button
    uint8        m_IndexInList;
    int8         m_Priority;
};
VALIDATE_SIZE(IKChain_c, 0x58);
