/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "extensions/enumerate.hpp"

#include "Garages.h"
#include "Pickups.h"
#include "tPickupMessage.h"
#include "Radar.h"
#include "TaskSimpleJetPack.h"

int32& CollectPickupBuffer = *(int32*)0x97D644;

void CPickups::InjectHooks() {
    RH_ScopedClass(CPickups);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x454A70);
    RH_ScopedInstall(ReInit, 0x456E60, { .reversed = false });
    RH_ScopedInstall(AddToCollectedPickupsArray, 0x455240, { .reversed = false });
    //RH_ScopedInstall(CreatePickupCoorsCloseToCoors, 0x458A80, { .reversed = false });
    RH_ScopedInstall(CreateSomeMoney, 0x458970, { .reversed = false });
    RH_ScopedInstall(DetonateMinesHitByGunShot, 0x4590C0, { .reversed = false });
    RH_ScopedInstall(DoCollectableEffects, 0x455E20, { .reversed = false });
    RH_ScopedInstall(DoMineEffects, 0x4560E0, { .reversed = false });
    RH_ScopedInstall(DoMoneyEffects, 0x454E80, { .reversed = false });
    RH_ScopedInstall(DoPickUpEffects, 0x455720, { .reversed = false });
    RH_ScopedInstall(FindPickUpForThisObject, 0x4551C0, { .reversed = false });
    RH_ScopedInstall(GenerateNewOne, 0x456F20, { .reversed = false });
    RH_ScopedInstall(GenerateNewOne_WeaponType, 0x457380, { .reversed = false });
    RH_ScopedInstall(GetActualPickupIndex, 0x4552A0, { .reversed = false });
    RH_ScopedInstall(GetNewUniquePickupIndex, 0x456A30, { .reversed = false });
    RH_ScopedInstall(GetUniquePickupIndex, 0x455280, { .reversed = false });
    RH_ScopedInstall(GivePlayerGoodiesWithPickUpMI, 0x4564F0);
    RH_ScopedInstall(IsPickUpPickedUp, 0x454B40);
    RH_ScopedInstall(ModelForWeapon, 0x454AC0);
    RH_ScopedInstall(PassTime, 0x455200);
    RH_ScopedInstall(PickedUpHorseShoe, 0x455390);
    RH_ScopedInstall(PickedUpOyster, 0x4552D0);
    RH_ScopedInstall(PictureTaken, 0x456A70, { .reversed = false });
    RH_ScopedInstall(PlayerCanPickUpThisWeaponTypeAtThisMoment, 0x4554C0);
    RH_ScopedInstall(RemoveMissionPickUps, 0x456DE0);
    RH_ScopedInstall(RemovePickUp, 0x4573D0);
    RH_ScopedInstall(RemovePickUpsInArea, 0x456D30, { .reversed = false });
    RH_ScopedInstall(RemovePickupObjects, 0x455470);
    RH_ScopedInstall(RemoveUnnecessaryPickups, 0x4563A0);
    RH_ScopedInstall(RenderPickUpText, 0x455000, { .reversed = false });
    RH_ScopedInstall(TestForPickupsInBubble, 0x456450);
    RH_ScopedInstall(TryToMerge_WeaponType, 0x4555A0, { .reversed = false });
    RH_ScopedInstall(Update, 0x458DE0, { .reversed = false });
    RH_ScopedInstall(UpdateMoneyPerDay, 0x455680, { .reversed = false });
    RH_ScopedInstall(WeaponForModel, 0x454AE0, { .reversed = false });
    RH_ScopedInstall(Load, 0x5D35A0, { .reversed = false });
    RH_ScopedInstall(Save, 0x5D3540, { .reversed = false });
}

// 0x454A70
void CPickups::Init() {
    NumMessages = 0;
    for (auto& pickup : aPickUps) {
        pickup.m_nPickupType = PICKUP_NONE;
        pickup.m_nReferenceIndex = 1;
        pickup.m_pObject = nullptr;
    }
    aPickUpsCollected.fill(0);
    CollectedPickUpIndex = 0;
    DisplayHelpMessage = 10;
}

// 0x456E60
void CPickups::ReInit() {
    plugin::Call<0x456E60>();
}

// 0x455240
void CPickups::AddToCollectedPickupsArray(int32 handle) {
    plugin::Call<0x455240, int32>(handle);
}

/*!
 * @addr 0x458A80
 * @brief Created a pickup close to pos (\r inX, \r inY, \r inZ)
 *
 * @param [out] outX, outY, outZ Created pickup's position
 */
void CPickups::CreatePickupCoorsCloseToCoors(float inX, float inY, float inZ, float* outX, float* outY, float* outZ) {
    plugin::Call<0x458A80, float, float, float, float*, float*, float*>(inX, inY, inZ, outX, outY, outZ);
}

