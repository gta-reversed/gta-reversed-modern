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
        m_Status = eConversationForPedStatus::NOT_AVAILABLE;
        return;
    }

    const auto PrintSubtitle = [this](const char* text, uint16 flag) {
        if (m_bSuppressSubtitles)
            return;

        CMessages::ClearSmallMessagesOnly();
        CMessages::AddMessageJumpQ(text, 4000, flag, true);
    };

    const auto Speak = [](int32 speechId, CPed* ped) {
        if (speechId > 0) {
            ped->Say(speechId);
        }

        if (speechId < 0) {
            CConversations::AwkwardSay(-speechId, ped);
        }
    };

    const auto pad = CPad::GetPad();
    if (CTimer::GetTimeInMS() > m_LastTimeWeWereCloseEnough + 1000 ||
        m_Status == eConversationForPedStatus::UNK_1 &&
        (CTimer::GetTimeInMS() > m_LastChange + 4000 || pad->ConversationYesJustDown() || pad->ConversationNoJustDown())) {

        assert(GetCurrentNode());
        PrintSubtitle(TheText.Get(GetCurrentNode()->m_Name), 1);
        Speak(GetCurrentNode()->m_Speech, m_Ped);

        m_Status = eConversationForPedStatus::UNK_2;
        m_LastChange = CTimer::GetTimeInMS();
    } else if (CTimer::GetTimeInMS() > m_LastChange + 400) {
        switch (m_Status) {
        case eConversationForPedStatus::NOT_AVAILABLE:
        case eConversationForPedStatus::UNK_2:
        case eConversationForPedStatus::UNK_3: {
            assert(GetCurrentNode());
            if (pad->ConversationNoJustDown() && GetCurrentNode()->m_NodeNo >= 0) {
                PrintSubtitle(TheText.Get(std::format("{}N", GetCurrentNode()->m_Name).c_str()), 3);
                Speak(GetCurrentNode()->m_SpeechN, FindPlayerPed());

                m_CurrentNode = GetCurrentNode()->m_NodeNo;
                PrintSubtitle(TheText.Get(GetCurrentNode()->m_Name), 1);
            } else if (pad->ConversationYesJustDown() && GetCurrentNode()->m_NodeYes >= 0) {
                PrintSubtitle(TheText.Get(std::format("{}Y", GetCurrentNode()->m_Name).c_str()), 3);
                Speak(GetCurrentNode()->m_SpeechY, FindPlayerPed());

                m_CurrentNode = GetCurrentNode()->m_NodeYes;
                PrintSubtitle(TheText.Get(GetCurrentNode()->m_Name), 1);
            }

            m_Status = eConversationForPedStatus::UNK_1;
            m_LastChange = CTimer::GetTimeInMS();
            break;
        }
        }
    }
    m_LastTimeWeWereCloseEnough = CTimer::GetTimeInMS();
    if (m_Status == eConversationForPedStatus::UNK_2 && CTimer::GetTimeInMS() > m_LastChange + 4000) {
        m_Status = eConversationForPedStatus::UNK_3;
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
