#pragma once

#include "TaskSimpleCarDrive.h"

class CPed;
class CEvent;
class CVehicle;
class CTaskSimpleCarSetTempAction;


class  CTaskSimpleCarSetTempAction : public CTaskSimpleCarDrive {
 
public:
    int32 m_action = {};  // 0x60
    int32 m_timeMs = {};  // 0x64

public:
    static void InjectHooks();

    CTaskSimpleCarSetTempAction(CVehicle * veh, int32 action, int32 timeMs);
    ~CTaskSimpleCarSetTempAction();


    virtual  CTask * Clone();  
     virtual int32 GetTaskType();  
     virtual bool MakeAbortable(CPed * ped, int32 priority, CEvent const* event);  
     virtual bool ProcessPed(CPed * ped);  
 
private: // Wrappers for hooks

// 0x63D6F0
CTaskSimpleCarSetTempAction* Constructor(CVehicle * veh, int32 action, int32 timeMs) {
    this->CTaskSimpleCarSetTempAction::CTaskSimpleCarSetTempAction(veh, action, timeMs);
    return this;
}
// 0x63D730
CTaskSimpleCarSetTempAction* Destructor() {
    this->CTaskSimpleCarSetTempAction::~CTaskSimpleCarSetTempAction();
    return this;
}


};
