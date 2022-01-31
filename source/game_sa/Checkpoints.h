/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class Checkpoint;

constexpr auto MAX_NUM_CHECKPOINTS{ 32u };

class CCheckpoints {
public:
    static uint32 &NumActiveCPts; // not used, only initialised (0)
    static CCheckpoint *m_aCheckPtArray; // static CCheckpoint m_aCheckPtArray[32]

    static void DeleteCP(uint32 id, uint16 type);
    static void Init();
    static CCheckpoint* PlaceMarker(uint32 id, uint16 type, CVector& posn, CVector& direction, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate);
    static void Render();
    static void SetHeading(uint32 id, float angle);
    // dummy function
    static void Shutdown();
    static void Update();
    static void UpdatePos(uint32 id, CVector& posn);
};
