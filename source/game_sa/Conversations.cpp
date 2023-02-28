#include "StdInc.h"

#include "Conversations.h"
#include "PedClothesDesc.h"
#include "IKChainManager_c.h"
#include "TaskSimpleStandStill.h"
#include "TaskComplexKillPedOnFoot.h"

void CPedToPlayerConversations::InjectHooks() {
    RH_ScopedClass(CPedToPlayerConversations);
    RH_ScopedCategory("Conversations");

    RH_ScopedInstall(Clear, 0x43AAE0);
    RH_ScopedInstall(Update, 0x43B0F0);
    RH_ScopedInstall(EndConversation, 0x43AB10);
}

// 0x43AAE0
void CPedToPlayerConversations::Clear() {
    if (m_State != State::NO_CONVERSATION) {
        m_State = State::NO_CONVERSATION;
        CAEPedSpeechAudioEntity::ReleasePlayerConversation();
    }
    m_pPed = nullptr;
    m_TimeOfLastPlayerConversation = 0;
}

// 0x43B0F0
void CPedToPlayerConversations::Update() {
    if (const auto vehicle = FindPlayerVehicle()) {
        pLastVehicle = vehicle;
        CEntity::RegisterReference(pLastVehicle);
    }

    static int32& lastPedPoolIdx = *(int32*)0x969A3C;

    const auto player = FindPlayerPed();
    switch (m_State) {
    case State::NO_CONVERSATION: {
        if (CTimer::GetTimeInMS() <= m_TimeOfLastPlayerConversation + 30'000)
            return;

        if (FindPlayerVehicle())
            return;

        if (player->GetWantedLevel() != 0 || !player->PedIsReadyForConversation(true))
            return;

        if (CConversations::IsConversationGoingOn())
            return;

        for (auto i = 0; i < 8; i++) {
            if (++lastPedPoolIdx >= GetPedPool()->GetSize()) {
                // rewind
                lastPedPoolIdx = 0;
            }
            
            const auto ped = GetPedPool()->GetAt(lastPedPoolIdx);
            if (!ped || ped->m_nCreatedBy != PED_GAME || ped->bHasAScriptBrain || !ped->GetIsOnScreen())
                continue;

            const auto &playerPos = player->GetPosition(), &pedPos = ped->GetPosition();

            if (ped->GetForwardVector().Dot(playerPos - pedPos) <= 0.0f)
                continue;

            if (player->GetForwardVector().Dot(pedPos - playerPos) <= 0.0f)
                continue;

            m_Topic = GetRandomTopicForPed(ped);
            if (!ped->m_pedSpeech.WillPedChatAboutTopic(static_cast<int16>(m_Topic)))
                continue;

            const auto RandomPedTalk = [ped] {
                if (CGeneral::RandomBool(0.02f)) { // NOTSA, originally: rand() % 4096 == 3
                    ped->Say(88);
                }
            };

            const auto CalculateStatRespect = [ped](eStats stat, uint32 modulo, float sub) {
                return (uint32)(CStats::GetStatValue(stat) + (float)(ped->m_nRandomSeed % modulo) - sub);
            };

            // shorthands, these were called from each topic's procedure.
            const auto pedRequestsPlayerConversation = CAEPedSpeechAudioEntity::RequestPlayerConversation(ped);
            if (!pedRequestsPlayerConversation) {
                RandomPedTalk();
                continue;
            }

            switch (m_Topic) {
            case Topic::CAR: {
                if (!pLastVehicle || DistanceBetweenPoints2D(pLastVehicle->GetPosition(), ped->GetPosition()) >= 20.0f) {
                    RandomPedTalk();
                    continue;
                }

                switch (pLastVehicle->GetModelInfo()->m_n2dfxCount) {
                case 1:
                case 4:
                case 5:
                case 6:
                    m_bPositiveOpening = false;
                    ped->Say(48); // Ped dislikes the player's vehicle.
                    break;
                case 2:
                case 3:
                case 9:
                    if (pLastVehicle->m_fHealth <= 800.0f) {
                        RandomPedTalk();
                        continue;
                    }

                    m_bPositiveOpening = true;
                    ped->Say(57); // Ped likes the player's vehicle.
                    break;
                default:
                    RandomPedTalk();
                    continue;
                }
                break;
            }
            case Topic::CLOTHES: {
                const auto respect = CalculateStatRespect(STAT_CLOTHES_RESPECT, 512, 256.0f);
                if (respect > 500) {
                    m_bPositiveOpening = true;
                    ped->Say(58); // Ped likes the player's clothes.
                } else if (respect < 150) {
                    m_bPositiveOpening = false;
                    ped->Say(49); // Ped dislikes the player's clothes.
                }

                break;
            }
            case Topic::HAIR: {
                if (!player->GetClothesDesc()->HasVisibleNewHairCut(0)) {
                    RandomPedTalk();
                    continue;
                }

                const auto respect = CalculateStatRespect(STAT_CLOTHES_RESPECT, 512, 256.0f);
                if (respect > 500) {
                    m_bPositiveOpening = true;
                    ped->Say(0x3b); // Ped likes the player's hair.
                } else if (respect < 150 || CStats::GetStatValue(STAT_HAIRDRESSING_BUDGET) < 5.0f) {
                    m_bPositiveOpening = false;
                    ped->Say(0x32); // Ped dislikes the player's hair.
                }
                break;
            }
            case Topic::PHYSICS: {
                const auto muscle = CalculateStatRespect(STAT_MUSCLE, 256, 128.0f),
                    fat = CalculateStatRespect(STAT_FAT, 256, 128.0f);

                if (muscle > 400 && fat < 250) {
                    m_bPositiveOpening = true;
                    ped->Say(0x3c); // Ped likes the player's physics.
                } else if (muscle - fat < 200 && fat > 500) {
                    m_bPositiveOpening = false;
                    ped->Say(0x33); // Ped likes the player's physics.
                }
                break;
            }
            case Topic::SHOES: {
                const auto respect = CalculateStatRespect(STAT_CLOTHES_RESPECT, 1024, 512.0f);
                if (respect > 700) {
                    m_bPositiveOpening = true;
                    ped->Say(0x3d); // Ped likes the player's shoes.
                } else if (respect < 300) {
                    m_bPositiveOpening = false;
                    ped->Say(0x34); // Ped dislikes the player's shoes.
                }
                break;
            }
            case Topic::SMELL: {
                const auto respect = CalculateStatRespect(STAT_SEX_APPEAL, 512, 256.0f);
                if (respect > 700) {
                    m_bPositiveOpening = true;
                    ped->Say(0x3e); // Ped likes the player's smell.
                } else if (respect < 300) {
                    m_bPositiveOpening = false;
                    ped->Say(0x35); // Ped dislikes the player's smell.
                }
                break;
            }
            case Topic::TATTOO: {
                if (!player->GetClothesDesc()->HasVisibleTattoo()) {
                    RandomPedTalk();
                    continue;
                }

                const auto respect = CGeneral::GetRandomNumberInRange(0, 1000);
                if (respect > 700) {
                    m_bPositiveOpening = true;
                    ped->Say(0x3f); // Ped likes the player's tattoo.
                } else if (respect < 300) {
                    m_bPositiveOpening = false;
                    ped->Say(0x36); // Ped dislikes the player's tattoo.
                }
                break;
            }
            case Topic::WEATHER: {
                if (CWeather::Wind > 0.5f) {
                    m_bPositiveOpening = false;
                    ped->Say(0x37); // Ped dislikes the current weather.
                } else if (CWeather::Wind < 0.1f && CClock::GetGameClockHours() < 20 && CClock::GetGameClockMinutes() > 6) {
                    m_bPositiveOpening = true;
                    ped->Say(0x40); // Ped likes the current weather.
                } else {
                    RandomPedTalk();
                    continue;
                }
                break;
            }
            case Topic::WHERE_ARE_YOU_FROM:
                ped->Say(0xfb); // Gangster asks player which turf he is from.
                break;
            case Topic::GANGBANG:
                m_bPositiveOpening = true;
                ped->Say(0xfc);
                break;
            default:
                RandomPedTalk();
                continue;
            }

            // Ped said something to the player, change the conversation state.
            m_State = State::PLAYER_REPLY;
            m_TimeOfLastPlayerConversation = m_StartTime = CTimer::GetTimeInMS();

            m_pPed = ped;
            CEntity::RegisterReference(m_pPed);
            ped->DisablePedSpeech(false);

            g_ikChainMan.LookAt(
                "Ped2Pl_Conversation",
                ped,
                player,
                100'000,
                BONE_HEAD,
                nullptr,
                false,
                0.25f,
                500,
                8,
                false
            );

            g_ikChainMan.LookAt(
                "Ped2Pl_ConversationP",
                player,
                ped,
                100'000,
                BONE_HEAD,
                nullptr,
                false,
                0.25f,
                500,
                8,
                false
            );
            break; // Found a ped for talking, Update()'s job is done. Originally return;
        }
        break;
    }
    case State::PLAYER_REPLY: {
        if (!m_pPed) {
            return EndConversation();
        }

        if (CTimer::GetTimeInMS() > m_StartTime + 4000) {
            if (g_ikChainMan.IsLooking(m_pPed) && m_bPositiveOpening) {
                m_pPed->Say(0x38); // Ped is ignored by the player.
            }
            return EndConversation();
        }

        const auto MakePedAttackPlayer = [player] {
            CTaskComplexSequence taskSequence{};
            taskSequence.AddTask(new CTaskSimpleStandStill(2000));
            taskSequence.AddTask(new CTaskComplexKillPedOnFoot(player, -1, 0, 0, 0, 0));

            m_pPed->GetIntelligence()->m_eventGroup.Add(CEventScriptCommand{3, taskSequence.AsComplex()});
        };

        if (CPad::GetPad()->ConversationYesJustDown()) {
            if (!m_bPositiveOpening) {
                // responding catcalling
                player->Say(IsPedTypeFemale(m_pPed->m_nPedType) ? 0x83 : 0x84);

                m_State = State::ENDING;
                m_StartTime = CTimer::GetTimeInMS();
                break;
            }

            // Player replies...
            switch (m_Topic) {
            case Topic::CAR:
                player->Say(0x81);
                break;
            case Topic::CLOTHES:
                player->Say(0x82);
                break;
            case Topic::HAIR:
                player->Say(0x86);
                break;
            case Topic::PHYSICS:
                player->Say(0x89);
                break;
            case Topic::SHOES:
                player->Say(0x8a);
                break;
            case Topic::SMELL:
                player->Say(0x8b);
                break;
            case Topic::TATTOO:
                player->Say(0x8c);
                break;
            case Topic::WEATHER:
                player->Say(0xea);
                break;
            case Topic::WHERE_ARE_YOU_FROM:
            case Topic::GANGBANG: {
                // Player always dismisses calls from enemy gangsters.
                player->Say(m_Topic == Topic::WHERE_ARE_YOU_FROM ? 0xec : 0x6b);

                if (CGeneral::RandomBool(75.0f)) {
                    MakePedAttackPlayer();
                }
                return EndConversation();
            }
            default:
                break;
            }

            m_State = State::ENDING;
            m_StartTime = CTimer::GetTimeInMS();
        } else if (CPad::GetPad()->ConversationNoJustDown()) {
            if (m_bPositiveOpening) {
                // Player dismisses the ped.
                switch (m_Topic) {
                case Topic::WHERE_ARE_YOU_FROM:
                case Topic::GANGBANG:
                    player->Say(m_Topic == Topic::WHERE_ARE_YOU_FROM ? 0xeb : 0x6a);
                    return EndConversation();
                default:
                    player->Say(IsPedTypeFemale(m_pPed->m_nPedType) ? 0x83 : 0x84);
                    break;
                }

                m_State = State::PLAYER_DISMISSED;
                m_StartTime = CTimer::GetTimeInMS();
                break;
            }

            // Player curses the ped.
            player->Say(IsPedTypeFemale(m_pPed->m_nPedType) ? 0x87 : 0x88);

            if (m_pPed->m_nPedType != PED_TYPE_GANG2 && CGeneral::RandomBool(40.0f)) {
                MakePedAttackPlayer();
            }

            m_State = State::ENDING;
            m_StartTime = CTimer::GetTimeInMS();
        }

        break;
    }
    case State::PLAYER_DISMISSED:
        if (!m_pPed) {
            return EndConversation();
        }

        if (CTimer::GetTimeInMS() > m_StartTime + 3000 && !m_pPed->GetPedTalking()) {
            m_pPed->Say(0x85); // Ped replies to the dismissal.
            m_State = State::ENDING;
            m_StartTime = CTimer::GetTimeInMS();
        }
        break;
    case State::ENDING:
        if (!m_pPed || CTimer::GetTimeInMS() > m_StartTime + 2500) {
            return EndConversation();
        }
        break;
    default:
        break;
    }
}

// 0x43AB10
void CPedToPlayerConversations::EndConversation() {
    m_State = State::NO_CONVERSATION;
    CAEPedSpeechAudioEntity::ReleasePlayerConversation();

    if (const auto player = FindPlayerPed(); g_ikChainMan.IsLooking(player)) {
        g_ikChainMan.AbortLookAt(player);
    }

    if (m_pPed) {
        m_pPed->EnablePedSpeech();

        if (g_ikChainMan.IsLooking(m_pPed)) {
            g_ikChainMan.AbortLookAt(m_pPed);
        }
    }
}

void CConversations::InjectHooks() {
    RH_ScopedClass(CConversations);
    RH_ScopedCategory("Conversations");;
}

void CConversations::Clear() {
    plugin::Call<0x43A7B0>();
}

void CConversations::Update() {
    plugin::Call<0x43C590>();
}

// 0x43AAC0
bool CConversations::IsConversationGoingOn() {
    return plugin::CallAndReturn<bool, 0x43AAC0>();
}

// 0x43A960
void CConversations::RemoveConversationForPed(CPed* ped) {
    plugin::Call<0x43A960, CPed*>(ped);
}
