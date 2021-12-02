#pragma once

class CCranes {
public:
    static void InjectHooks();

    static void InitCranes();
    static void UpdateCranes();
    static bool IsThisCarBeingCarriedByAnyCrane();
    static bool IsThisCarBeingTargettedByAnyCrane();
    static bool IsThisCarPickedUp();
};
