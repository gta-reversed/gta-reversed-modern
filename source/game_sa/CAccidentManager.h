#pragma once
#include "CAccident.h"

const int NUM_ACCIDENTS = 16;

class CAccidentManager
{
public:
    CAccident m_Accidents[NUM_ACCIDENTS];

    static CAccidentManager*& gAccidentManager;

    static void InjectHooks();
    static CAccidentManager* GetInstance();

    void ReportAccident(CPed* ped);
    int GetNumberOfFreeAccidents();
    CAccident* GetNearestFreeAccidentExceptThisOne(CVector& posn, CAccident* thisOne, bool bIgnoreHeadless);
    CAccident* GetNearestFreeAccident(CVector& posn, bool bIgnoreHeadless);
};

VALIDATE_SIZE(CAccidentManager, 0x80);
