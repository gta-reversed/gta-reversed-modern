/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CompressedVector.h"
#include "CVector.h"

enum ePickupType {
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

class CObject;
class CVehicle;
class CPlayerPed;

class CPickup {
public:
    float             m_fRevenueValue;
    CObject          *m_pObject;
    unsigned int      m_nAmmo;
    unsigned int      m_nRegenerationTime;
    CompressedVector  m_vecPos;
    unsigned short    m_nMoneyPerDay;
    short             m_nModelIndex;
    short             m_nReferenceIndex;
    unsigned char     m_nPickupType; // see ePickupType
    struct {
        unsigned char   bDisabled : 1; // waiting for regeneration
        unsigned char   bEmpty : 1; // no ammo
        unsigned char   bHelpMessageDisplayed : 1;
        unsigned char   bVisible : 1;
        unsigned char   nPropertyTextIndex : 3; // see enum ePickupPropertyText
    }                 m_nFlags;
private:
    char _pad1E[2];
public:

    void SetPosn(float coord_x, float coord_y, float coord_z);
    // get pickup position
    CVector GetPosn();
    // get pickup x coord
    float GetXCoord();
    // get pickup y coord
    float GetYCoord();
    // get pickup z coord
    float GetZCoord();
    // set pickup x coord
    inline void SetXCoord(float coord) { m_vecPos.x = static_cast<short>(coord * 8.0f); }
    // set pickup y coord
    inline void SetYCoord(float coord) { m_vecPos.y = static_cast<short>(coord * 8.0f); }
    // set pickup z coord
    inline void SetZCoord(float coord) { m_vecPos.z = static_cast<short>(coord * 8.0f); }
    // give player an ammo from weapon pickup
    void ExtractAmmoFromPickup(CPlayerPed* playerPed);
    // is pickup visible (checks if distance between pickup and camera is shorter than 100 units)
    bool IsVisible();
    // delete pickup's object (CObject)
    void GetRidOfObjects();
    bool PickUpShouldBeInvisible();
    // remove pickup
    void Remove();
    // creates an object (CObject) for pickup. objectPoolSlotIndex - object to replace; use -1 to create a new object
    void GiveUsAPickUpObject(CObject** pObject, int objectPoolSlotIndex);
    // updates the pickup. Returns TRUE if pickup was removed/disabled
    void Update(CPlayerPed* playerPed, CVehicle* vehicle, int playerId);
    // checks if pickup collides with line (origin;target), removes pickup and creates an explosion. Used in previous GTA games for mine pickup
    void ProcessGunShot(CVector* origin, CVector* target);

    // message = GXT key
    static void FindTextIndexForString(char* message);
    static char const *FindStringForTextIndex(int index);
};

VALIDATE_SIZE(CPickup, 0x20);