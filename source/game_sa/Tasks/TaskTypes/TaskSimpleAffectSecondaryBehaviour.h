#pragma once

#include "TaskSimple.h"

class CTask;
class CEvent;
class CPed;
class CTaskSimpleAffectSecondaryBehaviour;


class  CTaskSimpleAffectSecondaryBehaviour : public CTaskSimple {
 
public:
    bool m_bAdd = {};  // 0x8
    int32 m_secondaryTaskType = {};  // 0xC
    CTask * m_pTask = {};  // 0x10

public:
    static void InjectHooks();

    CTaskSimpleAffectSecondaryBehaviour(bool add, int32 secondaryTaskType, CTask * a4);


    virtual  CTask * Clone();  
     virtual int32 GetTaskType();  
     virtual bool MakeAbortable(CPed * ped, int32 priority, CEvent const* event);  
     virtual bool ProcessPed(CPed * ped);  
 
private: // Wrappers for hooks

// 0x691270
CTaskSimpleAffectSecondaryBehaviour* Constructor(bool add, int32 secondaryTaskType, CTask * a4) {
    this->CTaskSimpleAffectSecondaryBehaviour::CTaskSimpleAffectSecondaryBehaviour(add, secondaryTaskType, a4);
    return this;
}


};
