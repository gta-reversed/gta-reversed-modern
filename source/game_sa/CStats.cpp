/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

tStatMessage (&CStats::StatMessage)[8] = *(tStatMessage(*)[8])0xB78200;
char (&CStats::LastMissionPassedName)[8] = *(char(*)[8])0xB78A00;
int (&CStats::TimesMissionAttempted)[100] = *(int(*)[100])0xB78CC8;
int (&CStats::FavoriteRadioStationList)[14] = *(int(*)[14])0xB78E58;
int (&CStats::PedsKilledOfThisType)[32] = *(int(*)[32])0xB78E90;
float (&CStats::StatReactionValue)[59] = *(float(*)[59])0xB78F10;
int (&CStats::StatTypesInt)[223] = *(int(*)[223])0xB79000;
float (&CStats::StatTypesFloat)[82] = *(float(*)[82])0xB79380;
unsigned int& CStats::TotalNumStatMessages = *(unsigned int*)0xB794D0;
bool& CStats::bStatUpdateMessageDisplayed = *(bool*)0xB794D4;
unsigned int& CStats::m_SprintStaminaCounter = *(unsigned int*)0xB794D8;
unsigned int& CStats::m_CycleStaminaCounter = *(unsigned int*)0xB794DC;
unsigned int& CStats::m_CycleSkillCounter = *(unsigned int*)0xB794E0;
unsigned int& CStats::m_SwimStaminaCounter = *(unsigned int*)0xB794E4;
unsigned int& CStats::m_SwimUnderWaterCounter = *(unsigned int*)0xB794E8;
unsigned int& CStats::m_DrivingCounter = *(unsigned int*)0xB794EC;
unsigned int& CStats::m_FlyingCounter = *(unsigned int*)0xB794F0;
unsigned int& CStats::m_BoatCounter = *(unsigned int*)0xB794F4;
unsigned int& CStats::m_BikeCounter = *(unsigned int*)0xB794F8;
unsigned int& CStats::m_FatCounter = *(unsigned int*)0xB794FC;
unsigned int& CStats::m_RunningCounter = *(unsigned int*)0xB79500;
unsigned int& CStats::m_WeaponCounter = *(unsigned int*)0xB79504;
unsigned int& CStats::m_DeathCounter = *(unsigned int*)0xB79508;
unsigned int& CStats::m_MaxHealthCounter = *(unsigned int*)0xB7950C;
unsigned int& CStats::m_AddToHealthCounter = *(unsigned int*)0xB79510;
unsigned int& CStats::m_LastWeaponTypeFired = *(unsigned int*)0xB79514;

