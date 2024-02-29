#include "StdInc.h"

void CSetPiece::InjectHooks() {
    RH_ScopedClass(CSetPiece);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(TryToGenerateCopPed, 0x499690, {.reversed=false});
    RH_ScopedInstall(TryToGenerateCopCar, 0x4998A0, {.reversed=false});
    RH_ScopedInstall(Update, 0x499A80, {.reversed=false});
}

// 0x499690
CCopPed* CSetPiece::TryToGenerateCopPed(CVector2D posn) {
    return nullptr;
}

// 0x4998A0
CVehicle* CSetPiece::TryToGenerateCopCar(CVector2D posn, CVector2D target) {
    return nullptr;
}

// 0x499A80
void CSetPiece::Update() {
}
