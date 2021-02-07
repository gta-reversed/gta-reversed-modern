#pragma once
#include "CAEAudioEntity.h"

class CAEDoorAudioEntity : public CAEAudioEntity
{
    uint32_t m_nTime;
    uint32_t m_nField80;
    uint32_t m_nField84;
};
VALIDATE_SIZE(CAEDoorAudioEntity, 0x88);
