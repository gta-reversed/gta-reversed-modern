#pragma once
#include "PluginBase.h"
#include "CMatrix.h"

class CEntity;
class CPhysical;

class cBuoyancy
{
public:
    CVector         m_vecPos;                     // 0
    CMatrix         m_EntityMatrix;               // 12
    CVector         field_54;
    float           field_60;
    float           m_fWaterLevel;                // 100
    unsigned int    field_68;                   // 104
    float           m_fBuoyancy;                  // 108
    CVector         field_70;                   // 112
    CVector         field_7C;                   // 124
    unsigned int    field_88;
    unsigned int    field_8C;
    unsigned int    field_90;
    unsigned int    field_94;
    unsigned char   field_98;
    unsigned char   field_99;
    unsigned char   field_9A;
    unsigned char   field_9B;
    unsigned int    field_9C;
    unsigned int    field_A0;
    unsigned int    field_A4;
    CVector         field_A8;
    unsigned int    field_B4;
    unsigned char   field_B8[2];                // 184
    unsigned char   m_bProcessingBoat;            // 186
    unsigned char   field_BB;                   // 187
    float           m_fDistanceToWaterSurfaceZ;  // distance in Z-axis between entity and water surface
    CVector         m_vecMoveForce;               // 192
    unsigned int    field_CC;                   // 204

    static void InjectHooks();
    bool ProcessBuoyancy(CPhysical* pEntity, float fBuoyancy, CVector* pVecTurnSpeed, CVector* pBuoyancy);
    bool CalcBuoyancyForce(CPhysical* pEntity, CVector* pVecTurnSpeed, CVector* pBuoyancy);
    float PreCalcSetup(CPhysical* pEntity, float fBuoyancy);
    void AddSplashParticles(CPhysical* pEntity, CVector a3, CVector a4, CVector a5, bool bUnknown);
    void SimpleCalcBuoyancy(CPhysical* pEntity);
};

VALIDATE_SIZE(cBuoyancy, 0xD0);

extern cBuoyancy& mod_Buoyancy;