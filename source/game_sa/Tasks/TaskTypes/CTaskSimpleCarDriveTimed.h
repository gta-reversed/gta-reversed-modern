#pragma once
#include "CTaskSimpleCarDrive.h"

class CVehicle;

class CTaskSimpleCarDriveTimed : CTaskSimpleCarDrive
{
    CTaskSimpleCarDriveTimed() = delete;
public:

    CTaskSimpleCarDriveTimed* Constructor(CVehicle* pVehicle, int arg2);
};