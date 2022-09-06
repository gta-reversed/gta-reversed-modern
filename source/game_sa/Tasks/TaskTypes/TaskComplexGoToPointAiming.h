#pragma once

#include "TaskComplex.h"
class CEntity;

class CTaskComplexGoToPointAiming : public CTaskComplex {
public:
    int32    dwordC;
    CEntity* m_Entity;
    CVector  v14;
    CVector  v20;
    float    float2C;
    float    float30;
    uint8    m_Flags;

public:
    static constexpr auto Type = eTaskType::TASK_COMPLEX_GO_TO_POINT_AIMING;

    CTaskComplexGoToPointAiming(int32 arg0, CVector const& arg1, CEntity* arg2, CVector arg3, float arg4, float arg5);
    ~CTaskComplexGoToPointAiming() override;

    eTaskType GetTaskType() override { return Type; } // 0x668860
    CTask* Clone() override { return new CTaskComplexGoToPointAiming(dwordC, v20, m_Entity, v14, float2C, float30); } // 0x66CD80
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType);

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexGoToPointAiming* Constructor(int32 arg0, CVector const& arg1, CEntity* arg2, CVector arg3, float arg4, float arg5) { this->CTaskComplexGoToPointAiming::CTaskComplexGoToPointAiming(arg0, arg1, arg2, arg3, arg4, arg5); return this; }
    CTaskComplexGoToPointAiming* Destructor() { this->CTaskComplexGoToPointAiming::~CTaskComplexGoToPointAiming(); return this; }
};