void CStats::InjectHooks() {
    ReversibleHooks::Install("CStats", "Init", 0x55C0C0, &CStats::Init);
    ReversibleHooks::Install("CStats", "GetStatValue", 0x558E40, &CStats::GetStatValue);
    ReversibleHooks::Install("CStats", "SetStatValue", 0x55A070, &CStats::SetStatValue);
    ReversibleHooks::Install("CStats", "GetStatType", 0x558E30, &CStats::GetStatType);
    ReversibleHooks::Install("CStats", "GetFullFavoriteRadioStationList", 0x558F90, &CStats::GetFullFavoriteRadioStationList);
    ReversibleHooks::Install("CStats", "FindCriminalRatingNumber", 0x559080, &CStats::FindCriminalRatingNumber);
    ReversibleHooks::Install("CStats", "GetPercentageProgress", 0x5591E0, &CStats::GetPercentageProgress);
    ReversibleHooks::Install("CStats", "ConvertToMins", 0x559540, &CStats::ConvertToMins);
    ReversibleHooks::Install("CStats", "ConvertToSecs", 0x559560, &CStats::ConvertToSecs);
    ReversibleHooks::Install("CStats", "SafeToShowThisStat", 0x559590, &CStats::SafeToShowThisStat);
    ReversibleHooks::Install("CStats", "CheckForThreshold", 0x5595F0, &CStats::CheckForThreshold);
    ReversibleHooks::Install("CStats", "IsStatCapped", 0x559630, &CStats::IsStatCapped);
    ReversibleHooks::Install("CStats", "LoadActionReactionStats", 0x5599B0, &CStats::LoadActionReactionStats);
    ReversibleHooks::Install("CStats", "FindMaxNumberOfGroupMembers", 0x559A50, &CStats::FindMaxNumberOfGroupMembers);
    ReversibleHooks::Install("CStats", "ProcessReactionStatsOnDecrement", 0x559730, &CStats::ProcessReactionStatsOnDecrement);
    ReversibleHooks::Install("CStats", "DecrementStat", 0x559FA0, &CStats::DecrementStat);
    ReversibleHooks::Install("CStats", "SetNewRecordStat", 0x55C410, &CStats::SetNewRecordStat);
    ReversibleHooks::Install("CStats", "RegisterFastestTime", 0x55A0B0, &CStats::RegisterFastestTime);
    ReversibleHooks::Install("CStats", "RegisterBestPosition", 0x55A160, &CStats::RegisterBestPosition);
    ReversibleHooks::Install("CStats", "ProcessReactionStatsOnIncrement", 0x55B900, &CStats::ProcessReactionStatsOnIncrement);
    ReversibleHooks::Install("CStats", "IncrementStat", 0x55C180, &CStats::IncrementStat);
    ReversibleHooks::Install("CStats", "UpdateStatsWhenSprinting", 0x55C660, &CStats::UpdateStatsWhenSprinting);
    ReversibleHooks::Install("CStats", "UpdateStatsWhenRunning", 0x55C6F0, &CStats::UpdateStatsWhenRunning);
    ReversibleHooks::Install("CStats", "UpdateStatsWhenOnMotorBike", 0x55CD60, &CStats::UpdateStatsWhenOnMotorBike);
    ReversibleHooks::Install("CStats", "UpdateStatsWhenFighting", 0x55CFA0, &CStats::UpdateStatsWhenFighting);
    ReversibleHooks::Install("CStats", "ModifyStat", 0x55D090, &CStats::ModifyStat);

    // unused
    ReversibleHooks::Install("CStats", "GetStatID", 0x558DE0, &CStats::GetStatID);
    ReversibleHooks::Install("CStats", "GetTimesMissionAttempted", 0x558E70, &CStats::GetTimesMissionAttempted);
    ReversibleHooks::Install("CStats", "RegisterMissionAttempted", 0x558E80, &CStats::RegisterMissionAttempted);
    ReversibleHooks::Install("CStats", "RegisterMissionPassed", 0x558EA0, &CStats::RegisterMissionPassed);

    ReversibleHooks::Install("CStats", "Save", 0x5D3B40, &CStats::Save);
    ReversibleHooks::Install("CStats", "Load", 0x5D3BF0, &CStats::Load);
}

// 0x55C0C0
void CStats::Init() {
    memset(StatTypesFloat, 0, sizeof(StatTypesFloat));
    memset(StatTypesInt, 0, sizeof(StatTypesInt));
    memset(PedsKilledOfThisType, 0, sizeof(PedsKilledOfThisType));
    memset(TimesMissionAttempted, 0, sizeof(TimesMissionAttempted));

    bStatUpdateMessageDisplayed = false;
    CTimer::m_snTimeInMilliseconds = 0;
    for (int32_t i = 0; i < 8; i++) {
        LastMissionPassedName[i] = '\0';
    }
    m_SprintStaminaCounter = 0;
    m_CycleStaminaCounter = 0;
    m_SwimStaminaCounter = 0;
    m_DrivingCounter = 0;
    m_FlyingCounter = 0;
    m_BoatCounter = 0;
    m_BikeCounter = 0;
    m_FatCounter = 0;
    m_RunningCounter = 0;

    StatTypesFloat[STAT_MAX_HEALTH] = 569.0f;
    CheckForStatsMessage();
    StatTypesFloat[STAT_STAMINA] = 100.0f;
    CheckForStatsMessage();

    PopulateFavoriteRadioStationList();
    LoadActionReactionStats();
    LoadStatUpdateConditions();
}

// 0x558E40
float CStats::GetStatValue(eStats stat) {
    if (!GetStatType(stat)) { // int
        assert(stat >= FIRST_INT_STAT);

        return static_cast<float>(StatTypesInt[stat - FIRST_INT_STAT]);
    }

    return StatTypesFloat[stat];
}

