#pragma once

#include "Base.h"

#include "TaskTimer.h"

class CMentalHealth {
public:
    CMentalHealth() = default;
    ~CMentalHealth() = default;
    
    void IncrementAnger();
    void Process();
public:
  uint8       m_anger{};
  uint8       m_oldAnger{};

  CTaskTimer m_timer{ CTimer::GetTimeInMS(), 0u };

  uint8      m_pedHealth{};
  uint8      m_oldPedHealth{};

  uint8      m_vehicleHealth{};
  uint8      m_oldVehicleHealth{};
};
VALIDATE_SIZE(CMentalHealth, 0x14);
