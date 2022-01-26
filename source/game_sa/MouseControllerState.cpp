#include "StdInc.h"

void CMouseControllerState::InjectHooks() {
    RH_ScopedClass(CMouseControllerState);
    RH_ScopedCategoryRoot();

    RH_ScopedInstall(Constructor, 0x53F220);
    RH_ScopedInstall(Clear, 0x53F250);
    RH_ScopedInstall(CheckForInput, 0x53F270);
}

// 0x53F220
CMouseControllerState::CMouseControllerState() {
    this->Z = 0.0f;
    this->X = 0.0f;
    this->Y = 0.0f;
    this->Clear();
}

CMouseControllerState* CMouseControllerState::Constructor() {
    this->CMouseControllerState::CMouseControllerState();
    return this;
}

// 0x53F250
void CMouseControllerState::Clear() {
    lmb = 0;
    rmb = 0;
    mmb = 0;
    wheelUp = 0;
    wheelDown = 0;
    bmx1 = 0;
    bmx2 = 0;
}

// 0x53F270
bool CMouseControllerState::CheckForInput() {
    return (
        lmb
        || rmb
        || mmb
        || wheelUp
        || wheelDown
        || bmx1
        || bmx2
        || X != 0.0f
        || Y != 0.0f
    );
}


