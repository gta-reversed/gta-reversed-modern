/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "PopCycle.h"

float& CPopCycle::m_NumOther_Cars = *(float*)0xC0BC30;
float& CPopCycle::m_NumCops_Cars = *(float*)0xC0BC34;
float& CPopCycle::m_NumGangs_Cars = *(float*)0xC0BC38;
float& CPopCycle::m_NumDealers_Cars = *(float*)0xC0BC3C;
float& CPopCycle::m_NumOther_Peds = *(float*)0xC0BC40;
float& CPopCycle::m_NumCops_Peds = *(float*)0xC0BC44;
float& CPopCycle::m_NumGangs_Peds = *(float*)0xC0BC48;
float& CPopCycle::m_fPercOther = *(float*)0xC0BC4C;
float& CPopCycle::m_fPercCops = *(float*)0xC0BC50;
float& CPopCycle::m_fPercGangs = *(float*)0xC0BC54;
float& CPopCycle::m_fPercDealers = *(float*)0xC0BC58;
bool& CPopCycle::m_bCurrentZoneIsGangArea = *(bool*)0xC0BC5C;
float& CPopCycle::m_fCurrentZoneDodgyness = *(float*)0xC0BC60;
CZone*& CPopCycle::m_pCurrZone = *(CZone**)0xC0BC64;
CZoneInfo*& CPopCycle::m_pCurrZoneInfo = *(CZoneInfo**)0xC0BC68;
int32& CPopCycle::m_nCurrentZoneType = *(int32*)0xC0BC6C;
int32& CPopCycle::m_nCurrentTimeOfWeek = *(int32*)0xC0BC70;
int32& CPopCycle::m_nCurrentTimeIndex = *(int32*)0xC0BC74;
float& CPopCycle::m_NumDealers_Peds = *(float*)0xC0E978;


void CPopCycle::InjectHooks() {
    RH_ScopedClass(CPopCycle);
    RH_ScopedCategoryGlobal();

    RH_ScopedGlobalInstall(Initialise, 0x5BC090);
    RH_ScopedGlobalInstall(PickGangToCreateMembersOf, 0x60F8D0, { .reversed = false });
    RH_ScopedGlobalInstall(FindNewPedType, 0x60FBD0);
    RH_ScopedGlobalInstall(PickPedMIToStreamInForCurrentZone, 0x60FFD0, { .reversed = false });
    RH_ScopedGlobalInstall(IsPedAppropriateForCurrentZone, 0x610150, { .reversed = false });
    RH_ScopedGlobalInstall(IsPedInGroup, 0x610210);
    RH_ScopedGlobalInstall(PickARandomGroupOfOtherPeds, 0x610420);
    RH_ScopedGlobalInstall(PlayerKilledADealer, 0x610490, { .reversed = false });
    RH_ScopedGlobalInstall(UpdateDealerStrengths, 0x6104B0, { .reversed = false });
    RH_ScopedGlobalInstall(UpdateAreaDodgyness, 0x610560, { .reversed = false });
    //RH_ScopedGlobalInstall(UpdateIsGangArea, 0x6106D0, { .reversed = false });
    RH_ScopedGlobalInstall(PedIsAcceptableInCurrentZone, 0x610720);
    RH_ScopedGlobalInstall(UpdatePercentages, 0x610770, { .reversed = false });
    RH_ScopedGlobalInstall(Update, 0x610BF0, { .reversed = false });
    RH_ScopedGlobalInstall(GetCurrentPercOther_Peds, 0x610310);
    RH_ScopedGlobalInstall(IsPedAppropriateForCurrentZone, 0x610150);
}

// 0x5BC090
void CPopCycle::Initialise() {
    CFileMgr::SetDir("DATA");
    const auto file = CFileMgr::OpenFile("POPCYCLE.DAT", "r");
    CFileMgr::SetDir("");

    const notsa::AutoCallOnDestruct autoCloser{ [&] { CFileMgr::CloseFile(file); } };

    auto nline{ 1u };
    for (auto zone = 0; zone < (uint32)ZoneType::COUNT; zone++) {
        for (auto wktime = 0; wktime < 2; wktime++) { // weekday (0) / weekend(1)
            for (auto daytime = 0; daytime < 24 / PERC_DATA_TIME_RESOLUTION_HR; daytime++) {
                // Find next suitable data line
                const char* l{};
                while (true) {
                    l = CFileLoader::LoadLine(file);
                    if (!l) {
                        NOTSA_UNREACHABLE("Expected more data, got EOF!");
                    }
                    nline++;
                    if (l[0] != '/' && l[0]) {
                        break;
                    }
                }

                // Ideall we could/would use a file pointer here (instead of `LoadLine`)
                // and read each number one-by-one.
                // But until then we're stuck with this hardcoded version.

                auto& curr = m_nPercTypeGroup[daytime][wktime][zone];
                const auto nread = sscanf(
                    l,
                    "%hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu",

                    &m_nMaxNumPeds[daytime][wktime][zone],
                    &m_nMaxNumCars[daytime][wktime][zone],

                    &m_nPercDealers[daytime][wktime][zone],
                    &m_nPercGang[daytime][wktime][zone],
                    &m_nPercCops[daytime][wktime][zone],
                    &m_nPercOther[daytime][wktime][zone],

                    &curr[0], &curr[1], &curr[2], &curr[3], &curr[4], &curr[5],
                    &curr[6], &curr[7], &curr[8], &curr[9], &curr[10], &curr[11],
                    &curr[12], &curr[13], &curr[14], &curr[15], &curr[16], &curr[17]
                );
                if (nread != 6 + 18) {
                    NOTSA_UNREACHABLE("Failed reading all data!");
                }
            }
        }
    }
}

