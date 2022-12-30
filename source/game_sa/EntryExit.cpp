#include "StdInc.h"

#include "EntryExit.h"
#include "EntryExitManager.h"
#include "TaskComplexGotoDoorAndOpen.h"
#include "TaskSimpleUninterruptable.h"
#include "TaskComplexFacial.h"

bool& CEntryExit::ms_bWarping = *(bool*)0x96A7B8;
CObject*& CEntryExit::ms_pDoor = *(CObject**)0x96A7BC;
CEntryExit*& CEntryExit::ms_spawnPoint = *(CEntryExit**)0x96A7C0;

void CEntryExit::InjectHooks() {
    RH_ScopedClass(CEntryExit);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(GenerateAmbientPeds, 0x43E8B0);
    RH_ScopedInstall(GetEntryExitToDisplayNameOf, 0x43E650);
    RH_ScopedInstall(FindValidTeleportPoint, 0x43EAF0);
    RH_ScopedInstall(IsInArea, 0x43E460);
    RH_ScopedInstall(GetPositionRelativeToOutsideWorld, 0x43EA00);
    RH_ScopedInstall(TransitionStarted, 0x43FFD0);
    RH_ScopedInstall(TransitionFinished, 0x4404A0, { .reversed = false });
    RH_ScopedInstall(RequestObjectsInFrustum, 0x43E690);
    RH_ScopedInstall(RequestAmbientPeds, 0x43E6D0);
    RH_ScopedInstall(WarpGangWithPlayer, 0x43F1F0, { .reversed = false });
    RH_ScopedInstall(ProcessStealableObjects, 0x43E990, { .reversed = false });
}

// 0x43E8B0
void CEntryExit::GenerateAmbientPeds(const CVector& posn) {
    CPopulation::bInPoliceStation = false;
    if (CGame::currArea == eAreaCodes::AREA_CODE_NORMAL_WORLD) {
        CPopulation::NumberOfPedsInUseInterior = 0;
        float exitAngle = DegreesToRadians(ms_spawnPoint->m_fExitAngle);
        CPopulation::CreateWaitingCoppers(posn, exitAngle);
    } else {
        constexpr const char* PoliceStationEnExNames[]{ "POLICE1", "POLICE2", "POLICE3", "POLICE4" };
        CPopulation::bInPoliceStation = rng::any_of(PoliceStationEnExNames, [this](auto&& n) { return _stricmp(m_szName, n) == 0; });
        auto numPedsToSpawn = m_pLink ? m_pLink->m_nNumberOfPeds : m_nNumberOfPeds;
        CPopulation::NumberOfPedsInUseInterior = numPedsToSpawn;
        CPopulation::PopulateInterior(numPedsToSpawn, posn);
    }
}

// 0x43E650
CEntryExit* CEntryExit::GetEntryExitToDisplayNameOf() {
    if (ms_spawnPoint->m_nArea != eAreaCodes::AREA_CODE_NORMAL_WORLD && HasNameSet()) {
        if (m_nArea != eAreaCodes::AREA_CODE_NORMAL_WORLD) {
            // TODO: Probably inlined from `CEntryExitManager`
            if (   CEntryExitManager::ms_entryExitStackPosn > 1
                && CEntryExitManager::ms_entryExitStack[CEntryExitManager::ms_entryExitStackPosn - 1] == ms_spawnPoint
            ) {
                return CEntryExitManager::ms_entryExitStack[CEntryExitManager::ms_entryExitStackPosn];
            }
            return this;
        }
    }
    return nullptr;
}

// 0x43EA00
// TODO: `_asm` shouldn't be removed, because the caller `EntryExitManager::GetPositionRelativeToOutsideWorld`
// uses it as well (and without reserving `edx` it is going to crash)
void CEntryExit::GetPositionRelativeToOutsideWorld(CVector& outPos) {
    _asm { push edx };

    const auto enex = GetLinkedOrThis();
    if (enex->m_nArea != eAreaCodes::AREA_CODE_NORMAL_WORLD) {
        outPos += GetPosition() - enex->m_vecExitPos;
    }

    _asm { pop edx };
}

// Return center of entrance rect
CVector CEntryExit::GetPosition() const {
    return CVector{ m_recEntrance.GetCenter(), m_fEntranceZ };
}

CVector2D CEntryExit::GetPosition2D() const {
    return CVector2D{ m_recEntrance.GetCenter() };
}