// 0x458970
void CPickups::CreateSomeMoney(CVector coors, int32 amount) {
    plugin::Call<0x458970, CVector, int32>(coors, amount);
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

// returns pickup handle
// 0x456F20
int32 CPickups::GenerateNewOne(CVector coors, uint32 modelId, uint8 pickupType, uint32 ammo, uint32 moneyPerDay, bool isEmpty, char* message) {
    return plugin::CallAndReturn<int32, 0x456F20, CVector, uint32, uint8, uint32, uint32, bool, char*>(coors, modelId, pickupType, ammo, moneyPerDay, isEmpty, message);
}

/*!
 *
 * @param coors Position of new pickup
 * @param weaponType Weapon type
 * @param pickupType Pickup type
 * @param ammo
 * @param isEmpty
 * @param message
 * @return Pickup handle
 * @addr 0x457380
 */
int32 CPickups::GenerateNewOne_WeaponType(CVector coors, eWeaponType weaponType, uint8 pickupType, uint32 ammo, bool isEmpty, char* message) {
    return plugin::CallAndReturn<int32, 0x457380, CVector, eWeaponType, uint8, uint32, bool, char*>(coors, weaponType, pickupType, ammo, isEmpty, message);
}

/*!
 * @param pickupIndex Index of pickup
 * @return -1 if this index is not actual
 * @addr 0x4552A0
 */
int32 CPickups::GetActualPickupIndex(int32 pickupIndex) {
    return plugin::CallAndReturn<int32, 0x4552A0, int32>(pickupIndex);
}

// 0x456A30
int32 CPickups::GetNewUniquePickupIndex(int32 pickupIndex) {
    return plugin::CallAndReturn<int32, 0x456A30, int32>(pickupIndex);
}

// returns pickup handle
// 0x455280
int32 CPickups::GetUniquePickupIndex(int32 pickupIndex) {
    return plugin::CallAndReturn<int32, 0x455280, int32>(pickupIndex);
}

// returns TRUE if player got goodies
// 0x4564F0
bool CPickups::GivePlayerGoodiesWithPickUpMI(uint16 modelId, int32 playerId) {
    auto* ped = FindPlayerPed(playerId);

    if (modelId == ModelIndices::MI_PICKUP_ADRENALINE) {
        ped->m_pPlayerData->m_bAdrenaline = true;
        ped->m_pPlayerData->m_nAdrenalineEndTime = CTimer::GetTimeInMS() + 20'000;
        ped->ResetSprintEnergy();
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_ADRENALINE);
        return true;
    }

    if (modelId == ModelIndices::MI_PICKUP_BODYARMOUR) {
        ped->m_fArmour = (float)FindPlayerInfo(playerId).m_nMaxArmour;
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_BODY_ARMOUR);
        return true;
    }

    if (modelId == ModelIndices::MI_PICKUP_INFO) {
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_INFO);
        return true;
    }

    if (modelId == ModelIndices::MI_PICKUP_HEALTH) {
        auto maxHealth = FindPlayerInfo(playerId).m_nMaxHealth;
        CStats::UpdateStatsAddToHealth((uint32)((float)maxHealth - ped->m_fHealth));
        ped->m_fHealth = (float)maxHealth;
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_HEALTH);
        return true;
    }

    if (modelId == ModelIndices::MI_PICKUP_BONUS) {
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_INFO);
        return true;
    }

    if (modelId == ModelIndices::MI_PICKUP_BRIBE) {
        auto wantedLevel = std::max(0u, FindPlayerPed()->GetWantedLevel() - 1);
        FindPlayerPed(0)->SetWantedLevel(wantedLevel);
        CStats::IncrementStat(STAT_NUMBER_OF_POLICE_BRIBES, 1.0f);
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_INFO);
        return true;
    }

    if (modelId == ModelIndices::MI_PICKUP_KILLFRENZY) {
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_INFO);
        return true;
    }

    if (modelId == MODEL_JETPACK) {
        auto* task = new CTaskSimpleJetPack(nullptr, 10.0f, 0, nullptr);
        CEventScriptCommand event(3, task, 0);
        ped->GetEventGroup().Add(&event, false);
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_INFO);
        return true;
    }

    if (modelId == ModelIndices::MI_OYSTER) {
        PickedUpOyster();
        return true;
    }

    if (modelId == ModelIndices::MI_HORSESHOE) {
        PickedUpHorseShoe();
        return true;
    }

    return false;
}

/*!
 * @brief Check if pickup was picked up, and then mark it as not picked up.
 * @addr 0x454B40
 */
bool CPickups::IsPickUpPickedUp(int32 pickupHandle) {
    if (const auto it = rng::find(aPickUpsCollected, pickupHandle); it != aPickUpsCollected.end()) {
        *it = 0; // Reset
        return true;
    }
    return false;
}

