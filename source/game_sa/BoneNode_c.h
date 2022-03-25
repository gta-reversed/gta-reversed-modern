#pragma once

#include "Base.h"

#include "List_c.h"
#include "ListItem_c.h"

#include <rwplcore.h>
#include <rtquat.h>

class BoneNode_c : public ListItem_c {
public:
    int32                    m_BoneTag;
    RpHAnimBlendInterpFrame* m_InterpFrame;
    RtQuat                   m_Orientation;
    RwV3d                    m_Pos;
    BoneNode_c*              m_Parent;
    TList_c<BoneNode_c>      m_Childs;
    RwMatrix                 m_WorldMat;
    RwV3d                    m_LimitMin;
    RwV3d                    m_LimitMax;
    float                    m_Speed;

public:
    static void InjectHooks();

    BoneNode_c() = default;  // 0x616B30
    ~BoneNode_c() = default; // 0x616B80

    bool Init(int32 boneTag, RpHAnimBlendInterpFrame* interpFrame);
    void InitLimits();

    // Originally these 2 took in the return value as a pointer, lets see if this is ABI compatible..
    static RtQuat EulerToQuat(RwV3d* vec);
    static RwV3d  QuatToEuler(RtQuat* quat);
    static int32  GetIdFromBoneTag(ePedBones bone);

    void ClampLimitsCurrent(bool LimitX, bool LimitY, bool LimitZ);
    void ClampLimitsDefault(bool LimitX, bool LimitY, bool LimitZ);

    void Limit(float lim);

    void BlendKeyframe(float blend);

    float GetSpeed() const;
    void SetSpeed(float);

    void SetLimits(eRotationAxis axis, float min, float max);
    void GetLimits(eRotationAxis axis, float& min, float& max);

    void AddChild(BoneNode_c * children);
    RwMatrix* CalcWldMat(const RwMatrix* boneMatrix);

    const auto& GetPosition() const { return *RwMatrixGetPos(&m_WorldMat); }
    const auto& GetMatrix() const { return m_WorldMat;  }

private:
    BoneNode_c* Constructor() { this->BoneNode_c::BoneNode_c(); return this; }
    BoneNode_c* Destructor() { this->BoneNode_c::~BoneNode_c(); return this; }
};
VALIDATE_SIZE(BoneNode_c, 0x98);
