#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CEntity;
class CObject;

class CTaskComplexGotoDoorAndOpen : public CTaskComplex {
public:
    CEntity* m_pEntity = {};   // 0xC
    CVector m_vecStart = {};   // 0x10
    CVector m_vecEnd = {};     // 0x1C
    uint32 m_nStartTime = {};  // 0x28
    uint32 m_nOffsetTime = {}; // 0x2C
    uint8 byte30 = {};         // 0x30
    uint8 byte31 = {};         // 0x31
    uint8 gap32[2] = {};       // 0x32
    uint8 m_nFlags = {};       // 0x34

public:
    static void InjectHooks();

    ~CTaskComplexGotoDoorAndOpen();
    CTaskComplexGotoDoorAndOpen(CObject* door);
    CTaskComplexGotoDoorAndOpen(CVector const& start, CVector const& end);

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return TASK_COMPLEX_GOTO_DOOR_AND_OPEN; }
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private:
    CTaskComplexGotoDoorAndOpen* Constructor(CObject* door);
    CTaskComplexGotoDoorAndOpen* Constructor(CVector const& start, CVector const& end);
    CTaskComplexGotoDoorAndOpen* Destructor();

    // Virtual function hook wrappers
    CTask* Clone_Reversed() {
        return CTaskComplexGotoDoorAndOpen::Clone();
    }
    eTaskType GetTaskType_Reversed() {
        return CTaskComplexGotoDoorAndOpen::GetTaskType();
    }
    bool MakeAbortable_Reversed(CPed* ped, int32 priority, CEvent const* event) {
        return CTaskComplexGotoDoorAndOpen::MakeAbortable(ped, priority, event);
    }
    CTask* CreateNextSubTask_Reversed(CPed* ped) {
        return CTaskComplexGotoDoorAndOpen::CreateNextSubTask(ped);
    }
    CTask* CreateFirstSubTask_Reversed(CPed* ped) {
        return CTaskComplexGotoDoorAndOpen::CreateFirstSubTask(ped);
    }
    CTask* ControlSubTask_Reversed(CPed* ped) {
        return CTaskComplexGotoDoorAndOpen::ControlSubTask(ped);
    }
};
VALIDATE_SIZE(CTaskComplexGotoDoorAndOpen, 0x38);
