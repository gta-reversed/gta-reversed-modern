/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eWeaponType.h"
#include <array>

class CEntity;
class CPickup;

struct tPickupMessage;

constexpr uint32 MAX_COLLECTED_PICKUPS = 20;
constexpr uint32 MAX_PICKUP_MESSAGES = 16;
constexpr uint32 MAX_NUM_PICKUPS = 620;

// Dump @ 0x8A5F50
constexpr uint16 AmmoForWeapon_OnStreet[NUM_WEAPONS]{ 0u, 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u, 8u, 8u, 8u, 8u, 4u, 4u, 30u, 10u, 10u, 15u, 10u, 10u, 60u, 60u, 80u, 80u, 60u, 20u, 10u, 4u, 3u, 100u, 500u, 5u, 1u, 500u, 500u, 36u, 0u, 0u, 1u, 0u};

class CPickups {
public:
    static inline uint8& DisplayHelpMessage = *(uint8*)0x8A5F48;
    static inline int32& PlayerOnWeaponPickup = *(int32*)0x97D640;
    static inline int32& StaticCamStartTime = *(int32*)0x978618;
    static inline CVector* StaticCamCoors = (CVector*)0x97D660;
    static inline CVehicle*& pPlayerVehicle = *(CVehicle**)0x97861C;
    static inline bool& bPickUpcamActivated = *(bool*)0x978620;
    static inline uint16& CollectedPickUpIndex = *(uint16*)0x978624;
    static inline std::array<int32, MAX_COLLECTED_PICKUPS>& aPickUpsCollected = *(std::array<int32, MAX_COLLECTED_PICKUPS>*)0x978628;
    static inline uint16& NumMessages = *(uint16*)0x978678;
    static inline std::array<tPickupMessage, MAX_PICKUP_MESSAGES>& aMessages = *(std::array<tPickupMessage, MAX_PICKUP_MESSAGES>*)0x978680;
    static inline std::array<CPickup, MAX_NUM_PICKUPS>& aPickUps = *(std::array<CPickup, MAX_NUM_PICKUPS>*)0x9788C0;

public:
    static void InjectHooks();

    static void Init();
    static void ReInit();

    static void AddToCollectedPickupsArray(int32 handle);
    static void CreatePickupCoorsCloseToCoors(float in_x, float in_y, float in_z, float* out_x, float* out_y, float* out_z);
    static void CreateSomeMoney(CVector coors, int32 amount);
    static void DetonateMinesHitByGunShot(CVector* shotOrigin, CVector* shotTarget);

    static void DoCollectableEffects(CEntity* entity);
    static void DoMineEffects(CEntity* entity);
    static void DoMoneyEffects(CEntity* entity);
    static void DoPickUpEffects(CEntity* entity);

    static CPickup* FindPickUpForThisObject(CObject* object);
    // returns pickup handle
    static int32 GenerateNewOne(CVector coors, uint32 modelId, uint8 pickupType, uint32 ammo, uint32 moneyPerDay, bool isEmpty, char* message);
    // returns pickup handle
    static int32 GenerateNewOne_WeaponType(CVector coors, eWeaponType weaponType, uint8 pickupType, uint32 ammo, bool isEmpty, char* message);
    // returns -1 if this index is not actual
    static int32 GetActualPickupIndex(int32 pickupIndex);
    static int32 GetNewUniquePickupIndex(int32 pickupIndex);
    // returns pickup handle
    static int32 GetUniquePickupIndex(int32 pickupIndex);
    // returns TRUE if player got goodies
    static bool GivePlayerGoodiesWithPickUpMI(uint16 modelId, int32 playerId);
    static bool IsPickUpPickedUp(int32 pickupHandle);
    // returns model id
    static int32 ModelForWeapon(eWeaponType weaponType);
    static void PassTime(uint32 time);
    static void PickedUpHorseShoe();
    static void PickedUpOyster();
    static void PictureTaken();
    static bool PlayerCanPickUpThisWeaponTypeAtThisMoment(eWeaponType weaponType);
    static void RemoveMissionPickUps();
    static void RemovePickUp(int32 pickupHandle);
    static void RemovePickUpsInArea(float cornerA_x, float cornerA_y, float cornerA_z, float cornerB_x, float cornerB_y, float cornerB_z);
    static void RemovePickupObjects();
    // remove pickups with types PICKUP_ONCE_TIMEOUT and PICKUP_MONEY in area
    static void RemoveUnnecessaryPickups(const CVector& posn, float radius);
    static void RenderPickUpText();
    // check for pickups in area
    static bool TestForPickupsInBubble(CVector posn, float radius);
    // search for pickup in area (radius = 5.5 units) with this weapon model and pickup type and add ammo to this pickup; returns TRUE if merged
    static bool TryToMerge_WeaponType(CVector posn, eWeaponType weaponType, uint8 pickupType, uint32 ammo, bool _IGNORED_ arg4);
    static void Update();
    static void UpdateMoneyPerDay(int32 pickupHandle, uint16 money);
    // returns weapon type (see eWeaponType)
    static int32 WeaponForModel(int32 modelId);
    static bool Load();
    static bool Save();

    // Helpers NOTSA
    static void CreatePickupCoorsCloseToCoors(const CVector& pos, CVector& createdAtPos);
    static void CreatePickupCoorsCloseToCoors(const CVector& pos, float& out_x, float& out_y, float& out_z);
    static auto GetAllActivePickups() { return aPickUps | std::views::filter([](auto&& p) { return p.m_nPickupType != PICKUP_NONE; }); }
};

extern int32 &CollectPickupBuffer;

void ModifyStringLabelForControlSetting(char* stringLabel);
