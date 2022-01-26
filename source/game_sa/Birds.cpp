#include "StdInc.h"

bool& CBirds::bHasBirdBeenShot = *(bool*)0xC6A8A0;
uint32& CBirds::uiNumberOfBirds = *(uint32*)0xC6A8A4;
CBird* CBirds::aBirds = (CBird*)0xC6A8B0;
CVector& CBirds::vecBirdShotAt = *(CVector*)0xC6AA48;

float* CBirds::faCreationCoorsX = (float*)0x8D5250; // Size: 6
float* CBirds::faCreationCoorsY = (float*)0x8D5268; // Size: 6
float* CBirds::faCreationCoorsZ = (float*)0x8D5280; // Size: 6
float* CBirds::faRenderCoorsU = (float*)0x8D52B8; // Size: 8
float* CBirds::faRenderCoorsV = (float*)0x8D5298; // Size: 8
float* CBirds::faRenderPosY = (float*)0x8D52D8; // Size: 8
uint32* CBirds::auRenderIndices = (uint32*)0x8D52F8; // Size: 30

void CBirds::InjectHooks()
{
    RH_ScopedClass(CBirds);
    RH_ScopedCategoryRoot();

    RH_ScopedInstall(Init, 0x711EC0);
    RH_ScopedInstall(Shutdown, 0x712300);
    RH_ScopedInstall(HandleGunShot, 0x712E40);
    RH_ScopedInstall(Update, 0x712330);
    RH_ScopedInstall(CreateNumberOfBirds, 0x711EF0);
    RH_ScopedInstall(Render, 0x712810);
}

// 0x711EC0
void CBirds::Init()
{
    for (int32 i = 0; i < MAX_BIRDS; ++i) {
        auto& bird = aBirds[i];
        bird.m_bCreated = false;
    }
    uiNumberOfBirds = 0;
    bHasBirdBeenShot = false;
}

