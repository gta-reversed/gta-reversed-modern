/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Base.h"
#include "Vector.h"

class CTaskUtilityLineUpPedWithCar {
public:
    CVector m_offset{};
    float m_doorOpenPosZ{-999.99f};
    int32_t m_time{};
    int32_t m_doorOpenPosType{};
    int32_t m_doorIdx{};

public:
    CTaskUtilityLineUpPedWithCar(const CVector& offset, int32 time, int32 doorOpenPosType, int32 doorIdx);
    ~CTaskUtilityLineUpPedWithCar() = default;

    CVector GetLocalPositionToOpenCarDoor(CVehicle* vehicle, float animProgress, CAnimBlendAssociation* animAssoc);
    CVector GetPositionToOpenCarDoor(CVehicle* vehicle, float animProgress, CAnimBlendAssociation* animAssoc);
    bool ProcessPed(CPed* pPed, CVehicle* pVehicle, CAnimBlendAssociation* pAnimAssoc);

private: // Wrappers for hooks
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskUtilityLineUpPedWithCar* Constructor(CVector* offsets, int32 nTime, int32 doorOpenPosType, int32 doorIdx) {
        this->CTaskUtilityLineUpPedWithCar::CTaskUtilityLineUpPedWithCar(offsets, nTime, doorOpenPosType, doorIdx);
        return this;
    }

    CTaskUtilityLineUpPedWithCar* Destructor() {
        this->CTaskUtilityLineUpPedWithCar::~CTaskUtilityLineUpPedWithCar();
        return this;
    }
};
VALIDATE_SIZE(CTaskUtilityLineUpPedWithCar, 0x1C);
