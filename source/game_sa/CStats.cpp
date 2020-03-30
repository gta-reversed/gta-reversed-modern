/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

tStatMessage *CStats::StatMessage = (tStatMessage*)0xB78200;
char *CStats::LastMissionPassedName = (char*)0xB78A00;
int *CStats::TimesMissionAttempted = (int*)0xB78CC8;
int *CStats::FavoriteRadioStationList = (int*)0xB78E58;
int *CStats::PedsKilledOfThisType = (int*)0xB78E90;
float *CStats::StatReactionValue = (float*)0xB78F10;
int *CStats::StatTypesInt = (int*)0xB79034;
float *CStats::StatTypesFloat = (float*)0xB79380;
short &CStats::m_ThisStatIsABarChart = *(short*)0xB794CC;
unsigned int &CStats::TotalNumStatMessages = *(unsigned int*)0xB794D0;
bool &CStats::bStatUpdateMessageDisplayed = *(bool*)0xB794D4;
unsigned int &CStats::m_SprintStaminaCounter = *(unsigned int*)0xB794D8;
unsigned int &CStats::m_CycleStaminaCounter = *(unsigned int*)0xB794DC;
unsigned int &CStats::m_CycleSkillCounter = *(unsigned int*)0xB794E0;
unsigned int &CStats::m_SwimStaminaCounter = *(unsigned int*)0xB794E4;
unsigned int &CStats::m_SwimUnderWaterCounter = *(unsigned int*)0xB794E8;
unsigned int &CStats::m_DrivingCounter = *(unsigned int*)0xB794EC;
unsigned int &CStats::m_FlyingCounter = *(unsigned int*)0xB794F0;
unsigned int &CStats::m_BoatCounter = *(unsigned int*)0xB794F4;
unsigned int &CStats::m_BikeCounter = *(unsigned int*)0xB794F8;
unsigned int &CStats::m_FatCounter = *(unsigned int*)0xB794FC;
unsigned int &CStats::m_RunningCounter = *(unsigned int*)0xB79500;
unsigned int &CStats::m_WeaponCounter = *(unsigned int*)0xB79504;
unsigned int &CStats::m_DeathCounter = *(unsigned int*)0xB79508;
unsigned int &CStats::m_MaxHealthCounter = *(unsigned int*)0xB7950C;
unsigned int &CStats::m_AddToHealthCounter = *(unsigned int*)0xB79510;
unsigned int &CStats::m_LastWeaponTypeFired = *(unsigned int*)0xB79514;

void CStats::InjectHooks()
{
    HookInstall(0x558DE0, &CStats::GetStatID, 7);
    HookInstall(0x558E70, &CStats::GetTimesMissionAttempted, 7);
    HookInstall(0x558E80, &CStats::RegisterMissionAttempted, 7);
    HookInstall(0x558EA0, &CStats::RegisterMissionPassed, 7);  
    HookInstall(0x558F90, &CStats::GetFullFavoriteRadioStationList, 7);
    HookInstall(0x559540, &CStats::ConvertToMins, 7);
    HookInstall(0x559560, &CStats::ConvertToSecs, 7);
    HookInstall(0x5595F0, &CStats::CheckForThreshold, 7);
    HookInstall(0x559630, &CStats::IsStatCapped, 7);
    HookInstall(0x55B900, &CStats::ProcessReactionStatsOnIncrement, 7); 
    HookInstall(0x55C6F0, &CStats::UpdateStatsWhenRunning, 7);
    HookInstall(0x55CD60, &CStats::UpdateStatsWhenOnMotorBike, 7);
    HookInstall(0x55C6F0, &CStats::UpdateStatsWhenRunning, 7);
    HookInstall(0x55CFA0, &CStats::UpdateStatsWhenFighting, 7);
}

// Unused
char* CStats::GetStatID(unsigned short stat) 
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<char*, 0x558DE0, unsigned short>(stat);
#else
    if (stat >= 0x52u)
        sprintf(gString, "stat_i_%d", stat);
    else
        sprintf(gString, "stat_f_%d", stat);
    return gString;
#endif 
}

// Unused
bool CStats::GetStatType(unsigned short stat) 
{
//#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x558E30, unsigned short>(stat);
//#else
//    return (unsigned __int16)this < 0x52u;
//#endif
}

