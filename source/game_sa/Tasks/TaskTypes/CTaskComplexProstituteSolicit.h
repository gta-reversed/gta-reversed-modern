/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CTaskComplex.h"
#include "CPed.h"

class CTaskComplexProstituteSolicit : public CTaskComplex {
public:
    CPed *m_pClient; // player only
    CVector m_vecVehiclePosn;
    int32 m_nLastSavedTime;
    int32 m_nNextTimeToCheckForSecludedPlace; // when we will scan nearby peds again
    int32 m_nLastPaymentTime; // when CJ will pay $2 again
    int16 m_nVehicleMovementTimer; // wait some time and push vehicle again
    int16 m_nCurrentTimer;
    struct {
        uint16 bSearchingForSecludedPlace : 1;
        uint16 bSexProcessStarted : 1;
        uint16 bTaskCanBeFinished : 1;
        uint16 bPedsCanPotentiallySeeThis : 1;
        uint16 bPedsCanSeeThis : 1;
        uint16 bCopsCanSeeThis : 1;
        uint16 b07 : 1;
        uint16 b08 : 1;
        uint16 bMoveCameraDown : 1;
        uint16 b10 : 1;
        uint16 bPlayerHasAcceptedSexProposition : 1;
        uint16 bVehicleShifted : 1;
        uint16 bSecludedPlaceMessageShown : 1;
    } m_nFlags;
private:
    uint16 _pad2E;
public:
    CTaskComplexProstituteSolicit(CPed* pClient);
    CTask* CreateSubTask(int32 taskId, CPed* pProstitute);
    static void GetRidOfPlayerProstitute();
    static bool IsTaskValid(CPed* pProstitute, CPed* pClient);
};

VALIDATE_SIZE(CTaskComplexProstituteSolicit, 0x30);
