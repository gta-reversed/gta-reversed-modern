#pragma once
#include "TaskComplex.h"

class CTaskComplex;

class CTaskGangHasslePed : public CTaskComplex {
public:
    CEntity* m_pEntity = {}; // 0xC
    int32    dword10 = {}; // 0x10
    int32    dword14 = {}; // 0x14
    int32    dword18 = {}; // 0x18
    uint8    m_bAnimationNotDeleted = {}; // 0x1C
    uint8    gap1D[3] = {}; // 0x1D
    int32    m_nTime = {}; // 0x20
    int32    m_nSomeRandomShit = {}; // 0x24
    uint8    m_bFirstSubTaskInitialised = {}; // 0x28
    uint8    byte29 = {}; // 0x29

public:
    static void InjectHooks();

    CTaskGangHasslePed(CPed* ped, int32 a3, int32 a4, int32 a5);
    ~CTaskGangHasslePed();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GANG_HASSLE_PED;

    virtual CTask* 	  Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual CTask*    CreateNextSubTask(CPed* ped);
    virtual CTask*    CreateFirstSubTask(CPed* ped);
    virtual CTask*    ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x65FED0
    CTaskGangHasslePed* Constructor(CPed* ped, int32 a3, int32 a4, int32 a5) {
        this->CTaskGangHasslePed::CTaskGangHasslePed(ped, a3, a4, a5);
        return this;
    }

    // 0x65FF60
    CTaskGangHasslePed* Destructor() {
        this->CTaskGangHasslePed::~CTaskGangHasslePed();
        return this;
    }

};
VALIDATE_SIZE(CTaskGangHasslePed, 0x2C);