// 0x60FBD0
bool CPopCycle::FindNewPedType(ePedType& outPedType, int32& outPedMI, bool noGangs, bool noCops) {
    // NOTSA: Bug prevention
    outPedMI = MODEL_INVALID;

    if (!m_pCurrZoneInfo) {
        return false;
    }

    if (CPopulation::bInPoliceStation && CGeneral::RandomBool(70)) {
        outPedType = PED_TYPE_COP;
        outPedMI = CPopulation::ChoosePolicePedOccupation();
        return true;
    }

    auto dealersChance = m_NumDealers_Peds - (float)CPopulation::ms_nNumDealers;

    auto gangChance = m_NumGangs_Peds - (float)CPopulation::GetTotalNumGang();
    if (CPopulation::m_bOnlyCreateRandomGangMembers) {
        gangChance = 50.f;
    }
    if (CPopulation::m_bDontCreateRandomGangMembers || noGangs) {
        gangChance = -10.f;
    }

    auto copChance = m_NumCops_Peds - (float)CPopulation::ms_nNumCop;
    if (CGangWars::GangWarFightingGoingOn() || CPopulation::m_bDontCreateRandomCops || noCops || m_pCurrZoneInfo->noCops) {
        copChance = -10.f;
    }

    auto civPedsChance = CPopCycle::m_NumOther_Peds - (float)(CPopulation::ms_nNumCivMale + CPopulation::ms_nNumCivFemale);

    for (auto chance : { &civPedsChance, &copChance, &dealersChance, &gangChance }) {
        if (*chance < 2.f) {
            *chance *= CGeneral::GetRandomNumber();
        }
    }

    if (!CGame::CanSeeOutSideFromCurrArea()) {
        dealersChance = -10.f;
    }

    // Pirulax: I had to refactor the code to be acceptable and bugless - sorry}
    while (true) {
        const auto highestChance = std::max({ civPedsChance, copChance, dealersChance, gangChance });

        if (highestChance <= 0.f) {
            return false;
        }

        if (highestChance == dealersChance) {
            // 0x60FEF2:
            // Because originally there was no `return` inside the loop itself it always returned at the last viable ID.
            // we reverse the loop and just return at the first viable ID.
            // It seems intentional, but I'm unsure what the purpose was.
            for (auto modelId : CPopulation::GetModelsInPedGroup(CPopulation::GetPedGroupId(POPCYCLE_GROUP_DEALERS)) | rng::views::reverse) {
                if (CStreaming::IsModelLoaded(modelId)) {
                    outPedMI = modelId;
                    return true;
                }
            }
            dealersChance = 0.f;
            outPedType = PED_TYPE_DEALER;
            continue;
        } else if (highestChance == gangChance) { // 0x60FBD0
            outPedType = PickGangToCreateMembersOf();
            if (outPedType) {
                outPedMI = CPopulation::ChooseGangOccupation(outPedType - ePedType::PED_TYPE_GANG1);
                if (outPedMI >= 0) {
                    return true;
                }
            } else {
                outPedMI = -1;
            }
            if (CPopulation::m_bOnlyCreateRandomGangMembers) {
                return false;
            }
            gangChance = 0.f;
            continue;
        } else if (highestChance == copChance) { // 0x60FF62
            outPedMI = CPopulation::ChoosePolicePedOccupation();
            outPedType = PED_TYPE_COP;
            return true;
        } else if (highestChance == civPedsChance) { // 0x60FF8F
            outPedMI = CPopulation::ChooseCivilianOccupation(0, 0, -1, -1, -1, 0, 1, 0, 0);
            if (outPedMI <= MODEL_INVALID || outPedMI == MODEL_MALE01) {
                return false;
            }
            outPedType = CModelInfo::GetPedModelInfo(outPedMI)->m_nPedType;
            return true;
        } else {
            NOTSA_UNREACHABLE();
        }
    }
}