/*!
 * @addr 0x454AC0
 * @returns The `nModelId1` of the given weapon type.
 */
int32 CPickups::ModelForWeapon(eWeaponType weaponType) {
    return CWeaponInfo::GetWeaponInfo(weaponType)->m_nModelId1;
}

/*!
 * @brief Update each pickup's (except if of type NONE or ASSET_REVENUE) `nRegenerationTime` field.
 * @addr 0x455200
 */
void CPickups::PassTime(uint32 time) {
    for (auto& pickup : aPickUps) {
        switch (pickup.m_nPickupType) {
        case PICKUP_NONE:
        case PICKUP_ASSET_REVENUE:
            continue;
        }

        if (pickup.m_nRegenerationTime <= time) {
            pickup.m_nRegenerationTime = 0;
        } else {
            pickup.m_nRegenerationTime -= time;
        }
    }
}

// 0x455390
void CPickups::PickedUpHorseShoe() {
    AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_COLLECTABLE1);

    CStats::IncrementStat(STAT_HORSESHOES_COLLECTED);
    CStats::IncrementStat(STAT_LUCK, 1000.f / CStats::GetStatValue(STAT_TOTAL_HORSESHOES)); // TODO: Is this some inlined stuff? (The division part)

    FindPlayerInfo(0).m_nMoney += 100;

    if (CStats::GetStatValue(STAT_TOTAL_HORSESHOES) == CStats::GetStatValue(STAT_HORSESHOES_COLLECTED)) { // Check if there's more to collect or not
        CGarages::TriggerMessage("HO_ALL");
        FindPlayerInfo(0).m_nMoney += 1000;
    } else {
        CGarages::TriggerMessage("HO_ONE", (int16)CStats::GetStatValue(STAT_TOTAL_HORSESHOES), 5000u, (int16)CStats::GetStatValue(STAT_HORSESHOES_COLLECTED));
    }
}

// 0x4552D0
void CPickups::PickedUpOyster() {
    AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_COLLECTABLE1);

    CStats::IncrementStat(STAT_OYSTERS_COLLECTED);

    FindPlayerInfo(0).m_nMoney += 100;

    if (CStats::GetStatValue(STAT_TOTAL_OYSTERS) == CStats::GetStatValue(STAT_OYSTERS_COLLECTED)) { // Check if there's more to collect or not
        CGarages::TriggerMessage("OY_ALL");
        FindPlayerInfo(0).m_nMoney += 100'000;
    } else {
        CGarages::TriggerMessage("OY_ONE", (int16)CStats::GetStatValue(STAT_TOTAL_OYSTERS), 5000u, (int16)CStats::GetStatValue(STAT_OYSTERS_COLLECTED));
    }
}

// 0x456A70
void CPickups::PictureTaken() {
    plugin::Call<0x456A70>();
}

// 0x4554C0
bool CPickups::PlayerCanPickUpThisWeaponTypeAtThisMoment(eWeaponType weaponType) {
    if (!CWeaponInfo::GetWeaponInfo(weaponType)->flags.bAimWithArm) {
        if (FindPlayerPed()->GetIntelligence()->GetTaskJetPack()) {
            return false;
        }
    }
    return true;
}

// 0x456DE0
void CPickups::RemoveMissionPickUps() {
    for (auto&& [i, pickup] : notsa::enumerate(aPickUps)) {
        switch (pickup.m_nPickupType) {
        case PICKUP_ONCE_FOR_MISSION: {
            CRadar::ClearBlipForEntity(BLIP_PICKUP, GetUniquePickupIndex(i));

            if (pickup.m_pObject) {
                pickup.GetRidOfObjects();
            }

            pickup.m_nFlags.bDisabled = true;
            pickup.m_nPickupType = PICKUP_NONE;
            break;
        }
        }
    }
}

// 0x4573D0
void CPickups::RemovePickUp(int32 pickupHandle) {
    if (const auto i = GetActualPickupIndex(pickupHandle); i != -1) {
        aPickUps[i].Remove();
    }
}

// 0x456D30
void CPickups::RemovePickUpsInArea(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
    CBoundingBox bb{ { minX, minY, minZ }, { maxX, maxY, maxZ } }; // They didn't use a bounding box, but it's nicer to do so.
    for (auto& pickup : aPickUps) {
        switch (pickup.m_nPickupType) {
        case PICKUP_NONE:
            continue;
        }

        if (bb.IsPointWithin(pickup.GetPosn())) {
            pickup.Remove();
        }
    }
}

// 0x455470
void CPickups::RemovePickupObjects() {
    for (auto& pickup : GetAllActivePickups()) {
        if (pickup.m_pObject) {
            pickup.GetRidOfObjects();
            pickup.m_nFlags.bVisible = false;
        }
    }
}

