#pragma once

#include <Matrix.h>

class CFallingGlassPane {
public:
    CMatrix matrix = {};        // 0
    CVector velocity = {};      // 0x48
    CVector randomNumbers = {}; // 0x54
    uint32 createdTime = {};     // 0x60
    float groundZ = {};         // 0x64
    float size = {};            // 0x68
    uint8 nPieceIndex = {};     // 0x6C
    int8 existFlag = {};        // 0x6D
    int8 bRenderShatter = {};   // 0x6E
    int8 field_6F = {};         // 0x6F
public:
    static void InjectHooks();

    ~CFallingGlassPane();
    CFallingGlassPane();

    void Update();
    auto CalculateHiHlightPolyColor();
    auto CalculateShatterPolyColor();
    void Render();

private:
    CFallingGlassPane* Constructor();
    CFallingGlassPane* Destructor();
};
VALIDATE_SIZE(CFallingGlassPane, 0x70);
