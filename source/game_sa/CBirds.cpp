#include "StdInc.h"

bool& CBirds::bHasBirdBeenShot = *(bool*)0xC6A8A0;
unsigned int& CBirds::uiNumberOfBirds = *(unsigned int*)0xC6A8A4;
CBird* CBirds::aBirds = (CBird*)0xC6A8B0;
CVector& CBirds::vecBirdShotAt = *(CVector*)0xC6AA48;

float* CBirds::faCreationCoorsX = (float*)0x8D5250; // Size: 6
float* CBirds::faCreationCoorsY = (float*)0x8D5268; // Size: 6
float* CBirds::faCreationCoorsZ = (float*)0x8D5280; // Size: 6
float* CBirds::faRenderCoorsU = (float*)0x8D52B8; // Size: 8
float* CBirds::faRenderCoorsV = (float*)0x8D5298; // Size: 8
float* CBirds::faRenderPosY = (float*)0x8D52D8; // Size: 8
unsigned int* CBirds::auRenderIndices = (unsigned int*)0x8D52F8; // Size: 30

void CBirds::InjectHooks()
{
    ReversibleHooks::Install("CBirds", "Init", 0x711EC0, &CBirds::Init);
    ReversibleHooks::Install("CBirds", "Shutdown", 0x712300, &CBirds::Shutdown);
    ReversibleHooks::Install("CBirds", "HandleGunShot", 0x712E40, &CBirds::HandleGunShot);
    ReversibleHooks::Install("CBirds", "Update", 0x712330, &CBirds::Update);
    ReversibleHooks::Install("CBirds", "CreateNumberOfBirds", 0x711EF0, &CBirds::CreateNumberOfBirds);
    ReversibleHooks::Install("CBirds", "Render", 0x712810, &CBirds::Render);
}

void CBirds::Init()
{
    for (int32_t i = 0; i < MAX_BIRDS; ++i) {
        auto& pBird = aBirds[i];
        pBird.m_bCreated = false;
    }
    CBirds::uiNumberOfBirds = 0;
    CBirds::bHasBirdBeenShot = false;
}