// Returns the matrix with which `rectEntrance`'s points were calculated.
CMatrix CEntryExit::GetRectEntranceMatrix() const {
    CMatrix mat;
    mat.SetRotateZ(m_fEntranceAngle);
    mat.GetPosition() = GetPosition();
    return mat;
}

bool CEntryExit::IsVisibleByTime() const {
    return CClock::GetIsTimeInRange(m_nTimeOn, m_nTimeOff);
}

// Transforms a point into the entrance rect
CVector CEntryExit::TransformEntrancePoint(const CVector& point) const {
    return MultiplyMatrixWithVector(GetRectEntranceMatrix(), point - GetPosition());
}

// 0x43EAF0
void CEntryExit::FindValidTeleportPoint(CVector* outTeleportPoint) {
    const auto spawnPointExitPos = ms_spawnPoint->m_vecExitPos;

    if (!CWorld::TestSphereAgainstWorld(spawnPointExitPos, 0.35f, nullptr, true, true, true, true, true, false)) {
        return;
    }

    // Test 8 spheres around the spawn point, and return whichever
    // doesn't collide with the world and the line of sight between it and `outPoint` is clear
    for (auto r : { 1.25f, 2.f }) { // Test with 2 ranges
        constexpr auto NumTestPoints{ 8 };
        for (auto i = 0; i < NumTestPoints; i++) {
            const auto rot{ (float)i * TWO_PI / (float)NumTestPoints };
            const auto point = *outTeleportPoint + CVector{
                std::cos(rot) * r,
                std::sin(rot) * r,
                0.f
            };
            if (!CWorld::TestSphereAgainstWorld(point, 0.35f, nullptr, true, true, true, true, true, false)) {
                if (CWorld::GetIsLineOfSightClear(*outTeleportPoint, point, true, true, false, true, true, false, false)) {
                    *outTeleportPoint = point;
                    return;
                }
            }
        }
    }
}

bool CEntryExit::HasNameSet() const {
    return m_szName[0] != 0;
}

const CRect& CEntryExit::GetEntranceRect() const {
    return m_recEntrance;
}

// Return center of entrance rect
CVector CEntryExit::GetPosition() const {
    const auto& center = GetEntranceRect().GetCenter();
    return CVector{ center.x, center.y, m_fEntranceZ };
}

CVector2D CEntryExit::GetPosition2D() const {
    const auto& center = GetEntranceRect().GetCenter();
    return CVector2D{ center.x, center.y };
}

uint8 CEntryExit::GetMyOrLinkedArea() const {
    return m_pLink ? m_pLink->m_nArea : m_nArea;
}

// 0x43E460
bool CEntryExit::IsInArea(const CVector& position) {

    const auto CheckPointInEntranceRect = [this](const CVector& point) {
        if (m_recEntrance.IsPointInside(point)) {
            if (std::abs(point.z - m_fEntranceZ) < 1.0f) {
                return true;
            }
        }
        return false;
    };

    // It's quite common `m_fEntranceAngle` is 0, so I guess this is some kind of an optimization?
    return CheckPointInEntranceRect(m_fEntranceAngle == 0.f ? position : TransformEntrancePoint(position));
}

