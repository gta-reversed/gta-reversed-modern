/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Ped.h"
#include "Vector.h"
#include "PointList.h"
#include "Matrix.h"
#include "PedList.h"
#include "Vehicle.h"

class CFormation {
public:
    static int32 (&m_aFinalPedLinkToDestinations)[8]; // static int32 m_aFinalPedLinkToDestinations[8]
    static int32 (&m_aPedLinkToDestinations)[8];      // static int32 m_aPedLinkToDestinations[8]
    static CPointList& m_Destinations;
    static CPedList&   m_DestinationPeds;
    static CPedList&   m_Peds;

    static void DistributeDestinations(CPedList* pedlist);
    static void DistributeDestinations_CoverPoints(CPedList* pedlist, CVector pos);
    static void DistributeDestinations_PedsToAttack(CPedList* pedlist);
    static void FindCoverPoints(CVector pos, float radius);
    static void FindCoverPointsBehindBox(CPointList* pointlist, CVector Pos, CMatrix* coverEntityMatrix, CVector const* vecCenter, CVector const* vecMin, CVector const* vecMax, float radius);
    static signed int FindNearestAvailableDestination(CVector pos, float* pOutDistance);
    static void GenerateGatherDestinations(CPedList* pedList, CPed* ped);
    static void GenerateGatherDestinations_AroundCar(CPedList* pedlist, CVehicle* vehicle);
    static bool ReturnDestinationForPed(CPed* ped, CVector* pos);
    static int32 ReturnTargetPedForPed(CPed* ped, CPed** pOutTargetPed);
};
