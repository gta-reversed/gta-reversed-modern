#include "StdInc.h"

#include "CCarGenerator.h"

#include "CTheCarGenerators.h"

bool& CCarGenerator::m_bHotdogVendorPositionOffsetInitialized = *reinterpret_cast<bool*>(0xC2B974);
CVector& CCarGenerator::m_HotdogVendorPositionOffset = *reinterpret_cast<CVector*>(0xC2B968);

void CCarGenerator::InjectHooks()
{
    ReversibleHooks::Install("CCarGenerator", "CheckForBlockage", 0x6F32E0, &CCarGenerator::CheckForBlockage);
    ReversibleHooks::Install("CCarGenerator", "CheckIfWithinRangeOfAnyPlayers", 0x6F2F40, &CCarGenerator::CheckIfWithinRangeOfAnyPlayers);
    ReversibleHooks::Install("CCarGenerator", "DoInternalProcessing", 0x6F34D0, &CCarGenerator::DoInternalProcessing);
    ReversibleHooks::Install("CCarGenerator", "Process", 0x6F3E90, &CCarGenerator::Process);
    ReversibleHooks::Install("CCarGenerator", "Setup", 0x6F2E50, &CCarGenerator::Setup);
    ReversibleHooks::Install("CCarGenerator", "SwitchOff", 0x6F2E30, &CCarGenerator::SwitchOff);
    ReversibleHooks::Install("CCarGenerator", "SwitchOn", 0x6F32C0, &CCarGenerator::SwitchOn);
    ReversibleHooks::Install("CCarGenerator", "CalcNextGen", 0x6F2E40, &CCarGenerator::CalcNextGen);
}

// 0x6F32E0
bool CCarGenerator::CheckForBlockage(int modelId)
{
    auto pCarColModel = CModelInfo::GetModelInfo(modelId)->GetColModel();
    float radius = pCarColModel ? pCarColModel->GetBoundRadius() : 2.0f;

    short entityCount;
    CEntity* pObjectList[8];

    CVector posn = UncompressLargeVector(m_vecPosn);
    CWorld::FindObjectsKindaColliding(posn, radius, true, &entityCount, 8, pObjectList, false, true, true, false, false);

    for (int i = 0; i < entityCount; i++)
    {
        auto pEntityColModel = CModelInfo::GetModelInfo(pObjectList[i]->m_nModelIndex)->GetColModel();

        if (pCarColModel)
        {
            if (pObjectList[i]->GetPosition().z + pEntityColModel->GetBoundingBox().m_vecMax.z + 1.0f > posn.z + pCarColModel->GetBoundingBox().m_vecMin.z &&
                pObjectList[i]->GetPosition().z + pEntityColModel->GetBoundingBox().m_vecMin.z - 1.0f < posn.z + pCarColModel->GetBoundingBox().m_vecMax.z)
            {
                bWaitUntilFarFromPlayer = true;
                return true;
            }
        }
        else
        {
            if (pObjectList[i]->GetPosition().z + pEntityColModel->GetBoundingBox().m_vecMax.z + 1.0f > posn.z - 1.0f &&
                pObjectList[i]->GetPosition().z + pEntityColModel->GetBoundingBox().m_vecMin.z - 1.0f < posn.z + 1.0f)
            {
                bWaitUntilFarFromPlayer = true;
                return true;
            }
        }
    }

    return false;
}

// 0x6F2F40
bool CCarGenerator::CheckIfWithinRangeOfAnyPlayers()
{
    bool bVisible = false;
    CVector relPosn = FindPlayerCentreOfWorld(CWorld::PlayerInFocus) - UncompressLargeVector(m_vecPosn);
    if (fabs(relPosn.z) > 50.0f)
        return false;

    if (m_nModelId > 0 &&
        CModelInfo::GetModelInfo(m_nModelId)->AsVehicleModelInfoPtr()->IsBoat() &&
        relPosn.Magnitude2D() < TheCamera.m_fGenerationDistMultiplier * 240.0f)
    {
        CVector origin = UncompressLargeVector(m_vecPosn);
        if (TheCamera.IsSphereVisible(origin, 0.0f) && !COcclusion::IsPositionOccluded(origin, 0.0f))
        {
            bVisible = true;
        }
    }

    if (relPosn.Magnitude2D() >= TheCamera.m_fGenerationDistMultiplier * 160.0f && !bVisible)
    {
        bWaitUntilFarFromPlayer = false;
        return false;
    }

    if (CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter)
        return true;

    if (bWaitUntilFarFromPlayer)
        return false;

    float posnZ = UncompressLargeVector(m_vecPosn).z;
    if ((CGame::currArea == AREA_CODE_NORMAL_WORLD && posnZ < 950.0f || CGame::currArea != AREA_CODE_NORMAL_WORLD && posnZ >= 950.0f)
        && (relPosn.Magnitude2D() >= TheCamera.m_fGenerationDistMultiplier * 160.0f - 20.0f || bHighPriority)
        && DotProduct2D(FindPlayerSpeed(-1), relPosn) <= 0.0f
    ) {
        return true;
    }

    return false;
}