void CBirds::CreateNumberOfBirds(CVector vecStartPos, CVector vecTargetPos, int iBirdCount, eBirdsBiome eBiome, bool bCheckObstacles)
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

    for (int32_t i = 0; i < iBirdCount; ++i) {
        int iFreeBirdIndex = 0;
        while (iFreeBirdIndex < MAX_BIRDS) {
            auto& pBird = CBirds::aBirds[iFreeBirdIndex];
            if (!pBird.m_bCreated)
                break;

            ++iFreeBirdIndex;
        }

        if (iFreeBirdIndex >= MAX_BIRDS)
            return;

        auto& pBird = CBirds::aBirds[iFreeBirdIndex];
        pBird.m_vecPosn = vecStartPos;

        auto vecBirdDirection = vecTargetPos - pBird.m_vecPosn;
        vecBirdDirection.Normalise();
        auto vecCheckPos = pBird.m_vecPosn + (vecBirdDirection * fMaxDistance * 2.4F);
        if (bCheckObstacles && !CWorld::GetIsLineOfSightClear(pBird.m_vecPosn, vecCheckPos, true, false, false, false, false, false, false))
            continue;

        auto fAngle = atan2(vecBirdDirection.x, vecBirdDirection.y);
        unsigned int iSpeedRandFactor = rand() % 31;

        ++CBirds::uiNumberOfBirds;
        pBird.m_bCreated = true;
        pBird.m_fMaxBirdDistance = fMaxDistance;
        pBird.m_eBirdMode = eBirdMode::BIRD_DRAW_UPDATE;
        pBird.m_nUpdateAfterMS = 0;
        pBird.m_bMustDoCurves = false;
        pBird.m_fAngle = fAngle;
        pBird.m_vecPosn.x += CBirds::faCreationCoorsX[i];
        pBird.m_vecPosn.y += CBirds::faCreationCoorsY[i];
        pBird.m_vecPosn.z += CBirds::faCreationCoorsZ[i];

        float fSpeedMult;
        switch (eBiome) {
        case eBirdsBiome::BIOME_WATER:
            fSpeedMult = (float)iSpeedRandFactor * 0.02F + 4.0F;    // [4.0 : 4.6]
            pBird.m_BodyColor.Set((rand() & 0x3F) + 0x50);          // [80 : 143]
            pBird.m_WingsColor.Set((rand() & 0x3F) - 0x4C);         // [166 : 242]
            pBird.m_fSize = CGeneral::GetRandomNumberInRange(0.8F, 1.2F);
            pBird.m_nWingStillness = 1000 - 12 * iSpeedRandFactor;  // [640 : 1000]
            break;
        case eBirdsBiome::BIOME_DESERT:
            fSpeedMult = (float)iSpeedRandFactor * 0.02F + 3.0F;    // [3.0 : 3.6]
            pBird.m_BodyColor.Set(30, 15, 10);
            pBird.m_WingsColor.Set(80, 15, 10);
            pBird.m_fSize = CGeneral::GetRandomNumberInRange(2.0F, 2.5F);
            pBird.m_nWingStillness = 12 * (125 - iSpeedRandFactor); // [1140 : 1500]
            if (rand() & 4)
                pBird.m_nWingStillness = 1000000; // Not moving it's wings

            if (rand() & 8)
                pBird.m_bMustDoCurves = true;

            break;
        case eBirdsBiome::BIOME_NORMAL:
        default:
            fSpeedMult = (float)iSpeedRandFactor * 0.02F + 5.0F;    // [5.0 : 5.6]
            pBird.m_BodyColor.Set((rand() & 0x7F) + 0x80);          // [127 : 255]
            pBird.m_WingsColor.Set((rand() & 0x7F) + 0x80);         // [127 : 255]
            pBird.m_fSize = CGeneral::GetRandomNumberInRange(0.5F, 0.6F);
            pBird.m_nWingStillness = 500 - 6 * iSpeedRandFactor;    // [320 : 500]
            break;
        }

        pBird.m_vecTargetVelocity = vecBirdDirection * fSpeedMult;
        pBird.m_vecCurrentVelocity = pBird.m_vecTargetVelocity;
    }
}

void CBirds::Shutdown()
{
    for (int32_t i = 0; i < MAX_BIRDS; ++i) {
        auto& pBird = aBirds[i];
        if (pBird.m_bCreated)
            pBird.m_bCreated = false;
    }
    CBirds::uiNumberOfBirds = 0;
}

