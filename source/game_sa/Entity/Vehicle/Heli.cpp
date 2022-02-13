/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

bool& CHeli::bPoliceHelisAllowed = *(bool*)0x8D338C;
uint32& CHeli::TestForNewRandomHelisTimer = *(uint32*)0xC1C960;
CHeli* (&CHeli::pHelis)[2] = *(CHeli*(*)[2])0xC1C964;
uint32& CHeli::NumberOfSearchLights = *(uint32*)0xC1C96C;
bool& CHeli::bHeliControlsCheat = *(bool*)0xC1C970;
tHeliLight (&CHeli::HeliSearchLights)[4] = *(tHeliLight(*)[4])0xC1C990;

void CHeli::InjectHooks() {
    RH_ScopedClass(CHeli);
    RH_ScopedCategory("Vehicle");

    RH_ScopedInstall(InitHelis, 0x6C4560);
    RH_ScopedInstall(AddHeliSearchLight, 0x6C45B0);
    RH_ScopedInstall(Pre_SearchLightCone, 0x6C4650);
    RH_ScopedInstall(Post_SearchLightCone, 0x6C46E0);
    RH_ScopedInstall(SwitchPoliceHelis, 0x6C4800);
    RH_ScopedInstall(RenderAllHeliSearchLights, 0x6C7C50);
    RH_ScopedInstall(TestSniperCollision, 0x6C6890);
    RH_ScopedInstall(Render_Reversed, 0x6C4400);
    RH_ScopedInstall(Fix_Reversed, 0x6C4530);
    RH_ScopedInstall(BurstTyre_Reversed, 0x6C4330);
    RH_ScopedInstall(SetUpWheelColModel_Reversed, 0x6C4320);
}

// 0x6C4190
CHeli::CHeli(int32 modelIndex, eVehicleCreatedBy createdBy) : CAutomobile({}) {
    plugin::CallMethod<0x6C4190, CHeli*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
}

// 0x6C4340
CHeli::~CHeli() {
    if (m_ppGunflashFx) {
        for (auto i = 0; i < CVehicle::GetPlaneNumGuns(); i++) {
            auto& fx = m_ppGunflashFx[i];
            if (fx) {
                fx->Kill();
                g_fxMan.DestroyFxSystem(fx);
            }
        }
        delete[] m_ppGunflashFx;
        m_ppGunflashFx = nullptr;
    }

    m_vehicleAudio.Terminate();
}

// 0x6C4560
void CHeli::InitHelis() {
    std::ranges::fill(pHelis, nullptr);
    for (auto& light : HeliSearchLights) {
        light.Init();
    }
    NumberOfSearchLights = 0;
    bPoliceHelisAllowed = true;
}

// 0x6C45B0
void CHeli::AddHeliSearchLight(const CVector& origin, const CVector& target, float targetRadius, float power, uint32 coronaIndex, uint8 unknownFlag, uint8 drawShadow) {
    // return ((void(__cdecl*)(const CVector&, const CVector&, float, float, uint32, uint8, uint8))0x6C45B0)(origin, target, targetRadius, power, coronaIndex, unknownFlag, drawShadow);

    auto& light = HeliSearchLights[NumberOfSearchLights];

    light.m_vecOrigin     = origin;
    light.m_vecTarget     = target;
    light.m_fTargetRadius = targetRadius;
    light.m_fPower        = power;
    light.m_nCoronaIndex  = coronaIndex;
    light.field_24        = unknownFlag;
    light.m_bDrawShadow   = drawShadow;

    NumberOfSearchLights += 1;
}

// 0x6C4640
void CHeli::PreRenderAlways() {
    // NOP
}

// 0x6C4650
void CHeli::Pre_SearchLightCone() {
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDONE));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDONE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,        RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            RWRSTATE(rwSHADEMODEGOURAUD));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATEREQUAL));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(0));
}

// 0x6C46E0
void CHeli::Post_SearchLightCone() {
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATECULLMODE,             RWRSTATE(rwCULLMODECULLBACK));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(2u));
}

// 0x6C4750
void CHeli::SpecialHeliPreRender() {
    // NOP
}

// 0x6C4760
CVector CHeli::FindSwatPositionRelativeToHeli(int32 swatNumber) {
    CVector result;
    ((void(__thiscall*)(CHeli*, CVector*, int32))0x6C4760)(this, &result, swatNumber);
    return result;

    switch ( swatNumber ) {
    case 0:
        return { -1.2f, -1.0f, -0.5f };
    case 1:
        return { 1.2f,  -1.0f, -0.5f };
    case 2:
        return { -1.2f, 1.0f,  -0.5f };
    case 3:
        return { 1.2f,  1.0f,  -0.5f };
    default:
        return { 0.0f,  0.0f,  0.0f  };
    }
}

// 0x6C4800
void CHeli::SwitchPoliceHelis(bool enable) {
    bPoliceHelisAllowed = enable;
}

// 0x6C58E0
void CHeli::SearchLightCone(int32 coronaIndex,
                            CVector origin, CVector target,
                            float targetRadius,
                            float power,
                            uint8 unknownFlag, uint8 drawShadow,
                            CVector* useless0, CVector* useless1, CVector* useless2,
                            bool a11, float baseRadius, float a13,float a14,float a15
) {
    ((void(__cdecl*)(int32, CVector, CVector, float, float, uint8, uint8, CVector*, CVector*, CVector*, bool, float, float, float, float))0x6C58E0)(coronaIndex, origin, target, targetRadius, power, unknownFlag, drawShadow, useless0, useless1, useless2, a11, baseRadius, a13, a14, a15);
}

