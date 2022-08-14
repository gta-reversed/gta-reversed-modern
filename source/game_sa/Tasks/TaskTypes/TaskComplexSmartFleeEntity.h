#pragma once

#include "TaskComplex.h"
#include "Vector.h"
#include "Base.h"

class CEntity;

class CTaskComplexSmartFleeEntity : public CTaskComplex {
public:
    CEntity*  m_entity  = {}; // 0xC
    CVector   m_posn    = {}; // 0x10
    int32     m_dword1C = {}; // 0x1C
    float     m_dword20 = {}; // 0x20
    uint8     m_byte24  = {}; // 0x24
    int32     m_dword28 = {}; // 0x28
    float     m_dword2C = {}; // 0x2C
    int32     m_dword30 = {}; // 0x30
    uint32    m_nTime   = {}; // 0x34
    int32     m_dword38 = {}; // 0x38
    bool      m_byte3C  = {}; // 0x3C
    uint8     m_byte3D  = {}; // 0x3D

public:
    static void InjectHooks();

    CTaskComplexSmartFleeEntity(CEntity * entity_1, bool a3, float a4, int32 a5, int32 a6, float a7);
    ~CTaskComplexSmartFleeEntity();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_SMART_FLEE_ENTITY;

    virtual CTask*    Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual CTask*    CreateNextSubTask(CPed * ped);
    virtual CTask*    CreateFirstSubTask(CPed * ped);
    virtual CTask*    ControlSubTask(CPed * ped);

private: // Wrappers for hooks
    // 0x65C430
    CTaskComplexSmartFleeEntity* Constructor(CEntity * entity_1, bool a3, float a4, int32 a5, int32 a6, float a7) {
        this->CTaskComplexSmartFleeEntity::CTaskComplexSmartFleeEntity(entity_1, a3, a4, a5, a6, a7);
        return this;
    }

    // 0x65C4D0
    CTaskComplexSmartFleeEntity* Destructor() {
        this->CTaskComplexSmartFleeEntity::~CTaskComplexSmartFleeEntity();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexSmartFleeEntity, 0x40);