// 0x55A070
void CStats::SetStatValue(eStats stat, float value) {
    if (GetStatType(stat)) {
        StatTypesFloat[stat] = value;
    } else { // int
        assert(stat >= FIRST_INT_STAT);

        StatTypesInt[stat - FIRST_INT_STAT] = static_cast<int>(value);
    }
    CheckForStatsMessage();
}

// 0x558E30
bool CStats::GetStatType(eStats stat) {
    return stat < FIRST_UNUSED_STAT;
}

// 0x558EC0
bool CStats::PopulateFavoriteRadioStationList() {
    return plugin::CallAndReturn<bool, 0x558EC0>();
}

// 0x558F90
int* CStats::GetFullFavoriteRadioStationList() {
    return FavoriteRadioStationList;
}

// 0x558FA0
int CStats::FindMostFavoriteRadioStation() {
    return plugin::CallAndReturn<int, 0x558FA0>();
}

// 0x559010
int CStats::FindLeastFavoriteRadioStation() {
    return plugin::CallAndReturn<int, 0x559010>();
}

// 0x559080
int CStats::FindCriminalRatingNumber() {
    CPlayerInfo* playerInfo = FindPlayerPed()->GetPlayerInfoForThisPlayerPed();

    int value = (int)(
        GetStatValue(STAT_TOTAL_LEGITIMATE_KILLS)
        - (GetStatValue(STAT_TIMES_BUSTED) - GetStatValue(STAT_NUMBER_OF_HOSPITAL_VISITS)) * 3.0f
        + (GetStatValue(STAT_HIGHEST_FIREFIGHTER_MISSION_LEVEL) + GetStatValue(STAT_HIGHEST_PARAMEDIC_MISSION_LEVEL)) * 10.0f
        + playerInfo->m_nMoney / 5000.0f
        + GetStatValue(STAT_PLANES_HELICOPTERS_DESTROYED) * 30.0f
        + GetStatValue(STAT_TOTAL_FIRES_EXTINGUISHED)
        + GetStatValue(STAT_CRIMINALS_KILLED_ON_VIGILANTE_MISSION)
        + GetStatValue(STAT_PEOPLE_SAVED_IN_AN_AMBULANCE));

    if (CCheat::m_bHasPlayerCheated || GetStatValue(STAT_TIMES_CHEATED)) {
        value -= 10 * GetStatValue(STAT_TIMES_CHEATED);

        value = std::max(value, -10000);
    } else {
        value = std::max(value, 0);
    }

    float bulletsFired = GetStatValue(STAT_BULLETS_FIRED);

    if (bulletsFired >= 100.0f) {
        value += (int)(500 * (GetStatValue(STAT_BULLETS_THAT_HIT) / bulletsFired));
    }

    return value + (int)(10 * GetPercentageProgress());
}

// 0x5591E0
float CStats::GetPercentageProgress() {
    return std::min(StatTypesFloat[STAT_PROGRESS_MADE] / 187.0f * 100.0f, 100.0f);
}

// 0x559230
void CStats::BuildStatLine(char* line, void* pValue1, int metrics, void* pValue2, int type) {
    plugin::Call<0x559230, char*, void*, int, void*, int>(line, pValue1, metrics, pValue2, type);
}

// 0x559540
int CStats::ConvertToMins(int statValue) {
    if (statValue > 59)
        return (statValue - 60) / 60 + 1;
    return 0;
}

// 0x559560
int CStats::ConvertToSecs(int statValue) {
    int seconds = statValue;
    if (statValue > 59)
        seconds = -60 - 60 * ((statValue - 60) / 60) + statValue;
    if (seconds < 0)
        seconds = -seconds;
    return seconds;
}

