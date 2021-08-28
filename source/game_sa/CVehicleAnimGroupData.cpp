#include "StdInc.h"

CVehicleAnimGroup(&CVehicleAnimGroupData::m_vehicleAnimGroups)[NUM_VEH_ANIM_GROUPS] = *(CVehicleAnimGroup(*)[NUM_VEH_ANIM_GROUPS])0xC1CDC0;

void CVehicleAnimGroup::InjectHooks()
{
    ReversibleHooks::Install("CVehicleAnimGroup", "InitAnimGroup", 0x5B9EB0, &CVehicleAnimGroup::InitAnimGroup);
    ReversibleHooks::Install("CVehicleAnimGroup", "CopyAnimGroup", 0x5B9E40, &CVehicleAnimGroup::CopyAnimGroup);
    ReversibleHooks::Install("CVehicleAnimGroup", "GetGroup", 0x6E3B00, &CVehicleAnimGroup::GetGroup);
    ReversibleHooks::Install("CVehicleAnimGroup", "ComputeCriticalBlendTime", 0x6E3C80, &CVehicleAnimGroup::ComputeCriticalBlendTime);
    ReversibleHooks::Install("CVehicleAnimGroup", "ComputeAnimDoorOffsets", 0x6E3D10, &CVehicleAnimGroup::ComputeAnimDoorOffsets);
}

CVehicleAnimGroup::CVehicleAnimGroup() : m_animFlags(), m_specialFlags(), m_generalTiming(), m_aInOutTiming()
{
    m_ucFirstGroup = 0;
    m_ucSecondGroup = 0;

    for (auto i = 0; i < 5; ++i)
        m_aVecDoorOffsets[i] = CVector(0.0F, 0.0F, 0.0F); //BUG? The 2 last entires in the array aren't initialized to 0
}

void CVehicleAnimGroup::InitAnimGroup(unsigned char firstGroup, unsigned char secondGroup, int animFlags,
                                      int animSpecialFlags, sVehAnimGroupGeneralTiming* generalTiming, sVehAnimGroupInOutTiming* startTiming,
                                      sVehAnimGroupInOutTiming* endTiming)
{
    m_ucFirstGroup = firstGroup;
    m_ucSecondGroup = secondGroup;
    m_animFlags.intValue = animFlags;
    m_specialFlags.intValue = animSpecialFlags;
    m_generalTiming = *generalTiming;
    GetInOutTiming(eInOutTiming::TIMING_START) = *startTiming;
    GetInOutTiming(eInOutTiming::TIMING_END) = *endTiming;
}

void CVehicleAnimGroup::CopyAnimGroup(CVehicleAnimGroup* src)
{
    m_ucFirstGroup = src->m_ucFirstGroup;
    m_ucSecondGroup = src->m_ucSecondGroup;
    m_animFlags = src->m_animFlags;
    m_specialFlags = src->m_specialFlags;
    m_generalTiming = src->m_generalTiming;
    GetInOutTiming(eInOutTiming::TIMING_START) = src->GetInOutTiming(eInOutTiming::TIMING_START);
    GetInOutTiming(eInOutTiming::TIMING_END) = src->GetInOutTiming(eInOutTiming::TIMING_END);
}