// remove pickups with types PICKUP_ONCE_TIMEOUT and PICKUP_MONEY in area
// 0x4563A0
void CPickups::RemoveUnnecessaryPickups(const CVector& posn, float radius) {
    for (auto& pickup : aPickUps) {
        switch (pickup.m_nPickupType) {
        case PICKUP_ONCE_TIMEOUT:
        case PICKUP_MONEY: {
            if (IsPointInSphere(pickup.GetPosn(), posn, radius)) {
                pickup.Remove();
            }
            break;
        }
        }
    }
}

// 0x455000
void CPickups::RenderPickUpText() {
    return plugin::Call<0x455000>();

    for (auto& message : std::span{ aMessages.data(), NumMessages }) {
        if (!message.price) {
            continue;
        }

        if (!message.text) {
            continue;
        }

        if (message.flags & 2) {
            CMessages::InsertNumberInString(message.text, 0, 0, 0, 0, 0, 0, gString);
        }

        sprintf(gString, "$%d", message.price);
        AsciiToGxtChar(gString, message.text);

        float scaleX, scaleY;

        const auto width = message.width / 30.0f;
        if (SCREEN_WIDTH_UNIT >= width)
            scaleX = width;
        else
            scaleX = SCREEN_WIDTH_UNIT;

        const auto height = message.height / 30.0f;
        if (SCREEN_WIDTH_UNIT >= height)
            scaleY = height;
        else
            scaleY = SCREEN_WIDTH_UNIT;

        CFont::SetProportional(true);
        CFont::SetBackground(false, false);
        CFont::SetScale(scaleX, scaleY);
        CFont::SetOrientation(eFontAlignment::ALIGN_CENTER);
        CFont::SetCentreSize(SCREEN_WIDTH);
        CFont::SetColor(message.color);
        CFont::SetFontStyle(eFontStyle::FONT_PRICEDOWN);
        CFont::PrintString(message.pos.x, message.pos.y, message.text);
    }
    NumMessages = 0;
}

// check for pickups in area
// 0x456450
bool CPickups::TestForPickupsInBubble(const CVector posn, float radius) {
    // NOTE: (Possible bug) - They dont check if the pickup is active (eg: type != NONE)
    return rng::any_of(aPickUps, [sp = CSphere{ posn, radius }](const CPickup& p) {
        return sp.IsPointWithin(p.GetPosn()); // They obviously didn't use `CSphere` here, but it's nicer.
    });
}

// search for pickup in area (radius = 5.5 units) with this weapon model and pickup type and add ammo to this pickup; returns TRUE if merged
// 0x4555A0
bool CPickups::TryToMerge_WeaponType(CVector posn, eWeaponType weaponType, uint8 pickupType, uint32 ammo, bool arg4) {
    UNUSED(arg4);
    return plugin::CallAndReturn<bool, 0x4555A0, CVector, eWeaponType, uint8, uint32, bool>(posn, weaponType, pickupType, ammo, arg4);
}

// 0x458DE0
void CPickups::Update() {
    plugin::Call<0x458DE0>();
}

// 0x455680
void CPickups::UpdateMoneyPerDay(int32 pickupHandle, uint16 money) {
    plugin::Call<0x455680, int32, uint16>(pickupHandle, money);
}

// 0x454AE0
eWeaponType CPickups::WeaponForModel(int32 modelId) {
    return plugin::CallAndReturn<eWeaponType, 0x454AE0, int32>(modelId);
}

// 0x5D35A0
bool CPickups::Load() {
    return plugin::CallAndReturn<bool, 0x5D35A0>();
}
// 0x5D3540
bool CPickups::Save() {
    return plugin::CallAndReturn<bool, 0x5D3540>();
}

/*!
 * @brief Our custom Vector based overload
 * @copydocs CPickups::CreatePickupCoorsCloseToCoors
 */
void CPickups::CreatePickupCoorsCloseToCoors(const CVector& pos, CVector& createdAtPos) {
    return CreatePickupCoorsCloseToCoors(pos.x, pos.y, pos.z, &createdAtPos.x, &createdAtPos.y, &createdAtPos.z);
}

/*!
 * @brief Our custom Vector based overload
 * @copydocs CPickups::CreatePickupCoorsCloseToCoors
 */
void CPickups::CreatePickupCoorsCloseToCoors(const CVector& pos, float& outX, float& outY, float& outZ) {
    return CreatePickupCoorsCloseToCoors(pos.x, pos.y, pos.z, &outX, &outY, &outZ);
}

// 0x454B70
void ModifyStringLabelForControlSetting(char* stringLabel) {
    plugin::Call<0x454B70, char*>(stringLabel);
}
