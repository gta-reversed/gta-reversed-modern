/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class CCredits {
public:
    static int &m_nCreditsStartTime;
    static bool &m_bCreditsGoing;

    //NOTSA
    static float m_Position;
    static float m_CurrentOffset;

public:
    static void InjectHooks();

    static void Render();
    static void PrintCreditText(float scaleX, float scaleY, const char* text, float& position, float currentOffset, bool highlighted);
    static void PrintCreditSpace(float spaceSize, unsigned int& position);
    static void RenderCredits();
    static void Start();
    static void Stop();

    //NOTSA
    static void PrintCreditTextHelper(char *textKey, float scale, bool highlighted);
};
