#include "StdInc.h"

void CBmx::InjectHooks() {
    RH_ScopedClass(CBmx);
    RH_ScopedCategory("Vehicle");

    RH_ScopedInstall(Constructor, 0x6BF820);
    RH_ScopedVirtualInstall(SetUpWheelColModel, 0x6BF9B0);
    RH_ScopedVirtualInstall(BurstTyre, 0x6BF9C0);
    RH_ScopedVirtualInstall(FindWheelWidth, 0x6C0550);
}

// 0x6BF820
CBmx::CBmx(int32 modelIndex, eVehicleCreatedBy createdBy) : CBike(modelIndex, createdBy) {
    auto mi = CModelInfo::GetModelInfo(modelIndex);
    m_nVehicleSubType = VEHICLE_TYPE_BMX;
    m_rideAnimData.m_nAnimGroup = CAnimManager::ms_aAnimBlocks[mi->GetAnimFileIndex()].animationStyle;
    if (m_rideAnimData.m_nAnimGroup < ANIM_GROUP_BMX || m_rideAnimData.m_nAnimGroup > ANIM_GROUP_CHOPPA) {
        m_rideAnimData.m_nAnimGroup = ANIM_GROUP_BMX;
    }

    m_fTimeStep = 0.0f;
    m_fBaseAnimLean = 0.0f;
    m_fRotPedalChainset = 0.0f;
    m_fRotPedalR = 0.0f;
    m_fRotPedalL = 0.0f;
    m_fDistanceBetweenWheels = 0.0f;
    m_bPedLeftHandFixed = false;
    m_bPedRightHandFixed = false;
    m_b831 = false;

    const auto Calc = [&](eBmxNodes node) -> float {
        RwMatrix matrix;
        RwFrame* wheelFront = m_aBikeNodes[node];
        matrix = *RwFrameGetMatrix(wheelFront);

        auto parent = RwFrameGetParent(wheelFront);
        if (parent) {
            do {
                RwMatrixTransform(&matrix, RwFrameGetMatrix(parent), rwCOMBINEPOSTCONCAT);
                parent = RwFrameGetParent(parent);
            } while (parent != wheelFront && parent);
        }
        return matrix.pos.y;
    };
    auto wheelFrontPosY = Calc(BMX_WHEEL_FRONT);
    auto wheelRearPosY  = Calc(BMX_WHEEL_REAR);

    m_fWheelsBalance = wheelFrontPosY - wheelRearPosY;
    m_f830 = wheelFrontPosY / m_fWheelsBalance;
}

// 0x6BF9D0
CBmx::~CBmx() {
    m_vehicleAudio.Terminate();
}

// 0x6BF9B0
bool CBmx::SetUpWheelColModel(CColModel* wheelCol) {
    return false;
}

// 0x6BF9C0
bool CBmx::BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) {
    return false;
}

// 0x6BFA30
void CBmx::ProcessControl() {
    plugin::CallMethod<0x6BFA30, CBmx*>(this);
}

// 0x6BFB50
void CBmx::ProcessDrivingAnims(CPed* driver, bool blend) {
    plugin::CallMethod<0x6BFB50, CBmx*, CPed*, uint8>(this, driver, blend);
}

// 0x6C0390
void CBmx::LaunchBunnyHopCB(CAnimBlendAssociation* assoc, void* data) {
    return plugin::Call<0x6C0390, CAnimBlendAssociation*, void*>(assoc, data);
    auto bmx = static_cast<CBmx*>(data);
    if ((bmx->m_aWheelTimer[0] > 0.0f || bmx->m_aWheelTimer[1] > 0.0f) &&
        (bmx->m_aWheelTimer[2] > 0.0f || bmx->m_aWheelTimer[3] > 0.0f)
    ) {
        auto power = std::min(bmx->m_fTimeStep / 25.0f, 1.0f) + 1.0f;
        if ((bmx->m_nType & 0xF8) == 0) {
            power *= CStats::GetFatAndMuscleModifier(STAT_MOD_6);
        }
        if (CCheat::IsActive(CHEAT_HUGE_BUNNY_HOP)) {
            power *= 5.0f;
        }
        auto f0 = 0.06f * bmx->m_fMass * power;
        bmx->ApplyMoveForce(f0 * bmx->m_matrix->GetUp());
        auto f1 = 0.01f * bmx->m_fTurnMass * power;
        bmx->ApplyTurnForce(f1 * bmx->m_matrix->GetUp(), bmx->m_matrix->GetForward());
    }
}

// 0x6C0500 | inlined | see 0x6C11F3
void CBmx::GetFrameOffset(float& a1, float& a2) {
    const auto d1 = m_aWheelFrontPosition - m_aWheelBaseFrontPosition;
    const auto d2 = m_aWheelRearPosition - m_aWheelBaseRearPosition;

    a1 = (1.0f - m_f830) * d1 + d2 * m_f830;
    a2 = std::atan2(d1 - d2, m_fWheelsBalance);
}

// 0x6C0550
float CBmx::FindWheelWidth(bool bRear) {
    return 0.07f;
}

// 0x6C0560
void CBmx::BlowUpCar(CEntity* damager, bool bHideExplosion) {
    // NOP
}

// 0x6C0590
void CBmx::ProcessBunnyHop() {
    plugin::CallMethod<0x6C0590, CBmx*>(this);
}

// 0x6C0810
void CBmx::PreRender() {
    plugin::CallMethod<0x6C0810, CBmx*>(this);
}

// 0x6C1470
bool CBmx::ProcessAI(uint32& extraHandlingFlags) {
    return plugin::CallMethodAndReturn<bool, 0x6C1470, CBmx*, uint32&>(this, extraHandlingFlags);
}
