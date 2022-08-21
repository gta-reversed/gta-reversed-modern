#pragma once


class CTaskSimpleCower;
class CPed;


class  CTaskSimpleCower : public  {
 
public:
    static void InjectHooks();

    CTaskSimpleCower();
    ~CTaskSimpleCower();


    virtual  CTask * Clone();  
     virtual bool IsInterruptable(CPed const* ped);  
 
private: // Wrappers for hooks

// 0x48DE70
CTaskSimpleCower* Constructor() {
    this->CTaskSimpleCower::CTaskSimpleCower();
    return this;
}
// 0x48E900
CTaskSimpleCower* Destructor() {
    this->CTaskSimpleCower::~CTaskSimpleCower();
    return this;
}


};