// 0x610310
float CPopCycle::GetCurrentPercOther_Peds() {
    const auto percOther = (float)m_nPercOther[CPopCycle::m_nCurrentTimeIndex][CPopCycle::m_nCurrentTimeOfWeek][CPopCycle::m_nCurrentZoneType];

    if (CDarkel::FrenzyOnGoing()) {
        return percOther;
    }

    if (CTheScripts::IsPlayerOnAMission()) {
        if (const auto plyr = FindPlayerPed()) {
            if (plyr->IsInVehicle()) {
                switch (plyr->m_pVehicle->m_nModelIndex) {
                case MODEL_TAXI:
                case MODEL_CABBIE:
                    return percOther;
                }
            }
        }
    }

    return percOther * (1.f - std::sqrt(CWeather::Rain) * 0.8f);
}

// 0x610150
bool CPopCycle::IsPedAppropriateForCurrentZone(int32 modelIndex) {
    // Check if the model's race is allowed
    if (IsRaceAllowedInCurrentZone(CModelInfo::GetPedModelInfo(modelIndex)->GetRace())) {
        return false;
    }

    // Check if any group active in this zone contains the given model
    for (auto grpId = 0; grpId < POPCYCLE_TOTAL_GROUPS; grpId++) {
        // Check if this group is active now
        if (!m_nPercTypeGroup[m_nCurrentTimeIndex][m_nCurrentTimeOfWeek][m_pCurrZoneInfo->zonePopulationType]) {
            continue;
        }

        // Check if group contains this model
        for (auto mdlId : CPopulation::GetModelsInPedGroup(CPopulation::GetPedGroupId((ePopcycleGroup)grpId, CPopulation::CurrentWorldZone))) {
            if (mdlId == modelIndex) {
                return true;
            }
        }
    }

    // No group currently active contains the given model
    return false;
}

// 0x610210
bool CPopCycle::IsPedInGroup(int32 modelIndex, ePopcycleGroup group) {
    for (auto pedGroup : CPopulation::GetPedGroupsOfGroup(group)) {
        for (auto mdlId : CPopulation::GetModelsInPedGroup(pedGroup)) {
            if (mdlId == modelIndex) {
                return true;
            }
        }
    }
    return false;
}

// 0x610720
bool CPopCycle::PedIsAcceptableInCurrentZone(int32 modelIndex) {
    if (!m_pCurrZoneInfo) {
        return false;
    }

    if (CCheat::IsZoneStreamingAllowed()) {
        return true;
    }

    if (IsRaceAllowedInCurrentZone(CModelInfo::GetPedModelInfo(modelIndex)->GetRace())) {
        return true;
    }

    return false;
}

// 0x610420
int32 CPopCycle::PickARandomGroupOfOtherPeds() {
    auto rndPerc = (uint8)CGeneral::GetRandomNumberInRange(0.f, 100.f);
    for (auto [grpIdx, grpPerc] : notsa::enumerate(m_nPercTypeGroup[m_nCurrentTimeIndex][m_nCurrentTimeOfWeek][m_pCurrZoneInfo->zonePopulationType])) {
        if (rndPerc >= grpPerc) {
            return (ePopcycleGroupPerc)grpIdx;
        }
        rndPerc -= grpPerc;
    }
    NOTSA_UNREACHABLE(); // In reality this would return an invalid (index eqv. of `.end()` of the array) => UB
}

// 0x60FFD0
int32 CPopCycle::PickPedMIToStreamInForCurrentZone() {
    return plugin::CallAndReturn<int32, 0x60FFD0>();
}

// 0x610490
void CPopCycle::PlayerKilledADealer() {
    if (m_pCurrZoneInfo && m_pCurrZoneInfo->DrugDealerCounter) {
        m_pCurrZoneInfo->DrugDealerCounter--;
    }
}

// 0x610BF0
void CPopCycle::Update() {
    plugin::Call<0x610BF0>();
}

// 0x610560
void CPopCycle::UpdateAreaDodgyness() {
    return plugin::Call<0x610560>();

    m_fCurrentZoneDodgyness = 0.0f;
    m_fCurrentZoneDodgyness = (float)m_pCurrZoneInfo->DrugDealerCounter * 0.07f;
    m_fCurrentZoneDodgyness = std::accumulate(
        std::begin(m_pCurrZoneInfo->GangDensity),
        std::end(m_pCurrZoneInfo->GangDensity),
        m_fCurrentZoneDodgyness,
        [](const auto& a, const auto& b) { return a + float(b) / 100.0f; }
    );
    m_fCurrentZoneDodgyness = std::min(m_fCurrentZoneDodgyness, 1.0f);
}

// 0x6104B0
void CPopCycle::UpdateDealerStrengths() {
    plugin::Call<0x6104B0>();
}

// 0x610770
void CPopCycle::UpdatePercentages() {
    plugin::Call<0x610770>();
}

// 0x60F8D0
ePedType CPopCycle::PickGangToCreateMembersOf() {
    return plugin::CallAndReturn<ePedType, 0x60F8D0>();
}

// notsa
bool CPopCycle::IsRaceAllowedInCurrentZone(ePedRace race) {
    return race != RACE_DEFAULT && m_pCurrZoneInfo->zonePopulationRace & (1 << (race - 1));
}
