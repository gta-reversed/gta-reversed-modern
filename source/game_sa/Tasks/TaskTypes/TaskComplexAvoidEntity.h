#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CEntity;
class CColSphere;

class CTaskComplexAvoidEntity : CTaskComplex {
public:
    CEntity* m_Entity;
    int32    field_10;
    CVector  m_PedPos;
    CVector  f20;
    CVector  f2C;
    CVector  f38;
    int32    field_44;
    int32    field_48;
    char     field_4C;
    char     field_4D;
    char     field_4E;
    char     field_4F;
    union {
        struct {
            bool m_b1 : 1; // IK initialized
        };
        uint8 m_Flags;
    };

public:
    CTaskComplexAvoidEntity(int32, CEntity* entity, const CVector& pos);
    ~CTaskComplexAvoidEntity() override;

    CTask* Clone() override { return new CTaskComplexAvoidEntity(field_10, m_Entity, f20); } // 0x66D0C0
    eTaskType GetTaskType() override { return TASK_COMPLEX_AVOID_ENTITY; } // 0x66AAD0
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;

    bool ComputeDetourTarget(const CPed& ped);
    bool ComputeDetourTarget(const CPed& ped, const CColSphere& sphere);
    void ComputeAvoidSphere(const CPed& ped, CColSphere& sphere);

    static void ComputeSphere(CColSphere& sphere, CEntity** entities);
    void QuitIK(CPed* ped) const;
    void SetUpIK(CPed *ped);
    uint8 NearbyEntitiesInSphere(const CPed& ped, const CColSphere& sphere, CEntity**, CEntity **);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexAvoidEntity* Constructor(int32 a2, CEntity* entity, const CVector& pos) { this->CTaskComplexAvoidEntity::CTaskComplexAvoidEntity(a2, entity, pos); return this; };
    CTask* ControlSubTask_Reversed(CPed* ped) { return ControlSubTask(ped); }
    CTask* CreateFirstSubTask_Reversed(CPed* ped) { return CreateFirstSubTask(ped); }
    CTask* CreateNextSubTask_Reversed(CPed* ped) { return CreateNextSubTask(ped); }
};
VALIDATE_SIZE(CTaskComplexAvoidEntity, 0x54);
