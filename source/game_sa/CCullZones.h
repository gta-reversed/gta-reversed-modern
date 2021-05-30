#pragma once
#include "CVector.h"

// https://gtamods.com/wiki/CULL

enum eZoneAttributes : uint16_t {
    NONE = 0x0,

    // Camera close in into player using closest third-person view camera mode,
    // does not close in if in first person or cinematic mode,
    // camera mode cannot be changed while in the zone
    CAM_CLOSE_IN_FOR_PLAYER = 0x1,

    // Camera remotely placed outside the zone, no control of camera,
    // camera mode cannot be changed while in the zone
    CAM_STAIRS_FOR_PLAYER = 0x2,

    // Lowers the camera angle on boats
    CAM_1ST_PERSONS_FOR_PLAYER = 0x4,

    // Rain-free, police helicopter-free zone
    CAM_NO_RAIN = 0x8,

    // Police will not exit their vehicles voluntarily.
    // They will only exit if you do something to them (like shoot it).
    // Cops both on foot and in vehicles will not chase you but can shoot at you.
    NO_POLICE = 0x10,

    DO_I_NEED_TO_LOAD_COLLISION = 0x40,

    UNKNOWN_1 = 0x80,

    // Police will always exit their vehicles
    // once they are spawned ONLY IF you have a wanted level.
    // If you don't, they'll drive normally.
    POLICES_ABANDON_CARS = 0x100,

    IN_ROOMS_FOR_AUDIO = 0x200,

    // Some visual ocean water effects are removed
    // like the transparent waves and sparkles on the water.
    IN_ROOMS_FEWER_PEDS = 0x400,

    UNKNOWN_2 = 0x800,

    // 5-Star Military zone.
    MILITARY_ZONE = 0x1000,

    // Doesn't allow cars to reach top speed.
    EXTRA_AIR_RESISTANCE = 0x4000,

    // Spawn fewer cars in this area.
    FEWER_CARS = 0x8000,
};

struct CZoneDef {
    short x;
    short y;
    short field_4;
    short widthY;
    short widthX;
    short field_A;
    short bottomZ;
    short topZ;

    // 0x72D850
    bool IsPointWithin(const CVector& point) const {
        if (bottomZ >= point.z || topZ <= point.z)
            return false;

        float x1 = point.x - x;
        float y1 = point.y - y;
        float sum = field_4 * x1 + widthY * y1;
        if (sum >= 0.0f && sum <= (widthY * widthY + field_4 * field_4)) {
            float v6 = widthX * x1 + field_A * y1;
            if (v6 >= 0.0f && v6 <= (field_A * field_A + widthX * widthX)) {
                return true;
            }
        }

        return false;
    }
};

VALIDATE_SIZE(CZoneDef, 0x10);

struct CCullZoneReflection {
    CZoneDef zoneDef;
    int cm;
    char vx;
    char vy;
    char vz;
    char flags;

    bool IsPointWithin(const CVector& point) { return zoneDef.IsPointWithin(point); };
};

VALIDATE_SIZE(CCullZoneReflection, 0x18);

struct CCullZone {
    CZoneDef zoneDef;
    eZoneAttributes flags;

    bool IsPointWithin(const CVector& point) { return zoneDef.IsPointWithin(point); };
};

VALIDATE_SIZE(CCullZone, 0x12);

class CCullZones {
public:
    static CCullZoneReflection (&aMirrorAttributeZones)[72];
    static CCullZone (&aTunnelAttributeZones)[40];
    static CCullZone (&aAttributeZones)[1300];
    static int& CurrentFlags_Player;
    static int& CurrentFlags_Camera;
    static int& NumTunnelAttributeZones;
    static int& NumMirrorAttributeZones;
    static int& NumAttributeZones;
    static bool& bMilitaryZonesDisabled;

public:
    static void InjectHooks();

    static void Init();
    static void Update();

    static void AddCullZone(const CVector* center, float zero1, float fWidthY, float fBottomZ, float fWidthX, float zero2, float fTopZ, uint16_t flags);
    static void AddTunnelAttributeZone(const CVector* center, float unk1, float fWidthY, float fBottomZ, float fWidthX, float unk2, float fTopZ, uint16_t flags);
    static void AddMirrorAttributeZone(const CVector* center, float unk1, float fWidthY, float fBottomZ, float fWidthX, float unk2, float fTopZ, uint16_t flags, int cm, float vX, float vY, float vZ);

    static bool InRoomForAudio();
    static bool CamNoRain();
    static bool PlayerNoRain();
    static bool FewerPeds();
    static bool NoPolice();
    static bool DoExtraAirResistanceForPlayer();

    static eZoneAttributes FindTunnelAttributesForCoors(CVector point);
    static CCullZoneReflection* FindMirrorAttributesForCoors_(CVector cameraPosition);
    static CCullZoneReflection* FindMirrorAttributesForCoors(float x, float y, float z);
    static CCullZone* FindZoneWithStairsAttributeForPlayer();
    static eZoneAttributes FindAttributesForCoors(float x, float y);
};
