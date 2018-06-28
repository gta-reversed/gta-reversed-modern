/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplex.h"
#include "CPed.h"

class CTaskComplexProstituteSolicit : public CTaskComplex {
protected:
    CTaskComplexProstituteSolicit(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    CPed *m_pClient; // player only
    CVector m_vecVehiclePosn;
    int m_nLastSavedTime;
    int m_nNextTimeToCheckForSecludedPlace; // when we will scan nearby peds again
    int m_nLastPaymentTime; // when CJ will pay $2 again
    short m_nVehicleMovementTimer; // wait some time and push vehicle again
    short m_nCurrentTimer;
    struct {
        unsigned short bSearchingForSecludedPlace : 1;
        unsigned short bSexProcessStarted : 1;
        unsigned short bTaskCanBeFinished : 1;
        unsigned short bPedsCanPotentiallySeeThis : 1;
        unsigned short bPedsCanSeeThis : 1;
        unsigned short bCopsCanSeeThis : 1;
        unsigned short b07 : 1;
        unsigned short b08 : 1;
        unsigned short bMoveCameraDown : 1;
        unsigned short b10 : 1;
        unsigned short bPlayerHasAcceptedSexProposition : 1;
        unsigned short bVehicleShifted : 1;
        unsigned short bSecludedPlaceMessageShown : 1;
    } m_nFlags;
private:
    unsigned short _pad2E;
public:
    CTaskComplexProstituteSolicit(CPed* pClient);
    CTask* CreateSubTask(int taskId, CPed* pProstitute);
    static void GetRidOfPlayerProstitute();
    static bool IsTaskValid(CPed* pProstitute, CPed* pClient);
};

VALIDATE_SIZE(CTaskComplexProstituteSolicit, 0x30);
