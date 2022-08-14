#pragma once
#include "TaskComplex.h"
#include "Vector.h"

class CPedGroup;

class CTaskComplexGangFollower : public CTaskComplex {
public:
    CPedGroup* m_PedGroup = {};    // 0xC
    CPed* m_Ped = {};              // 0x10
    CVector m_PedPosn = {};        // 0x14
    CVector dword20 = {};          // 0x20
    CVector dword2C = {};          // 0x2C
    float dword38 = {};            // 0x38
    uint8 byte3C = {};             // 0x3C
    uint8 m_Flags = {};            // 0x3D
    uint8 gap3E[2] = {};           // 0x3E
    int32 dword40 = {};            // 0x40
    int32 dword44 = {};            // 0x44
    uint8 byte48 = {};             // 0x48
    uint8 byte49 = {};             // 0x49

public:
    static void InjectHooks();

    ~CTaskComplexGangFollower();
    CTaskComplexGangFollower(CPedGroup* pedGroup, CPed* ped, uint8 uint8, CVector pos, float a6);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GANG_FOLLOWER;

    int32 CalculateOffsetPosition(CVector& pos);

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x65EAA0
    CTaskComplexGangFollower* Constructor(CPedGroup* pedGroup, CPed* ped, uint8 uint8, CVector pos, float a6) {
        this->CTaskComplexGangFollower::CTaskComplexGangFollower(pedGroup, ped, uint8, pos, a6);
        return this;
    }

    // 0x65EBB0
    CTaskComplexGangFollower* Destructor() {
        this->CTaskComplexGangFollower::~CTaskComplexGangFollower();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexGangFollower, 0x4C);
