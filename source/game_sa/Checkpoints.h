/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CCheckpoint;

class CCheckpoints {
public:
    static inline uint32 &NumActiveCPts = *(uint32*)0xC7C6D4; // not used, only initialised (0)
    static inline std::array<CCheckpoint, 32>& m_aCheckPtArray = *(std::array<CCheckpoint, 32>*)0xC7F158;

public:
    static void InjectHooks();

    static void Init();
    static void Shutdown();
    static void Update();
    static void Render();

    static CCheckpoint* PlaceMarker(uint32 id, uint16 type, CVector& posn, CVector& direction, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate);
    static void DeleteCP(uint32 id, uint16 type);
    static void SetHeading(uint32 id, float angle);
    static void UpdatePos(uint32 id, CVector& posn);

    static CCheckpoint* FindById(uint32 id); // NOTSA
};
