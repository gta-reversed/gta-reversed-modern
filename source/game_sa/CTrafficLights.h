#pragma once
#include "PluginBase.h"
#include "CVehicle.h"

enum eTrafficLightsState {
    LIGHT_GREEN = 0,
    LIGHT_YELLOW = 1,
    LIGHT_RED = 2,
    LIGHT_OFF = 3
};

//1 - North-South, 2 - West-East cycle
enum eTrafficLightsDirection {
    DIR_NORTH_SOUTH = 1,
    DIR_WEST_EAST = 2
};

class CTrafficLights {
private:
    static uint8_t(&aTrafficLightColoursR)[3];
    static uint8_t(&aTrafficLightColoursG)[3];
    static uint8_t(&aTrafficLightColoursB)[3];
    static float& fLightMult;

    static CVector& vecTrafficLights5_1;
    static CVector& vecTrafficLights5_2;
    static CVector& vecTrafficLights_1;
    static CVector& vecTrafficLights_2;
    static uint32_t& uiPedLightFlags;

public:
    static void InjectHooks();

public:
    static bool ShouldCarStopForLight(CVehicle* pVehicle, bool bUnkn);
    static bool ShouldCarStopForBridge(CVehicle* pVehicle);
    static void DisplayActualLight(CEntity* pEntity);
    static bool IsMITrafficLight(int modelIndex);
    static unsigned char LightForPeds();

private:
    static unsigned char LightForCars1();
    static unsigned char LightForCars2();
    static unsigned char LightForCars1_Visual();
    static unsigned char LightForCars2_Visual();
    static int FindTrafficLightType(CEntity* pEntity);
    static float FindOrientationForTrafficLightType(CEntity* pEntity);
    static int FindTrafficLightTypeFromOrientation(float fOrientation);
};