// 0x711EF0
void CBirds::CreateNumberOfBirds(CVector vecStartPos, CVector vecTargetPos, int32 iBirdCount, eBirdsBiome eBiome, bool bCheckObstacles)
{
    float fMaxDistance;

    switch (eBiome) {
    case eBirdsBiome::BIOME_WATER:
        fMaxDistance = 45.0F;
        break;
    case eBirdsBiome::BIOME_DESERT:
        fMaxDistance = 80.0F;
        break;
    case eBirdsBiome::BIOME_NORMAL:
    default:
        fMaxDistance = 40.0F;
        break;
    }

    if (iBirdCount <= 0)
        return;

    for (int32 i = 0; i < iBirdCount; ++i) {
        int32 iFreeBirdIndex = 0;
        while (iFreeBirdIndex < MAX_BIRDS) {
            auto& bird = aBirds[iFreeBirdIndex];
            if (!bird.m_bCreated)
                break;

            ++iFreeBirdIndex;
        }

        if (iFreeBirdIndex >= MAX_BIRDS)
            return;

        auto& bird = aBirds[iFreeBirdIndex];
        bird.m_vecPosn = vecStartPos;

        auto vecBirdDirection = vecTargetPos - bird.m_vecPosn;
        vecBirdDirection.Normalise();
        auto vecCheckPos = bird.m_vecPosn + (vecBirdDirection * fMaxDistance * 2.4F);
        if (bCheckObstacles && !CWorld::GetIsLineOfSightClear(bird.m_vecPosn, vecCheckPos, true, false, false, false, false, false, false))
            continue;

        auto fAngle = atan2(vecBirdDirection.x, vecBirdDirection.y);
        uint32 iSpeedRandFactor = rand() % 31;

        ++uiNumberOfBirds;
        bird.m_bCreated = true;
        bird.m_fMaxBirdDistance = fMaxDistance;
        bird.m_eBirdMode = eBirdMode::BIRD_DRAW_UPDATE;
        bird.m_nUpdateAfterMS = 0;
        bird.m_bMustDoCurves = false;
        bird.m_fAngle = fAngle;
        bird.m_vecPosn.x += faCreationCoorsX[i];
        bird.m_vecPosn.y += faCreationCoorsY[i];
        bird.m_vecPosn.z += faCreationCoorsZ[i];

        float fSpeedMult;
        switch (eBiome) {
        case eBirdsBiome::BIOME_WATER:
            fSpeedMult = (float)iSpeedRandFactor * 0.02F + 4.0F;    // [4.0 : 4.6]
            bird.m_BodyColor.Set(rand() % 64 + 80);                 // [80 : 143]
            bird.m_WingsColor.Set(rand() % 64 - 76);                // [166 : 242]
            bird.m_fSize = CGeneral::GetRandomNumberInRange(0.8F, 1.2F);
            bird.m_nWingStillness = 1000 - 12 * iSpeedRandFactor;  // [640 : 1000]
            break;
        case eBirdsBiome::BIOME_DESERT:
            fSpeedMult = (float)iSpeedRandFactor * 0.02F + 3.0F;    // [3.0 : 3.6]
            bird.m_BodyColor.Set(30, 15, 10);
            bird.m_WingsColor.Set(80, 15, 10);
            bird.m_fSize = CGeneral::GetRandomNumberInRange(2.0F, 2.5F);
            bird.m_nWingStillness = 12 * (125 - iSpeedRandFactor); // [1140 : 1500]
            if (rand() & 4)
                bird.m_nWingStillness = 1000000; // Not moving it's wings

            if (rand() & 8)
                bird.m_bMustDoCurves = true;

            break;
        case eBirdsBiome::BIOME_NORMAL:
        default:
            fSpeedMult = (float)iSpeedRandFactor * 0.02F + 5.0F;    // [5.0 : 5.6]
            bird.m_BodyColor.Set(rand() % 128 + 128);               // [127 : 255]
            bird.m_WingsColor.Set(rand() % 128 + 128);              // [127 : 255]
            bird.m_fSize = CGeneral::GetRandomNumberInRange(0.5F, 0.6F);
            bird.m_nWingStillness = 500 - 6 * iSpeedRandFactor;    // [320 : 500]
            break;
        }

        bird.m_vecTargetVelocity = vecBirdDirection * fSpeedMult;
        bird.m_vecCurrentVelocity = bird.m_vecTargetVelocity;
    }
}

// 0x712300
void CBirds::Shutdown()
{
    for (int32 i = 0; i < MAX_BIRDS; ++i) {
        auto& bird = aBirds[i];
        if (bird.m_bCreated)
            bird.m_bCreated = false;
    }
    uiNumberOfBirds = 0;
}

