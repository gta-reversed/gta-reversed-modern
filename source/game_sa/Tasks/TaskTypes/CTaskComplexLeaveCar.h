/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplex.h"
#include "CVehicle.h"
#include "CTaskUtilityLineUpPedWithCar.h"

class CTaskComplexLeaveCar : public CTaskComplex {
public:
    CVehicle* m_pTargetVehicle;
    int m_nTargetDoor;
    int m_nDelayTime;
    bool m_bSensibleLeaveCar;
    bool m_bForceGetOut;
    bool m_bDie;
private:
    char _pad1;
public:

    CTaskUtilityLineUpPedWithCar *m_pTaskUtilityLineUpPedWithCar;
    unsigned char m_nDoorFlagsSet;
    unsigned char m_nNumGettingInSet;
private:
    char _pad2[2];
public:

    int m_nDieAnimID;
    float m_fDieAnimBlendDelta;
    float m_fDieAnimSpeed;

    bool m_bIsInAir;
private:
    char _pad3[3];
public:

    CTaskComplexLeaveCar(CVehicle* pTargetVehicle, int nTargetDoor, int nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut);
    ~CTaskComplexLeaveCar();

    CTaskComplexLeaveCar* Constructor(CVehicle* pTargetVehicle, int nTargetDoor, int nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut);

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_COMPLEX_LEAVE_CAR; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
};

VALIDATE_SIZE(CTaskComplexLeaveCar, 0x34);

