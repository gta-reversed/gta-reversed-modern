#pragma once
#include "CTaskSimpleCarDrive.h"

class CVehicle;

class CTaskSimpleCarDriveTimed : public CTaskSimpleCarDrive
{
    CTaskSimpleCarDriveTimed() = delete;
public:

    CTaskSimpleCarDriveTimed* Constructor(CVehicle* pVehicle, int arg2);
};
