#include "StdInc.h"

uint8_t(&CTrafficLights::aTrafficLightColoursR)[3] = *(uint8_t(*)[3])0x8A6214;
uint8_t(&CTrafficLights::aTrafficLightColoursG)[3] = *(uint8_t(*)[3])0x8A6218;
uint8_t(&CTrafficLights::aTrafficLightColoursB)[3] = *(uint8_t(*)[3])0xA9AD94;
float& CTrafficLights::fLightMult = *(float*)0x8A621C;

CVector& CTrafficLights::vecTrafficLights5_1 = *(CVector*)0xA9ADD4;
CVector& CTrafficLights::vecTrafficLights5_2 = *(CVector*)0xA9ADC8;
CVector& CTrafficLights::vecTrafficLights_1 = *(CVector*)0xA9ADBC;
CVector& CTrafficLights::vecTrafficLights_2 = *(CVector*)0xA9ADB0;
uint32_t& CTrafficLights::uiPedLightFlags = *(uint32_t*)0xA9ADE0;

void CTrafficLights::InjectHooks()
{
    ReversibleHooks::Install("CTrafficLights", "ShouldCarStopForLight", 0x49D610, &CTrafficLights::ShouldCarStopForLight);
    ReversibleHooks::Install("CTrafficLights", "ShouldCarStopForBridge", 0x49D420, &CTrafficLights::ShouldCarStopForBridge);
    ReversibleHooks::Install("CTrafficLights", "IsMITrafficLight", 0x49D5A0, &CTrafficLights::IsMITrafficLight);
    ReversibleHooks::Install("CTrafficLights", "DisplayActualLight", 0x49DAB0, &CTrafficLights::DisplayActualLight);
    ReversibleHooks::Install("CTrafficLights", "FindTrafficLightType", 0x49D580, &CTrafficLights::FindTrafficLightType);
    ReversibleHooks::Install("CTrafficLights", "FindTrafficLightTypeFromOrientation", 0x49D4D0, &CTrafficLights::FindTrafficLightTypeFromOrientation);
    ReversibleHooks::Install("CTrafficLights", "FindOrientationForTrafficLightType", 0x49D520, &CTrafficLights::FindOrientationForTrafficLightType);
    ReversibleHooks::Install("CTrafficLights", "LightForPeds", 0x49D400, &CTrafficLights::LightForPeds);
    ReversibleHooks::Install("CTrafficLights", "LightForCars1", 0x49D2D0, &CTrafficLights::LightForCars1);
    ReversibleHooks::Install("CTrafficLights", "LightForCars2", 0x49D310, &CTrafficLights::LightForCars2);
    ReversibleHooks::Install("CTrafficLights", "LightForCars1_Visual", 0x49D350, &CTrafficLights::LightForCars1_Visual);
    ReversibleHooks::Install("CTrafficLights", "LightForCars2_Visual", 0x49D3A0, &CTrafficLights::LightForCars2_Visual);
}