// 0x559590
bool CStats::SafeToShowThisStat(eStats stat) {
    if (!CLocalisation::GermanGame()) {
        return true;
    }

    switch (stat) {
        case STAT_RAMPAGES_ATTEMPTED:
        case STAT_RAMPAGES_PASSED:
        case STAT_TOTAL_LEGITIMATE_KILLS:
        case STAT_HIGHEST_CIVILIAN_PEDS_KILLED_ON_RAMPAGE:
        case STAT_HIGHEST_POLICE_PEDS_KILLED_ON_RAMPAGE:
        case STAT_HIGHEST_CIVILIAN_VEHICLES_DESTROYED_ON_RAMPAGE:
        case STAT_HIGHEST_POLICE_VEHICLES_DESTROYED_ON_RAMPAGE:
        case STAT_HIGHEST_NUMBER_OF_TANKS_DESTROYED_ON_RAMPAGE:
            return false;
        default:
            return true;
    }
}

// 0x5595F0
bool CStats::CheckForThreshold(float* pValue, float range) {
    if (*pValue + 40.0f >= range && *pValue - 40.0f <= range) {
        return false;
    }
    *pValue = range;
    return true;
}

// 0x559630
bool CStats::IsStatCapped(eStats stat) {
    switch (stat) {
    case STAT_GIRLFRIEND_RESPECT:
    case STAT_CLOTHES_RESPECT:
    case STAT_FITNESS_RESPECT:
    case STAT_FAT:
    case STAT_STAMINA:
    case STAT_MUSCLE:
    case STAT_MAX_HEALTH:
    case STAT_SEX_APPEAL:
    case STAT_PISTOL_SKILL:
    case STAT_SILENCED_PISTOL_SKILL:
    case STAT_DESERT_EAGLE_SKILL:
    case STAT_SHOTGUN_SKILL:
    case STAT_SAWN_OFF_SHOTGUN_SKILL:
    case STAT_COMBAT_SHOTGUN_SKILL:
    case STAT_MACHINE_PISTOL_SKILL:
    case STAT_SMG_SKILL:
    case STAT_AK_47_SKILL:
    case STAT_M4_SKILL:
    case STAT_RIFLE_SKILL:
    case STAT_APPEARANCE:
    case STAT_ARMOR:
    case STAT_ENERGY:
    case STAT_DRIVING_SKILL:
    case STAT_FLYING_SKILL:
    case STAT_LUNG_CAPACITY:
    case STAT_BIKE_SKILL:
    case STAT_LUCK:
    case STAT_HORSESHOES_COLLECTED:
    case STAT_TOTAL_HORSESHOES:
    case STAT_OYSTERS_COLLECTED:
    case STAT_TOTAL_OYSTERS:
    case STAT_CYCLING_SKILL:
        return true;
    }
    return false;
}

// 0x559760
void CStats::CheckForStatsMessage() {
    plugin::Call<0x559760>();
}

// 0x559860
void CStats::LoadStatUpdateConditions() {
    plugin::Call<0x559860>();
}

// 0x5599B0
void CStats::LoadActionReactionStats() {
    CFileMgr::SetDir(gta_empty_string);

    FILESTREAM fp = CFileMgr::OpenFile("DATA\\AR_STATS.DAT", "rb");
    char statName[64] = {}; // unused

    for (char* line = CFileLoader::LoadLine(fp); line != nullptr; line = CFileLoader::LoadLine(fp)) {
        int reactId;
        float reactValue;

        if (line[0] != '#' && line[0] != NULL) {
            sscanf(line, "%d %s %f", &reactId, &statName, &reactValue);

            StatReactionValue[reactId] = reactValue;
        }
    }

    CFileMgr::CloseFile(fp);
}

// 0x559A50
int CStats::FindMaxNumberOfGroupMembers() {
    float respect = StatTypesFloat[STAT_TOTAL_RESPECT];

    if (respect < 10.0f)
        return 0;
    if (respect < 60.0f)
        return 2;
    if (respect < 160.0f)
        return 3;
    if (respect < 330.0f)
        return 4;
    if (respect < 540.0f)
        return 5;
    if (respect < 800.0f)
        return 6;

    return 7;
}

// 0x559AF0
float CStats::GetFatAndMuscleModifier(eStatModAbilities statMod) {
    return plugin::CallAndReturn<float, 0x559AF0, eStatModAbilities>(statMod);
}

// 0x559730
void CStats::ProcessReactionStatsOnDecrement(eStats stat) {
    if (stat == STAT_ENERGY && GetStatValue(STAT_ENERGY) < 0.0f)
        DecrementStat(STAT_FAT, 23.0f);
}