uint32 CVehicleAnimGroup::GetGroup(AnimationId animId)
{
    switch (animId)
    {
    case ANIM_ID_CAR_ALIGN_LHS:
    case ANIM_ID_CAR_ALIGN_RHS:
    case ANIM_ID_CAR_ALIGNHI_LHS:
    case ANIM_ID_CAR_ALIGNHI_RHS:
        return m_animFlags.bAlign ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_OPEN_LHS:
    case ANIM_ID_CAR_OPEN_RHS:
        return m_animFlags.bOpenFrontDoorsOnExit ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_OPEN_LHS_1:
    case ANIM_ID_CAR_OPEN_RHS_1:
        return m_animFlags.bOpenRearDoorsOnExit ? m_ucSecondGroup : m_ucFirstGroup;
        
    case ANIM_ID_CAR_GETIN_LHS_0:
    case ANIM_ID_CAR_GETIN_RHS_0:
    case ANIM_ID_CAR_GETIN_BIKE_FRONT:
        return m_animFlags.bCanEnterFrontDoors ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_GETIN_LHS_1:
    case ANIM_ID_CAR_GETIN_RHS_1:
        return m_animFlags.bCanEnterRearDoors ? m_ucSecondGroup : m_ucFirstGroup;
        
    case ANIM_ID_CAR_PULLOUT_LHS:
    case ANIM_ID_CAR_PULLOUT_RHS:
    case ANIM_ID_UNKNOWN_15:
        return m_animFlags.bCanPulloutPed ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_CLOSEDOOR_LHS_0:
    case ANIM_ID_CAR_CLOSEDOOR_RHS_0:
        return m_animFlags.bCloseFrontDoorWhenInside ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_CLOSEDOOR_LHS_1:
    case ANIM_ID_CAR_CLOSEDOOR_RHS_1:
        return m_animFlags.bCloseRearDoorWhenInside ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_SHUFFLE_RHS_0:
    case ANIM_ID_CAR_SHUFFLE_RHS_1:
        return m_animFlags.bShuffle ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_GETOUT_LHS_0:
    case ANIM_ID_CAR_GETOUT_RHS_0:
        return m_animFlags.bCanExitFrontDoors ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_GETOUT_LHS_1:
    case ANIM_ID_CAR_GETOUT_RHS_1:
        return m_animFlags.bCanExitRearDoors ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_JACKEDLHS:
    case ANIM_ID_CAR_JACKEDRHS:
        return m_animFlags.bPlayerCanBeJacked ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_CLOSE_LHS_0:
    case ANIM_ID_CAR_CLOSE_RHS_0:
        return m_animFlags.bCloseFrontDoorWhenOutside ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_CLOSE_LHS_1:
    case ANIM_ID_CAR_CLOSE_RHS_1:
        return m_animFlags.bCloseRearDoorWhenOutside ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_ROLLOUT_LHS:
    case ANIM_ID_CAR_ROLLOUT_RHS:
        return m_animFlags.bCanJumpOutOfVehicle ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_ROLLDOOR:
        return m_animFlags.bRollDownWindowOnDoorClose ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_FALLOUT_LHS:
    case ANIM_ID_CAR_FALLOUT_RHS:
        return m_animFlags.bPlayerCanFallOut ? m_ucSecondGroup : m_ucFirstGroup;

    case ANIM_ID_CAR_DOORLOCKED_LHS:
    case ANIM_ID_CAR_DOORLOCKED_RHS:
        return m_animFlags.bDoorLocked ? m_ucSecondGroup : m_ucFirstGroup;
    }

    assert(false); // Shouldn't ever get to this point
    return (m_animFlags.intValue & (1 << animId)) != 0 ? m_ucSecondGroup : m_ucFirstGroup;
}

float CVehicleAnimGroup::ComputeCriticalBlendTime(AnimationId animId)
{
    switch (animId)
    {
    case ANIM_ID_CAR_ALIGN_LHS:
    case ANIM_ID_CAR_ALIGN_RHS:
    case ANIM_ID_CAR_ALIGNHI_LHS:
    case ANIM_ID_CAR_ALIGNHI_RHS:
    case ANIM_ID_CAR_OPEN_LHS:
    case ANIM_ID_CAR_OPEN_RHS:
    case ANIM_ID_CAR_OPEN_LHS_1:
    case ANIM_ID_CAR_OPEN_RHS_1:
    case ANIM_ID_CAR_GETIN_LHS_0:
    case ANIM_ID_CAR_GETIN_RHS_0:
    case ANIM_ID_CAR_GETIN_LHS_1:
    case ANIM_ID_CAR_GETIN_RHS_1:
    case ANIM_ID_CAR_GETIN_BIKE_FRONT:
        return m_generalTiming.m_fGetInTime;

    case ANIM_ID_CAR_GETOUT_LHS_0:
    case ANIM_ID_CAR_GETOUT_RHS_0:
    case ANIM_ID_CAR_GETOUT_LHS_1:
    case ANIM_ID_CAR_GETOUT_RHS_1:
        return m_generalTiming.m_fGetOutTime;

    case ANIM_ID_CAR_JACKEDLHS:
    case ANIM_ID_CAR_JACKEDRHS:
        return m_generalTiming.m_fCarJackTime;

    case ANIM_ID_CAR_ROLLOUT_LHS:
    case ANIM_ID_CAR_ROLLOUT_RHS:
        return m_generalTiming.m_fJumpOutTime;

    case ANIM_ID_CAR_FALLOUT_LHS:
    case ANIM_ID_CAR_FALLOUT_RHS:
        return m_generalTiming.m_fFallOutTime;

    default:
        return 0.0F;
    }
}