// Converted from cdecl float CStats::GetStatValue(ushort stat) 0x558E40
float CStats::GetStatValue(unsigned short stat) {
    return plugin::CallAndReturn<float, 0x558E40, unsigned short>(stat);
}

// Unused
char CStats::GetTimesMissionAttempted(unsigned char missionId) 
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<char, 0x558E70, unsigned char>(missionId);
#else
    return TimesMissionAttempted[missionId];
#endif
}

// Unused
void CStats::RegisterMissionAttempted(unsigned char missionId) 
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x558E80, unsigned char>(missionId);
#else
    int timesMissionAttempted = CStats::TimesMissionAttempted[missionId];
    if (timesMissionAttempted != -1)
        CStats::TimesMissionAttempted[missionId] = timesMissionAttempted + 1;
#endif
}

// Unused
void CStats::RegisterMissionPassed(unsigned char missionId) 
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x558EA0, unsigned char>(missionId);
#else
    CStats::TimesMissionAttempted[missionId] = -1;
#endif
}

// Converted from cdecl bool CStats::PopulateFavoriteRadioStationList(void) 0x558EC0
bool CStats::PopulateFavoriteRadioStationList() {
    return plugin::CallAndReturn<bool, 0x558EC0>();
}

// Converted from cdecl int* CStats::GetFullFavoriteRadioStationList(void) 0x558F90
int *CStats::GetFullFavoriteRadioStationList() 
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<int*, 0x558F90>();
#else
    return FavoriteRadioStationList;
#endif
}

// Converted from cdecl int CStats::FindMostFavoriteRadioStation(void) 0x558FA0
int CStats::FindMostFavoriteRadioStation() {
    return plugin::CallAndReturn<int, 0x558FA0>();
}

// Converted from cdecl int CStats::FindLeastFavoriteRadioStation(void) 0x559010
int CStats::FindLeastFavoriteRadioStation() {
    return plugin::CallAndReturn<int, 0x559010>();
}

// Converted from cdecl int CStats::FindCriminalRatingNumber(void) 0x559080
int CStats::FindCriminalRatingNumber() {
    return plugin::CallAndReturn<int, 0x559080>();
}

// Converted from cdecl float CStats::GetPercentageProgress(void) 0x5591E0
float CStats::GetPercentageProgress() {
    return plugin::CallAndReturn<float, 0x5591E0>();
}

// Converted from cdecl void CStats::BuildStatLine(char *line, void *pValue1, int metrics, void *pValue2, int type) 0x559230
void CStats::BuildStatLine(char* line, void* pValue1, int metrics, void* pValue2, int type) {
    plugin::Call<0x559230, char*, void*, int, void*, int>(line, pValue1, metrics, pValue2, type);
}

// Converted from cdecl int CStats::ConvertToMins(int value) 0x559540
int CStats::ConvertToMins(int statValue){
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<int, 0x559540, int>(value);
#else
    unsigned int minutes = 0;
    if (statValue >= 60)
        minutes = (statValue - 60) / 60 + 1;
    return minutes;
#endif
}

// Converted from cdecl int CStats::ConvertToSecs(int value) 0x559560
int CStats::ConvertToSecs(int statValue){
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<int, 0x559560, int>(value);
#else
    int seconds = statValue;
    if (statValue >= 60)
        seconds = -60 - 60 * ((statValue - 60) / 60) + statValue;
    if (seconds < 0)
        seconds = -seconds;
    return seconds;
#endif
}

// Getting errors on IDA.
// Converted from cdecl bool CStats::SafeToShowThisStat(uchar stat) 0x559590
bool CStats::SafeToShowThisStat(unsigned char stat) {
    return plugin::CallAndReturn<bool, 0x559590, unsigned char>(stat);
}

// Converted from cdecl bool CStats::CheckForThreshold(float *pValue, float range) 0x5595F0
bool CStats::CheckForThreshold(float* pValue, float range) 
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x5595F0, float*, float>(pValue, range);
#else
    if (*pValue + 40.0f >= range && *pValue - 40.0f <= range)
        return false;
    *pValue = range;
    return true;
#endif // USE_DEFAULT_FUNCTIONS
}

