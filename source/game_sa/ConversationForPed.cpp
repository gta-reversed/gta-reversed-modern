#include "StdInc.h"

#include "ConversationForPed.h"

void CConversationForPed::InjectHooks() {
    RH_ScopedClass(CConversationForPed);
    RH_ScopedCategory("Conversations");

    RH_ScopedInstall(Clear, 0x43A770);
    RH_ScopedInstall(Update, 0x43C190, {.reversed = false});
    RH_ScopedInstall(IsPlayerInPositionForConversation, 0x43AC40);
}

// 0x43C190
void CConversationForPed::Update() {

}

// 0x43AC40
bool CConversationForPed::IsPlayerInPositionForConversation(bool isRandomConversation) const {
    const auto player = FindPlayerPed();
    if (DistanceBetweenPoints(player->GetPosition(), m_Ped->GetPosition()) > 4.0f) {
        return false;
    }

    if (player->GetForward().Dot(m_Ped->GetForward()) > 0.0f) {
        return false;
    }

    if (player->m_vecMoveSpeed.Magnitude2D() > 0.01f) {
        return false;
    }

    if (m_Ped->m_pLastEntityDamage == player && CTimer::GetTimeInMS() < m_Ped->m_nLastDamageTime + 6000) {
        return false;
    }

    if (isRandomConversation) {
        if (player->GetGroup()->GetMembership().CountMembersExcludingLeader() >= 1) {
            return false;
        }
    }

    if (!player->PedIsReadyForConversation(isRandomConversation)) {
        return false;
    }

    return m_Ped->PedIsReadyForConversation(isRandomConversation);
}
