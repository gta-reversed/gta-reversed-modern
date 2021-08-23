/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CCredits {
public:
    static uint32_t& CreditsStartTime;
    static bool& bCreditsGoing;

public:
    static void InjectHooks();

    static void Start();
    static void Stop();

    static void Render();
    static void PrintCreditText(float scaleX, float scaleY, const char* text, float& position, float currentOffset, bool highlighted);
    static inline void PrintCreditSpace(float spaceSize, float& position);
    static void RenderCredits();
};
