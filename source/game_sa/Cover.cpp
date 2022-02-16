#include "StdInc.h"

#include "Cover.h"

void CCover::InjectHooks() {
    RH_ScopedClass(CCover);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(ShouldThisBuildingHaveItsCoverPointsCreated, 0x699230);
    RH_ScopedInstall(FindCoverPointsForThisBuilding, 0x699120);
}

void CCover::Init() {
    plugin::Call<0x698710>();
}

void CCover::AddCoverPoint(int32 maxPeds, CEntity* coverEntity, CVector* position, char coverType, uint8 direction) {
    plugin::Call<0x698F30, int32, CEntity*, CVector*, char, uint8>(maxPeds, coverEntity, position, coverType, direction);
}

void CCover::FindCoverPointsForThisBuilding(CBuilding* building) {
    auto* mi = CModelInfo::GetModelInfo(building->m_nModelIndex);
    if (!mi->m_n2dfxCount)
        return;

    for (int32 iFxInd = 0; iFxInd < mi->m_n2dfxCount; ++iFxInd) {
        auto* effect = mi->Get2dEffect(iFxInd);
        if (effect->m_nType != e2dEffectType::EFFECT_COVER_POINT)
            continue;

        auto vecDir = CVector(effect->coverPoint.m_vecDirection.x, effect->coverPoint.m_vecDirection.y, 0.0F);
        const auto vedTransformed = Multiply3x3(building->GetMatrix(), vecDir);

        const auto fTwoPiToChar = 256.0F / TWO_PI;
        const auto ucAngle = static_cast<uint8>(atan2(vedTransformed.x, vedTransformed.y) * fTwoPiToChar);
        auto vecPoint = building->GetMatrix() * effect->m_vecPosn;
        CCover::AddCoverPoint(3, building, &vecPoint, effect->coverPoint.m_nType, ucAngle);
    }
}

bool CCover::ShouldThisBuildingHaveItsCoverPointsCreated(CBuilding* building) {
    const auto vecPos = FindPlayerCoors(-1);
    CVector vecCenter;
    building->GetBoundCentre(vecCenter);
    auto distance = vecCenter - vecPos;
    auto* mi = CModelInfo::GetModelInfo(building->m_nModelIndex);
    return distance.Magnitude() <= mi->GetColModel()->GetBoundRadius() + 30.0F;
}