// 0x712330
void CBirds::Update()
{
    const auto& vecCamPos = TheCamera.GetPosition();

    if (!CGame::currArea
        && uiNumberOfBirds < MAX_BIRDS
        && CClock::ClockHoursInRange(5, 22)
        && (CTimer::GetFrameCounter() % 512) == MAX_BIRDS) {

        auto iNumBirdsToCreate = (uint32)CGeneral::GetRandomNumberInRange(1, MAX_BIRDS + 1 - uiNumberOfBirds);
        eBirdsBiome eBiome = eBirdsBiome::BIOME_WATER;

        if (TheCamera.m_fDistanceToWater > 30.0F) {
            if (CWeather::WeatherRegion == eWeatherRegion::WEATHER_REGION_DESERT) {
                eBiome = eBirdsBiome::BIOME_DESERT;
                iNumBirdsToCreate = std::min(iNumBirdsToCreate, uiNumberOfBirds);
            }
            else {
                eBiome = eBirdsBiome::BIOME_NORMAL;
            }
        }

        if (iNumBirdsToCreate > 0) {
            rand(); // Called 2 times for some reason
            rand();

            float fFlightHeight;
            float fSpawnDistance;

            switch (eBiome) {
            case eBirdsBiome::BIOME_WATER:
                fFlightHeight = CGeneral::GetRandomNumberInRange(4.0F, 13.0F);
                fSpawnDistance = 45.0F;
                break;
            case eBirdsBiome::BIOME_DESERT:
                fFlightHeight = CGeneral::GetRandomNumberInRange(15.0F, 25.0F);
                fSpawnDistance = 80.0F;
                break;
            case eBirdsBiome::BIOME_NORMAL:
            default:
                fFlightHeight = CGeneral::GetRandomNumberInRange(2.0F, 10.0F);
                fSpawnDistance = 40.0F;
                break;
            }

            if (fFlightHeight > 5.0F) {
                float fBirdSpawnZ = fFlightHeight + vecCamPos.z;
                float fSpawnAngleCamRelative;

                if (rand() % 2)
                    fSpawnAngleCamRelative = (float)(uint8)(rand() % 256) * 0.024531251F; // [0 : 255] mapped to [0 : 2π]
                else {
                    auto vecForward = TheCamera.m_mCameraMatrix.GetForward();
                    vecForward.z = 0.0F;
                    if (vecForward.x == 0.0F)
                        vecForward.x = 0.01F;

                    vecForward.Normalise();
                    uint8 cRand = (uint8)(rand() % 256) - 128;
                    fSpawnAngleCamRelative = ((float)cRand) / 256.0F + atan2(vecForward.x, vecForward.y); // [0 : 1] + atan2(...)
                }
                    
                auto vecBirdSpawnPos = CVector(
                    sin(fSpawnAngleCamRelative) * fSpawnDistance + vecCamPos.x,
                    cos(fSpawnAngleCamRelative) * fSpawnDistance + vecCamPos.y,
                    fBirdSpawnZ
                );

                float fWaterLevel;
                if (!CWaterLevel::GetWaterLevelNoWaves(vecBirdSpawnPos.x, vecBirdSpawnPos.y, vecBirdSpawnPos.z, &fWaterLevel, nullptr, nullptr) || fWaterLevel + 4.0F < fBirdSpawnZ) {
                    auto vecForward = TheCamera.m_mCameraMatrix.GetForward();
                    vecForward.z = 0.0F;
                    vecForward.Normalise();

                    auto vecFlightTargetPos = vecCamPos + (vecForward * 8.0F);
                    vecFlightTargetPos.z = fBirdSpawnZ;

                    CreateNumberOfBirds(vecBirdSpawnPos, vecFlightTargetPos, iNumBirdsToCreate, eBiome, true);
                }
            }
        }
    }

    int32 iBirdIndex = CTimer::GetFrameCounter() % MAX_BIRDS;
    auto& checkedBird = aBirds[iBirdIndex];
    if (checkedBird.m_bCreated && DistanceBetweenPoints2D(CVector2D(checkedBird.m_vecPosn), CVector2D(vecCamPos)) > checkedBird.m_fMaxBirdDistance)
    {
        checkedBird.m_bCreated = false;
        uiNumberOfBirds--;
    }

    for (int32 i = 0; i < MAX_BIRDS; ++i) {
        auto& bird = aBirds[i];
        if (!bird.m_bCreated)
            continue;

        if (bird.m_eBirdMode != eBirdMode::BIRD_DRAW_UPDATE || bird.m_nUpdateAfterMS > CTimer::GetTimeInMS())
            continue;

        if (bird.m_bMustDoCurves) {
            auto fCircleProgress = CTimer::GetTimeStep() / 500.0F; // todo: GetTimeStepInMS?
            auto vecCurTarget = CVector2D(bird.m_vecTargetVelocity);
            auto fSinAngle = sin(fCircleProgress);
            auto fCosAngle = cos(fCircleProgress);

            bird.m_vecTargetVelocity.x = fCosAngle * vecCurTarget.x + fSinAngle * vecCurTarget.y;
            bird.m_vecTargetVelocity.y = fCosAngle * vecCurTarget.y - fSinAngle * vecCurTarget.x;
        }

        auto fTimeStep = CTimer::GetTimeStepInSeconds();
        auto fLerp = std::min(fTimeStep * 0.5F, 1.0F);
        bird.m_vecCurrentVelocity = Lerp(bird.m_vecCurrentVelocity, bird.m_vecTargetVelocity, fLerp);
        bird.m_vecPosn += (fTimeStep * bird.m_vecCurrentVelocity);
        bird.m_fAngle = atan2(bird.m_vecTargetVelocity.x, bird.m_vecTargetVelocity.y);
    }
}

