/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CPickup.h"
#include "tPickupMessage.h"
#include "eWeaponType.h"

class CEntity;

extern unsigned int MAX_COLLECTED_PICKUPS; // 20
extern unsigned int MAX_PICKUP_MESSAGES; // 16
extern unsigned int MAX_NUM_PICKUPS; // 620

class CPickups {
public:
    static unsigned char &DisplayHelpMessage;
    static int &PlayerOnWeaponPickup;
    static int &StaticCamStartTime;
    static CVector *StaticCamCoors;
    static CVehicle *&pPlayerVehicle;
    static bool &bPickUpcamActivated;
    static unsigned short &CollectedPickUpIndex;
    static int *aPickUpsCollected;               // static int aPickUpsCollected[20];
    static unsigned short &NumMessages;
    static tPickupMessage *aMessages;            // static tPickupMessage aMessages[16]
    static CPickup *aPickUps;                    // static CPickup aPickUps[620]

    static void AddToCollectedPickupsArray(int handle);
    static void CreatePickupCoorsCloseToCoors(float in_x, float in_y, float in_z, float* out_x, float* out_y, float* out_z);
    static void CreateSomeMoney(CVector coors, int amount);
    static void DetonateMinesHitByGunShot(CVector* shotOrigin, CVector* shotTarget);
    static void DoCollectableEffects(CEntity* entity);
    static void DoMineEffects(CEntity* entity);
    static void DoMoneyEffects(CEntity* entity);
    static void DoPickUpEffects(CEntity* entity);
    static CPickup* FindPickUpForThisObject(CObject* object);
    // returns pickup handle
    static int GenerateNewOne(CVector coors, unsigned int modelId, unsigned char pickupType, unsigned int ammo, unsigned int moneyPerDay, bool isEmpty, char* message);
    // returns pickup handle
    static int GenerateNewOne_WeaponType(CVector coors, eWeaponType weaponType, unsigned char pickupType, unsigned int ammo, bool isEmpty, char* message);
    // returns -1 if this index is not actual
    static int GetActualPickupIndex(int pickupIndex);
    static int GetNewUniquePickupIndex(int pickupIndex);
    // returns pickup handle
    static int GetUniquePickupIndex(int pickupIndex);
    // returns TRUE if player got goodies
    static bool GivePlayerGoodiesWithPickUpMI(unsigned short modelId, int playerId);
    static void Init();
    static bool IsPickUpPickedUp(int pickupHandle);
    // load pickups from save file; always return TRUE
    static bool Load();
    // returns model id
    static int ModelForWeapon(eWeaponType weaponType);
    static void PassTime(unsigned int time);
    static void PickedUpHorseShoe();
    static void PickedUpOyster();
    static void PictureTaken();
    static bool PlayerCanPickUpThisWeaponTypeAtThisMoment(eWeaponType weaponType);
    static void ReInit();
    static void RemoveMissionPickUps();
    static void RemovePickUp(int pickupHandle);
    static void RemovePickUpsInArea(float cornerA_x, float cornerA_y, float cornerA_z, float cornerB_x, float cornerB_y, float cornerB_z);
    static void RemovePickupObjects();
    // remove pickups with types PICKUP_ONCE_TIMEOUT and PICKUP_MONEY in area
    static void RemoveUnnecessaryPickups(CVector const& posn, float radius);
    static void RenderPickUpText();
    // save pickups to save file; always return TRUE
    static bool Save();
    // check for pickups in area
    static bool TestForPickupsInBubble(CVector posn, float radius);
    // search for pickup in area (radius = 5.5 units) with this weapon model and pickup type and add ammo to this pickup; returns TRUE if merged
    static bool TryToMerge_WeaponType(CVector posn, eWeaponType weaponType, unsigned char pickupType, unsigned int ammo, bool _IGNORED_ arg4);
    static void Update();
    static void UpdateMoneyPerDay(int pickupHandle, unsigned short money);
    // returns weapon type (see eWeaponType)
    static int WeaponForModel(int modelId);
};

extern int &CollectPickupBuffer;

void ModifyStringLabelForControlSetting(char* stringLabel);