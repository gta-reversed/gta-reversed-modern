#include "StdInc.h"

void CCover::InjectHooks()
{
    ReversibleHooks::Install("CCover", "ShouldThisBuildingHaveItsCoverPointsCreated", 0x699230, &CCover::ShouldThisBuildingHaveItsCoverPointsCreated);
    ReversibleHooks::Install("CCover", "FindCoverPointsForThisBuilding", 0x699120, &CCover::FindCoverPointsForThisBuilding);
}

void CCover::AddCoverPoint(int32 maxPeds, CEntity* coverEntity, CVector* position, char coverType, uint8 direction)
{
    plugin::Call<0x698F30, int32, CEntity*, CVector*, char, uint8>(maxPeds, coverEntity, position, coverType, direction);
}

void CCover::FindCoverPointsForThisBuilding(CBuilding* building)
{
    auto* pInfo = CModelInfo::GetModelInfo(building->m_nModelIndex);
    if (!pInfo->m_n2dfxCount)
        return;

    for (int32 iFxInd = 0; iFxInd < pInfo->m_n2dfxCount; ++iFxInd) {
        auto* pEffect = pInfo->Get2dEffect(iFxInd);
        if (pEffect->m_nType != e2dEffectType::EFFECT_COVER_POINT)
            continue;

        auto vecDir = CVector(pEffect->coverPoint.m_vecDirection.x, pEffect->coverPoint.m_vecDirection.y, 0.0F);
        const auto vedTransformed = Multiply3x3(building->GetMatrix(), vecDir);

        const auto fTwoPiToChar = 256.0F / TWO_PI;
        const auto ucAngle = static_cast<uint8>(atan2(vedTransformed.x, vedTransformed.y) * fTwoPiToChar);
        auto vecPoint = building->GetMatrix() * pEffect->m_vecPosn;
        CCover::AddCoverPoint(3, building, &vecPoint, pEffect->coverPoint.m_nType, ucAngle);
    }
}

void CCover::Init() {
    plugin::Call<0x698710>();
}

bool CCover::ShouldThisBuildingHaveItsCoverPointsCreated(CBuilding* building)
{
    const auto vecPos = FindPlayerCoors(-1);
    CVector vecCenter;
    building->GetBoundCentre(vecCenter);
    auto distance = vecCenter - vecPos;
    auto* pInfo = CModelInfo::GetModelInfo(building->m_nModelIndex);
    return distance.Magnitude() <= pInfo->GetColModel()->GetBoundRadius() + 30.0F;
}
