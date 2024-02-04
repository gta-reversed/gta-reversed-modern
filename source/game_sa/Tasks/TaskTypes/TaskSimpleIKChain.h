#pragma once

#include "Base.h"
#include <rwplcore.h>
#include "TaskSimple.h"
#include <extensions/WEnum.hpp>

class CEntity;
class CPed;
class CTaskSimpleIKChain;
class IKChain_c;

class NOTSA_EXPORT_VTABLE CTaskSimpleIKChain : public CTaskSimple {
public:
    static constexpr auto Type = TASK_SIMPLE_IK_CHAIN;

    CTaskSimpleIKChain(const char* name, ePedBones effectorBoneTag, CVector effectorPos, ePedBones pivotBoneTag, CEntity* entity, ePedBones offsetBoneTag, CVector offsetPos,
                       float speed, int32 time, int32 blendTime);
    ~CTaskSimpleIKChain() override;


    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override; // 0x62EC30
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;

    virtual bool CreateIKChain(CPed* ped);

    void BlendOut(int32 blendOutTime = 250);
    IKChain_c* GetIKChain() const;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleIKChain* Constructor(char* name, ePedBones effectorBoneTag, RwV3d effectorVec, ePedBones pivotBoneTag, CEntity* a6, ePedBones offsetBoneTag, RwV3d offsetPos, float speed, int32 time, int32 blendTime) { this->CTaskSimpleIKChain::CTaskSimpleIKChain(name, effectorBoneTag, effectorVec, pivotBoneTag, a6, offsetBoneTag, offsetPos, speed, time, blendTime); return this; }
    CTaskSimpleIKChain* Destructor() { this->CTaskSimpleIKChain::~CTaskSimpleIKChain(); return this; }

public:
    int32                      m_Duration{};
    int32                      m_BlendDuration{};
    IKChain_c*                 m_IKChain{};
    int16                      m_SlotId{};
    ePedBones                  m_PivotBoneTag{};
    ePedBones                  m_EffectorBoneTag{};
    CVector                    m_EffectorVec{};
    CEntity::Ref               m_Entity{};
    notsa::WEnumS32<ePedBones> m_OffsetBoneTag;
    CVector                    m_OffsetPos{};
    float                      m_Speed{};
    bool                       m_EntityExisted{};
    float                      m_Blend{};
    int32                      m_EndTime{};
    float                      m_TargetBlend{};
    int32                      m_TargetTime{};
    int32                      m_IsBlendingOut{};
};
VALIDATE_SIZE(CTaskSimpleIKChain, 0x58);
