#include "StdInc.h"

void CRunningScript::InjectHooks()
{
    HookInstall(0x465C20, &CRunningScript::GivePedScriptedTask);;
}

void* CRunningScript::GetPointerToLocalVariable(int varId) {
    return plugin::CallMethodAndReturnDynGlobal<void*, CRunningScript*, int>(0x463CA0, this, varId);
}

void CRunningScript::GivePedScriptedTask(std::int32_t pedHandle, CTask* task, std::int32_t opcode) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethodDynGlobal<CRunningScript*, std::int32_t, CTask*, std::int32_t>(0x465C20, this, pedHandle, task, opcode);
#else
    if (pedHandle == -1) {
        CTaskSequences::AddTaskToActiveSequence(task);
        return;
    }
    CPed* ped = CPools::ms_pPedPool->GetAtRef(pedHandle);
    CPedGroup* pPedGroup = CPedGroups::GetPedsGroup(ped);
    CPed* pOtherPed = nullptr;
    if (m_externalType == 5 || m_externalType == 2 || !m_externalType || m_externalType == 3) {
        std::int32_t* pLocalVariable = reinterpret_cast<std::int32_t*>(GetPointerToLocalVariable(0));
        pOtherPed = CPools::ms_pPedPool->GetAtRef(*pLocalVariable);
    }
    if (ped->bHasAScriptBrain && pOtherPed != ped) {
        if (task)
            delete task;
    }
    else if (pOtherPed && m_externalType == 5) {
        if (CScriptedBrainTaskStore::SetTask(ped, task)) {
            const std::int32_t slot = CPedScriptedTaskRecord::GetVacantSlot();
            CPedScriptedTaskRecord::ms_scriptedTasks[slot].SetAsAttractorScriptTask(ped, opcode, task);
        }
    }
    else if (!pPedGroup || ped->IsPlayer()) {
        CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, task, 0);
        CEventScriptCommand* event = static_cast<CEventScriptCommand*>(ped->GetEventGroup().Add(&eventScriptCommand, 0));
        if (event)
        {
            const std::int32_t slot = CPedScriptedTaskRecord::GetVacantSlot();
            CPedScriptedTaskRecord::ms_scriptedTasks[slot].Set(ped, opcode, event);
        }
    }
    else {
        pPedGroup->GetIntelligence().SetScriptCommandTask(ped, task);
        CTask* pScriptedTask = pPedGroup->GetIntelligence().GetTaskScriptCommand(ped);
        const std::int32_t slot = CPedScriptedTaskRecord::GetVacantSlot();
        CPedScriptedTaskRecord::ms_scriptedTasks[slot].SetAsGroupTask(ped, opcode, pScriptedTask);
        if (task)
            delete task;
    }
#endif
}