// Converted from cdecl bool CStats::IsStatCapped(ushort stat) 0x559630
bool CStats::IsStatCapped(eStats stat)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x559630, eStats>(stat);
#else
    return 
        stat == STAT_GIRLFRIEND_RESPECT || 
        stat == STAT_CLOTHES_RESPECT || 
        stat == STAT_FITNESS_RESPECT || 
        stat == STAT_FAT || 
        stat == STAT_STAMINA ||
        stat == STAT_MUSCLE || 
        stat == STAT_MAX_HEALTH ||
        stat == STAT_SEX_APPEAL || 
        stat == STAT_PISTOL_SKILL || 
        stat == STAT_SILENCED_PISTOL_SKILL || 
        stat == STAT_DESERT_EAGLE_SKILL || 
        stat == STAT_SHOTGUN_SKILL || 
        stat == STAT_SAWN_OFF_SHOTGUN_SKILL ||
        stat == STAT_COMBAT_SHOTGUN_SKILL ||
        stat == STAT_MACHINE_PISTOL_SKILL || 
        stat == STAT_SMG_SKILL ||
        stat == STAT_AK_47_SKILL || 
        stat == STAT_M4_SKILL || 
        stat == STAT_RIFLE_SKILL ||
        stat == STAT_APPEARANCE ||
        stat == STAT_ARMOR || 
        stat == STAT_ENERGY || 
        stat == STAT_DRIVING_SKILL ||
        stat == STAT_FLYING_SKILL ||
        stat == STAT_LUNG_CAPACITY || 
        stat == STAT_BIKE_SKILL || 
        stat == STAT_LUCK || 
        stat == STAT_HORSESHOES_COLLECTED ||
        stat == STAT_TOTAL_HORSESHOES || 
        stat == STAT_OYSTERS_COLLECTED ||
        stat == STAT_TOTAL_OYSTERS || 
        stat == STAT_CYCLING_SKILL;
#endif
}

// Converted from cdecl void CStats::ProcessReactionStatsOnDecrement(uchar stat) 0x559730
void CStats::ProcessReactionStatsOnDecrement(unsigned char stat) {
    plugin::Call<0x559730, unsigned char>(stat);
}

// Converted from cdecl void CStats::CheckForStatsMessage() 0x559760
void CStats::CheckForStatsMessage() {
    plugin::Call<0x559760>();
}

// Converted from cdecl void CStats::LoadStatUpdateConditions(void) 0x559860
void CStats::LoadStatUpdateConditions() {
    plugin::Call<0x559860>();
}

// Converted from cdecl void CStats::LoadActionReactionStats(void) 0x5599B0
void CStats::LoadActionReactionStats() {
    plugin::Call<0x5599B0>();

}

// Converted from cdecl int CStats::FindMaxNumberOfGroupMembers(void) 0x559A50
int CStats::FindMaxNumberOfGroupMembers() {
    return plugin::CallAndReturn<int, 0x559A50>();
}

// Converted from cdecl float CStats::GetFatAndMuscleModifier(eStatModAbilities statMod) 0x559AF0
float CStats::GetFatAndMuscleModifier(eStatModAbilities statMod) {
    return plugin::CallAndReturn<float, 0x559AF0, eStatModAbilities>(statMod);
}

// Converted from cdecl void CStats::DecrementStat(ushort stat, float value) 0x559FA0
void CStats::DecrementStat(eStats stat, float value) {
    plugin::Call<0x559FA0, eStats, float>(stat, value);
}

// Converted from cdecl void CStats::SetStatValue(ushort stat, float value) 0x55A070
void CStats::SetStatValue(eStats stat, float value) {
    plugin::Call<0x55A070, eStats, float>(stat, value);
}

// Converted from cdecl void CStats::RegisterFastestTime(int stat, int time) 0x55A0B0
void CStats::RegisterFastestTime(eStats stat, int time) {
    plugin::Call<0x55A0B0, eStats, int>(stat, time);
}

// Converted from cdecl void CStats::RegisterBestPosition(int stat, int position) 0x55A160
void CStats::RegisterBestPosition(eStats stat, int position) {
    plugin::Call<0x55A160, eStats, int>(stat, position);
}

// Converted from cdecl char* CStats::FindCriminalRatingString(void) 0x55A210
char* CStats::FindCriminalRatingString() {
    return plugin::CallAndReturn<char*, 0x55A210>();
}

// Converted from cdecl int CStats::ConstructStatLine(int, uchar) 0x55A780
int CStats::ConstructStatLine(int arg0, unsigned char arg1) {
    return plugin::CallAndReturn<int, 0x55A780, int, unsigned char>(arg0, arg1);
}