bool CTrafficLights::ShouldCarStopForLight(CVehicle* pVehicle, bool bUnkn)
{
    auto iAppeareance = pVehicle->GetVehicleAppearance();
    if (iAppeareance == eVehicleApperance::VEHICLE_APPEARANCE_HELI || iAppeareance == eVehicleApperance::VEHICLE_APPEARANCE_PLANE)
        return false;

    auto& pCurrentNodeInfo = pVehicle->m_autoPilot.m_nCurrentPathNodeInfo;
    if (pCurrentNodeInfo.IsValid() && ThePaths.m_pPathNodes[pCurrentNodeInfo.m_wAreaId]) {
        const auto& pNaviNode = ThePaths.GetCarPathLink(pCurrentNodeInfo);
        if (pNaviNode.m_nTrafficLightState) {
            if ((!pNaviNode.m_bTrafficLightDirection || pNaviNode.m_address == pVehicle->m_autoPilot.m_currentAddress)
              && (pNaviNode.m_bTrafficLightDirection || pNaviNode.m_address != pVehicle->m_autoPilot.m_currentAddress)) {

                if (!bUnkn
                    && (pNaviNode.m_nTrafficLightState != DIR_NORTH_SOUTH || !CTrafficLights::LightForCars1())
                    && (pNaviNode.m_nTrafficLightState != DIR_WEST_EAST   || !CTrafficLights::LightForCars2())) {

                    return false;
                }

                const auto& vehPos = pVehicle->GetPosition();
                auto fDot = (vehPos.y - pNaviNode.m_posn.y / 8.0F) * (pNaviNode.m_nDirY / 100.0F)
                          + (vehPos.x - pNaviNode.m_posn.x / 8.0F) * (pNaviNode.m_nDirX / 100.0F);

                if (pVehicle->m_autoPilot._smthCurr == -1) {
                    if (fDot > 0.0F && fDot < 12.0F)
                        return true;
                }
                else if (fDot < 0.0F && fDot > -12.0F)
                    return true;
            }
        }
    }

    auto& pNextNodeInfo = pVehicle->m_autoPilot.m_nNextPathNodeInfo;
    if (pNextNodeInfo.IsValid() && ThePaths.m_pPathNodes[pNextNodeInfo.m_wAreaId]) {
        const auto& pNaviNode = ThePaths.GetCarPathLink(pNextNodeInfo);
        if (pNaviNode.m_nTrafficLightState) {
            if ((!pNaviNode.m_bTrafficLightDirection || pNaviNode.m_address == pVehicle->m_autoPilot.m_startingRouteNode)
              && (pNaviNode.m_bTrafficLightDirection || pNaviNode.m_address != pVehicle->m_autoPilot.m_startingRouteNode)) {

                if (!bUnkn
                    && (pNaviNode.m_nTrafficLightState != DIR_NORTH_SOUTH || !CTrafficLights::LightForCars1())
                    && (pNaviNode.m_nTrafficLightState != DIR_WEST_EAST   || !CTrafficLights::LightForCars2())) {

                    return false;
                }

                const auto& vehPos = pVehicle->GetPosition();
                auto fDot = (vehPos.y - pNaviNode.m_posn.y / 8.0F) * (pNaviNode.m_nDirY / 100.0F)
                          + (vehPos.x - pNaviNode.m_posn.x / 8.0F) * (pNaviNode.m_nDirX / 100.0F);

                if (pVehicle->m_autoPilot._smthNext == -1) {
                    if (fDot > 0.0F && fDot < 12.0F)
                        return true;
                }
                else if (fDot < 0.0F && fDot > -12.0F)
                    return true;
            }
        }
    }

    auto& pPrevNodeInfo = pVehicle->m_autoPilot.m_nPreviousPathNodeInfo;
    if (pPrevNodeInfo.IsValid() && ThePaths.m_pPathNodes[pPrevNodeInfo.m_wAreaId]) {
        const auto& pNaviNode = ThePaths.GetCarPathLink(pPrevNodeInfo);
        if (pVehicle->m_nStatus == eEntityStatus::STATUS_PHYSICS && pNaviNode.m_nTrafficLightState) {
            if ((!pNaviNode.m_bTrafficLightDirection || pNaviNode.m_address == pVehicle->m_autoPilot.m_endingRouteNode)
              && (pNaviNode.m_bTrafficLightDirection || pNaviNode.m_address != pVehicle->m_autoPilot.m_endingRouteNode)) {

                if (!bUnkn
                    && (pNaviNode.m_nTrafficLightState != DIR_NORTH_SOUTH || !CTrafficLights::LightForCars1())
                    && (pNaviNode.m_nTrafficLightState != DIR_WEST_EAST   || !CTrafficLights::LightForCars2())) {

                    return false;
                }

                const auto& vehPos = pVehicle->GetPosition();
                auto fDot = (vehPos.y - pNaviNode.m_posn.y / 8.0F) * (pNaviNode.m_nDirY / 100.0F)
                          + (vehPos.x - pNaviNode.m_posn.x / 8.0F) * (pNaviNode.m_nDirX / 100.0F);

                if (pVehicle->m_autoPilot._smthPrev == -1) {
                    if (fDot > 0.0F && fDot < 6.0F)
                        return true;
                }
                else if (fDot < 0.0F && fDot > -6.0F)
                    return true;
            }
        }
    }

    return false;
}

