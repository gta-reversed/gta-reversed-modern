#pragma once
#include "TaskComplex.h"

class CPedGroup;
class CEntity;

class CTaskComplexGangLeader : public CTaskComplex {
public:
    CPedGroup* m_PedGroup;
    uint32     m_Time;
    int32      m_Time1;
    bool       byte18;
    uint8      byte19;
    uint8      gap1A[2];
    int32      m_Time2;
    int32      m_Time3;
    uint8      byte24;
    bool       m_bTime;
    uint8      gap26[2];
    int32      dword28;
    int32      dword2C;
    uint8      byte30;
    uint8      byte31;
    uint8      gap32[2];
    bool       byte34;

public:
    static constexpr auto Type = eTaskType::TASK_COMPLEX_GANG_LEADER;

    explicit CTaskComplexGangLeader(CPedGroup* pedGroup);
    ~CTaskComplexGangLeader() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexGangLeader(m_PedGroup); } // 0x661FA0;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    void ScanForStuff(CPed* ped);
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
