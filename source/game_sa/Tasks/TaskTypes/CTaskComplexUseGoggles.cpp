#include "StdInc.h"

#include "CTaskComplexUseGoggles.h"

#include "CTaskSimpleRunAnim.h"
#include "CTaskSimplePlayerOnFoot.h"

// 0x634EF0
CTaskComplexUseGoggles::CTaskComplexUseGoggles() : CTaskComplex() {
    // NOP
}

// 0x634F20
CTaskComplexUseGoggles::~CTaskComplexUseGoggles() {
    // NOP
}

// 0x634F40
CTask* CTaskComplexUseGoggles::CreateNextSubTask(CPed* ped) {
    int enabled = m_pSubTask->GetTaskType() - TASK_SIMPLE_GOGGLES_ON;
    if (enabled) {
        if (enabled == 1) {
            ped->TakeOffGoggles();
            return nullptr;
        }
    } else {
        ped->PutOnGoggles();
        ped->m_weaponAudio.AddAudioEvent(AE_WEAPON_FIRE);
    }
    return nullptr;
}

// 0x634F90
CTask* CTaskComplexUseGoggles::CreateFirstSubTask(CPed* ped) {
    ped->m_pPlayerData->m_bDontAllowWeaponChange = true;

    const char* taskName = ped->m_pGogglesObject ? "GogglesOff" : "GogglesOn";
    const eTaskType taskType = ped->m_pGogglesObject ? TASK_SIMPLE_GOGGLES_OFF : TASK_SIMPLE_GOGGLES_ON;

    return new CTaskSimpleRunAnim(ANIM_GROUP_GOGGLES, ANIM_ID_FIRE, 4.0f, taskType, taskName, false);
}

// 0x635050
CTask* CTaskComplexUseGoggles::ControlSubTask(CPed* ped) {
    ped->m_pPlayerData->m_bDontAllowWeaponChange = true;

    auto* m_pPlayerData = ped->m_pPlayerData;
    if (m_pPlayerData) {
        m_pPlayerData->m_bPlayerSprintDisabled = true;
        m_pPlayerData->m_fTimeCanRun = std::max(m_pPlayerData->m_fTimeCanRun, 0.0f);

        auto* task = ped->m_pIntelligence->FindTaskByType(TASK_SIMPLE_PLAYER_ON_FOOT);
        if (task)
            static_cast<CTaskSimplePlayerOnFoot*>(task)->PlayerControlZelda(ped, true);

        ped->m_pPlayerData->m_bPlayerSprintDisabled = false;
    }
    return m_pSubTask;
}

void TaskComplexUseGogglesTestCode() {
    CStreaming::RequestModel(MODEL_NVGOGGLES, STREAMING_GAME_REQUIRED);
    CPlayerPed* player = FindPlayerPed();
    player->GiveWeapon(WEAPON_NIGHTVISION, 1, true);
}