bool CTrafficLights::ShouldCarStopForBridge(CVehicle* pVehicle)
{
    auto iAppeareance = pVehicle->GetVehicleAppearance();
    if (iAppeareance == eVehicleApperance::VEHICLE_APPEARANCE_HELI || iAppeareance == eVehicleApperance::VEHICLE_APPEARANCE_PLANE)
        return false;

    auto& pNextNodeInfo = pVehicle->m_autoPilot.m_nNextPathNodeInfo;
    if (!pNextNodeInfo.IsValid() || !ThePaths.m_pPathNodes[pNextNodeInfo.m_wAreaId])
        return false;

    auto& pCurNodeInfo = pVehicle->m_autoPilot.m_nCurrentPathNodeInfo;
    if (!pCurNodeInfo.IsValid())
        return false;

    if (ThePaths.m_pPathNodes[pCurNodeInfo.m_wAreaId]
        && ThePaths.GetCarPathLink(pNextNodeInfo).m_bTrainCrossing
        && ThePaths.GetCarPathLink(pNextNodeInfo).m_bTrainCrossing)
        return true;

    return false;
}

int CTrafficLights::FindTrafficLightType(CEntity* pEntity)
{
    auto pHeading = CTrafficLights::FindOrientationForTrafficLightType(pEntity);
    return CTrafficLights::FindTrafficLightTypeFromOrientation(pHeading);
}

float CTrafficLights::FindOrientationForTrafficLightType(CEntity* pEntity)
{
    auto pMat = pEntity->GetMatrix();
    return RadiansToDegrees(CGeneral::GetATanOfXY(pMat.GetForward().x, pMat.GetForward().y));
}

int CTrafficLights::FindTrafficLightTypeFromOrientation(float fOrientation)
{
    if ((fOrientation <= 60.0F || fOrientation >= 150.0F)
        && (fOrientation <= 240.0F || fOrientation >= 330.0F))
        return eTrafficLightsDirection::DIR_WEST_EAST;

    return eTrafficLightsDirection::DIR_NORTH_SOUTH;
}