// 0x712810
void CBirds::Render()
{
    if (uiNumberOfBirds == 0)
        return;

    uint32 uiWingMoveTimeOffset = 0;
    uiTempBufferIndicesStored = 0;
    uiTempBufferVerticesStored = 0;

    for (int32 i = 0; i < MAX_BIRDS; ++i) {
        const auto& bird = aBirds[i];
        if (!bird.m_bCreated) {
            uiWingMoveTimeOffset += 100;
            continue;
        }

        CMatrix matBirdTransform;
        matBirdTransform.SetTranslate(bird.m_vecPosn);

        if (bird.m_eBirdMode == eBirdMode::BIRD_DRAW_NOUPDATE || bird.m_eBirdMode == eBirdMode::BIRD_DRAW_UPDATE) {
            auto& vecPos = matBirdTransform.GetPosition();
            auto uiTime = CTimer::GetTimeInMS() + uiWingMoveTimeOffset;
            vecPos.z += sin((float)(uiTime % bird.m_nWingStillness) * (TWO_PI / (float)bird.m_nWingStillness)) * 0.1F;
        }

        auto vecScreenPos = RwV3d();
        float fScreenWidth;
        float fScreenHeight;
        if (CSprite::CalcScreenCoors(matBirdTransform.GetPosition(), &vecScreenPos, &fScreenWidth, &fScreenHeight, false, true)) {
            auto fAngle = bird.m_fAngle;
            auto fCosSize = cos(fAngle) * bird.m_fSize;
            auto fSinSize = sin(fAngle) * bird.m_fSize;

            matBirdTransform.GetRight().Set(fCosSize, -fSinSize, 0.0F);
            matBirdTransform.GetForward().Set(fSinSize, fCosSize, 0.0F);
            matBirdTransform.GetUp().Set(0.0F, 0.0F, bird.m_fSize);

            if (bird.m_eBirdMode == eBirdMode::BIRD_DRAW_NOUPDATE || bird.m_eBirdMode == eBirdMode::BIRD_DRAW_UPDATE) {
                for (int32 iIndice = 0; iIndice < 30; ++iIndice) {
                    auto uiVertInd = static_cast<RxVertexIndex>(uiTempBufferVerticesStored + CBirds::auRenderIndices[iIndice]);
                    aTempBufferIndices[uiTempBufferIndicesStored + iIndice] = uiVertInd;
                    aTempBufferIndices[uiTempBufferIndicesStored + iIndice + 30] = uiVertInd + 8;
                }

                auto uiTime = CTimer::GetTimeInMS() + uiWingMoveTimeOffset;
                auto fSin1 = -sin((float)((uiTime + bird.m_nWingStillness / 6) % bird.m_nWingStillness) * TWO_PI / (float)bird.m_nWingStillness);
                auto fSin2 = -sin((float)((uiTime + bird.m_nWingStillness) % bird.m_nWingStillness) * TWO_PI / (float)bird.m_nWingStillness);

                auto fSizeUsed = std::max(1.0F, bird.m_fSize);
                auto fSin1Factor = fSin1 / fSizeUsed;
                auto fSin2Factor = fSin2 / fSizeUsed;

                auto fOffX1 = cos(fSin1Factor) * 0.5F;
                auto fOffZ1 = sin(fSin1Factor) * 0.5F;
                auto fOffX2 = cos(fSin2Factor) * 0.5F;
                auto fOffZ2 = sin(fSin2Factor) * 0.5F;

                RwUInt8 cAlpha = 255;
                const auto& vecCameraPos = TheCamera.GetPosition();
                auto fCameraDist = DistanceBetweenPoints(vecCameraPos, bird.m_vecPosn);
                auto fAlphaCutoffDist = bird.m_fMaxBirdDistance * 0.7F;
                if (fCameraDist > fAlphaCutoffDist) {
                    auto fTransparency = 1.0F - invLerp(fAlphaCutoffDist, bird.m_fMaxBirdDistance, fCameraDist);
                    fTransparency = clamp(0.0F, 1.0F, fTransparency);
                    cAlpha = static_cast<RwUInt8>(fTransparency * 255.0F);
                }

                for (int32 uiVertInd = 0; uiVertInd < 8; ++uiVertInd) {
                    CVector vecPoint;
                    CBirdColor vertColor;

                    switch (uiVertInd) {
                    case 0:
                    case 1:
                    case 7:
                        vecPoint.x = 0.0F;
                        vecPoint.z = 0.0F;
                        vertColor = bird.m_BodyColor;
                        break;
                    case 2:
                    case 3:
                        vecPoint.x = fOffX1;
                        vecPoint.z = fOffZ1;
                        vertColor = bird.m_BodyColor;
                        break;
                    case 4:
                    case 5:
                        vecPoint.x = fOffX1 + fOffX2;
                        vecPoint.z = fOffZ1 + fOffZ2;
                        vertColor = bird.m_WingsColor;
                        break;
                    case 6:
                        vecPoint.x = 0.1F;
                        vecPoint.z = 0.0F;
                        vertColor = bird.m_BodyColor;
                        break;
                    }

                    vecPoint.y = faRenderPosY[uiVertInd];
                    auto vecWorldPos = matBirdTransform * vecPoint;

                    auto iBufferInd = uiTempBufferVerticesStored + uiVertInd;
                    auto vert1 = &aTempBufferVertices[iBufferInd];
                    RwRGBA rwColor = CRGBA(vertColor.cRed, vertColor.cGreen, vertColor.cBlue, cAlpha).ToRwRGBA();
                    RxObjSpace3DVertexSetPreLitColor(vert1, &rwColor);
                    RxObjSpace3DVertexSetPos(vert1, &vecWorldPos);
                    RxObjSpace3DVertexSetU(vert1, CBirds::faRenderCoorsU[uiVertInd]);
                    RxObjSpace3DVertexSetV(vert1, CBirds::faRenderCoorsV[uiVertInd]);

                    // Mirror on the other side with slightly changed colors
                    vecPoint.x = -vecPoint.x;
                    vecWorldPos = matBirdTransform * vecPoint;
                    vertColor.Scale(0.8F);
                    rwColor = CRGBA(vertColor.cRed, vertColor.cGreen, vertColor.cBlue, cAlpha).ToRwRGBA();

                    auto vert2 = &aTempBufferVertices[iBufferInd + 8];
                    RxObjSpace3DVertexSetPreLitColor(vert2, &rwColor);
                    RxObjSpace3DVertexSetPos(vert2, &vecWorldPos);
                    RxObjSpace3DVertexSetU(vert2, CBirds::faRenderCoorsU[uiVertInd]);
                    RxObjSpace3DVertexSetV(vert2, CBirds::faRenderCoorsV[uiVertInd]);
                }

                uiTempBufferIndicesStored += 60;
                uiTempBufferVerticesStored += 16;
            }
        }
        uiWingMoveTimeOffset += 100;
    }

    if (uiTempBufferVerticesStored) {
        RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
        RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
        RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,    RWRSTATE(rwTEXTUREADDRESSCLAMP));
        RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(FALSE));
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(gpCloudTex[1]->raster));
        CBrightLights::RenderOutGeometryBuffer();
    }
}

// 0x712E40
void CBirds::HandleGunShot(const CVector* pointA, const CVector* pointB) {
    CColLine colLine{};

    for (int32 i = 0; i < MAX_BIRDS; ++i) {
        auto& bird = aBirds[i];
        if (!bird.m_bCreated)
            continue;

        if (CCollision::TestLineSphere({*pointA, *pointB}, { 0.5f, bird.m_vecPosn })) {
            vecBirdShotAt = bird.m_vecPosn;
            bHasBirdBeenShot = true;
            uiNumberOfBirds--;
            bird.m_bCreated = false;
        }
    }
}
