#include "StdInc.h"
#include "TaskComplexGangLeader.h"

void CTaskComplexGangLeader::InjectHooks() {
    RH_ScopedClass(CTaskComplexGangLeader);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x65DED0);
    RH_ScopedInstall(Destructor, 0x65DF30);

    // RH_ScopedGlobalInstall(GetRandomGangAmbientAnim, 0x65E730);
    // RH_ScopedGlobalInstall(ShouldLoadGangAnims, 0x65E7F0);
    // RH_ScopedGlobalInstall(DoGangAbuseSpeech, 0x65E860);

    // RH_ScopedInstall(TryToPassObject, 0x65EA50);

    // RH_ScopedInstall(Clone, 0x661FA0);
    RH_ScopedInstall(GetTaskType, 0x65DF20);
    // RH_ScopedInstall(MakeAbortable, 0x65DFA0);
    // RH_ScopedInstall(CreateNextSubTask, 0x65DFF0);
    // RH_ScopedInstall(CreateFirstSubTask, 0x65E1F0);
    // RH_ScopedInstall(ControlSubTask, 0x662370);
    // RH_ScopedInstall(ScanForStuff, 0x65E200);
}

// 0x65DED0
CTaskComplexGangLeader::CTaskComplexGangLeader(CPedGroup* pedGroup) {}

// 0x65DF30
CTaskComplexGangLeader::~CTaskComplexGangLeader() {}

// 0x65E730
int32 CTaskComplexGangLeader::GetRandomGangAmbientAnim(CPed* ped, CEntity* entity) {
    return plugin::CallAndReturn<int32, 0x65E730, CPed*, CEntity*>(ped, entity);
}

// 0x65E7F0
bool CTaskComplexGangLeader::ShouldLoadGangAnims() {
    return plugin::CallAndReturn<bool, 0x65E7F0>();
}

// 0x65E860
void CTaskComplexGangLeader::DoGangAbuseSpeech(CPed* ped, CPed* a2) {
    plugin::Call<0x65E860, CPed*, CPed*>(ped, a2);
}

// 0x65EA50
CPed* CTaskComplexGangLeader::TryToPassObject(CPed* ped, CPedGroup* pedGroup) {
    return plugin::CallMethodAndReturn<CPed*, 0x65EA50, CTaskComplexGangLeader*, CPed*, CPedGroup*>(this, ped, pedGroup);
}

// 0x661FA0
CTask* CTaskComplexGangLeader::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x661FA0, CTaskComplexGangLeader*>(this);
}

// 0x65DFA0
bool CTaskComplexGangLeader::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x65DFA0, CTaskComplexGangLeader*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x65DFF0
CTask* CTaskComplexGangLeader::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x65DFF0, CTaskComplexGangLeader*, CPed*>(this, ped);
}

// 0x65E1F0
CTask* CTaskComplexGangLeader::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x65E1F0, CTaskComplexGangLeader*, CPed*>(this, ped);
}

// 0x662370
CTask* CTaskComplexGangLeader::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x662370, CTaskComplexGangLeader*, CPed*>(this, ped);
}

// 0x65E200
void CTaskComplexGangLeader::ScanForStuff(CPed* ped) {
    plugin::CallMethod<0x65E200, CTaskComplexGangLeader*, CPed*>(this, ped);
}
