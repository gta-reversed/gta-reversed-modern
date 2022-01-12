#pragma once

class CBridge {
public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void FindBridgeEntities();
    static bool ShouldLightsBeFlashing();
    static bool ThisIsABridgeObjectMovingUp(uint32);
};