// 0x559FA0
void CStats::DecrementStat(eStats stat, float value) {
    if (value <= 0.0f)
        return;

    float oldValue = GetStatValue(stat);

    SetStatValue(stat, std::max(oldValue - value, 0.0f));

    ProcessReactionStatsOnDecrement(stat);
    CheckForStatsMessage();
}

// 0x55C410
void CStats::SetNewRecordStat(eStats stat, float value) {
    float currentValue = GetStatValue(stat);

    if (currentValue < value)
        SetStatValue(stat, value);

    CheckForStatsMessage();
}

// 0x55A0B0
void CStats::RegisterFastestTime(eStats stat, int fastestTime) {
    SetNewRecordStat(stat, (float)fastestTime);
}

// 0x55A160
void CStats::RegisterBestPosition(eStats stat, int position) {
    SetNewRecordStat(stat, (float)position);
}

// 0x55A210
char* CStats::FindCriminalRatingString() {
    return plugin::CallAndReturn<char*, 0x55A210>();
}

// 0x55A780
int CStats::ConstructStatLine(int arg0, unsigned char arg1) {
    return plugin::CallAndReturn<int, 0x55A780, int, unsigned char>(arg0, arg1);
}

// 0x55B900
void CStats::ProcessReactionStatsOnIncrement(eStats stat) {
    if (stat != STAT_STAMINA && stat != STAT_ENERGY && stat != STAT_LUNG_CAPACITY)
        return;

    float energy = GetStatValue(STAT_ENERGY);

    if (stat == STAT_STAMINA || stat == STAT_LUNG_CAPACITY) {
        if (energy < 0.0f) {
            StatTypesFloat[STAT_FAT] = std::max(StatTypesFloat[STAT_FAT] - 23.0f, 0.0f);
            CheckForStatsMessage();
        }
        return;
    }

    if (energy > 1000.0f)
        IncrementStat(STAT_FAT, energy - 1000.0f);
}

// 0x55B980
void CStats::DisplayScriptStatUpdateMessage(unsigned char state, eStats stat, float value) {
    plugin::Call<0x55B980, unsigned char, eStats, float>(state, stat, value);
}

// 0x55BC50
void CStats::UpdateRespectStat(unsigned char arg0) {
    plugin::Call<0x55BC50, unsigned char>(arg0);
}

// 0x55BF20
void CStats::UpdateSexAppealStat() {
    plugin::Call<0x55BF20>();
}

// 0x55C180
void CStats::IncrementStat(eStats stat, float value)
{
    if (value <= 0.0f)
        return;

    if (GetStatType(stat)) { // float
        StatTypesFloat[stat] += value;

        if (IsStatCapped(stat))
            StatTypesFloat[stat] = std::min(StatTypesFloat[stat], 1000.0f);

        ProcessReactionStatsOnIncrement(stat);
        CheckForStatsMessage();

        return;
    }

    CPlayerPed* player = FindPlayerPed();
    CPlayerInfo* playerInfo = player->GetPlayerInfoForThisPlayerPed();

    if (stat == STAT_CALORIES) {
        float healthDiff = playerInfo->m_nMaxHealth - player->m_fHealth;

        IncrementStat(STAT_RIOT_MISSION_ACCOMPLISHED, value);

        if (value > healthDiff) {
            float avg = (value - healthDiff) / 2.0f;

            IncrementStat(STAT_FAT, avg);
        }

        ProcessReactionStatsOnIncrement(stat);
        CheckForStatsMessage();

        return;
    }

    if (stat != STAT_RIOT_MISSION_ACCOMPLISHED) {
        assert(stat >= FIRST_INT_STAT);

        StatTypesInt[stat - FIRST_INT_STAT] += (int)value;

        if (IsStatCapped(stat))
            StatTypesInt[stat - FIRST_INT_STAT] = std::min(StatTypesInt[stat - FIRST_INT_STAT], 1000);

        ProcessReactionStatsOnIncrement(stat);
        CheckForStatsMessage();

        return;
    }

    // STAT_RIOT_MISSION_ACCOMPLISHED increment, enum name incorrect?

    float kcals = playerInfo->m_nNumHoursDidntEat - value / 2.0f;
    kcals = clamp(kcals, 0.0f, 36.0f);

    float healthDiff = playerInfo->m_nMaxHealth - player->m_fHealth;

    if (value >= healthDiff) {
        playerInfo->m_nNumHoursDidntEat = 0;
    }

    player->m_fHealth += value;
    UpdateStatsAddToHealth((uint32_t)value);
    ProcessReactionStatsOnIncrement(stat);
    CheckForStatsMessage();
}

