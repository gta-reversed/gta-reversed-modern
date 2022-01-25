#include "StdInc.h"

void CEventDraggedOutCar::InjectHooks()
{
    Install("CEventDraggedOutCar", "Constructor", 0x4AD250, &CEventDraggedOutCar::Constructor);
    Install("CEventDraggedOutCar", "CloneEditable_Reversed", 0x4B6DC0, &CEventDraggedOutCar::CloneEditable_Reversed);
}

CEventDraggedOutCar::CEventDraggedOutCar(CVehicle* vehicle, CPed* carjacker, bool IsDriverSeat)
{
    m_carjacker = carjacker;
    m_vehicle = vehicle;
    m_IsDriverSeat = IsDriverSeat;
    if (m_vehicle)
        m_vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
    if (m_carjacker)
        m_carjacker->RegisterReference(reinterpret_cast<CEntity**>(&m_carjacker));
}

CEventDraggedOutCar::~CEventDraggedOutCar()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
    if (m_carjacker)
        m_carjacker->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_carjacker));
}

CEventDraggedOutCar* CEventDraggedOutCar::Constructor(CVehicle* vehicle, CPed* carjacker, bool IsDriverSeat)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventDraggedOutCar*, 0x4AD250, CEvent*, CVehicle*, CPed*, bool>(this, vehicle, carjacker, IsDriverSeat);
#else
    this->CEventDraggedOutCar::CEventDraggedOutCar(vehicle, carjacker, IsDriverSeat);
    return this;
#endif
}

CEventEditableResponse* CEventDraggedOutCar::CloneEditable()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventEditableResponse*, 0x4B6DC0, CEvent*>(this);
#else
    return CEventDraggedOutCar::CloneEditable_Reversed();
#endif
}

CEventEditableResponse* CEventDraggedOutCar::CloneEditable_Reversed()
{
    return new CEventDraggedOutCar(m_vehicle, m_carjacker, m_IsDriverSeat);
}
