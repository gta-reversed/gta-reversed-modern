#include "StdInc.h"
#include "TaskSimpleIKPointArm.h"

void CTaskSimpleIKPointArm::InjectHooks() {
    RH_ScopedClass(CTaskSimpleIKPointArm);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Constructor, 0x634150);
    RH_ScopedInstall(Destructor, 0x634240);

    // RH_ScopedInstall(UpdatePointArmInfo, 0x634370);
    // RH_ScopedInstall(Clone_Reversed, 0x634250);
    RH_ScopedInstall(GetTaskType_Reversed, 0x634230);
    // RH_ScopedInstall(CreateIKChain_Reversed, 0x6342F0);
}

// 0x634150
CTaskSimpleIKPointArm::CTaskSimpleIKPointArm(const char* purpose, int32 arm, CEntity* targetEntity, ePedBones offsetBone, RwV3d offsetPosn, float speed, int32 blendTime) :
    CTaskSimpleIKChain{ purpose, arm ? BONE_L_HAND : BONE_R_HAND, CVector{ 0.f, 0.05f, 0.f }, BONE_NORMAL, targetEntity, offsetBone, offsetPosn, speed, 999'999, blendTime },
    m_hand{arm}
{
}

// 0x634240
CTaskSimpleIKPointArm::~CTaskSimpleIKPointArm() {}

CTaskSimpleIKPointArm* CTaskSimpleIKPointArm::Constructor(const char* purpose, int32 hand, CEntity* targetEntity, ePedBones bone, RwV3d offsetPosn, float speed, int32 blendTime) {
    this->CTaskSimpleIKPointArm::CTaskSimpleIKPointArm(purpose, hand, targetEntity, bone, offsetPosn, speed, blendTime);
    return this;
}

// 0x634240
CTaskSimpleIKPointArm* CTaskSimpleIKPointArm::Destructor() {
    this->CTaskSimpleIKPointArm::~CTaskSimpleIKPointArm();
    return this;
}

// 0x634370
void CTaskSimpleIKPointArm::UpdatePointArmInfo(const char* name, CEntity* entity, ePedBones offsetBoneTag, RwV3d posn, float speed, int32 timeOffset) {
    plugin::CallMethod<0x634370, CTaskSimpleIKPointArm*, const char*, CEntity*, ePedBones, RwV3d, float, int32>(this, name, entity, offsetBoneTag, posn, speed, timeOffset);
}

// 0x634250
CTaskSimpleIKPointArm* CTaskSimpleIKPointArm::Clone() {
    return plugin::CallMethodAndReturn<CTaskSimpleIKPointArm*, 0x634250, CTaskSimpleIKPointArm*>(this);
}

// 0x6342F0
bool CTaskSimpleIKPointArm::CreateIKChain(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x6342F0, CTaskSimpleIKPointArm*, CPed*>(this, ped);
}