CVector CVehicleAnimGroup::ComputeAnimDoorOffsets(eVehAnimDoorOffset doorId)
{
    // Memoize door offset if it's not set yet
    if (GetDoorOffset(doorId).SquaredMagnitude() == 0.0F)
    {
        AnimationId animId;
        switch (doorId)
        {
        case ENTER_FRONT:
            animId = ANIM_ID_CAR_GETIN_LHS_0;
            break;

        case ENTER_REAR:
            animId = ANIM_ID_CAR_GETIN_LHS_1;
            break;

        case ENTER_BIKE_FRONT:
            animId = ANIM_ID_CAR_GETIN_BIKE_FRONT;
            break;

        case EXIT_FRONT:
            animId = ANIM_ID_CAR_GETOUT_LHS_0;
            break;

        case EXIT_REAR:
            animId = ANIM_ID_CAR_GETOUT_LHS_1;
            break;

        case JACK_PED_LEFT:
            animId = ANIM_ID_CAR_JACKEDLHS;
            break;

        case JACK_PED_RIGHT:
            animId = ANIM_ID_CAR_JACKEDRHS;
            break;

        default:
            assert(false); // Shouldn't enter default case ever
            animId = static_cast<AnimationId>(doorId);
        }

        const auto groupId = CVehicleAnimGroup::GetGroup(animId);
        auto* pAnimAssoc = CAnimManager::GetAnimAssociation((AssocGroupId)groupId, animId);
        auto* pSequences = pAnimAssoc->m_pHierarchy->m_pSequences;
        CAnimManager::UncompressAnimation(pAnimAssoc->m_pHierarchy);
        if (pSequences->m_nFrameCount > 0)
        {
            const auto iFrame = pSequences->m_nFrameCount - 1;
            auto* pFrame = pSequences->GetUncompressedFrame(iFrame);
            GetDoorOffset(doorId) = pFrame->m_vecTranslation;
        }
    }

    return GetDoorOffset(doorId);
}

void CVehicleAnimGroupData::InjectHooks()
{
    ReversibleHooks::Install("CVehicleAnimGroupData", "GetInOutTimings", 0x645630, &CVehicleAnimGroupData::GetInOutTimings);
    ReversibleHooks::Install("CVehicleAnimGroupData", "GetGroupForAnim", 0x639FC0, &CVehicleAnimGroupData::GetGroupForAnim);
    ReversibleHooks::Install("CVehicleAnimGroupData", "GetAnimDoorOffset", 0x645600, &CVehicleAnimGroupData::GetAnimDoorOffset);
    ReversibleHooks::Install("CVehicleAnimGroupData", "UsesTruckDrivingAnims", 0x639FE0, &CVehicleAnimGroupData::UsesTruckDrivingAnims);
    ReversibleHooks::Install("CVehicleAnimGroupData", "UsesKartDrivingAnims", 0x6D09E0, &CVehicleAnimGroupData::UsesKartDrivingAnims);
}

// 0x645630
void CVehicleAnimGroupData::GetInOutTimings(AssocGroupId groupId, eInOutTimingMode mode, float* pfAnimStart, float* pfAnimEnd)
{
    auto& group = CVehicleAnimGroupData::GetVehicleAnimGroup(groupId);
    *pfAnimStart = group.GetInOutTiming(eInOutTiming::TIMING_START).m_afTimings[mode];
    *pfAnimEnd = group.GetInOutTiming(eInOutTiming::TIMING_END).m_afTimings[mode];
}

// 0x639FC0
int CVehicleAnimGroupData::GetGroupForAnim(AssocGroupId groupId, AnimationId animId)
{
    return CVehicleAnimGroupData::GetVehicleAnimGroup(groupId).GetGroup(animId);
}

// 0x645600
CVector CVehicleAnimGroupData::GetAnimDoorOffset(AssocGroupId groupId, eVehAnimDoorOffset doorId)
{
    return CVehicleAnimGroupData::GetVehicleAnimGroup(groupId).GetDoorOffset(doorId);
}

float CVehicleAnimGroupData::ComputeCriticalBlendTime(AssocGroupId groupId, AnimationId animId)
{
    // CVehicleAnimGroupData::GetVehicleAnimGroup(iGroup).GetGroup(animId)
    return CVehicleAnimGroupData::GetVehicleAnimGroup(groupId).ComputeCriticalBlendTime(animId);
}

// 0x639FE0
bool CVehicleAnimGroupData::UsesTruckDrivingAnims(AssocGroupId groupId)
{
    return CVehicleAnimGroupData::GetVehicleAnimGroup(groupId).m_specialFlags.bUseTruckDriveAnims;
}

// 0x6D09E0
bool CVehicleAnimGroupData::UsesKartDrivingAnims(AssocGroupId groupId)
{
    return CVehicleAnimGroupData::GetVehicleAnimGroup(groupId).m_specialFlags.bUseKartDriveAnims;
}

bool CVehicleAnimGroupData::UsesHovercraftDrivingAnims(AssocGroupId groupId)
{
    return CVehicleAnimGroupData::GetVehicleAnimGroup(groupId).m_specialFlags.bUseHovercraftDriveAnims;
}