void CTrafficLights::DisplayActualLight(CEntity* pEntity)
{
    auto pEntMat = pEntity->GetMatrix();
    if (pEntMat.GetUp().z < 0.96F || pEntity->m_bRenderDamaged)
        return;

    auto iLightColorBase = eBrightLightColor::BRIGHTLIGHT_GREEN_BIG;
    if (pEntity->m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_3
        || pEntity->m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_4
        || pEntity->m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_5
        || pEntity->m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_GAY
        || pEntity->m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_MIAMI) {

        iLightColorBase = eBrightLightColor::BRIGHTLIGHT_GREEN_SMALL;
    }

    int iLightState;
    if (CTrafficLights::FindTrafficLightType(pEntity) == eTrafficLightsDirection::DIR_NORTH_SOUTH)
        iLightState = CTrafficLights::LightForCars1_Visual();
    else
        iLightState = CTrafficLights::LightForCars2_Visual();

    auto pModelInfo = CModelInfo::GetModelInfo(pEntity->m_nModelIndex);
    bool bSameDir = DotProduct(TheCamera.m_mCameraMatrix.GetForward(), pEntMat.GetForward()) > 0.0F;

    CVector vecCenter(0.0F, 0.0F, 0.0F);
    for (int32_t iFxInd = 0; iFxInd < pModelInfo->m_n2dfxCount; ++iFxInd) {
        auto pEffect = pModelInfo->Get2dEffect(iFxInd);
        if (pEffect->m_nType != e2dEffectType::EFFECT_LIGHT)
            continue;

        auto vecLightPos = pEntity->GetMatrix() * pEffect->m_vecPosn;
        vecCenter += vecLightPos;
        int iColorState = eTrafficLightsState::LIGHT_GREEN;
        if (pEffect->light.m_color.red > 200) {
            if (pEffect->light.m_color.green > 100)
                iColorState = eTrafficLightsState::LIGHT_YELLOW;
            else
                iColorState = eTrafficLightsState::LIGHT_RED;
        }

        if (bSameDir == pEffect->m_vecPosn.y > 0.0F || iColorState != iLightState)
            continue;

        auto fBrightness = CTimeCycle::m_CurrentColours.m_fSpriteBrightness * 0.07F;
        auto fSize = CTimeCycle::m_CurrentColours.m_fSpriteSize * 0.175F;

        CCoronas::RegisterCorona(reinterpret_cast<uint32_t>(pEntity) + iFxInd,
                                 nullptr,
                                 static_cast<unsigned char>(aTrafficLightColoursR[iColorState] * fBrightness),
                                 static_cast<unsigned char>(aTrafficLightColoursG[iColorState] * fBrightness),
                                 static_cast<unsigned char>(aTrafficLightColoursB[iColorState] * fBrightness),
                                 255,
                                 vecLightPos,
                                 fSize,
                                 50.0F,
                                 eCoronaType::CORONATYPE_SHINYSTAR,
                                 eCoronaFlareType::FLARETYPE_NONE,
                                 true,
                                 false,
                                 0,
                                 0.0F,
                                 false,
                                 1.5F,
                                 0,
                                 15.0F,
                                 false,
                                 false);

        CBrightLights::RegisterOne(vecLightPos,
                                   pEntity->GetMatrix().GetUp(),
                                   pEntity->GetMatrix().GetRight(),
                                   CVector(0.0F, 0.0F, 0.0F),
                                   iLightState + iLightColorBase,
                                   0,
                                   0,
                                   0);
    }

    if (pModelInfo->m_n2dfxCount) {
        vecCenter /= pModelInfo->m_n2dfxCount;
        if (iLightState < eTrafficLightsState::LIGHT_OFF) {
            if (CWeather::TrafficLightsBrightness > 0.5F) {
                auto ucRed =   std::max(CTrafficLights::aTrafficLightColoursR[iLightState], uint8_t(50));
                auto ucGreen = std::max(CTrafficLights::aTrafficLightColoursG[iLightState], uint8_t(50));
                auto ucBlue =  std::max(CTrafficLights::aTrafficLightColoursB[iLightState], uint8_t(50));

                CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT,
                                       vecCenter,
                                       CVector(0.0F, 0.0F, 0.0F),
                                       14.0F,
                                       CTrafficLights::fLightMult * ucRed,
                                       CTrafficLights::fLightMult * ucGreen,
                                       CTrafficLights::fLightMult * ucBlue,
                                       RwFogType::rwFOGTYPELINEAR,
                                       true,
                                       nullptr);
            }

            if (CWeather::TrafficLightsBrightness > 0.05F) {
                auto fColMult = CTimeCycle::m_CurrentColours.m_fLightsOnGroundBrightness * CWeather::TrafficLightsBrightness / 80.0F;
                uint8_t ucRed = static_cast<uint8_t>(CTrafficLights::aTrafficLightColoursR[iLightState] * fColMult);
                uint8_t ucGreen = static_cast<uint8_t>(CTrafficLights::aTrafficLightColoursG[iLightState] * fColMult);
                uint8_t ucBlue = static_cast<uint8_t>(CTrafficLights::aTrafficLightColoursB[iLightState] * fColMult);

                CShadows::StoreStaticShadow(reinterpret_cast<uint32_t>(pEntity),
                                            eShadowType::SHADOW_ADDITIVE,
                                            gpShadowExplosionTex,
                                            &vecCenter,
                                            8.0F,
                                            0.0F,
                                            0.0F,
                                            -8.0F,
                                            128,
                                            ucRed,
                                            ucGreen,
                                            ucBlue,
                                            12.0F,
                                            1.0F,
                                            40.0F,
                                            false,
                                            0.0F);
            }
        }
    }

    CVector vecCorner1(0.0F, 0.0F, 0.0F);
    CVector vecCorner2(0.0F, 0.0F, 0.0F);
    if (pEntity->m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_4
     || pEntity->m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_GAY) {

        vecCorner1.Set(0.189F, -0.157F, 1.848F);
        vecCorner2.Set(-0.141F, -0.157F, 1.607F);
    }
    else if (pEntity->m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_5) {
        if (!(CTrafficLights::uiPedLightFlags & 1)) {
            CTrafficLights::uiPedLightFlags |= 1;
            CTrafficLights::vecTrafficLights5_1.Set(-0.044F, -0.261F, 1.561F);
        }

        if (!(CTrafficLights::uiPedLightFlags & 2)) {
            CTrafficLights::uiPedLightFlags |= 2;
            CTrafficLights::vecTrafficLights5_2.Set(0.222F, -0.261F, 1.867F);
        }
        vecCorner1 = CTrafficLights::vecTrafficLights5_2;
        vecCorner2 = CTrafficLights::vecTrafficLights5_1;
    }
    else if (pEntity->m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS) {
        if (!(CTrafficLights::uiPedLightFlags & 4)) {
            CTrafficLights::uiPedLightFlags |= 4;
            CTrafficLights::vecTrafficLights_1.Set(2.673F, 1.262F, -0.539F);
        }
        if (!(CTrafficLights::uiPedLightFlags & 8)) {
            CTrafficLights::uiPedLightFlags |= 8;
            CTrafficLights::vecTrafficLights_2.Set(2.673F, 0.713F, -0.127F);
        }
        vecCorner1 = CTrafficLights::vecTrafficLights_2;
        vecCorner2 = CTrafficLights::vecTrafficLights_1;
    }
    else {
        return;
    }

    auto iPedLightState = CTrafficLights::LightForPeds();
    if (iPedLightState == eTrafficLightsState::LIGHT_RED) {
        // Ped lights are composed of 2 images side by side, we want to draw only the required half
        auto vecMidPoint = (vecCorner1 + vecCorner2) * 0.5F;

        auto p1 = CVector(vecCorner2.x, vecCorner2.y, vecCorner1.z);
        auto p2 = CVector(vecMidPoint.x, vecMidPoint.y, vecCorner1.z);
        auto p3 = vecCorner2;
        auto p4 = CVector(vecMidPoint.x, vecMidPoint.y, vecCorner2.z);

        CShinyTexts::RegisterOne(pEntity->GetMatrix() * p1,
                                 pEntity->GetMatrix() * p2,
                                 pEntity->GetMatrix() * p3,
                                 pEntity->GetMatrix() * p4,
                                 0.5F,
                                 0.0F,
                                 0.0F,
                                 0.0F,
                                 0.5F,
                                 1.0F,
                                 0.0F,
                                 1.0F,
                                 1,
                                 255,
                                 0,
                                 0,
                                 60.0F);

    }
    else if (iPedLightState == eTrafficLightsState::LIGHT_GREEN || CTimer::m_snTimeInMilliseconds & 0x100) {
        // Ped lights are composed of 2 images side by side, we want to draw only the required half
        auto vecMidPoint = (vecCorner1 + vecCorner2) * 0.5F;

        auto p1 = CVector(vecMidPoint.x, vecMidPoint.y, vecCorner1.z);
        auto p2 = vecCorner1;
        auto p3 = CVector(vecMidPoint.x, vecMidPoint.y, vecCorner2.z);
        auto p4 = CVector(vecCorner1.x, vecCorner1.y, vecCorner2.z);

        CShinyTexts::RegisterOne(pEntity->GetMatrix()* p1,
            pEntity->GetMatrix()* p2,
            pEntity->GetMatrix()* p3,
            pEntity->GetMatrix()* p4,
            1.0F,
            0.0F,
            0.5F,
            0.0F,
            1.0F,
            1.0F,
            0.5F,
            1.0F,
            1,
            255,
            255,
            255,
            60.0F);
    }
}

