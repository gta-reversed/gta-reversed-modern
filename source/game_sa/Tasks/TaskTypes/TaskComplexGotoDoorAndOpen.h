#pragma once
#include "TaskComplex.h"
#include "Vector.h"

class CEntity;
class CObject;

class CTaskComplexGotoDoorAndOpen : public CTaskComplex {
public:
    CEntity* m_pEntity = {};       // 0xC
    CVector m_vecStart = {};       // 0x10
    CVector m_vecEnd = {};         // 0x1C
    uint32 m_nStartTime = {};      // 0x28
    uint32 m_nOffsetTime = {};     // 0x2C
    uint8 byte30 = {};             // 0x30
    uint8 byte31 = {};             // 0x31
    uint8 gap32[2] = {};           // 0x32
    uint8 m_nFlags = {};           // 0x34

public:
    static void InjectHooks();

    CTaskComplexGotoDoorAndOpen(CObject* door);
    CTaskComplexGotoDoorAndOpen(CVector const& start, CVector const& end);
    ~CTaskComplexGotoDoorAndOpen();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GOTO_DOOR_AND_OPEN;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x66BB20
    CTaskComplexGotoDoorAndOpen* Constructor(CObject* door) {
        this->CTaskComplexGotoDoorAndOpen::CTaskComplexGotoDoorAndOpen(door);
        return this;
    }
    // 0x66BBA0
    CTaskComplexGotoDoorAndOpen* Constructor(CVector const& start, CVector const& end) {
        this->CTaskComplexGotoDoorAndOpen::CTaskComplexGotoDoorAndOpen(start, end);
        return this;
    }

    // 0x66BC00
    CTaskComplexGotoDoorAndOpen* Destructor() {
        this->CTaskComplexGotoDoorAndOpen::~CTaskComplexGotoDoorAndOpen();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexGotoDoorAndOpen, 0x38);
