#pragma once

#include "eGarage.h"

class CGarage;

struct CSaveGarage {
    eGarageType      m_nType;
    eGarageDoorState m_nDoorState;
    uint8            m_nFlags;
    CVector          m_vPosn;
    CVector2D        m_vDirectionA, m_vDirectionB;
    float            m_fTopZ;
    float            m_fWidth, m_fHeight;
    float            m_fLeftCoord;
    float            m_fRightCoord;
    float            m_fFrontCoord;
    float            m_fBackCoord;
    float            m_fDoorPosition;
    uint32           m_nTimeToOpen;
    char             m_anName[8];
    eGarageType      m_nOriginalType;

    void CopyGarageIntoSaveGarage(const CGarage& garage);
    void CopyGarageOutOfSaveGarage(CGarage& garage) const;
};
VALIDATE_SIZE(CSaveGarage, 0x50);
