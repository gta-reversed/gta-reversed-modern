/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

unsigned int MAX_COLLECTED_PICKUPS = 20;
unsigned int MAX_PICKUP_MESSAGES = 16;
unsigned int MAX_NUM_PICKUPS = 620;

unsigned char& CPickups::DisplayHelpMessage = *(unsigned char*)0x8A5F48;
int& CPickups::PlayerOnWeaponPickup = *(int*)0x97D640;
int& CPickups::StaticCamStartTime = *(int*)0x978618;
CVector* CPickups::StaticCamCoors = (CVector*)0x97D660;
CVehicle*& CPickups::pPlayerVehicle = *(CVehicle * *)0x97861C;
bool& CPickups::bPickUpcamActivated = *(bool*)0x978620;
unsigned short& CPickups::CollectedPickUpIndex = *(unsigned short*)0x978624;
int* CPickups::aPickUpsCollected = (int*)0x978628;
unsigned short& CPickups::NumMessages = *(unsigned short*)0x978678;
tPickupMessage* CPickups::aMessages = (tPickupMessage*)0x978680;
CPickup* CPickups::aPickUps = (CPickup*)0x9788C0;
int& CollectPickupBuffer = *(int*)0x97D644;

// 0x455240
void CPickups::AddToCollectedPickupsArray(int handle) {
    plugin::Call<0x455240, int>(handle);
}

// 0x458A80
void CPickups::CreatePickupCoorsCloseToCoors(float in_x, float in_y, float in_z, float* out_x, float* out_y, float* out_z) {
    plugin::Call<0x458A80, float, float, float, float*, float*, float*>(in_x, in_y, in_z, out_x, out_y, out_z);
}

// 0x458970
void CPickups::CreateSomeMoney(CVector coors, int amount) {
    plugin::Call<0x458970, CVector, int>(coors, amount);
}

// 0x4590C0
void CPickups::DetonateMinesHitByGunShot(CVector* shotOrigin, CVector* shotTarget) {
    plugin::Call<0x4590C0, CVector*, CVector*>(shotOrigin, shotTarget);
}

// 0x455E20
void CPickups::DoCollectableEffects(CEntity* entity) {
    plugin::Call<0x455E20, CEntity*>(entity);
}

// 0x4560E0
void CPickups::DoMineEffects(CEntity* entity) {
    plugin::Call<0x4560E0, CEntity*>(entity);
}

// 0x454E80
void CPickups::DoMoneyEffects(CEntity* entity) {
    plugin::Call<0x454E80, CEntity*>(entity);
}

// 0x455720
void CPickups::DoPickUpEffects(CEntity* entity) {
    plugin::Call<0x455720, CEntity*>(entity);
}

// 0x4551C0
CPickup* CPickups::FindPickUpForThisObject(CObject* object) {
    return plugin::CallAndReturn<CPickup*, 0x4551C0, CObject*>(object);
}

// 0x456F20
int CPickups::GenerateNewOne(CVector coors, unsigned int modelId, unsigned char pickupType, unsigned int ammo, unsigned int moneyPerDay, bool isEmpty, char* message) {
    return plugin::CallAndReturn<int, 0x456F20, CVector, unsigned int, unsigned char, unsigned int, unsigned int, bool, char*>(coors, modelId, pickupType, ammo, moneyPerDay, isEmpty, message);
}

// 0x457380
int CPickups::GenerateNewOne_WeaponType(CVector coors, eWeaponType weaponType, unsigned char pickupType, unsigned int ammo, bool isEmpty, char* message) {
    return plugin::CallAndReturn<int, 0x457380, CVector, eWeaponType, unsigned char, unsigned int, bool, char*>(coors, weaponType, pickupType, ammo, isEmpty, message);
}

// 0x4552A0
int CPickups::GetActualPickupIndex(int pickupIndex) {
    return plugin::CallAndReturn<int, 0x4552A0, int>(pickupIndex);
}

// 0x456A30
int CPickups::GetNewUniquePickupIndex(int pickupIndex) {
    return plugin::CallAndReturn<int, 0x456A30, int>(pickupIndex);
}