// 0x55C470
void CStats::UpdateFatAndMuscleStats(unsigned int value) {
    plugin::Call<0x55C470, unsigned int>(value);
}

// 0x55C660
void CStats::UpdateStatsWhenSprinting() {
    UpdateFatAndMuscleStats(static_cast<unsigned int>(StatReactionValue[STAT_EXERCISE_RATE_SPRINT]));
    if (StatReactionValue[STAT_TIMELIMIT_SPRINT_STAMINA] * 1000.0f >= static_cast<float>(m_SprintStaminaCounter)) {
        m_SprintStaminaCounter += static_cast<unsigned int>(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
    } else {
        m_SprintStaminaCounter = 0;
        IncrementStat(STAT_STAMINA, StatReactionValue[STAT_INC_SPRINT_STAMINA]);
        DisplayScriptStatUpdateMessage(1, STAT_STAMINA, StatReactionValue[STAT_INC_SPRINT_STAMINA]);
    }
}

// 0x55C6F0
void CStats::UpdateStatsWhenRunning() {
    UpdateFatAndMuscleStats((unsigned int)StatReactionValue[STAT_EXERCISE_RATE_RUN]);
    if (StatReactionValue[STAT_TIMELIMIT_RUNNING] * 1000.0f >= static_cast<float>(m_RunningCounter)) {
        m_RunningCounter += static_cast<unsigned int>(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
    } else {
        m_RunningCounter = 0;
        IncrementStat(STAT_STAMINA, StatReactionValue[STAT_INC_RUNNING]);
        DisplayScriptStatUpdateMessage(1, STAT_STAMINA, StatReactionValue[STAT_INC_RUNNING]);
    }
}

// 0x55C780
void CStats::UpdateStatsWhenCycling(bool arg0, CBmx* bmx) {
    plugin::Call<0x55C780, bool, CBmx*>(arg0, bmx);
}

// 0x55C990
void CStats::UpdateStatsWhenSwimming(bool arg0, bool arg1) {
    plugin::Call<0x55C990, bool, bool>(arg0, arg1);
}

// 0x55CAC0
void CStats::UpdateStatsWhenDriving(CVehicle* vehicle) {
    plugin::Call<0x55CAC0, CVehicle*>(vehicle);
}

// 0x55CC00
void CStats::UpdateStatsWhenFlying(CVehicle* vehicle) {
    plugin::Call<0x55CC00, CVehicle*>(vehicle);
}

// 0x55CD60
void CStats::UpdateStatsWhenOnMotorBike(CBike* bike) {
    float bikeCounter = static_cast<float>(m_BikeCounter);
    if (StatReactionValue[STAT_TIMELIMIT_MOTORBIKE_SKILL] * 1000.0f >= bikeCounter) {
        float bikeMoveSpeed = bike->m_vecMoveSpeed.Magnitude();
        float fTimeStep = (CTimer::ms_fTimeStep * 0.02f * 1000.0f);
        if (bikeMoveSpeed > 0.6f || bike->m_nNumContactWheels < 3u && bikeMoveSpeed > 0.1f)
            m_BikeCounter = static_cast<unsigned int>(fTimeStep * 1.5f + bikeCounter);
        else if (bikeMoveSpeed > 0.2f)
            m_BikeCounter = static_cast<unsigned int>(fTimeStep * 0.5f + bikeCounter);
    } else {
        m_BikeCounter = 0;
        IncrementStat(STAT_BIKE_SKILL, StatReactionValue[STAT_INC_MOTORBIKE_SKILL]);
        DisplayScriptStatUpdateMessage(1, STAT_BIKE_SKILL, StatReactionValue[STAT_INC_MOTORBIKE_SKILL]);
    }
}

// 0x55CEB0
void CStats::UpdateStatsWhenWeaponHit(eWeaponType weaponType) {
    plugin::Call<0x55CEB0, eWeaponType>(weaponType);
}

// 0x55CFA0
void CStats::UpdateStatsWhenFighting() {
    UpdateFatAndMuscleStats(static_cast<unsigned int>(StatReactionValue[STAT_EXERCISE_RATE_FIGHT]));
}

// 0x55CFC0
void CStats::UpdateStatsOnRespawn() {
    plugin::Call<0x55CFC0>();
}

// 0x55D030
void CStats::UpdateStatsAddToHealth(unsigned int addToHealth) {
    plugin::Call<0x55D030, unsigned int>(addToHealth);
}

// 0x55D090
void CStats::ModifyStat(eStats stat, float value) {
    if (value < 0.0f) {
        CStats::DecrementStat(stat, -value);
    } else {
        CStats::IncrementStat(stat, value);
    }
}

// 0x5D3B40
bool CStats::Save() {
    float unsavedKills = GetStatValue(STAT_KILLS_SINCE_LAST_CHECKPOINT);
    IncrementStat(STAT_TOTAL_LEGITIMATE_KILLS, unsavedKills);
    SetStatValue(STAT_KILLS_SINCE_LAST_CHECKPOINT, 0.0);

    CGenericGameStorage::SaveDataToWorkBuffer(StatTypesFloat,           sizeof(StatTypesFloat));
    CGenericGameStorage::SaveDataToWorkBuffer(StatTypesInt,             sizeof(StatTypesInt));
    CGenericGameStorage::SaveDataToWorkBuffer(PedsKilledOfThisType,     sizeof(PedsKilledOfThisType));
    CGenericGameStorage::SaveDataToWorkBuffer(LastMissionPassedName,    sizeof(LastMissionPassedName));
    CGenericGameStorage::SaveDataToWorkBuffer(FavoriteRadioStationList, sizeof(FavoriteRadioStationList));
    CGenericGameStorage::SaveDataToWorkBuffer(TimesMissionAttempted,    sizeof(TimesMissionAttempted));

    for (int i = 0; i < sizeof(StatMessage); i++) {
        CGenericGameStorage::SaveDataToWorkBuffer(&StatMessage[i].displayed, sizeof(bool));
    }

    return true;
}

// 0x5D3BF0
bool CStats::Load() {
    CGenericGameStorage::LoadDataFromWorkBuffer(StatTypesFloat,           sizeof(StatTypesFloat));
    CGenericGameStorage::LoadDataFromWorkBuffer(StatTypesInt,             sizeof(StatTypesInt));
    CGenericGameStorage::LoadDataFromWorkBuffer(PedsKilledOfThisType,     sizeof(PedsKilledOfThisType));
    CGenericGameStorage::LoadDataFromWorkBuffer(LastMissionPassedName,    sizeof(LastMissionPassedName));
    CGenericGameStorage::LoadDataFromWorkBuffer(FavoriteRadioStationList, sizeof(FavoriteRadioStationList));
    CGenericGameStorage::LoadDataFromWorkBuffer(TimesMissionAttempted,    sizeof(TimesMissionAttempted));

    for (int i = 0; i < sizeof(StatMessage); i++) {
        CGenericGameStorage::LoadDataFromWorkBuffer(&StatMessage[i].displayed, sizeof(uint8_t));
    }

    return true;
}

// Unused
char* CStats::GetStatID(eStats stat) {
    if (!GetStatType(stat)) // int
        sprintf(gString, "stat_i_%d", stat);
    else
        sprintf(gString, "stat_f_%d", stat);

    return gString;
}

// Unused
char CStats::GetTimesMissionAttempted(unsigned char missionId) {
    return TimesMissionAttempted[missionId];
}

// Unused
void CStats::RegisterMissionAttempted(unsigned char missionId) {
    if (TimesMissionAttempted[missionId] != -1)
        TimesMissionAttempted[missionId]++;
}

// Unused
void CStats::RegisterMissionPassed(unsigned char missionId) {
    TimesMissionAttempted[missionId] = -1;
}