// 0x6F34D0
void CCarGenerator::DoInternalProcessing()
{
    int actualModelId;
    CVehicle* pVeh;
    float baseZ;
    CColPoint colPoint;
    CEntity* pEntity;
    tCarGenPlateText plate{};
    int tractorDriverPedType;

    bool nightTime = CClock::ms_nGameClockHours > 21 || CClock::ms_nGameClockHours < 7;
    if (!bIgnorePopulationLimit
        && (nightTime && CCarCtrl::NumParkedCars >= 10 || !nightTime && CCarCtrl::NumParkedCars >= 5)
    )
        return;

    if (m_nModelId >= 0)
    {
        if (CheckForBlockage(m_nModelId))
        {
            m_nNextGenTime += 4;
            return;
        }

        CStreaming::RequestModel(m_nModelId, STREAMING_KEEP_IN_MEMORY);
        actualModelId = m_nModelId;
        if (m_nModelId == MODEL_HOTDOG)
            CStreaming::RequestModel(MODEL_BMOCHIL, STREAMING_KEEP_IN_MEMORY);
    }
    else
    {
        if (m_nModelId == MODEL_INVALID || CStreaming::ms_aInfoForModel[-m_nModelId].m_nLoadState != LOADSTATE_LOADED)
        {
            CTheZones::GetZoneInfo(FindPlayerCoors(-1), nullptr);
            actualModelId = CPopulation::m_AppropriateLoadedCars.PickRandomCar(true, true);

            if (actualModelId < 0)
                return;

            auto pModelInfo = CModelInfo::GetModelInfo(actualModelId)->AsVehicleModelInfoPtr();
            if (pModelInfo->IsBoat())
                return;

            if (pModelInfo->GetBoundingBox()->GetLength() > 8.0f)
                return;

            m_nModelId = -actualModelId;
            m_nPrimaryColor = -1;
            m_nSecondaryColor = -1;
        }
        else
        {
            actualModelId = -m_nModelId;
        }

        if (CheckForBlockage(actualModelId))
        {
            m_nNextGenTime += 4;
            return;
        }
    }

    if (CStreaming::ms_aInfoForModel[actualModelId].m_nLoadState != LOADSTATE_LOADED ||
        actualModelId == MODEL_HOTDOG &&
        m_nModelId == MODEL_HOTDOG &&
        CStreaming::ms_aInfoForModel[MODEL_BMOCHIL].m_nLoadState != LOADSTATE_LOADED
    )
        return;

    if (CModelInfo::IsBoatModel(actualModelId) ||
        actualModelId == MODEL_LEVIATHN ||
        actualModelId == MODEL_SEASPAR ||
        actualModelId == MODEL_SKIMMER)
    {
        switch (CModelInfo::GetModelInfo(actualModelId)->AsVehicleModelInfoPtr()->m_nVehicleType)
        {
        case VEHICLE_HELI:
            pVeh = new CHeli(actualModelId, PARKED_VEHICLE);
            break;
        case VEHICLE_PLANE:
            pVeh = new CPlane(actualModelId, PARKED_VEHICLE);
            break;
        case VEHICLE_BOAT:
            pVeh = new CBoat(actualModelId, PARKED_VEHICLE);
            break;
        }

        CVector posn = UncompressLargeVector(m_vecPosn);
        baseZ = posn.z;
        if (baseZ <= -100.0f)
            baseZ = CWorld::FindGroundZForCoord(posn.x, posn.y);
        pVeh->m_nExtendedRemovalRange = 255;
    }
    else
    {
        CVector posn = UncompressLargeVector(m_vecPosn);
        if (posn.z > -100.0f)
            posn.z += 1.0f;
        else
            posn.z = 1000.0f;

        if (!CWorld::ProcessVerticalLine(posn, -1000.0f, colPoint, pEntity, true, false, false, false, false, false, nullptr))
            return;

        baseZ = colPoint.m_vecPoint.z;
        plate.m_nCarGenId = CTheCarGenerators::GetIndex(this);
        CTheCarGenerators::m_SpecialPlateHandler.Find(plate.m_nCarGenId, plate.m_szPlateText);
        if (plate.m_szPlateText[0])
        {
            auto pModel = CModelInfo::GetModelInfo(actualModelId)->AsVehicleModelInfoPtr();
            if (pModel->m_pPlateMaterial)
                pModel->SetCustomCarPlateText(plate.m_szPlateText);
        }

        switch (CModelInfo::GetModelInfo(actualModelId)->AsVehicleModelInfoPtr()->m_nVehicleType)
        {
        case VEHICLE_MTRUCK:
            pVeh = new CMonsterTruck(actualModelId, PARKED_VEHICLE);
            break;
        case VEHICLE_QUAD:
            pVeh = new CQuadBike(actualModelId, PARKED_VEHICLE);
            break;
        case VEHICLE_HELI:
            pVeh = new CHeli(actualModelId, PARKED_VEHICLE);
            break;
        case VEHICLE_PLANE:
            pVeh = new CPlane(actualModelId, PARKED_VEHICLE);
            break;
        case VEHICLE_TRAIN:
            pVeh = new CTrain(actualModelId, PARKED_VEHICLE);
            break;
        case VEHICLE_BIKE:
            pVeh = new CBike(actualModelId, PARKED_VEHICLE);
            pVeh->AsBike()->damageFlags.bDamageFlag4 = true;
            break;
        case VEHICLE_BMX:
            pVeh = new CBmx(actualModelId, PARKED_VEHICLE);
            pVeh->AsBike()->damageFlags.bDamageFlag4 = true;
            break;
        case VEHICLE_TRAILER:
            pVeh = new CTrailer(actualModelId, PARKED_VEHICLE);
            break;
        default:
            pVeh = new CAutomobile(actualModelId, PARKED_VEHICLE, true);
            break;
        }

        pVeh->GetDistanceFromCentreOfMassToBaseOfModel();
        pVeh->vehicleFlags.bLightsOn = false;
        pVeh->m_nOverrideLights = NO_CAR_LIGHT_OVERRIDE;
        pVeh->SetCollisionLighting(colPoint.m_nLightingB);
    }

    pVeh->SetIsStatic(false);
    pVeh->vehicleFlags.bEngineOn = false;
    CVector posn = UncompressLargeVector(m_vecPosn);
    posn.z = pVeh->GetDistanceFromCentreOfMassToBaseOfModel() + baseZ;
    pVeh->SetPosn(posn);
    pVeh->SetOrientation(0.0f, 0.0f, m_nAngle * (TWO_PI / 256));
    pVeh->m_nStatus = eEntityStatus::STATUS_ABANDONED;
    pVeh->m_nDoorLock = eCarLock::CARLOCK_UNLOCKED;
    pVeh->vehicleFlags.bHasBeenOwnedByPlayer = bPlayerHasAlreadyOwnedCar;
    tractorDriverPedType = -1;

    if (!nightTime &&
        (pVeh->m_nModelIndex == MODEL_TRACTOR || pVeh->m_nModelIndex == MODEL_COMBINE))
    {
        CVector vehPosn = pVeh->GetPosition();
        CNodeAddress pathLink;
        ThePaths.FindNodeClosestToCoors(&pathLink, vehPosn.x, vehPosn.y, vehPosn.z, 0, 20.0F, 0, 0, 0, 0, 1);
        if (pathLink.m_wAreaId != -1 || pathLink.m_wNodeId != -1)
        {
            CPathNode& pathNode = ThePaths.m_pPathNodes[pathLink.m_wAreaId][pathLink.m_wNodeId];
            if (pathNode.m_nNumLinks != 0)
            {
                CNodeAddress baseLink = ThePaths.m_pNodeLinks[pathLink.m_wAreaId][pathNode.m_wBaseLinkId];
                if (ThePaths.m_pPathNodes[baseLink.m_wAreaId])
                {
                    pVeh->SetVehicleCreatedBy(RANDOM_VEHICLE);
                    pVeh->m_autoPilot.m_currentAddress = pathLink;
                    pVeh->m_autoPilot.m_nCruiseSpeed = 7;
                    pVeh->m_autoPilot.m_nCarMission = eCarMission::MISSION_CRUISE;
                    pVeh->m_autoPilot.m_startingRouteNode = baseLink;
                    pVeh->m_nStatus = eEntityStatus::STATUS_PHYSICS;
                    pVeh->vehicleFlags.bNeverUseSmallerRemovalRange = true;
                    bWaitUntilFarFromPlayer = true;
                    tractorDriverPedType = PED_TYPE_CIVMALE;
                }
            }
        }
    }

    CWorld::Add(pVeh);
    if (tractorDriverPedType != -1)
        CCarCtrl::SetUpDriverAndPassengersForVehicle(pVeh, tractorDriverPedType, 0, false, false, 99);

    if (actualModelId == MODEL_HOTDOG && m_nModelId == MODEL_HOTDOG && CStreaming::ms_aInfoForModel[MODEL_BMOCHIL].m_nLoadState == LOADSTATE_LOADED)
    {
        CPed* ped = CPopulation::AddPed(ePedType::PED_TYPE_CIVMALE, MODEL_BMOCHIL, pVeh->GetPosition() - pVeh->GetRight() * 3.0f, false);
        if (ped)
        {
            if (!m_bHotdogVendorPositionOffsetInitialized)
            {
                m_bHotdogVendorPositionOffsetInitialized = true;
                m_HotdogVendorPositionOffset.Set(0.0f, 0.0f, 0.6f);
            }
            ped->AttachPedToEntity(pVeh, m_HotdogVendorPositionOffset, 3, 0.0f, eWeaponType::WEAPON_UNARMED);
            CTheScripts::ScriptsForBrains.CheckIfNewEntityNeedsScript(ped, 0, nullptr);
        }
    }

    if (CGeneral::GetRandomNumberInRange(0, 100) < m_nAlarmChance)
        pVeh->m_nAlarmState = -1;

    if (CGeneral::GetRandomNumberInRange(0, 100) < m_nDoorLockChance)
        pVeh->m_nDoorLock = eCarLock::CARLOCK_LOCKED;

    if (m_nPrimaryColor != -1 && m_nSecondaryColor != -1)
    {
        pVeh->m_nPrimaryColor = m_nPrimaryColor;
        pVeh->m_nSecondaryColor = m_nSecondaryColor;
    }
    else if (m_nModelId < -1)
    {
        m_nPrimaryColor = pVeh->m_nPrimaryColor;
        m_nSecondaryColor = pVeh->m_nSecondaryColor;
    }
    CVisibilityPlugins::SetClumpAlpha(pVeh->m_pRwClump, 0);
    m_nVehicleHandle = CPools::ms_pVehiclePool->GetRef(pVeh);
    m_nNextGenTime = CalcNextGen();
}

