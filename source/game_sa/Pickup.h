/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CompressedVector.h"
#include "Vector.h"

class CObject;
class CVehicle;
class CPlayerPed;

enum ePickupType : uint8 {
    PICKUP_NONE = 0,
    PICKUP_IN_SHOP = 1,
    PICKUP_ON_STREET = 2,
    PICKUP_ONCE = 3,
    PICKUP_ONCE_TIMEOUT = 4,
    PICKUP_ONCE_TIMEOUT_SLOW = 5,
    PICKUP_COLLECTABLE1 = 6,
    PICKUP_IN_SHOP_OUT_OF_STOCK = 7,
    PICKUP_MONEY = 8,
    PICKUP_MINE_INACTIVE = 9,
    PICKUP_MINE_ARMED = 10,
    PICKUP_NAUTICAL_MINE_INACTIVE = 11,
    PICKUP_NAUTICAL_MINE_ARMED = 12,
    PICKUP_FLOATINGPACKAGE = 13,
    PICKUP_FLOATINGPACKAGE_FLOATING = 14,
    PICKUP_ON_STREET_SLOW = 15,
    PICKUP_ASSET_REVENUE = 16,
    PICKUP_PROPERTY_LOCKED = 17,
    PICKUP_PROPERTY_FORSALE = 18,
    PICKUP_MONEY_DOESNTDISAPPEAR = 19,
    PICKUP_SNAPSHOT = 20,
    PICKUP_2P = 21,
    PICKUP_ONCE_FOR_MISSION = 22
};

enum ePickupPropertyText {
    PICKUP_PROPERTYTEXT_CANCEL = 0,   // "Cancel"
    PICKUP_PROPERTYTEXT_CANT_BUY = 1, // "You can't by..."
    PICKUP_PROPERTYTEXT_CAN_BUY = 2   // "Press TAB to buy ..."
};

class CPickup {
public:
    float            m_fRevenueValue;
    CObject*         m_pObject;
    uint32           m_nAmmo;
    uint32           m_nRegenerationTime;
    CompressedVector m_vecPos;
    uint16           m_nMoneyPerDay;
    int16            m_nModelIndex;
    int16            m_nReferenceIndex;
    ePickupType      m_nPickupType;
    struct {
        uint8 bDisabled : 1; // waiting for regeneration
        uint8 bEmpty : 1;    // no ammo
        uint8 bHelpMessageDisplayed : 1;
        uint8 bVisible : 1;
        uint8 nPropertyTextIndex : 3; // see enum ePickupPropertyText
    } m_nFlags;

public:
    static void InjectHooks();

    void SetPosn(float x, float y, float z);
    CVector GetPosn();
    float GetXCoord() { return m_vecPos.x / 8.0f; } // 0x4549F0
    float GetYCoord() { return m_vecPos.y / 8.0f; } // 0x454A10
    float GetZCoord() { return m_vecPos.z / 8.0f; } // 0x454A30
    void SetXCoord(float coord) { m_vecPos.x = static_cast<int16>(coord * 8.0f); }
    void SetYCoord(float coord) { m_vecPos.y = static_cast<int16>(coord * 8.0f); }
    void SetZCoord(float coord) { m_vecPos.z = static_cast<int16>(coord * 8.0f); }

    // Give player an ammo from weapon pickup
    void ExtractAmmoFromPickup(CPlayerPed* playerPed);
    // Is pickup visible (checks if distance between pickup and camera is shorter than 100 units)
    bool IsVisible();
    // Delete pickup's object (CObject)
    void GetRidOfObjects();
    bool PickUpShouldBeInvisible();
    void Remove();
    // Creates an object (CObject) for pickup. slotIndex - object to replace; use -1 to create a new object
    void GiveUsAPickUpObject(CObject** obj, int32 slotIndex);
    // Updates the pickup. Returns TRUE if pickup was removed/disabled
    void Update(CPlayerPed* player, CVehicle* vehicle, int32 playerId);
    // Checks if pickup collides with line (origin;target), removes pickup and creates an explosion. Used in previous GTA games for mine pickup
    void ProcessGunShot(CVector* origin, CVector* target);

    // message = GXT key
    static int32 FindTextIndexForString(char* message);
    static const char* FindStringForTextIndex(int32 index);
};

VALIDATE_SIZE(CPickup, 0x20);