// 0x43FFD0
bool CEntryExit::TransitionStarted(CPed* ped) {
    if (   !m_nFlags.bEnableAccess
        || CEntryExitManager::ms_exitEnterState != 0
        || !IsVisibleByTime()
    ) {
        return false;
    }

    // If ped in vehicle check if enex accepts it
    if (ped->bInVehicle) {
        if (ped->m_pVehicle->m_pHandlingData->m_bIsBig) { // Move before the IsAuto or Bike check
            return false; // No big vehicles allowed :(
        }

        switch (ped->m_pVehicle->m_nVehicleType) {
        case eVehicleType::VEHICLE_TYPE_AUTOMOBILE: {
            if (!m_nFlags.bCarsAndAircraft) {
                return false;
            }
            break;
        }
        case eVehicleType::VEHICLE_TYPE_BIKE: {
            if (!m_nFlags.bBikesAndMotorcycles) {
                return false;
            }
            break;
        }
        default: { // Nothing else is disallowed - TODO: Allow uncomment this, I want my Rhino in CJ's house
            return false;
        }
        }
    } else if (m_nFlags.bDisableExit) {
        return false;
    }

    if (m_pLink) {
        ms_spawnPoint = m_pLink;
        m_pLink->m_pLink = this;
    } else {
        ms_spawnPoint = this;
    }

    const auto spawnPointExitToUs{ ms_spawnPoint->m_vecExitPos - GetPosition() };

    if (!ped->AsPlayer()->CanPlayerStartMission()) {
        return false;
    }

    m_nFlags.bEnteredWithoutExit = true;
    ms_pDoor = nullptr;

    ped->bCanExitCar = false;

    const auto AddPedScriptCommand = [ped](auto* task) {
        CEventScriptCommand scriptCmdEvent{ ePrimaryTasks::TASK_PRIMARY_PRIMARY, task, false };
        ped->GetEventGroup().Add(&scriptCmdEvent);
    };

    if ((m_nFlags.bUnknownPairing || m_nFlags.bFoodDateFlag) || ped->bInVehicle) {
        if (spawnPointExitToUs.Magnitude() > 10.f) {
            ms_bWarping = true;
        }
    } else {
        ms_bWarping = spawnPointExitToUs.Magnitude() > 10.f;

        const auto spawnPointExitToUsDir = Normalized(spawnPointExitToUs);

        const auto SetupFixedCamera = [this](CVector lookAtDir) {
            // 0x44031A
            auto fixedModePos = GetPosition() - lookAtDir * 3.f;
            fixedModePos.z += 1.f;
            TheCamera.SetCamPositionForFixedMode(&fixedModePos, {});
            TheCamera.TakeControlNoEntity(GetPosition() + lookAtDir, eSwitchType::JUMPCUT, 1);
        };


        if (const auto door = CEntryExitManager::FindNearestDoor(*this, 10.f)) {
            // 0x4401AB

            AddPedScriptCommand(new CTaskComplexGotoDoorAndOpen(door));
            ms_pDoor = door;

            SetupFixedCamera(Normalized(CVector{ CVector2D{door->GetPosition()} - GetPosition2D(), 0.f }));
        } else {
            // 0x440246
            if (ms_bWarping) {
                m_nFlags.bUnknownPairing = true;
                return true;
            }
            AddPedScriptCommand(new CTaskComplexGotoDoorAndOpen(GetPosition(), GetPosition() + spawnPointExitToUsDir * 4.f));
        }
    }

    CPad::GetPad()->bPlayerOnInteriorTransition = true;
    if (!ped->bInVehicle) {
        AddPedScriptCommand(new CTaskSimpleUninterruptable);
    }

    return true;
}

