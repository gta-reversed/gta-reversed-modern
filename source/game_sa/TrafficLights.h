#pragma once

#include "Vehicle.h"

enum eTrafficLightsState {
    LIGHT_GREEN = 0,
    LIGHT_YELLOW = 1,
    LIGHT_RED = 2,
    LIGHT_OFF = 3
};

enum eTrafficLightsDirection {
    DIR_DISABLED = 0,
    DIR_NORTH_SOUTH = 1,
    DIR_WEST_EAST = 2
};

class CTrafficLights {
private:
    static uint8 (&aTrafficLightColoursR)[3];
    static uint8 (&aTrafficLightColoursG)[3];
    static uint8 (&aTrafficLightColoursB)[3];
    static float& fLightMult;

    static CVector& vecTrafficLights5_1;
    static CVector& vecTrafficLights5_2;
    static CVector& vecTrafficLights_1;
    static CVector& vecTrafficLights_2;
    static uint32& uiPedLightFlags;

public:
    static void InjectHooks();

public:
    static bool ShouldCarStopForLight(CVehicle* vehicle, bool bUnkn);
    static bool ShouldCarStopForBridge(CVehicle* vehicle);
    static void DisplayActualLight(CEntity* entity);
    static bool IsMITrafficLight(int32 modelIndex);
    static uint8 LightForPeds();

private:
    static uint8 LightForCars1();
    static uint8 LightForCars2();
    static uint8 LightForCars1_Visual();
    static uint8 LightForCars2_Visual();
    static int32 FindTrafficLightType(CEntity* entity);
    static float FindOrientationForTrafficLightType(CEntity* entity);
    static int32 FindTrafficLightTypeFromOrientation(float fOrientation);
};
