#pragma once




class  CTaskSimpleCarWaitToSlowDown : public  {
 
public:
    static void InjectHooks();

    CTaskSimpleCarWaitToSlowDown(CVehicle * veh, int32 type);
    ~CTaskSimpleCarWaitToSlowDown();


    virtual  CTask * Clone();  
     virtual int32 GetTaskType();  
     virtual bool MakeAbortable(CPed * ped, int32 priority, CEvent const* event);  
     virtual bool ProcessPed(CPed * ped);  
     virtual bool SetPedPosition(CPed * ped);  
 
private: // Wrappers for hooks

// 0x646990
CTaskSimpleCarWaitToSlowDown* Constructor(CVehicle * veh, int32 type) {
    this->CTaskSimpleCarWaitToSlowDown::CTaskSimpleCarWaitToSlowDown(veh, type);
    return this;
}

// 0x646A00
CTaskSimpleCarWaitToSlowDown* Destructor() {
    this->CTaskSimpleCarWaitToSlowDown::~CTaskSimpleCarWaitToSlowDown();
    return this;
}


};
