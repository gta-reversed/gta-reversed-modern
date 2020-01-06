#pragma once
#include "PluginBase.h"
#include "CMatrix.h"

class CEntity;

class cBuoyancy
{
public:

    bool ProcessBuoyancy(CEntity* pEntity, float fBuoyancy, CVector* pOutVecMoveForce, CVector* pOutVecTurnForce);

    CVector         vecPos;                     // 0
    CMatrix         EntityMatrix;               // 12
    unsigned int    pad1[4];                    // 84
    float           fWaterLevel;                // 100
    unsigned int    pad2;                       // 104
    float           fBuoyancy;                  // 108
    CVector         vecUnk1;                    // 112
    CVector         vecUnk2;                    // 124
    unsigned int    pad3[4];                    // 136
    unsigned char   pad4[4];                    // 152
    unsigned int    pad5[7];                    // 156
    unsigned char   pad6[2];                    // 184
    unsigned char   bProcessingBoat;            // 186
    unsigned char   pad7;                       // 187
    float           fTurnForceZ;                // 188
    CVector         vecMoveForce;               // 192
    unsigned int    pad8;                       // 204
};

VALIDATE_SIZE(cBuoyancy, 0xD0);

extern cBuoyancy& mod_Buoyancy;