void CBirds::Update()
{
    auto const& vecCamPos = TheCamera.GetPosition();

    if (!CGame::currArea
        && CBirds::uiNumberOfBirds < MAX_BIRDS
        && CClock::ms_nGameClockHours < 22U
        && CClock::ms_nGameClockHours > 5U
        && (CTimer::m_FrameCounter & 0x1FF) == MAX_BIRDS) {

        auto iNumBirdsToCreate = (uint32_t)CGeneral::GetRandomNumberInRange(1, MAX_BIRDS + 1 - CBirds::uiNumberOfBirds);
        eBirdsBiome eBiome = eBirdsBiome::BIOME_WATER;

        if (TheCamera.m_fDistanceToWater > 30.0F) {
            if (CWeather::WeatherRegion == eWeatherRegion::WEATHER_REGION_DESERT) {
                eBiome = eBirdsBiome::BIOME_DESERT;
                iNumBirdsToCreate = std::min(iNumBirdsToCreate, CBirds::uiNumberOfBirds);
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

                if (rand() & 1)
                    fSpawnAngleCamRelative = (float)((unsigned char)(rand() & 0xFF)) * 0.024531251F; // [0 : 255] mapped to [0 : 2π]
                else {
                    auto vecForward = TheCamera.m_mCameraMatrix.GetForward();
                    vecForward.z = 0.0F;
                    if (vecForward.x == 0.0F)
                        vecForward.x = 0.01F;

                    vecForward.Normalise();
                    unsigned char cRand = ((unsigned char)(rand() & 0xFF)) - 128;
                    fSpawnAngleCamRelative = ((float)cRand) / 256.0F + atan2(vecForward.x, vecForward.y); // [0 : 1] + atan2(...)
                }
                    
                auto vecBirdSpawnPos = CVector(sin(fSpawnAngleCamRelative) * fSpawnDistance + vecCamPos.x,
                                               cos(fSpawnAngleCamRelative) * fSpawnDistance + vecCamPos.y,
                                               fBirdSpawnZ);

                float fWaterLevel;
                if (!CWaterLevel::GetWaterLevelNoWaves(vecBirdSpawnPos.x, vecBirdSpawnPos.y, vecBirdSpawnPos.z, &fWaterLevel, nullptr, nullptr) || fWaterLevel + 4.0F < fBirdSpawnZ) {
                    auto vecForward = TheCamera.m_mCameraMatrix.GetForward();
                    vecForward.z = 0.0F;
                    vecForward.Normalise();

                    auto vecFlightTargetPos = vecCamPos + (vecForward * 8.0F);
                    vecFlightTargetPos.z = fBirdSpawnZ;

                    CBirds::CreateNumberOfBirds(vecBirdSpawnPos, vecFlightTargetPos, iNumBirdsToCreate, eBiome, true);
                }
            }
        }
    }

    int iBirdIndex = CTimer::m_FrameCounter % MAX_BIRDS;
    auto& pCheckedBird = CBirds::aBirds[iBirdIndex];
    if (pCheckedBird.m_bCreated && DistanceBetweenPoints(CVector2D(pCheckedBird.m_vecPosn), CVector2D(vecCamPos)) > pCheckedBird.m_fMaxBirdDistance)
    {
        pCheckedBird.m_bCreated = false;
        CBirds::uiNumberOfBirds--;
    }

    for (int32_t i = 0; i < MAX_BIRDS; ++i) {
        auto& pBird = aBirds[i];
        if (!pBird.m_bCreated)
            continue;

        if (pBird.m_eBirdMode != eBirdMode::BIRD_DRAW_UPDATE || pBird.m_nUpdateAfterMS > CTimer::m_snTimeInMilliseconds)
            continue;

        if (pBird.m_bMustDoCurves) {
            auto fCircleProgress = CTimer::ms_fTimeStep / 500.0F;
            auto vecCurTarget = CVector2D(pBird.m_vecTargetVelocity);
            auto fSinAngle = sin(fCircleProgress);
            auto fCosAngle = cos(fCircleProgress);

            pBird.m_vecTargetVelocity.x = fCosAngle * vecCurTarget.x + fSinAngle * vecCurTarget.y;
            pBird.m_vecTargetVelocity.y = fCosAngle * vecCurTarget.y - fSinAngle * vecCurTarget.x;
        }

        auto fTimeStep = CTimer::ms_fTimeStep / 50.0F;
        auto fLerp = std::min(fTimeStep * 0.5F, 1.0F);
        pBird.m_vecCurrentVelocity = Lerp(pBird.m_vecCurrentVelocity, pBird.m_vecTargetVelocity, fLerp);
        pBird.m_vecPosn += (fTimeStep * pBird.m_vecCurrentVelocity);
        pBird.m_fAngle = atan2(pBird.m_vecTargetVelocity.x, pBird.m_vecTargetVelocity.y);
    }
}

