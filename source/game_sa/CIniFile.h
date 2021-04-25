/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CIniFile {
public:
    static float &PedNumberMultiplier;
    static float &CarNumberMultiplier;

public:
    static void InjectHooks();

    static void LoadIniFile();
};
