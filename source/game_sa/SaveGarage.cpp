#include "StdInc.h"

#include "Garage.h"
#include "SaveGarage.h"

// 0x5D3020
void CSaveGarage::CopyGarageIntoSaveGarage(const CGarage& g) {
    m_nType         = g.Type;
    m_nDoorState    = g.DoorState;
    m_nFlags        = g.m_nFlags;
    m_vPosn         = g.Base;
    m_vDirectionA   = g.m_Delta1;
    m_vDirectionB   = g.m_Delta2;
    m_fTopZ         = g.CeilingZ;
    m_fWidth        = g.Delta1Length;
    m_fHeight       = g.Delta2Length;
    m_fLeftCoord    = g.MinX;
    m_fRightCoord   = g.MaxX;
    m_fFrontCoord   = g.MinY;
    m_fBackCoord    = g.MaxY;
    m_fDoorPosition = g.Openness;
    m_nTimeToOpen   = g.TimeOfNextEvent;
    m_nOriginalType = g.m_nOriginalType;
    strcpy_s(m_anName, g.Name);
}

// 0x5D30C0
void CSaveGarage::CopyGarageOutOfSaveGarage(CGarage& g) const {
    g.Type = m_nType;
    g.DoorState = m_nDoorState;
    g.m_nFlags        = m_nFlags;
    g.Base = m_vPosn;
    g.m_Delta1 = m_vDirectionA;
    g.m_Delta2 = m_vDirectionB;
    g.CeilingZ = m_fTopZ;
    g.Delta1Length = m_fWidth;
    g.Delta2Length = m_fHeight;
    g.MinX = m_fLeftCoord;
    g.MaxX = m_fRightCoord;
    g.MinY = m_fFrontCoord;
    g.MaxY = m_fBackCoord;
    g.Openness = m_fDoorPosition;
    g.TimeOfNextEvent = m_nTimeToOpen;
    g.m_nOriginalType = m_nOriginalType;
    g.CarToCollect = nullptr;
    strcpy_s(g.Name, m_anName);
}
