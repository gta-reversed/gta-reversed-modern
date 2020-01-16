#pragma once
#include "PluginBase.h"
#include "CTaskSimple.h"

class CVehicle;

class CTaskSimpleCarDrive : public CTaskSimple
{
    CTaskSimpleCarDrive() = delete;
protected:
    CTaskSimpleCarDrive(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    CVehicle* m_pVehicle;

    CTaskSimpleCarDrive* Constructor (CVehicle* pVehicle, int arg2, bool arg3);
};