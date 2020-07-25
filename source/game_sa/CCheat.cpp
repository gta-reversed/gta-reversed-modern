#include "StdInc.h"

void(*(&CCheat::m_aCheatFunctions)[92])() = *reinterpret_cast<void(*(*)[92])()>(0x8A5B58);

int(&CCheat::m_aCheatHashKeys)[92] = *reinterpret_cast<int(*)[92]>(0x8A5CC8);
char(&CCheat::m_CheatString)[30] = *reinterpret_cast<char(*)[30]>(0x969110);
bool(&CCheat::m_aCheatsActive)[92] = *reinterpret_cast<bool(*)[92]>(0x969130);
bool& CCheat::m_bHasPlayerCheated = *reinterpret_cast<bool*>(0x96918C);

void CCheat::InjectHooks()
{
    HookInstall(0x438FF0, &CCheat::SuicideCheat);
}

void CCheat::AddToCheatString(char LastPressedKey) {
    plugin::CallDynGlobal<char>(0x438480, LastPressedKey);
}

void CCheat::AdrenalineCheat() {
    plugin::CallDynGlobal(0x439880);
}

void CCheat::AllCarsAreGreatCheat() {
    plugin::CallDynGlobal(0x4394E0);
}

void CCheat::AllCarsAreShitCheat() {
    plugin::CallDynGlobal(0x4394B0);
}

void CCheat::ApacheCheat() {
    return plugin::CallDynGlobal(0x43A550);
}

void CCheat::BeachPartyCheat() {
    plugin::CallDynGlobal(0x439230);
}

void CCheat::BlackCarsCheat() {
    plugin::CallDynGlobal(0x4390F0);
}

void CCheat::BlowUpCarsCheat() {
    plugin::CallDynGlobal(0x439D80);
}

void CCheat::CloudyWeatherCheat() {
    plugin::CallDynGlobal(0x438F60);
}

void CCheat::CountrysideInvasionCheat() {
    plugin::CallDynGlobal(0x439F60);
}

void CCheat::DozerCheat() {
    plugin::CallDynGlobal(0x43A660);
}

void CCheat::DrivebyCheat() {
    plugin::CallDynGlobal(0x4398D0);
}

void CCheat::DuskCheat() {
    plugin::CallDynGlobal(0x439540);
}

void CCheat::ElvisLivesCheat() {
    plugin::CallDynGlobal(0x4391D0);
}

void CCheat::EverybodyAttacksPlayerCheat() {
    plugin::CallDynGlobal(0x439C70);
}

void CCheat::ExtraSunnyWeatherCheat() {
    plugin::CallDynGlobal(0x438F50);
}

void CCheat::FastTimeCheat() {
    plugin::CallDynGlobal(0x438F90);
}

void CCheat::FatCheat() {
    plugin::CallDynGlobal(0x439110);
}

void CCheat::FlyboyCheat() {
    plugin::CallDynGlobal(0x43A530);
}

void CCheat::FoggyWeatherCheat() {
    plugin::CallDynGlobal(0x438F80);
}

void CCheat::FunhouseCheat() {
    plugin::CallDynGlobal(0x439720);
}

void CCheat::GangLandCheat() {
    plugin::CallDynGlobal(0x4393D0);
}

void CCheat::GangsCheat() {
    plugin::CallDynGlobal(0x439360);
}

void CCheat::GolfcartCheat() {
    plugin::CallDynGlobal(0x43A520);
}

void CCheat::HandleSpecialCheats(int CheatID) {
    plugin::CallDynGlobal<int>(0x439A10, CheatID);
}

void CCheat::HealthCheat() {
    plugin::CallDynGlobal(0x438D60);
}

void CCheat::HearseCheat() {
    plugin::CallDynGlobal(0x43A4F0);
}

void CCheat::JetpackCheat() {
    plugin::CallDynGlobal(0x439600);
}

void CCheat::LoveConquersAllCheat() {
    plugin::CallDynGlobal(0x4393F0);
}

void CCheat::LovefistCheat() {
    plugin::CallDynGlobal(0x43A500);
}

void CCheat::MayhemCheat() {
    plugin::CallDynGlobal(0x439B20);
}

void CCheat::MidnightCheat() {
    plugin::CallDynGlobal(0x439510);
}

void CCheat::MoneyArmourHealthCheat() {
    plugin::CallDynGlobal(0x438E40);
}

void CCheat::MonsterTruckCheat() {
    plugin::CallDynGlobal(0x43A680);
}

void CCheat::MuscleCheat() {
    plugin::CallDynGlobal(0x439150);
}

void CCheat::NinjaCheat() {
    plugin::CallDynGlobal(0x439E50);
}

void CCheat::NotWantedCheat() {
    plugin::CallDynGlobal(0x4396C0);
}

void CCheat::ParachuteCheat() {
    plugin::CallDynGlobal(0x4395B0);
}

