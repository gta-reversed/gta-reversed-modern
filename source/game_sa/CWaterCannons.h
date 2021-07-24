#pragma once

#include "CWaterCannon.h"

class CVector;

class CWaterCannons {
public:
    static constexpr unsigned int MAX_WATER_CANNONS = 3;
    static CWaterCannon (&aCannons)[MAX_WATER_CANNONS];

public:
    static void InjectHooks();

    static void Init();
    static void UpdateOne(unsigned int pVehicle, CVector* start, CVector* end);
    static void Update();
    static void Render();
};
