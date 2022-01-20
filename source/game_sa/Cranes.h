#pragma once

class CCranes {
public:
    static void InjectHooks();

    static void InitCranes();
    static void UpdateCranes();
    static bool IsThisCarBeingCarriedByAnyCrane(CVehicle* vehicle);
    static bool IsThisCarBeingTargettedByAnyCrane(CVehicle* vehicle);
    static bool IsThisCarPickedUp(float a1, float a2, CVehicle* vehicle);
};
