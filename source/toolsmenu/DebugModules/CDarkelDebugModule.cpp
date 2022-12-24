#include "StdInc.h"

#include <unordered_map>
#include "CDarkelDebugModule.h"
#include "imgui.h"
#include "Timer.h"

using namespace ImGui;

constexpr const char* WEAPON_TYPE_STRING[] = {
    "UNARMED", "BRASSKNUCKLE", "GOLFCLUB", "NIGHTSTICK", "KNIFE", "BASEBALLBAT", "SHOVEL", "POOL_CUE", "KATANA", "CHAINSAW", "DILDO1", "DILDO2", "VIBE1", "VIBE2", "FLOWERS", "CANE", "GRENADE",
    "TEARGAS", "MOLOTOV", "ROCKET", "ROCKET_HS", "FREEFALL_BOMB", "PISTOL", "PISTOL_SILENCED", "DESERT_EAGLE", "SHOTGUN", "SAWNOFF_SHOTGUN", "SPAS12_SHOTGUN", "MICRO_UZI", "MP5", "AK47", "M4",
    "TEC9", "COUNTRYRIFLE", "SNIPERRIFLE", "RLAUNCHER", "RLAUNCHER_HS", "FLAMETHROWER", "MINIGUN", "REMOTE_SATCHEL_CHARGE", "DETONATOR", "SPRAYCAN", "EXTINGUISHER", "CAMERA", "NIGHTVISION",
    "INFRARED", "PARACHUTE", "LAST_WEAPON", "ARMOUR", "RAMMEDBYCAR", "RUNOVERBYCAR", "EXPLOSION", "UZI_DRIVEBY", "DROWNING", "FALL", "UNIDENTIFIED", "ANYMELEE", "ANYWEAPON", "FLARE" "UNARMED",
    "BRASSKNUCKLE", "GOLFCLUB", "NIGHTSTICK", "KNIFE", "BASEBALLBAT", "SHOVEL", "POOL_CUE", "KATANA", "CHAINSAW", "DILDO1", "DILDO2", "VIBE1", "VIBE2", "FLOWERS", "CANE", "GRENADE", "TEARGAS",
    "MOLOTOV", "ROCKET", "ROCKET_HS", "FREEFALL_BOMB", "PISTOL", "PISTOL_SILENCED", "DESERT_EAGLE", "SHOTGUN", "SAWNOFF_SHOTGUN", "SPAS12_SHOTGUN", "MICRO_UZI", "MP5", "AK47", "M4", "TEC9",
    "COUNTRYRIFLE", "SNIPERRIFLE", "RLAUNCHER", "RLAUNCHER_HS", "FLAMETHROWER", "MINIGUN", "REMOTE_SATCHEL_CHARGE", "DETONATOR", "SPRAYCAN", "EXTINGUISHER", "CAMERA", "NIGHTVISION", "INFRARED",
    "PARACHUTE", "LAST_WEAPON", "ARMOUR", "RAMMEDBYCAR", "RUNOVERBYCAR", "EXPLOSION", "UZI_DRIVEBY", "DROWNING", "FALL", "UNIDENTIFIED", "ANYMELEE", "ANYWEAPON", "FLARE"
};

void DumpCDarkel() {
    Text(
         "pStartMessage                 = '%s'\n"
         "AmmoInterruptedWeapon         = %u\n"
         "InterruptedWeaponType         = %s\n"
         "InterruptedWeaponTypeSelected = %s\n"
         "TimeOfFrenzyStart             = %u\n"
         "PreviousTime                  = %d\n"
         "TimeLimit                     = %d\n"
         "KillsNeeded                   = %d\n"
         "ModelToKill                   = { %d, %d, %d, %d }\n"
         "WeaponType                    = %s\n"
         "Status                        = %d\n"
         "bHeadShotRequired             = %d\n"
         "bStandardSoundAndMessages     = %d\n"
         "bProperKillFrenzy             = %d",
         CDarkel::pStartMessage ? CDarkel::pStartMessage : "<nullptr>", CDarkel::AmmoInterruptedWeapon, WEAPON_TYPE_STRING[CDarkel::InterruptedWeaponType],
         WEAPON_TYPE_STRING[CDarkel::InterruptedWeaponTypeSelected], CDarkel::TimeOfFrenzyStart, CDarkel::PreviousTime, CDarkel::TimeLimit, CDarkel::KillsNeeded,
         CDarkel::ModelToKill[0], CDarkel::ModelToKill[1], CDarkel::ModelToKill[2], CDarkel::ModelToKill[3], WEAPON_TYPE_STRING[CDarkel::WeaponType], CDarkel::Status,
         CDarkel::bHeadShotRequired, CDarkel::bStandardSoundAndMessages, CDarkel::bProperKillFrenzy
    );
}

DarkelDebugModule::DarkelDebugModule() :
    DebugModuleSingleWindow{ "Darkel Debug", {860.f, 290.f} }
{
}

void DarkelDebugModule::RenderMainWindow() {
    BeginGroup();
    DumpCDarkel();
    Separator();

    static int weaponType{30}, timeLimit{120}, killsNeeded{10}, modelsToKill[4]{-1, -1, -1, -1};
    static bool standardSoundAndMsg{true}, hsRequired{false};

    PushItemWidth(30.0f);
    InputInt("Weapon type", &weaponType, 0);
    SameLine(); InputInt("Time limit (in seconds)", &timeLimit, 0);
    SameLine(); InputInt("Kills needed", &killsNeeded, 0);
    PopItemWidth();

    PushItemWidth(120.0f);
    InputInt4("Models to kill (-1/-2/-3: for any ped/vehicle/bike)", modelsToKill, 0);
    PopItemWidth();

    SameLine(); Checkbox("Standard sound and msg", &standardSoundAndMsg);
    SameLine(); Checkbox("Headshot required", &hsRequired);

    if (Button("Start Frenzy")) {
        CDarkel::StartFrenzy(
            (eWeaponType)weaponType,
            timeLimit * 1000,
            killsNeeded,
            modelsToKill[0],
            TheText.Get("PAGE_00"),
            modelsToKill[1],
            modelsToKill[2],
            modelsToKill[3],
            standardSoundAndMsg,
            hsRequired
        );
    }

    EndGroup();
}

void DarkelDebugModule::RenderMenuEntry() {
    if (ImGui::BeginMenu("Extra")) {
        if (ImGui::MenuItem("Darkel")) {
            SetMainWindowOpen(true);
        }
        ImGui::EndMenu();
    }
}