// Converted from cdecl void CStats::ProcessReactionStatsOnIncrement(uchar stat) 0x55B900
void CStats::ProcessReactionStatsOnIncrement(eStats stat) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x55B900, unsigned char>(stat);
#else
    float longestExerciseBikeTime = 0.0f;
    float finalLongestExerciseBikeTime = 0.0f;

    if (stat != STAT_STAMINA && stat != STAT_ENERGY)
    {
        if (stat != STAT_LUNG_CAPACITY)
            return;
    }

    if (stat == STAT_STAMINA || stat != STAT_ENERGY) {
        float fLongestExerciseBikeTime = static_cast<float>(StatTypesInt[STAT_LONGEST_EXERCISE_BIKE_TIME]);
        if (fLongestExerciseBikeTime < 0.0f)
        {
            float fatValue = StatTypesFloat[STAT_FAT] - 23.0f;
            if (fatValue <= 0.0f)
                fatValue = 0.0f;
            StatTypesFloat[STAT_FAT] = fatValue;
            CheckForStatsMessage();
        }
        return;
    }

    longestExerciseBikeTime = (float)StatTypesInt[STAT_LONGEST_EXERCISE_BIKE_TIME];
    if (longestExerciseBikeTime > 1000.0f)
    {
        finalLongestExerciseBikeTime = longestExerciseBikeTime - 1000.0f;
        IncrementStat(STAT_FAT, finalLongestExerciseBikeTime);
    }
#endif

}

// Converted from cdecl void CStats::DisplayScriptStatUpdateMessage(uchar state, uint stat, float value) 0x55B980
void CStats::DisplayScriptStatUpdateMessage(unsigned char state, eStats stat, float value) {
    plugin::Call<0x55B980, unsigned char, eStats, float>(state, stat, value);
}

// Converted from cdecl void CStats::UpdateRespectStat(uchar) 0x55BC50
void CStats::UpdateRespectStat(unsigned char arg0) {
    plugin::Call<0x55BC50, unsigned char>(arg0);
}

// Converted from cdecl void CStats::UpdateSexAppealStat(void) 0x55BF20
void CStats::UpdateSexAppealStat() {
    plugin::Call<0x55BF20>();
}

// Converted from cdecl void CStats::Init(void) 0x55C0C0
void CStats::Init() {
    plugin::Call<0x55C0C0>();
}

// Converted from cdecl void CStats::IncrementStat(ushort stat, float value) 0x55C180
void CStats::IncrementStat(eStats stat, float value) {
    plugin::Call<0x55C180, eStats, float>(stat, value);
}

// Converted from cdecl void CStats::SetNewRecordStat(ushort stat, float value) 0x55C410
void CStats::SetNewRecordStat(unsigned short stat, float value) {
    plugin::Call<0x55C410, unsigned short, float>(stat, value);
}

// Converted from cdecl void CStats::UpdateFatAndMuscleStats(uint value) 0x55C470
void CStats::UpdateFatAndMuscleStats(unsigned int value) {
    plugin::Call<0x55C470, unsigned int>(value);
}

// Converted from cdecl void CStats::UpdateStatsWhenSprinting(void) 0x55C660
void CStats::UpdateStatsWhenSprinting() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x55C660>();
#else
    UpdateFatAndMuscleStats((unsigned int)CStats::StatReactionValue[30]);
    if (StatReactionValue[35] * 1000.0 >= (double)m_SprintStaminaCounter)
    {
        m_SprintStaminaCounter += (unsigned int)(CTimer::ms_fTimeStep * 0.02 * 1000.0);
    }
    else
    {
        m_SprintStaminaCounter = 0;
        IncrementStat(STAT_STAMINA, StatReactionValue[2]);
        DisplayScriptStatUpdateMessage(1, STAT_STAMINA, StatReactionValue[2]);
    }
#endif
}

// Converted from cdecl void CStats::UpdateStatsWhenRunning(void) 0x55C6F0
void CStats::UpdateStatsWhenRunning() 
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x55C6F0>();
#else
    UpdateFatAndMuscleStats((unsigned int)StatReactionValue[31]);
    if (StatReactionValue[36] * 1000.0 >= (double)m_RunningCounter)
    {
        m_RunningCounter += (unsigned int)(CTimer::ms_fTimeStep * 0.02 * 1000.0);
    }
    else
    {
        m_RunningCounter = 0;
        IncrementStat(STAT_STAMINA, StatReactionValue[3]);
        DisplayScriptStatUpdateMessage(1, STAT_STAMINA, StatReactionValue[3]);
    }
