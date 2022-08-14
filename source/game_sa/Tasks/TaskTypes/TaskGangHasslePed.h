#pragma once

#include "TaskComplex.h"

class CEntity;

class CTaskGangHasslePed : public CTaskComplex {
public:
    CPed* m_Ped;
    int32 dword10;
    int32 dword14;
    int32 dword18;
    uint8 m_bAnimationNotDeleted;
    int32 m_nTime;
    int32 m_nSomeRandomShit;
    uint8 m_bFirstSubTaskInitialised;
    uint8 byte29;

public:
    static void InjectHooks();

    CTaskGangHasslePed(CPed* ped, int32 a3, int32 a4, int32 a5);
    ~CTaskGangHasslePed() override;

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GANG_HASSLE_PED;

    CTask* Clone() override { return new CTaskGangHasslePed(m_Ped, dword10, dword14, dword18); } // 0x6620D0
    eTaskType GetTaskType() override { return Type; }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private:
    CTaskGangHasslePed* Constructor(CPed* ped, int32 a3, int32 a4, int32 a5) { this->CTaskGangHasslePed::CTaskGangHasslePed(ped, a3, a4, a5); return this; }
    CTaskGangHasslePed* Destructor() { this->CTaskGangHasslePed::~CTaskGangHasslePed(); return this; }
};
VALIDATE_SIZE(CTaskGangHasslePed, 0x2C);
