#pragma once

#include "TaskComplex.h"
#include "Vector.h"
#include "Base.h"

class CEntity;

class CTaskComplexSmartFleeEntity : public CTaskComplex {
public:
    CEntity* m_Entity;
    CVector  m_Pos;
    int32    m_dword1C;
    float    m_dword20;
    uint8    m_byte24;
    int32    m_dword28;
    float    m_dword2C;
    int32    m_dword30;
    uint32   m_nTime;
    int32    m_dword38;
    bool     m_byte3C;
    uint8    m_byte3D;

public:
    static constexpr auto Type = TASK_COMPLEX_SMART_FLEE_ENTITY;

    CTaskComplexSmartFleeEntity(CEntity * entity_1, bool a3, float a4, int32 a5, int32 a6, float a7);
    ~CTaskComplexSmartFleeEntity() override;

    eTaskType GetTaskType() override { return Type; } // 0x65C4C0
    CTask* Clone() override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType);

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexSmartFleeEntity* Constructor(CEntity* entity_1, bool a3, float a4, int32 a5, int32 a6, float a7) { this->CTaskComplexSmartFleeEntity::CTaskComplexSmartFleeEntity(entity_1, a3, a4, a5, a6, a7); return this; }
    CTaskComplexSmartFleeEntity* Destructor() { this->CTaskComplexSmartFleeEntity::~CTaskComplexSmartFleeEntity(); return this; }
};
VALIDATE_SIZE(CTaskComplexSmartFleeEntity, 0x40);
