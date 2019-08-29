#pragma once
#include "CTaskSimpleCarDrive.h"

class CVehicle;

class CTaskSimpleCarDriveTimed : CTaskSimpleCarDrive
{
    CTaskSimpleCarDriveTimed() = delete;
protected:
    CTaskSimpleCarDriveTimed(plugin::dummy_func_t a) : CTaskSimpleCarDrive(a) {}
public:

    CTaskSimpleCarDriveTimed* Constructor(CVehicle* pVehicle, int arg2);
};