#endif
}

// Converted from cdecl void CStats::UpdateStatsWhenCycling(bool, CBmx *bmx) 0x55C780
void CStats::UpdateStatsWhenCycling(bool arg0, CBmx* bmx) {
    plugin::Call<0x55C780, bool, CBmx*>(arg0, bmx);
}

// Converted from cdecl void CStats::UpdateStatsWhenSwimming(bool, bool) 0x55C990
void CStats::UpdateStatsWhenSwimming(bool arg0, bool arg1) {
    plugin::Call<0x55C990, bool, bool>(arg0, arg1);
}

// Converted from cdecl void CStats::UpdateStatsWhenDriving(CVehicle *vehicle) 0x55CAC0
void CStats::UpdateStatsWhenDriving(CVehicle* vehicle) {
    plugin::Call<0x55CAC0, CVehicle*>(vehicle);
}

// Converted from cdecl void CStats::UpdateStatsWhenFlying(CVehicle *vehicle) 0x55CC00
void CStats::UpdateStatsWhenFlying(CVehicle* vehicle) {
    plugin::Call<0x55CC00, CVehicle*>(vehicle);
}

// Converted from cdecl void CStats::UpdateStatsWhenOnMotorBike(CBike *bike) 0x55CD60
void CStats::UpdateStatsWhenOnMotorBike(CBike* bike) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x55CD60, CBike*>(bike);
#else
    float bikeCounter = (float)m_BikeCounter;
    if (StatReactionValue[40] * 1000.0f >= bikeCounter)
    {
        float bikeMoveSpeed = bike->m_vecMoveSpeed.Magnitude();
        if (bikeMoveSpeed > 0.60000002f || bike->m_nNumContactWheels < 3u && bikeMoveSpeed > 0.1f)
        {
            m_BikeCounter = (unsigned int)((CTimer::ms_fTimeStep * 0.02 * 1000.0) * 1.5 + bikeCounter);
        }
        else if (bikeMoveSpeed > 0.2f)
        {
            m_BikeCounter = (unsigned int)((CTimer::ms_fTimeStep * 0.02 * 1000.0) * 0.5 + bikeCounter);
        }
    }
    else
    {
        m_BikeCounter = 0;
        IncrementStat(STAT_BIKE_SKILL, StatReactionValue[7]);
        DisplayScriptStatUpdateMessage(1, STAT_BIKE_SKILL, StatReactionValue[7]);
    }
#endif
}

// Converted from cdecl void CStats::UpdateStatsWhenWeaponHit(int weaponType) 0x55CEB0
void CStats::UpdateStatsWhenWeaponHit(eWeaponType weaponType) {
    plugin::Call<0x55CEB0, eWeaponType>(weaponType);
}

// Converted from cdecl void CStats::UpdateStatsWhenFighting(void) 0x55CFA0
void CStats::UpdateStatsWhenFighting() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x55CFA0>();
#else
    CStats::UpdateFatAndMuscleStats((unsigned int)CStats::StatReactionValue[32]);
#endif
}

// Converted from cdecl void CStats::UpdateStatsOnRespawn(void) 0x55CFC0
void CStats::UpdateStatsOnRespawn() {
    plugin::Call<0x55CFC0>();
}

// Converted from cdecl void CStats::UpdateStatsAddToHealth(uint addToHealth) 0x55D030
void CStats::UpdateStatsAddToHealth(unsigned int addToHealth) {
    plugin::Call<0x55D030, unsigned int>(addToHealth);
}

// Converted from cdecl void CStats::ModifyStat(ushort stat, float value) 0x55D090
void CStats::ModifyStat(eStats stat, float value) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x55D090, eStats, float>(stat, value);
#else
    if (value < 0.0f)
    {
        CStats::DecrementStat(stat, -value);
    }
    else
    {
        CStats::IncrementStat(stat, value);
    }
#endif
}

// Converted from cdecl bool CStats::Save(void) 0x5D3B40
bool CStats::Save() {
    return plugin::CallAndReturn<bool, 0x5D3B40>();
}

// Converted from cdecl bool CStats::Load(void) 0x5D3BF0
bool CStats::Load() {
    return plugin::CallAndReturn<bool, 0x5D3BF0>();
}