// 0x455280
int CPickups::GetUniquePickupIndex(int pickupIndex) {
    return plugin::CallAndReturn<int, 0x455280, int>(pickupIndex);
}

// 0x4564F0
bool CPickups::GivePlayerGoodiesWithPickUpMI(unsigned short modelId, int playerId) {
    return plugin::CallAndReturn<bool, 0x4564F0, unsigned short, int>(modelId, playerId);
}

// 0x454A70
void CPickups::Init() {
    plugin::Call<0x454A70>();
}

// 0x454B40
bool CPickups::IsPickUpPickedUp(int pickupHandle) {
    return plugin::CallAndReturn<bool, 0x454B40, int>(pickupHandle);
}

// 0x5D35A0
bool CPickups::Load() {
    return plugin::CallAndReturn<bool, 0x5D35A0>();
}

// 0x454AC0
int CPickups::ModelForWeapon(eWeaponType weaponType) {
    return plugin::CallAndReturn<int, 0x454AC0, eWeaponType>(weaponType);
}

// 0x455200
void CPickups::PassTime(unsigned int time) {
    plugin::Call<0x455200, unsigned int>(time);
}

// 0x455390
void CPickups::PickedUpHorseShoe() {
    plugin::Call<0x455390>();
}

// 0x4552D0
void CPickups::PickedUpOyster() {
    plugin::Call<0x4552D0>();
}

// 0x456A70
void CPickups::PictureTaken() {
    plugin::Call<0x456A70>();
}

// 0x4554C0
bool CPickups::PlayerCanPickUpThisWeaponTypeAtThisMoment(eWeaponType weaponType) {
    return plugin::CallAndReturn<bool, 0x4554C0, eWeaponType>(weaponType);
}

// 0x456E60
void CPickups::ReInit() {
    plugin::Call<0x456E60>();
}

// 0x456DE0
void CPickups::RemoveMissionPickUps() {
    plugin::Call<0x456DE0>();
}

// 0x4573D0
void CPickups::RemovePickUp(int pickupHandle) {
    plugin::Call<0x4573D0, int>(pickupHandle);
}

// 0x456D30
void CPickups::RemovePickUpsInArea(float cornerA_x, float cornerA_y, float cornerA_z, float cornerB_x, float cornerB_y, float cornerB_z) {
    plugin::Call<0x456D30, float, float, float, float, float, float>(cornerA_x, cornerA_y, cornerA_z, cornerB_x, cornerB_y, cornerB_z);
}

// 0x455470
void CPickups::RemovePickupObjects() {
    plugin::Call<0x455470>();
}

// 0x4563A0
void CPickups::RemoveUnnecessaryPickups(CVector const& posn, float radius) {
    plugin::Call<0x4563A0, CVector const&, float>(posn, radius);
}

// 0x455000
void CPickups::RenderPickUpText() {
    plugin::Call<0x455000>();
}

// 0x5D3540
bool CPickups::Save() {
    return plugin::CallAndReturn<bool, 0x5D3540>();
}

// 0x456450
bool CPickups::TestForPickupsInBubble(CVector posn, float radius) {
    return plugin::CallAndReturn<bool, 0x456450, CVector, float>(posn, radius);
}

// 0x4555A0
bool CPickups::TryToMerge_WeaponType(CVector posn, eWeaponType weaponType, unsigned char pickupType, unsigned int ammo, bool _IGNORED_ arg4) {
    return plugin::CallAndReturn<bool, 0x4555A0, CVector, eWeaponType, unsigned char, unsigned int, bool>(posn, weaponType, pickupType, ammo, arg4);
}

// 0x458DE0
void CPickups::Update() {
    plugin::Call<0x458DE0>();
}

// 0x455680
void CPickups::UpdateMoneyPerDay(int pickupHandle, unsigned short money) {
    plugin::Call<0x455680, int, unsigned short>(pickupHandle, money);
}

// 0x454AE0
int CPickups::WeaponForModel(int modelId) {
    return plugin::CallAndReturn<int, 0x454AE0, int>(modelId);
}

// 0x454B70
void ModifyStringLabelForControlSetting(char* stringLabel) {
    plugin::Call<0x454B70, char*>(stringLabel);
}