// 0x4404A0
bool CEntryExit::TransitionFinished(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x4404A0, CEntryExit*, CPed*>(this, ped);

    const auto spawnPos = ms_spawnPoint->m_vecExitPos;

    if (const auto entity = ped->GetEntityThatThisPedIsHolding()) {
        entity->m_nAreaCode = (eAreaCodes)ms_spawnPoint->m_nArea;
    }

    const auto DisplayEnExName = [this]{
        if (const auto enex = GetEntryExitToDisplayNameOf()) {
            CHud::SetZoneName(TheText.Get(enex->m_szName), true);
        }
    };

    if ((m_nFlags.bFoodDateFlag || m_nFlags.bUnknownPairing) || ped->bInVehicle) {
        switch (CEntryExitManager::ms_exitEnterState) {
        case EXIT_ENTER_STATE_0: { // 0x440ABE
            TheCamera.SetFadeColour(0, 0, 0);
            TheCamera.Fade(0.5f, eFadeFlag::FADE_IN);
            CEntryExitManager::ms_exitEnterState = EXIT_ENTER_STATE_2;

            if (const auto pedsGroup = CPedGroups::GetPedsGroup(ped)) {
                CEventGroupEvent groupEvent{ ped, new CEventLeaderEntryExit(ped) };
                pedsGroup->GetIntelligence().AddEvent(&groupEvent);
            }
            DisplayEnExName();
            return false;
        }
        case EXIT_ENTER_STATE_3: { // 0x440689
            CGame::currArea = CEntryExit::ms_spawnPoint->m_nArea;
            CEntryExitManager::ms_numVisibleEntities = 0;
            break;
        }
        case EXIT_ENTER_STATE_2: { // 0x440A92
            if (!TheCamera.GetFading()) {
                CEntryExitManager::ms_exitEnterState = EXIT_ENTER_STATE_3;
            }
            return false;
        }
        }
    } else { // 0x44051B
        CColStore::AddCollisionNeededAtPosn(spawnPos);
        CIplStore::AddIplsNeededAtPosn(spawnPos);

        if (ms_bWarping) { // 0x440534
            CRenderer::m_loadingPriority = false;
            CStreaming::AddModelsToRequestList(spawnPos, STREAMING_LOADING_SCENE);
            ms_spawnPoint->RequestObjectsInFrustum();
            ThePaths.SetPathsNeededAtPosition(spawnPos);
        }

        switch (CEntryExitManager::ms_exitEnterState) {
        case 0: { // 0x4405E8
            CEntryExitManager::SetAreaCodeForVisibleObjects();
            CEntryExitManager::ms_exitEnterState = EXIT_ENTER_STATE_1;
            CGame::currArea = ms_spawnPoint->m_nArea;

            if (const auto pedsGroup = CPedGroups::GetPedsGroup(ped)) {
                CEventGroupEvent groupEvent{ ped, new CEventLeaderEntryExit(ped) };
                pedsGroup->GetIntelligence().AddEvent(&groupEvent);
            }

            return false;
        }
        case 1: { // 0x4405A1
            if (const auto primaryTask = ped->GetTaskManager().GetTaskPrimary(ePrimaryTasks::TASK_PRIMARY_PRIMARY)) {
                if (primaryTask->GetTaskType() == eTaskType::TASK_COMPLEX_GOTO_DOOR_AND_OPEN) {
                    TheCamera.SetFadeColour(0, 0, 0);
                    TheCamera.Fade(1.f, eFadeFlag::FADE_IN);
                    CEntryExitManager::ms_exitEnterState = EXIT_ENTER_STATE_2;
                }
            }
            DisplayEnExName();
            return false;
        }
        case 2: { // 0x44057F
            if (!TheCamera.GetFading()) {
                CEntryExitManager::ms_exitEnterState = EXIT_ENTER_STATE_3;
                break;
            }
            return false;
            break;
        }
        }
    }

    // ms_exitEnterState == 3
    ped->m_nAreaCode = (eAreaCodes)CGame::currArea;
    if (ped->m_pVehicle && ped->bInVehicle) {
        ped->m_pVehicle->m_nAreaCode = (eAreaCodes)CGame::currArea;
    }
    ped->m_pEnex = CGame::CanSeeOutSideFromCurrArea() ? nullptr : this; // Inverted

    CEntryExitManager::AddEntryExitToStack(this);

    ped->bCanExitCar = true;
    CPad::GetPad()->bDisablePlayerEnterCar = false;

    CClothes::RebuildPlayerIfNeeded(ped->AsPlayer());

    if (m_nFlags.bFoodDateFlag) {
        m_nFlags.bEnteredWithoutExit = false;
        return true;
    }

    TheCamera.SetPosn(spawnPos);
    TheCamera.RestoreWithJumpCut();

    CAudioZones::Update(true, spawnPos);

    CWaterLevel::FindNearestWaterAndItsFlow();
    CGarages::CloseHideOutGaragesBeforeSave();
    CEntryExitManager::ResetAreaCodeForVisibleObjects();
    //g_interiorMan.SetEntryExitPtr(this); // TODO
    CPopulation::RemoveAllRandomPeds();
    RequestAmbientPeds();
    CStreaming::LoadAllRequestedModels(0);
    CTimer::Suspend();

    if (!CGame::CanSeeOutSideFromCurrArea()) {
        RwCameraSetFarClipPlane(TheCamera.m_pRwCamera, CTimeCycle::FindFarClipForCoors(spawnPos));
    }

    ms_spawnPoint->RequestObjectsInFrustum();
    CStreaming::LoadScene(spawnPos);
    CStreaming::LoadAllRequestedModels(0);
    GenerateAmbientPeds(spawnPos);

    // TODO
    // if (g_interiorMan.Update())
    // {
    //     CStreaming::SetLoadVehiclesInLoadScene(false);
    //     CStreaming::LoadScene(spawnPoint);
    //     CStreaming::SetLoadVehiclesInLoadScene(true);
    // }

    CTimer::Resume();

    CStreaming::ClearFlagForAll(STREAMING_LOADING_SCENE);

    if (ms_spawnPoint->m_nSkyColor) {
        CTimeCycle::StartExtraColour(ms_spawnPoint->m_nSkyColor - 1, 0);
    } else {
        CTimeCycle::StopExtraColour(0);
    }

    // TODO
    //CRubbish::SetVisibility((CRubbish*)(ms_spawnPoint->flags & 1));

    if (ped->bInVehicle) {
        CVector teleportPos = spawnPos;
        teleportPos.z -= 1.f;
        ped->m_pVehicle->Teleport(teleportPos, false);
        ped->m_pVehicle->SetHeading(DegreesToRadians(m_fExitAngle));
    } else {
        CVector teleportPos;
        FindValidTeleportPoint(&teleportPos);
        ped->Teleport(teleportPos, false);

        ped->m_fCurrentRotation = DegreesToRadians(m_fExitAngle);
        ped->m_fAimingRotation = ped->m_fCurrentRotation;
        ped->SetHeading(ped->m_fCurrentRotation);

        TheCamera.Fade(1.f, eFadeFlag::FADE_OUT);

        CTheScripts::ClearSpaceForMissionEntity(ped->GetPosition(), ped);

        if (m_nFlags.bRewardInterior) {
            CShopping::RemoveLoadedShop();
        } else {
            CShopping::LoadShop(m_szName);
            if (m_pLink) {
                m_pLink->m_nFlags.bRewardInterior = true;
            }
        }

        CPopulation::ManageAllPopulation();
        CTheScripts::Process();

        if (ms_spawnPoint->m_nFlags.bAcceptNpcGroup) {
            WarpGangWithPlayer(ped);
        }

        ProcessStealableObjects(ped);

        ms_spawnPoint->m_nFlags.bEnteredWithoutExit = false;
        if (ms_spawnPoint->m_nFlags.bDeleteEnex) {
            CEntryExitManager::DeleteOne(CEntryExitManager::mp_poolEntryExits->GetIndex(ms_spawnPoint));
        }

        // TODO
        auto task = static_cast<CTaskComplexFacial*>(ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_FACIAL_COMPLEX));
        task->StopAll();

        CGame::TidyUpMemory(true, true);
    }

    return 0; // TODO
}

