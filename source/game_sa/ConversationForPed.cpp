#include "StdInc.h"

#include "ConversationForPed.h"

void CConversationForPed::InjectHooks() {
    RH_ScopedClass(CConversationForPed);
    RH_ScopedCategory("Conversations");

    RH_ScopedInstall(Clear, 0x43A770);
    RH_ScopedInstall(Update, 0x43C190);
    RH_ScopedInstall(IsPlayerInPositionForConversation, 0x43AC40);
}

// 0x43C190
void CConversationForPed::Update() {
    if (!m_Ped || !m_bEnabled || !IsPlayerInPositionForConversation(false)) {
        m_Status = 0;
        return;
    }

    const auto pad = CPad::GetPad();
    if (CTimer::GetTimeInMS() > m_LastTimeWeWereCloseEnough + 1000 || m_Status == 1 &&
        (CTimer::GetTimeInMS() > m_LastChange + 4000 || pad->ConversationYesJustDown() || pad->ConversationNoJustDown())) {

        assert(GetCurrentNode());
        if (!m_bSuppressSubtitles) {
            CMessages::ClearSmallMessagesOnly();
            CMessages::AddMessageJumpQ(TheText.Get(GetCurrentNode()->m_Name), 4000, 1, true);
        }

        if (GetCurrentNode()->m_Speech > 0) {
            m_Ped->Say(GetCurrentNode()->m_Speech);
        }

        if (GetCurrentNode()->m_Speech < 0) {
            CConversations::AwkwardSay(-GetCurrentNode()->m_Speech, m_Ped);
        }

        m_Status = 2;
        m_LastChange = CTimer::GetTimeInMS();
    } else if (CTimer::GetTimeInMS() > m_LastChange + 400) {
        switch (m_Status) {
        case 0:
        case 2:
        case 3: {
            assert(GetCurrentNode());
            if (pad->ConversationNoJustDown() && GetCurrentNode()->m_NodeNo >= 0) {
                if (!m_bSuppressSubtitles) {
                    CMessages::ClearSmallMessagesOnly();
                    strcpy_s(gString, GetCurrentNode()->m_Name);
                    gString[strlen(gString)] = 'N';
                    CMessages::AddMessageJumpQ(gString, 4000, 3, true);
                }

                const auto player = FindPlayerPed();
                if (GetCurrentNode()->m_SpeechN > 0) {
                    player->Say(GetCurrentNode()->m_SpeechN);
                }

                if (GetCurrentNode()->m_SpeechN < 0) {
                    CConversations::AwkwardSay(-GetCurrentNode()->m_SpeechN, player);
                }

                m_CurrentNode = GetCurrentNode()->m_NodeNo;
                m_LastChange = CTimer::GetTimeInMS();

                if (!m_bSuppressSubtitles) {
                    CMessages::AddMessageJumpQ(TheText.Get(GetCurrentNode()->m_Name), 4000, 1, true);
                }
                m_Status = 1;
            } else if (pad->ConversationYesJustDown() && GetCurrentNode()->m_NodeYes >= 0) {
                if (!m_bSuppressSubtitles) {
                    CMessages::ClearSmallMessagesOnly();
                    strcpy_s(gString, GetCurrentNode()->m_Name);
                    gString[strlen(gString)] = 'Y';
                    CMessages::AddMessageJumpQ(gString, 4000, 3, true);
                }

                const auto player = FindPlayerPed();
                if (GetCurrentNode()->m_SpeechY > 0) {
                    player->Say(GetCurrentNode()->m_SpeechY);
                }

                if (GetCurrentNode()->m_SpeechY < 0) {
                    CConversations::AwkwardSay(-GetCurrentNode()->m_SpeechY, player);
                }

                m_CurrentNode = GetCurrentNode()->m_NodeYes;
                m_LastChange = CTimer::GetTimeInMS();

                if (!m_bSuppressSubtitles) {
                    CMessages::AddMessageJumpQ(TheText.Get(GetCurrentNode()->m_Name), 4000, 1, true);
                }
                m_Status = 1;
            }
            break;
        }
        }
    }
    m_LastTimeWeWereCloseEnough = CTimer::GetTimeInMS();
    if (m_Status == 2 && CTimer::GetTimeInMS() > m_LastChange + 4000) {
        m_Status = 3;
    }
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
