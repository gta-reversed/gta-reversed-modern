#pragma once

struct CColSurface {
    eSurfaceType m_nMaterial{};
    uint8        m_nPiece{}; // ePedPieceTypes, eCarPiece ?
    tColLighting m_nLighting{};
    uint8        m_nLight{};
};
