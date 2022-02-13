/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eWeaponType.h"

class CEntity;
class CPickup;

struct tPickupMessage;

constexpr uint32 MAX_COLLECTED_PICKUPS = 20;
constexpr uint32 MAX_PICKUP_MESSAGES = 16;
constexpr uint32 MAX_NUM_PICKUPS = 620;

class CPickups {
public:
    static uint8&         DisplayHelpMessage;
    static int32&         PlayerOnWeaponPickup;
    static int32&         StaticCamStartTime;
    static CVector*       StaticCamCoors;
    static CVehicle*&     pPlayerVehicle;
    static bool&          bPickUpcamActivated;
    static uint16&        CollectedPickUpIndex;
    static int32          (&aPickUpsCollected)[MAX_COLLECTED_PICKUPS];
    static uint16&        NumMessages;
    static tPickupMessage (&aMessages)[MAX_PICKUP_MESSAGES];
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
};

extern int32 &CollectPickupBuffer;

void ModifyStringLabelForControlSetting(char* stringLabel);
