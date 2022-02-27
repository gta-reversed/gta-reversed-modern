#pragma once

#include "Base.h"

#include "List_c.h"
#include "ListItem_c.h"
#include <rwplcore.h>
#include <rtquat.h>

class BoneNode_c : public ListItem_c {
public:
    BoneNode_c() = default;
    ~BoneNode_c() = default;

    int32 m_boneTag;
    RtQuat* m_interpFrame;
    RtQuat m_orientation;
    RwV3d m_pos;
    BoneNode_c* m_parent;
    TList_c<BoneNode_c> m_childs;
    RwMatrix m_worldMat;
    RwV3d m_limitMin;
    RwV3d m_limitMax;
    float m_speed;
public:
    static void InjectHooks();

    BoneNode_c() = default;
    ~BoneNode_c() = default;

    // Originally these 2 took in the return value as a pointer, lets see if this is ABI compatible..
    static RtQuat EulerToQuat(RwV3d * a1);
    static RwV3d  QuatToEuler(RtQuat * quat);
    static  int32 GetIdFromBoneTag(ePedBones bone);

    void ClampLimitsCurrent(uint8 a2, uint8 a3, uint8 a4);
    void ClampLimitsDefault(uint8, uint8, uint8);
    void InitLimits();
    void Limit(float float_1);
    void BlendKeyframe(float blend);
    void SetSpeed(float);
    double GetSpeed();
    void SetLimits(int32 type, float min, float max);
    void GetLimits(int32 type, float* pMin, float* pMax);
    void AddChild(BoneNode_c * children);
    RwMatrixTag* CalcWldMat(RwMatrixTag * boneMatrix);
    int8_t Init(int32 a2, RpHAnimBlendInterpFrame * a3);

private:
    BoneNode_c* Constructor() {
        this->BoneNode_c::BoneNode_c();
        return this;
    }
    BoneNode_c* Destructor() {
        this->BoneNode_c::~BoneNode_c();
        return this;
    }
};
VALIDATE_SIZE(BoneNode_c, 0x98);