// 0x6F3E90
void CCarGenerator::Process()
{
    if (m_nVehicleHandle == -1 &&
        (
            CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter
            || m_nNextGenTime <= CTimer::m_snTimeInMilliseconds
        )
            && m_nGenerateCount != 0
            && CheckIfWithinRangeOfAnyPlayers()
    ) {
        DoInternalProcessing();
    }

    if (m_nVehicleHandle != -1)
    {
        auto pVeh = CPools::ms_pVehiclePool->GetAtRef(m_nVehicleHandle);
        if (!pVeh)
            m_nVehicleHandle = -1;
        else if (pVeh->m_nStatus == eEntityStatus::STATUS_PLAYER)
        {
            m_nNextGenTime += 60000;
            m_nVehicleHandle = -1;
            bWaitUntilFarFromPlayer = true;
            pVeh->m_nExtendedRemovalRange = 0;
            if (m_nModelId < 0)
                m_nModelId = -1;
        }
    }
}

// 0x6F2E50
void CCarGenerator::Setup(const CVector& posn, float angle, int modelId, short color1, short color2, uint8_t bForceSpawn,
                          uint8_t alarmChance, uint8_t doorLockChance, uint16_t minDelay, uint16_t maxDelay,
                          uint8_t iplId, bool ignorePopulationLimit)
{
    constexpr float magic = 256.0f / 360.0f; // 0x8722E8 original expression 128.0f / 180.0f

    m_vecPosn = CompressLargeVector(posn);
    m_nAngle = (char)(angle * magic);
    m_nModelId = modelId;
    m_nPrimaryColor = (uint8_t)(color1);
    m_nSecondaryColor = (uint8_t)(color2);;

    bWaitUntilFarFromPlayer = false;
    bIgnorePopulationLimit = ignorePopulationLimit;
    bHighPriority = bForceSpawn;
    bPlayerHasAlreadyOwnedCar = false;

    m_nAlarmChance = alarmChance;
    m_nDoorLockChance = doorLockChance;
    m_nMinDelay = minDelay;
    m_nMaxDelay = maxDelay;
    m_nIplId = iplId;

    m_nVehicleHandle = -1;
    m_nNextGenTime = CTimer::m_snTimeInMilliseconds + 1;
    m_nGenerateCount = 0;
    m_bIsUsed = true;
}

// 0x6F2E30
void CCarGenerator::SwitchOff()
{
    m_nGenerateCount = 0;
}

// 0x6F32C0
void CCarGenerator::SwitchOn()
{
    m_nGenerateCount = -1;
    m_nNextGenTime = CalcNextGen();
}

// 0x6F2E40
unsigned int CCarGenerator::CalcNextGen()
{
    return CTimer::m_snTimeInMilliseconds + 4;
}
