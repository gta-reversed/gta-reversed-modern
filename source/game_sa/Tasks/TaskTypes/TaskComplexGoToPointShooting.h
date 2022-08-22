#pragma once

#include "TaskComplexGoToPointAiming.h"

class CTaskComplexGoToPointShooting : public CTaskComplexGoToPointAiming {
public:
    static constexpr auto Type = TASK_COMPLEX_GO_TO_POINT_SHOOTING;

    CTaskComplexGoToPointShooting(int32 a2, const CVector& a3, CEntity* a4, CVector a5, float a6, float a7);
    ~CTaskComplexGoToPointShooting() override = default;

    eTaskType GetTaskType() override { return Type; } // 0x668CC0
    CTask* Clone() override { return new CTaskComplexGoToPointAiming(dwordC, v20, m_Entity, v14, float2C, float30); } // 0x66CE10

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexGoToPointShooting* Constructor(int32 arg0, CVector const& arg1, CEntity* arg2, CVector arg3, float arg4, float arg5) { this->CTaskComplexGoToPointShooting::CTaskComplexGoToPointShooting(arg0, arg1, arg2, arg3, arg4, arg5); return this; }
};