void CBirds::Render()
{
    if (!CBirds::uiNumberOfBirds)
        return;

    unsigned int uiWingMoveTimeOffset = 0;
    uiTempBufferIndicesStored = 0;
    uiTempBufferVerticesStored = 0;

    for (int32_t i = 0; i < MAX_BIRDS; ++i) {
        const auto& pBird = aBirds[i];
        if (!pBird.m_bCreated) {
            uiWingMoveTimeOffset += 100;
            continue;
        }

        auto matBirdTransform = CMatrix();
        matBirdTransform.SetTranslate(pBird.m_vecPosn);

        if (pBird.m_eBirdMode == eBirdMode::BIRD_DRAW_NOUPDATE || pBird.m_eBirdMode == eBirdMode::BIRD_DRAW_UPDATE) {
            auto& vecPos = matBirdTransform.GetPosition();
            auto uiTime = CTimer::m_snTimeInMilliseconds + uiWingMoveTimeOffset;
            vecPos.z += sin((float)(uiTime % pBird.m_nWingStillness) * (TWO_PI / (float)pBird.m_nWingStillness)) * 0.1F;
        }

        auto vecScreenPos = RwV3d();
        float fScreenWidth;
        float fScreenHeight;
        if (CSprite::CalcScreenCoors(matBirdTransform.GetPosition(), &vecScreenPos, &fScreenWidth, &fScreenHeight, false, true)) {
            auto fAngle = pBird.m_fAngle;
            auto fCosSize = cos(fAngle) * pBird.m_fSize;
            auto fSinSize = sin(fAngle) * pBird.m_fSize;

            matBirdTransform.GetRight().Set(fCosSize, -fSinSize, 0.0F);
            matBirdTransform.GetForward().Set(fSinSize, fCosSize, 0.0F);
            matBirdTransform.GetUp().Set(0.0F, 0.0F, pBird.m_fSize);

            if (pBird.m_eBirdMode == eBirdMode::BIRD_DRAW_NOUPDATE || pBird.m_eBirdMode == eBirdMode::BIRD_DRAW_UPDATE) {
                for (int32_t iIndice = 0; iIndice < 30; ++iIndice) {
                    auto uiVertInd = static_cast<RxVertexIndex>(uiTempBufferVerticesStored + CBirds::auRenderIndices[iIndice]);
                    aTempBufferIndices[uiTempBufferIndicesStored + iIndice] = uiVertInd;
                    aTempBufferIndices[uiTempBufferIndicesStored + iIndice + 30] = uiVertInd + 8;
                }

                auto uiTime = CTimer::m_snTimeInMilliseconds + uiWingMoveTimeOffset;
                auto fSin1 = -sin((float)((uiTime + pBird.m_nWingStillness / 6) % pBird.m_nWingStillness) * TWO_PI / (float)pBird.m_nWingStillness);
                auto fSin2 = -sin((float)((uiTime + pBird.m_nWingStillness) % pBird.m_nWingStillness) * TWO_PI / (float)pBird.m_nWingStillness);

                auto fSizeUsed = std::max(1.0F, pBird.m_fSize);
                auto fSin1Factor = fSin1 / fSizeUsed;
                auto fSin2Factor = fSin2 / fSizeUsed;

                auto fOffX1 = cos(fSin1Factor) * 0.5F;
                auto fOffZ1 = sin(fSin1Factor) * 0.5F;
                auto fOffX2 = cos(fSin2Factor) * 0.5F;
                auto fOffZ2 = sin(fSin2Factor) * 0.5F;

                RwUInt8 cAlpha = 255;
                const auto& vecCameraPos = TheCamera.GetPosition();
                auto fCameraDist = DistanceBetweenPoints(vecCameraPos, pBird.m_vecPosn);
                auto fAlphaCutoffDist = pBird.m_fMaxBirdDistance * 0.7F;
                if (fCameraDist > fAlphaCutoffDist) {
                    auto fTransparency = 1.0F - invLerp(fAlphaCutoffDist, pBird.m_fMaxBirdDistance, fCameraDist);
                    fTransparency = clamp(0.0F, 1.0F, fTransparency);
                    cAlpha = static_cast<RwUInt8>(fTransparency * 255.0F);
                }

                for (int32_t uiVertInd = 0; uiVertInd < 8; ++uiVertInd) {
                    CVector vecPoint;
                    CBirdColor vertColor;

                    switch (uiVertInd) {
                    case 0:
                    case 1:
                    case 7:
                        vecPoint.x = 0.0F;
                        vecPoint.z = 0.0F;
                        vertColor = pBird.m_BodyColor;
                        break;
                    case 2:
                    case 3:
                        vecPoint.x = fOffX1;
                        vecPoint.z = fOffZ1;
                        vertColor = pBird.m_BodyColor;
                        break;
                    case 4:
                    case 5:
                        vecPoint.x = fOffX1 + fOffX2;
                        vecPoint.z = fOffZ1 + fOffZ2;
                        vertColor = pBird.m_WingsColor;
                        break;
                    case 6:
                        vecPoint.x = 0.1F;
                        vecPoint.z = 0.0F;
                        vertColor = pBird.m_BodyColor;
                        break;
                    }

                    vecPoint.y = CBirds::faRenderPosY[uiVertInd];
                    auto vecWorldPos = matBirdTransform * vecPoint;

                    auto iBufferInd = uiTempBufferVerticesStored + uiVertInd;
                    auto pVert1 = &aTempBufferVertices[iBufferInd];
                    RwRGBA rwColor = CRGBA(vertColor.cRed, vertColor.cGreen, vertColor.cBlue, cAlpha).ToRwRGBA();
                    RxObjSpace3DVertexSetPreLitColor(pVert1, &rwColor);
                    RxObjSpace3DVertexSetPos(pVert1, &vecWorldPos);
                    RxObjSpace3DVertexSetU(pVert1, CBirds::faRenderCoorsU[uiVertInd]);
                    RxObjSpace3DVertexSetV(pVert1, CBirds::faRenderCoorsV[uiVertInd]);

                    // Mirror on the other side with slightly changed colors
                    vecPoint.x = -vecPoint.x;
                    vecWorldPos = matBirdTransform * vecPoint;
                    vertColor.Scale(0.8F);
                    rwColor = CRGBA(vertColor.cRed, vertColor.cGreen, vertColor.cBlue, cAlpha).ToRwRGBA();

                    auto pVert2 = &aTempBufferVertices[iBufferInd + 8];
                    RxObjSpace3DVertexSetPreLitColor(pVert2, &rwColor);
                    RxObjSpace3DVertexSetPos(pVert2, &vecWorldPos);
                    RxObjSpace3DVertexSetU(pVert2, CBirds::faRenderCoorsU[uiVertInd]);
                    RxObjSpace3DVertexSetV(pVert2, CBirds::faRenderCoorsV[uiVertInd]);
                }

                uiTempBufferIndicesStored += 60;
                uiTempBufferVerticesStored += 16;
            }
        }
        uiWingMoveTimeOffset += 100;
    }

    if (uiTempBufferVerticesStored) {
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
        RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void*)rwTEXTUREADDRESSCLAMP);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)gpCloudTex[1]->raster);
        CBrightLights::RenderOutGeometryBuffer();
    }
}

void CBirds::HandleGunShot(CVector const* pointA, CVector const* pointB)
{
    CColLine colLine(*pointA, *pointB);

    for (int32_t i = 0; i < MAX_BIRDS; ++i) {
        auto& pBird = aBirds[i];
        if (!pBird.m_bCreated)
            continue;

        auto birdSphere = CColSphere();
        birdSphere.m_fRadius = 0.5F;
        birdSphere.m_vecCenter = pBird.m_vecPosn;

        if (CCollision::TestLineSphere(colLine, birdSphere))
        {
            CBirds::vecBirdShotAt = pBird.m_vecPosn;
            CBirds::bHasBirdBeenShot = true;
            CBirds::uiNumberOfBirds--;
            pBird.m_bCreated = false;
        }
    }
}