// 0x6C6520
CHeli* CHeli::GenerateHeli(CPed* target, bool newsHeli) {
    return ((CHeli * (__cdecl*)(CPed*, bool))0x6C6520)(target, newsHeli);
}

// 0x6C6890
void CHeli::TestSniperCollision(CVector* origin, CVector* target) {
    CVector point = *target - *origin;

    if (point.z >= point.Magnitude() / 2.0f)
        return;

    for (auto& heli : pHelis) {
        if (!heli || heli->physicalFlags.bBulletProof)
            continue;

        const auto mat = (CMatrix*)heli->m_matrix;
        auto out = MultiplyMatrixWithVector(*mat, { -0.43f, 1.49f, 1.5f });
        if (CCollision::DistToLine(origin, target, &out) < 0.8f) {
            heli->m_fRotationBalance = (float)(rand() < pow(2, 14) - 1) * 0.1f - 0.05f; // 2^14 - 1 = 16383
            heli->BlowUpCar(FindPlayerPed(), false);
            heli->m_nNumSwatOccupants = 0;
        };
    }
}

// 0x6C69C0
bool CHeli::SendDownSwat() {
    return ((bool(__thiscall*)(CHeli*))0x6C69C0)(this);
}

// 0x6C79A0
void CHeli::UpdateHelis() {
    ((void(__cdecl*)())0x6C79A0)();
}

// 0x6C7C50
void CHeli::RenderAllHeliSearchLights() {
    for (auto& light : HeliSearchLights) {
        SearchLightCone(
            light.m_nCoronaIndex,
            light.m_vecOrigin,
            light.m_vecTarget,
            light.m_fTargetRadius,
            light.m_fPower,
            light.field_24,
            light.m_bDrawShadow,
            light.m_vecUseless,
            &light.m_vecUseless[1],
            &light.m_vecUseless[2],
            false,
            0.05f,
            0.0f,
            0.0f,
            1.0f
        );
    }
}

// 0x6C6D30
void CHeli::BlowUpCar(CEntity* damager, uint8 bHideExplosion) {
    plugin::CallMethod<0x6C6D30, CHeli*, CEntity*, uint8>(this, damager, bHideExplosion);
}

// 0x6C4530
void CHeli::Fix() {
    m_damageManager.ResetDamageStatus();
    SetupDamageAfterLoad();
}

// 0x6C4330
bool CHeli::BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) {
    return false;
}

// 0x6C4320
bool CHeli::SetUpWheelColModel(CColModel* wheelCol) {
    return false;
}

// 0x6C4830
void CHeli::ProcessControlInputs(uint8 playerNum) {
    plugin::CallMethod<0x6C4830, CHeli*, uint8>(this, playerNum);
}

// 0x6C4400
void CHeli::Render() {
    auto mi = CModelInfo::GetModelInfo(m_nModelIndex);
    m_nTimeTillWeNeedThisCar = CTimer::GetTimeInMS() + 3000;
    mi->AsVehicleModelInfoPtr()->SetVehicleColour(m_nPrimaryColor, m_nSecondaryColor, m_nTertiaryColor, m_nQuaternaryColor);

    auto staticRotor = m_aCarNodes[HELI_STATIC_ROTOR];
    RpAtomic* data = nullptr;
    if (staticRotor) {
        RwFrameForAllObjects(staticRotor, GetCurrentAtomicObjectCB, &data);
        if (data)
            CVehicle::SetComponentAtomicAlpha(data, 255);
    }

    auto staticRotor2 = m_aCarNodes[HELI_STATIC_ROTOR2];
    data = nullptr;
    if (staticRotor2) {
        RwFrameForAllObjects(staticRotor2, GetCurrentAtomicObjectCB, &data);
        if (data)
            CVehicle::SetComponentAtomicAlpha(data, 255);
    }

    auto movingRotor = m_aCarNodes[HELI_MOVING_ROTOR];
    data = nullptr;
    if (movingRotor) {
        RwFrameForAllObjects(movingRotor, GetCurrentAtomicObjectCB, &data);
        if (data)
            CVehicle::SetComponentAtomicAlpha(data, 0);
    }

    auto movingRotor2 = m_aCarNodes[HELI_MOVING_ROTOR2];
    data = nullptr;
    if (movingRotor2) {
        RwFrameForAllObjects(movingRotor2, GetCurrentAtomicObjectCB, &data);
        if (data)
            CVehicle::SetComponentAtomicAlpha(data, 0);
    }

    CEntity::Render(); // exactly CEntity
}

// 0x6C4550
void CHeli::SetupDamageAfterLoad() {
    vehicleFlags.bIsDamaged = false;
}

// 0x6C4E60
void CHeli::ProcessFlyingCarStuff() {
    plugin::CallMethod<0x6C4E60, CHeli*>(this);
}

// 0x6C5420
void CHeli::PreRender() {
    plugin::CallMethod<0x6C5420, CHeli*>(this);
}

// 0x6C7050
void CHeli::ProcessControl() {
    plugin::CallMethod<0x6C7050, CHeli*>(this);
}
