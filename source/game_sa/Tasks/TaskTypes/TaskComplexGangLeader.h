#pragma once
#include "TaskComplex.h"

class CPedGroup;
class CEntity;

class CTaskComplexGangLeader : public CTaskComplex {
public:
    CPedGroup* m_PedGroup;
    CTaskTimer m_Timer1;
    CTaskTimer m_Timer2;
    CTaskTimer m_Timer3;
    bool       m_bAnimBlockRefAdded;

public:
    static constexpr auto Type = TASK_COMPLEX_GANG_LEADER;

    explicit CTaskComplexGangLeader(CPedGroup* pedGroup);
    ~CTaskComplexGangLeader() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexGangLeader(m_PedGroup); } // 0x661FA0;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    virtual void ScanForStuff(CPed* ped);
    CPed* TryToPassObject(CPed* ped, CPedGroup* pedGroup);
    static int32 GetRandomGangAmbientAnim(CPed* ped, CEntity* entity);
    static bool ShouldLoadGangAnims();
    static void DoGangAbuseSpeech(CPed* ped1, CPed* ped2);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexGangLeader* Constructor(CPedGroup* pedGroup) { this->CTaskComplexGangLeader::CTaskComplexGangLeader(pedGroup); return this; }
    CTaskComplexGangLeader* Destructor() { this->CTaskComplexGangLeader::~CTaskComplexGangLeader(); return this; }
};
VALIDATE_SIZE(CTaskComplexGangLeader, 0x38);
