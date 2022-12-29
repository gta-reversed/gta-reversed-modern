#pragma once

/*!
* Various utility commands
*/

//! Not a script command, but used in other commands
void HighlightImportantArea(CRunningScript& S, CVector2D from, CVector2D to, float z = -100.f) {
    CTheScripts::HighlightImportantArea(reinterpret_cast<int32>(&S) + reinterpret_cast<int32>(S.m_IP), from.x, from.y, to.x, to.y, z);
}

void HighlightImportantArea(CRunningScript& S, CVector from, CVector to) {
    HighlightImportantArea(S, CVector2D{ from }, CVector2D{ to }, (from.z + to.z) / 2.f);
}
