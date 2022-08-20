#pragma once

#include "TaskSimple.h"

class CObject;
class CVehicle;

class CTaskSimpleCarOpenDoorFromOutside : public CTaskSimple {

public:
    uint8 byte8 = {};        // 8
    uint8 f9[3] = {};        // 9
    int32 dwordC = {};       // 0xC
    CObject* m_pEntity = {}; // 0x10
    int32 dword14 = {};      // 0x14
    uint8 byte18 = {};       // 0x18
    uint8 byte19 = {};       // 0x19
    uint8 f1A[2] = {};       // 0x1A
    int32 dword1C = {};      // 0x1C
    int32 dword20 = {};      // 0x20

public:
    static void InjectHooks();

    CTaskSimpleCarOpenDoorFromOutside(CVehicle* veh, int32 door, CTaskUtilityLineUpPedWithCar*, bool);
    ~CTaskSimpleCarOpenDoorFromOutside();

    virtual CTask* Clone();
    virtual int32 GetTaskType();
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual bool ProcessPed(CPed* ped);
    virtual bool SetPedPosition(CPed* ped);

private: // Wrappers for hooks
    // 0x645E50
    CTaskSimpleCarOpenDoorFromOutside* Constructor(CVehicle*, int32, CTaskUtilityLineUpPedWithCar*, bool) {
        this->CTaskSimpleCarOpenDoorFromOutside::CTaskSimpleCarOpenDoorFromOutside(, , , );
        return this;
    }

    // 0x645EE0
    CTaskSimpleCarOpenDoorFromOutside* Destructor() {
        this->CTaskSimpleCarOpenDoorFromOutside::~CTaskSimpleCarOpenDoorFromOutside();
        return this;
    }
};
