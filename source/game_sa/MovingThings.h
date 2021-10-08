#pragma once

class CMovingThings {
public:
    static void InjectHooks();

    static void Init();
    static void Shutdown();
    static void Update();
    static void Render();
    static void Render_BeforeClouds();
};
