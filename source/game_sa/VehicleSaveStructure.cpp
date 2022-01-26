#include "StdInc.h"

void CVehicleSaveStructure::InjectHooks()
{
    RH_ScopedClass(CVehicleSaveStructure);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Construct, 0x5D2330);
    RH_ScopedInstall(Extract, 0x5D23B0);
}

void CVehicleSaveStructure::Construct(CVehicle* pVeh)
{
    m_matrix = *pVeh->m_matrix;
    m_nPrimaryColor      = pVeh->m_nPrimaryColor;
    m_nSecondaryColor    = pVeh->m_nSecondaryColor;
    m_nTertiaryColor     = pVeh->m_nTertiaryColor;
    m_nQuaternaryColor   = pVeh->m_nQuaternaryColor;
    m_nAlarmState        = pVeh->m_nAlarmState;
    m_nMaxPassengers     = pVeh->m_nMaxPassengers;
    m_fSteerAngle        = pVeh->m_fSteerAngle;
    m_fGasPedal          = pVeh->m_fGasPedal;
    m_fBrakePedal        = pVeh->m_fBreakPedal;
    m_nVehicleUpperFlags = pVeh->m_nVehicleUpperFlags;
    m_nVehicleLowerFlags = pVeh->m_nVehicleLowerFlags;
}

void CVehicleSaveStructure::Extract(CVehicle* pVeh)
{
    pVeh->SetMatrix(m_matrix);
    pVeh->m_nPrimaryColor      = m_nPrimaryColor;
    pVeh->m_nSecondaryColor    = m_nSecondaryColor;
    pVeh->m_nTertiaryColor     = m_nTertiaryColor;
    pVeh->m_nQuaternaryColor   = m_nQuaternaryColor;
    pVeh->m_nAlarmState        = m_nAlarmState;
    pVeh->m_nMaxPassengers     = m_nMaxPassengers;
    pVeh->m_fSteerAngle        = m_fSteerAngle;
    pVeh->m_fGasPedal          = m_fGasPedal;
    pVeh->m_fBreakPedal        = m_fBrakePedal;
    pVeh->m_nVehicleUpperFlags = m_nVehicleUpperFlags;
    pVeh->m_nVehicleLowerFlags = m_nVehicleLowerFlags;
}