bool CTrafficLights::IsMITrafficLight(int modelIndex)
{
    return modelIndex == ModelIndices::MI_TRAFFICLIGHTS
        || modelIndex == ModelIndices::MI_TRAFFICLIGHTS_VERTICAL
        || modelIndex == ModelIndices::MI_TRAFFICLIGHTS_MIAMI
        || modelIndex == ModelIndices::MI_TRAFFICLIGHTS_VEGAS
        || modelIndex == ModelIndices::MI_TRAFFICLIGHTS_TWOVERTICAL
        || modelIndex == ModelIndices::MI_TRAFFICLIGHTS_3
        || modelIndex == ModelIndices::MI_TRAFFICLIGHTS_4
        || modelIndex == ModelIndices::MI_TRAFFICLIGHTS_5
        || modelIndex == ModelIndices::MI_TRAFFICLIGHTS_GAY;
}

unsigned char CTrafficLights::LightForPeds()
{
    auto uiMaskedTime = (CTimer::m_snTimeInMilliseconds / 2) & 0x3FFF;
    if (uiMaskedTime < 12000)
        return eTrafficLightsState::LIGHT_RED;

    if (uiMaskedTime < 15384)
        return eTrafficLightsState::LIGHT_GREEN;

    return eTrafficLightsState::LIGHT_YELLOW;
}

