/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CCredits {
public:
    static int &CreditsStartTime;
    static bool &bCreditsGoing;

    static void Render();
    static void PrintCreditText(float scaleX, float scaleY, unsigned short* text, unsigned int& position, float currentOffset, bool highlighted);
    static void PrintCreditSpace(float spaceSize, unsigned int& position);
    static void RenderCredits();
    static void Start();
    static void Stop();
};
