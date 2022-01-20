/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

static inline bool& JustLoadedDontFadeInYet = *(bool*)0xC16EDC;
static inline bool& StillToFadeOut = *(bool*)0xC16EDD;

class CDraw {
public:
    static float& ms_fFOV; // default 45.0
    static float& ms_fLODDistance;
    static float& ms_fFarClipZ;
    static float& ms_fNearClipZ;
    static float& ms_fAspectRatio;
    static uint8& FadeRed;
    static uint8& FadeGreen;
    static uint8& FadeBlue;
    static uint8& FadeValue;

public:
    static void InjectHooks();

    static void SetFOV(float fovValue);
    static void CalculateAspectRatio();
};

static void DoFade();
