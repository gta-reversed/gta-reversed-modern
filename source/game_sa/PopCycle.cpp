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
    //RH_ScopedGlobalInstall(PickGangToCreateMembersOf, 0x60F8D0, { .reversed = false });
    RH_ScopedGlobalInstall(FindNewPedType, 0x60FBD0, { .reversed = false });
    RH_ScopedGlobalInstall(PickPedMIToStreamInForCurrentZone, 0x60FFD0, { .reversed = false });
    RH_ScopedGlobalInstall(IsPedAppropriateForCurrentZone, 0x610150, { .reversed = false });
    RH_ScopedGlobalInstall(IsPedInGroup, 0x610210, { .reversed = false });
    RH_ScopedGlobalInstall(PickARandomGroupOfOtherPeds, 0x610420, { .reversed = false });
    RH_ScopedGlobalInstall(PlayerKilledADealer, 0x610490, { .reversed = false });
    RH_ScopedGlobalInstall(UpdateDealerStrengths, 0x6104B0, { .reversed = false });
    RH_ScopedGlobalInstall(UpdateAreaDodgyness, 0x610560, { .reversed = false });
    //RH_ScopedGlobalInstall(UpdateIsGangArea, 0x6106D0, { .reversed = false });
    RH_ScopedGlobalInstall(PedIsAcceptableInCurrentZone, 0x610720, { .reversed = false });
    RH_ScopedGlobalInstall(UpdatePercentages, 0x610770, { .reversed = false });
    RH_ScopedGlobalInstall(Update, 0x610BF0, { .reversed = false });
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
bool CPopCycle::FindNewPedType(ePedType* arg1, int32* modelIndex, bool arg3, bool arg4) {
    return plugin::CallAndReturn<bool, 0x60FBD0, ePedType*, int32*, bool, bool>(arg1, modelIndex, arg3, arg4);
}

// 0x610310
float CPopCycle::GetCurrentPercOther_Peds() {
    return plugin::CallAndReturn<float, 0x610310>();
}

// 0x610150
bool CPopCycle::IsPedAppropriateForCurrentZone(int32 modelIndex) {
    return plugin::CallAndReturn<bool, 0x610150, int32>(modelIndex);
}

// 0x610210
bool CPopCycle::IsPedInGroup(int32 modelIndex, int32 PopCycle_Group) {
    return plugin::CallAndReturn<bool, 0x610210, int32, int32>(modelIndex, PopCycle_Group);
}

// 0x610720
bool CPopCycle::PedIsAcceptableInCurrentZone(int32 modelIndex) {
    return plugin::CallAndReturn<bool, 0x610720, int32>(modelIndex);
}

// 0x610420
int32 CPopCycle::PickARandomGroupOfOtherPeds() {
    return plugin::CallAndReturn<int32, 0x610420>();
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