unsigned char CTrafficLights::LightForCars1()
{
    if (CGameLogic::LaRiotsActiveHere() || CCheat::m_aCheatsActive[eCheats::CHEAT_BGREEN_LIGHTS_CHEAT])
        return eTrafficLightsState::LIGHT_GREEN;

    auto uiMaskedTime = (CTimer::m_snTimeInMilliseconds / 2) & 0x3FFF;
    if (uiMaskedTime < 5000)
        return eTrafficLightsState::LIGHT_GREEN;

    if (uiMaskedTime < 6000)
        return eTrafficLightsState::LIGHT_YELLOW;

    return eTrafficLightsState::LIGHT_RED;
}

unsigned char CTrafficLights::LightForCars2()
{
    if (CGameLogic::LaRiotsActiveHere() || CCheat::m_aCheatsActive[eCheats::CHEAT_BGREEN_LIGHTS_CHEAT])
        return eTrafficLightsState::LIGHT_GREEN;

    auto uiMaskedTime = (CTimer::m_snTimeInMilliseconds / 2) & 0x3FFF;
    if (uiMaskedTime < 6000)
        return eTrafficLightsState::LIGHT_RED;

    if (uiMaskedTime < 11000)
        return eTrafficLightsState::LIGHT_GREEN;

    if (uiMaskedTime < 12000)
        return eTrafficLightsState::LIGHT_YELLOW;

    return eTrafficLightsState::LIGHT_RED;
}

unsigned char CTrafficLights::LightForCars1_Visual()
{
    if (CGameLogic::LaRiotsActiveHere()) {
        if ((CTimer::m_snTimeInMilliseconds / 1024) & 1)
            return eTrafficLightsState::LIGHT_OFF;
        else
            return eTrafficLightsState::LIGHT_YELLOW;
    }

    return CTrafficLights::LightForCars1();
}

unsigned char CTrafficLights::LightForCars2_Visual()
{
    if (CGameLogic::LaRiotsActiveHere()) {
        if ((CTimer::m_snTimeInMilliseconds / 1024) & 1)
            return eTrafficLightsState::LIGHT_OFF;
        else
            return eTrafficLightsState::LIGHT_YELLOW;
    }

    return CTrafficLights::LightForCars2();
}
