#pragma once
#include "PluginBase.h"
#include "CTaskSimple.h"

class CTaskSimpleCarDrive : CTaskSimple
{
    CTaskSimpleCarDrive() = delete;
protected:
    CTaskSimpleCarDrive(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    CTaskSimpleCarDrive* Constructor (CVehicle* pVehicle, int arg2, bool arg3);
};