// 0x43E6D0
void CEntryExit::RequestAmbientPeds() {
    if (!CGame::CanSeeOutSideFromCurrArea()) {
        CStreaming::RemoveDodgyPedsFromRandomSlots();
        return;
    }

    if (_stricmp("bar1", m_szName) == 0) {
        int32 peds[] = {
            MODEL_BFYRI, MODEL_OFYST, MODEL_WFYST, MODEL_WMYST,
            MODEL_BMYRI, MODEL_BMYST, MODEL_OMOST, MODEL_OMYST,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }

    if (_stricmp("strip2", m_szName) == 0) {
        int32 peds[] = {
            MODEL_SBFYSTR, MODEL_SWFYSTR, MODEL_INVALID, MODEL_INVALID,
            MODEL_INVALID, MODEL_INVALID, MODEL_INVALID, MODEL_INVALID,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }

    if (_stricmp("LAstrip", m_szName) == 0) {
        int32 peds[] = {
            MODEL_VWFYST1, MODEL_VBFYST2, MODEL_VHFYST3, MODEL_INVALID,
            MODEL_INVALID, MODEL_INVALID, MODEL_INVALID, MODEL_INVALID,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }

    if (_stricmp("MAFCAS", m_szName) == 0) {
        int32 peds[] = {
            MODEL_BFORI, MODEL_HFYRI, MODEL_OMYRI, MODEL_WMYRI,
            MODEL_OFYST, MODEL_VHMYELV, MODEL_WMOST, MODEL_BMORI,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }

    if (_stricmp("TRICAS", m_szName) == 0) {
        int32 peds[] = {
            MODEL_BFYRI, MODEL_BMYRI, MODEL_HFORI, MODEL_HMORI,
            MODEL_WMORI, MODEL_WFYRI, MODEL_OMOST, MODEL_VBMYELV,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }
}
// 0x43E690
void CEntryExit::RequestObjectsInFrustum() const {
    CRenderer::RequestObjectsInDirection(ms_spawnPoint->m_vecExitPos, m_fExitAngle, 0);
}

// 0x43F1F0
void CEntryExit::WarpGangWithPlayer(CPed* ped) {
    if (!CPedGroups::ScriptReferenceIndex[ped->AsPlayer()->GetGroupIdx()]) {
        return;
    }

    auto& playerGroup = ped->AsPlayer()->GetGroup();
    auto& membership = playerGroup.GetMembership();

    if (!membership.IsLeader(ped)) {
        return;
    }

    /*
    for (auto i = 0; i < 8 - 1; i++) {
        const auto member = membership.GetMember(i);
        if (!member || member == ped || )

        // TODO: Missing CTaskComplexFollowLeaderInFormation::ms_offsets
    }*/
}

// 0x43E990
void CEntryExit::ProcessStealableObjects(CPed* ped) {
    plugin::CallMethod<0x43E990, CEntryExit*, CPed*>(this, ped);
}
