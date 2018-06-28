/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVehicle.h"

class  CUpsideDownCarCheck {
public:

    struct {
        int m_nCarHandle;
        int field_4;
    } m_aUpsideDownCars[6];

     void AddCarToCheck(int carHandle);
    //! never used
     bool AreAnyCarsUpsideDown();
     char HasCarBeenUpsideDownForAWhile(int carHandle);
     void Init();
     void RemoveCarFromCheck(int carHandle);
     void UpdateTimers();

     static bool IsCarUpsideDown(CVehicle *pVehicle);
     static bool IsCarUpsideDown(int carhandle);
};
VALIDATE_SIZE(CUpsideDownCarCheck, 0x30);

//#include "meta/meta.CUpsideDownCarCheck.h"