void CCheat::PinkCarsCheat() {
    plugin::CallDynGlobal(0x4390D0);
}

void CCheat::PredatorCheat() {
    plugin::CallDynGlobal(0x4395A0);
}

void CCheat::QuadCheat() {
    plugin::CallDynGlobal(0x43A560);
}

void CCheat::RainyWeatherCheat() {
    plugin::CallDynGlobal(0x438F70);
}

void CCheat::RiotCheat() {
    plugin::CallDynGlobal(0x439710);
}

void CCheat::SandstormCheat() {
    plugin::CallDynGlobal(0x439590);
}

void CCheat::SkinnyCheat() {
    plugin::CallDynGlobal(0x439190);
}

void CCheat::SlowTimeCheat() {
    plugin::CallDynGlobal(0x438FC0);
}

void CCheat::StaminaCheat() {
    plugin::CallDynGlobal(0x439930);
}

void CCheat::StockCar2Cheat() {
    plugin::CallDynGlobal(0x43A4C0);
}

void CCheat::StockCar3Cheat() {
    plugin::CallDynGlobal(0x43A4D0);
}

void CCheat::StockCar4Cheat() {
    plugin::CallDynGlobal(0x43A4E0);
}

void CCheat::StockCarCheat() {
    plugin::CallDynGlobal(0x43A4B0);
}

void CCheat::StormCheat() {
    plugin::CallDynGlobal(0x439570);
}

void CCheat::StuntPlaneCheat() {
    plugin::CallDynGlobal(0x43A670);
}

void CCheat::SunnyWeatherCheat() {
    plugin::CallDynGlobal(0x438F40);
}

void CCheat::TankCheat() {
    plugin::CallDynGlobal(0x43A4A0);
}

void CCheat::TankerCheat() {
    plugin::CallDynGlobal(0x43A570);
}

void CCheat::TrashmasterCheat() {
    plugin::CallDynGlobal(0x43A510);
}

CVehicle* CCheat::VehicleCheat(int vehicleModelId) {
    return plugin::CallAndReturnDynGlobal<CVehicle*, int>(0x43A0B0, vehicleModelId);
}

void CCheat::VehicleSkillsCheat() {
    plugin::CallDynGlobal(0x4399D0);
}

void CCheat::VillagePeopleCheat() {
    plugin::CallDynGlobal(0x439DD0);
}

void CCheat::VortexCheat() {
    plugin::CallDynGlobal(0x43A540);
}

void CCheat::WantedCheat() {
    plugin::CallDynGlobal(0x4396F0);
}

void CCheat::WantedLevelDownCheat() {
    plugin::CallDynGlobal(0x438F20);
}

void CCheat::WantedLevelUpCheat() {
    plugin::CallDynGlobal(0x438E90);
}

void CCheat::WeaponCheat1() {
    plugin::CallDynGlobal(0x4385B0);
}

void CCheat::WeaponCheat2() {
    plugin::CallDynGlobal(0x438890);
}

void CCheat::WeaponCheat3() {
    plugin::CallDynGlobal(0x438B30);
}

void CCheat::WeaponSkillsCheat() {
    plugin::CallDynGlobal(0x439940);
}
void CCheat::SuicideCheat()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal(0x438FF0);
#else
    CPedDamageResponseCalculator damageCalculator(nullptr, 1000.0f, WEAPON_UNARMED, PED_PIECE_TORSO, 0);
    CEventDamage damageEvent(nullptr, CTimer::m_snTimeInMilliseconds, WEAPON_UNARMED, PED_PIECE_TORSO, 0, 0, 0);
    CPlayerPed* pPlayer = FindPlayerPed(-1);
    if (damageEvent.AffectsPed(pPlayer))
        damageCalculator.ComputeDamageResponse(pPlayer, &damageEvent.m_damageResponse, true);
    else
        damageEvent.m_damageResponse.m_bDamageCalculated = 1;
    pPlayer->GetEventGroup().Add(&damageEvent, 0);
#endif
}

bool CCheat::IsZoneStreamingAllowed()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x407410>();
#else
    return CCheat::m_aCheatsActive[CHEAT_ELVIS_IS_EVERYWHERE]
        || CCheat::m_aCheatsActive[CHEAT_PEDS_ATTACK_YOU_WITH_ROCKETS]
        || CCheat::m_aCheatsActive[CHEAT_BEACH_PARTY]
        || CCheat::m_aCheatsActive[CHEAT_GANGMEMBERS_EVERYWHERE]
        || CCheat::m_aCheatsActive[CHEAT_NINJA_THEME]
        || CCheat::m_aCheatsActive[CHEAT_SLUT_MAGNET]
        || CCheat::m_aCheatsActive[CHEAT_FUNHOUSE_THEME]
        || CCheat::m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC];
#endif
}
