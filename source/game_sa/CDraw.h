/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CDraw {
public:
    static float& ms_fFOV; // default 45.0
    static float& ms_fLODDistance;
    static float& ms_fFarClipZ;
    static float& ms_fNearClipZ;
    static float& ms_fAspectRatio;
    static unsigned char& FadeRed;
    static unsigned char& FadeGreen;
    static unsigned char& FadeBlue;
    static unsigned char& FadeValue;

public:
    static void InjectHooks();

    static void SetFOV(float fovValue);
    static float CalculateAspectRatio();
};
