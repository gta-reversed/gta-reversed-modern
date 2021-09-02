#include "StdInc.h"

COccluder(&COcclusion::aInteriorOccluders)[MAX_INTERIOR_OCCLUDERS] = *(COccluder(*)[MAX_INTERIOR_OCCLUDERS])0xC73CC8;
COccluder(&COcclusion::aOccluders)[MAX_MAP_OCCLUDERS] = *(COccluder(*)[MAX_MAP_OCCLUDERS])0xC73FA0;
CActiveOccluder(&COcclusion::aActiveOccluders)[MAX_ACTIVE_OCCLUDERS] = *(CActiveOccluder(*)[MAX_ACTIVE_OCCLUDERS])0xC78610;

int32& COcclusion::NumInteriorOcculdersOnMap = *(int32*)0xC73CC4;
int32& COcclusion::NumOccludersOnMap = *(int32*)0xC73F98;
int32& COcclusion::NumActiveOccluders = *(int32*)0xC73CC0;
int16& COcclusion::FarAwayList = *(int16*)0x8D5D68;
int16& COcclusion::NearbyList = *(int16*)0x8D5D6C;
int16& COcclusion::ListWalkThroughFA = *(int16*)0x8D5D70;
int16& COcclusion::PreviousListWalkThroughFA = *(int16*)0x8D5D74;

float& COcclusion::gMinXInOccluder = *(float*)0xC73CAC;
float& COcclusion::gMaxXInOccluder = *(float*)0xC73CA8;
float& COcclusion::gMinYInOccluder = *(float*)0xC73CA4;
float& COcclusion::gMaxYInOccluder = *(float*)0xC73CA0;

bool(&COcclusion::gOccluderCoorsValid)[8] = *(bool(*)[8])0xC73CB0;
CVector(&COcclusion::gOccluderCoors)[8] = *(CVector(*)[8])0xC798E0;
CVector(&COcclusion::gOccluderCoorsOnScreen)[8] = *(CVector(*)[8])0xC79950;
CVector& COcclusion::gCenterOnScreen = *(CVector*)0xC79940;

void COcclusion::InjectHooks()
{
    ReversibleHooks::Install("COcclusion", "Init", 0x71DCA0, &COcclusion::Init);
    ReversibleHooks::Install("COcclusion", "AddOne", 0x71DCD0, &COcclusion::AddOne);
    ReversibleHooks::Install("COcclusion", "IsPositionOccluded", 0x7200B0, &COcclusion::IsPositionOccluded);
    ReversibleHooks::Install("COcclusion", "OccluderHidesBehind", 0x71E080 , &COcclusion::OccluderHidesBehind);
    ReversibleHooks::Install("COcclusion", "ProcessBeforeRendering", 0x7201C0, &COcclusion::ProcessBeforeRendering);

    ReversibleHooks::Install("COccluder", "ProcessOneOccluder", 0x71E5D0, &COccluder::ProcessOneOccluder);
    ReversibleHooks::Install("COccluder", "ProcessLineSegment", 0x71E130, &COccluder::ProcessLineSegment);
    ReversibleHooks::Install("COccluder", "NearCamera", 0x71F960, &COccluder::NearCamera);

    ReversibleHooks::Install("CActiveOccluder", "IsPointWithinOcclusionArea", 0x71E580, &CActiveOccluder::IsPointWithinOcclusionArea);
    ReversibleHooks::Install("CActiveOccluder", "IsPointBehindOccluder", 0x71FA40, &CActiveOccluder::IsPointBehindOccluder);
}

// 0x71DCA0
void COcclusion::Init()
{
    NumOccludersOnMap         = 0;
    NumInteriorOcculdersOnMap = 0;
    FarAwayList               = -1;
    NearbyList                = -1;
    ListWalkThroughFA         = -1;
    PreviousListWalkThroughFA = -1;
}

// 0x71DCD0
void COcclusion::AddOne(float centerX, float centerY, float centerZ, float width, float length, float height, float rotZ, float rotY, float rotX, uint32 flags, bool isInterior)
{
    int32 numMissingDimensions = 0;

    auto iWidth = static_cast<int32>(fabs(width));
    auto iLength = static_cast<int32>(fabs(length));
    auto iHeight = static_cast<int32>(fabs(height));

    if (!iLength)
        numMissingDimensions++;
    if (!iWidth)
        numMissingDimensions++;
    if (!iHeight)
        numMissingDimensions++;

    if (numMissingDimensions > 1)
        return;

    // Get the angles in [0 : 360] space and convert to radians
    auto fRotZ = DegreesToRadians(CGeneral::LimitAngle(rotZ) + 180.0F);
    auto fRotY = DegreesToRadians(CGeneral::LimitAngle(rotY) + 180.0F);
    auto fRotX = DegreesToRadians(CGeneral::LimitAngle(rotX) + 180.0F);
    const auto fTwoPiToChar = 256.0F / TWO_PI;

    if (isInterior)
    {
        auto& occluder = aInteriorOccluders[NumInteriorOcculdersOnMap];
        occluder.m_wMidX = centerX * 4.0F;
        occluder.m_wMidY = centerY * 4.0F;
        occluder.m_wMidZ = centerZ * 4.0F;
        occluder.m_wWidth = iWidth * 4.0F;
        occluder.m_wLength = iLength * 4.0F;
        occluder.m_wHeight = iHeight * 4.0F;
        occluder.m_cRotZ = fRotZ * fTwoPiToChar;
        occluder.m_cRotY = fRotY * fTwoPiToChar;
        occluder.m_cRotX = fRotX * fTwoPiToChar;
        ++NumInteriorOcculdersOnMap;
    }
    else
    {
        auto& occluder = aOccluders[NumOccludersOnMap];
        occluder.m_wMidX = centerX * 4.0F;
        occluder.m_wMidY = centerY * 4.0F;
        occluder.m_wMidZ = centerZ * 4.0F;
        occluder.m_wWidth = iWidth * 4.0F;
        occluder.m_wLength = iLength * 4.0F;
        occluder.m_wHeight = iHeight * 4.0F;
        occluder.m_cRotZ = fRotZ * fTwoPiToChar;
        occluder.m_cRotY = fRotY * fTwoPiToChar;
        occluder.m_cRotX = fRotX * fTwoPiToChar;

        if (flags)
            occluder.m_bFarAway = true;
        else
            occluder.m_bFarAway = false;

        occluder.m_nNextIndex = FarAwayList;
        FarAwayList = NumOccludersOnMap;
        ++NumOccludersOnMap;
    }
}

// 0x71E080
bool COcclusion::OccluderHidesBehind(CActiveOccluder* first, CActiveOccluder* second)
{
    if (!first->m_cLinesCount)
        return second->m_cLinesCount == 0;

    for (auto iFirstInd = 0; iFirstInd < first->m_cLinesCount; ++iFirstInd) {
        auto& firstLine = first->m_aLines[iFirstInd];
        for (auto iSecondInd = 0; iSecondInd < second->m_cLinesCount; ++iSecondInd) {
            auto& secondLine = second->m_aLines[iSecondInd];

            if (!IsPointInsideLine(
                secondLine.m_vecOrigin.x,
                secondLine.m_vecOrigin.y,
                secondLine.m_vecDirection.x,
                secondLine.m_vecDirection.y,
                firstLine.m_vecOrigin.x,
                firstLine.m_vecOrigin.y,
                0.0)) {

                return false;
            }

            if (!IsPointInsideLine(
                secondLine.m_vecOrigin.x,
                secondLine.m_vecOrigin.y,
                secondLine.m_vecDirection.x,
                secondLine.m_vecDirection.y,
                firstLine.m_vecOrigin.x + (firstLine.m_fLength * firstLine.m_vecDirection.x),
                firstLine.m_vecOrigin.y + (firstLine.m_fLength * firstLine.m_vecDirection.y),
                0.0)) {

                return false;
            }
        }
    }

    return true;
}

// 0x7200B0
bool COcclusion::IsPositionOccluded(CVector vecPos, float fRadius)
{
    if (!NumActiveOccluders)
        return false;

    CVector outPos;
    float screenX, screenY;
    if (!CalcScreenCoors(vecPos, &outPos, &screenX, &screenY))
        return false;

    const auto fLongEdge = std::max(screenX, screenY);
    auto fScreenRadius = fRadius * fLongEdge;
    auto fScreenDepth = outPos.z - fRadius;

    for (auto ind = 0; ind < NumActiveOccluders; ++ind)
    {
        auto& occluder = aActiveOccluders[ind];
        if (occluder.m_wDepth >= fScreenDepth
            || !occluder.IsPointWithinOcclusionArea(outPos.x, outPos.y, fScreenRadius)
            || !occluder.IsPointBehindOccluder(vecPos, fRadius))
        {
            continue;
        }

        return true;
    }

    return false;
}

// 0x7201C0
void COcclusion::ProcessBeforeRendering()
{
    NumActiveOccluders = 0;
    if (!CGame::currArea) {
        auto listCur = ListWalkThroughFA;
        auto listPrev = ListWalkThroughFA;
        bool skipProcessing = false;
        if (ListWalkThroughFA == -1) {
            listCur = FarAwayList;
            PreviousListWalkThroughFA = ListWalkThroughFA;
            ListWalkThroughFA = FarAwayList;
            if (FarAwayList == -1)
                skipProcessing = true;
        }
        else
            listPrev = PreviousListWalkThroughFA;

        if (!skipProcessing) {
            for (auto i = 0; i < NUM_OCCLUDERS_PROCESSED_PER_FRAME; ++i) {
                if (listCur == -1)
                    break;

                if (aOccluders[listCur].NearCamera()) {
                    if (listPrev == -1)
                        FarAwayList = aOccluders[listCur].m_nNextIndex;
                    else
                        aOccluders[listPrev].m_nNextIndex = aOccluders[listCur].m_nNextIndex;

                    listCur = aOccluders[listCur].m_nNextIndex;
                    aOccluders[ListWalkThroughFA].m_nNextIndex = NearbyList;
                    NearbyList = ListWalkThroughFA;
                }
                else {
                    listPrev = listCur;
                    PreviousListWalkThroughFA = listPrev;
                    listCur = aOccluders[listCur].m_nNextIndex;
                }

                ListWalkThroughFA = listCur;
            }
        }

        auto curInd = NearbyList;
        auto prevInd = -1;
        while (curInd != -1) {
            if (NumActiveOccluders < MAX_ACTIVE_OCCLUDERS) {
                auto bActive = aOccluders[curInd].ProcessOneOccluder(&aActiveOccluders[NumActiveOccluders]);
                if (bActive)
                    ++NumActiveOccluders;
            }

            if (aOccluders[curInd].NearCamera()) {
                prevInd = curInd;
                curInd = aOccluders[curInd].m_nNextIndex;
            }
            else {
                if (prevInd == -1)
                    NearbyList = aOccluders[curInd].m_nNextIndex;
                else
                    aOccluders[prevInd].m_nNextIndex = aOccluders[curInd].m_nNextIndex;

                auto nextInd = aOccluders[curInd].m_nNextIndex;
                aOccluders[curInd].m_nNextIndex = FarAwayList;
                FarAwayList = curInd;
                curInd = nextInd;
            }
        }
    }
    else {
        for (auto i = 0; i < NumInteriorOcculdersOnMap; ++i) {
            if (NumActiveOccluders < MAX_ACTIVE_OCCLUDERS) {
                auto bActive = aInteriorOccluders[i].ProcessOneOccluder(&aActiveOccluders[NumActiveOccluders]);
                if (bActive)
                    ++NumActiveOccluders;
            }
        } 
    }

    for (auto i = 0; i < NumActiveOccluders; ++i) {
        auto* checked = &aActiveOccluders[i];
        for (auto k = 0; k < NumActiveOccluders; ++k) {
            if (i != k
                && aActiveOccluders[k].m_wDepth < checked->m_wDepth
                && OccluderHidesBehind(checked, &aActiveOccluders[k])) {

                auto prev = NumActiveOccluders - 1;
                if (i < prev)
                    *checked = *(checked + 1);

                --NumActiveOccluders;
                k = NumActiveOccluders;
            }
        }
    }
}

bool CActiveOccluder::IsPointWithinOcclusionArea(float fX, float fY, float fRadius)
{
    if (m_cLinesCount <= 0)
        return true;

    for (auto i = 0; i < m_cLinesCount; ++i) {
        auto& line = m_aLines[i];
        if (!IsPointInsideLine(line.m_vecOrigin.x, line.m_vecOrigin.y, line.m_vecDirection.x, line.m_vecDirection.y, fX, fY, fRadius))
            return false;
    }

    return true;
}

bool CActiveOccluder::IsPointBehindOccluder(CVector vecPos, float fRadius)
{
    if (m_cNumVectors <= 0)
        return true;

    for (auto i = 0; i < m_cNumVectors; ++i) {
        const auto& vecCamPos = TheCamera.GetPosition();

        auto fPosDotVec = DotProduct(vecPos, m_aVectors[i]) - m_afRadiuses[i];
        auto fCamDotVec = DotProduct(vecCamPos, m_aVectors[i]) - m_afRadiuses[i];

        if (fCamDotVec * fPosDotVec >= 0.0F || fabs(fPosDotVec) < fRadius)
            return false;
    }

    return true;
}

// 0x71E5D0
bool COccluder::ProcessOneOccluder(CActiveOccluder* pActiveOccluder)
{
    pActiveOccluder->m_cLinesCount = 0;
    auto vecPos = CVector(m_wMidX / 4.0F, m_wMidY / 4.0F, m_wMidZ / 4.0F);
    float temp1, temp2;

    if (!CalcScreenCoors(vecPos, &COcclusion::gCenterOnScreen, &temp1, &temp2) || COcclusion::gCenterOnScreen.z < -150.0F || COcclusion::gCenterOnScreen.z > 300.0F)
        return false;

    auto fMagnitude = CVector(m_wWidth / 4.0F, m_wLength / 4.0F, m_wHeight / 4.0F).Magnitude();
    pActiveOccluder->m_wDepth = COcclusion::gCenterOnScreen.z - fMagnitude;

    auto matRotX = CMatrix();
    auto matRotY = CMatrix();
    auto matRotZ = CMatrix();;
    auto matTransform = CMatrix();

    matRotX.SetRotateX(m_cRotX * PI / 128.0F);
    matRotY.SetRotateY(m_cRotY * PI / 128.0F);
    matRotZ.SetRotateZ(m_cRotZ * PI / 128.0F);
    matTransform = (matRotY * matRotX) * matRotZ;

    COcclusion::gMinXInOccluder = 999999.88F;
    COcclusion::gMinYInOccluder = 999999.88F;
    COcclusion::gMaxXInOccluder = -999999.88F;
    COcclusion::gMaxYInOccluder = -999999.88F;

    if (   m_wLength * 0.25F != 0.0F
        && m_wWidth  * 0.25F != 0.0F
        && m_wHeight * 0.25F != 0.0F) {
        auto vecWidth = CVector(m_wWidth / 8.0F, 0.0F, 0.0F);
        auto vecTransWidth = matTransform * vecWidth;

        auto vecLength = CVector(0.0F, m_wLength / 8.0F, 0.0F);
        auto vecTransLength = matTransform * vecLength;

        auto vecHeight = CVector(0.0F, 0.0F, m_wHeight / 8.0F);
        auto vecTransHeight = matTransform * vecHeight;

        CVector aVecArr[6]{
            vecTransLength, -vecTransLength,
            vecTransWidth, -vecTransWidth,
            vecTransHeight, -vecTransHeight
        };

        // Figure out if we see the front or back of a face
        const auto& vecCamPos = TheCamera.GetPosition();
        bool abOnScreen[6]{
            DotProduct((vecPos + aVecArr[0] - vecCamPos), aVecArr[0]) < 0.0F,
            DotProduct((vecPos + aVecArr[1] - vecCamPos), aVecArr[1]) < 0.0F,
            DotProduct((vecPos + aVecArr[2] - vecCamPos), aVecArr[2]) < 0.0F,
            DotProduct((vecPos + aVecArr[3] - vecCamPos), aVecArr[3]) < 0.0F,
            DotProduct((vecPos + aVecArr[4] - vecCamPos), aVecArr[4]) < 0.0F,
            DotProduct((vecPos + aVecArr[5] - vecCamPos), aVecArr[5]) < 0.0F
        };

        // Calculating vertices of a box
        COcclusion::gOccluderCoors[0] = vecPos + aVecArr[0] + aVecArr[2] + aVecArr[4];
        COcclusion::gOccluderCoors[1] = vecPos + aVecArr[1] + aVecArr[2] + aVecArr[4];
        COcclusion::gOccluderCoors[2] = vecPos + aVecArr[0] + aVecArr[3] + aVecArr[4];
        COcclusion::gOccluderCoors[3] = vecPos + aVecArr[1] + aVecArr[3] + aVecArr[4];
        COcclusion::gOccluderCoors[4] = vecPos + aVecArr[0] + aVecArr[2] + aVecArr[5];
        COcclusion::gOccluderCoors[5] = vecPos + aVecArr[1] + aVecArr[2] + aVecArr[5];
        COcclusion::gOccluderCoors[6] = vecPos + aVecArr[0] + aVecArr[3] + aVecArr[5];
        COcclusion::gOccluderCoors[7] = vecPos + aVecArr[1] + aVecArr[3] + aVecArr[5];

        for (auto i = 0; i < 8; ++i) {
            COcclusion::gOccluderCoorsValid[i] = CalcScreenCoors(COcclusion::gOccluderCoors[i], &COcclusion::gOccluderCoorsOnScreen[i], &temp1, &temp2);
        }

        // Between two differently facing sides we see an edge, so process those
        if (   (abOnScreen[0] == abOnScreen[2] || !ProcessLineSegment(0, 4, pActiveOccluder))
            && (abOnScreen[0] == abOnScreen[3] || !ProcessLineSegment(2, 6, pActiveOccluder))
            && (abOnScreen[0] == abOnScreen[4] || !ProcessLineSegment(0, 2, pActiveOccluder))
            && (abOnScreen[0] == abOnScreen[5] || !ProcessLineSegment(4, 6, pActiveOccluder))
            && (abOnScreen[1] == abOnScreen[2] || !ProcessLineSegment(1, 5, pActiveOccluder))
            && (abOnScreen[1] == abOnScreen[3] || !ProcessLineSegment(3, 7, pActiveOccluder))
            && (abOnScreen[1] == abOnScreen[4] || !ProcessLineSegment(1, 3, pActiveOccluder))
            && (abOnScreen[1] == abOnScreen[5] || !ProcessLineSegment(5, 7, pActiveOccluder))
            && (abOnScreen[2] == abOnScreen[4] || !ProcessLineSegment(0, 1, pActiveOccluder))
            && (abOnScreen[3] == abOnScreen[4] || !ProcessLineSegment(2, 3, pActiveOccluder))
            && (abOnScreen[3] == abOnScreen[5] || !ProcessLineSegment(6, 7, pActiveOccluder))
            && (abOnScreen[2] == abOnScreen[5] || !ProcessLineSegment(4, 5, pActiveOccluder))
            && SCREEN_WIDTH * 0.15F <= COcclusion::gMaxXInOccluder - COcclusion::gMinXInOccluder
            && SCREEN_HEIGHT * 0.1F <= COcclusion::gMaxYInOccluder - COcclusion::gMinYInOccluder) {

            pActiveOccluder->m_cNumVectors = 0;
            for (auto i = 0; i < 6; ++i) {
                if (abOnScreen[i]) {
                    auto vecNormalised = CVector(aVecArr[i]);
                    vecNormalised.Normalise();
                    auto vecScreenPos = vecPos + aVecArr[i];

                    pActiveOccluder->m_aVectors[pActiveOccluder->m_cNumVectors] = vecNormalised;
                    pActiveOccluder->m_afRadiuses[pActiveOccluder->m_cNumVectors] = DotProduct(vecScreenPos, vecNormalised);
                    ++pActiveOccluder->m_cNumVectors;
                }
            }
            return true;
        }

        return false;
    }

    CVector vec1, vec2;
    if (m_wLength * 0.25F == 0.0F) {
        auto vecWidth = CVector(m_wWidth / 8.0F, 0.0F, 0.0F);
        vec1 = matTransform * vecWidth;

        auto vecHeight = CVector(0.0F, 0.0F, m_wHeight / 8.0F);
        vec2 = matTransform * vecHeight;
    }
    else if (m_wWidth * 0.25F == 0.0F) {
        auto vecLength = CVector(0.0F, m_wLength / 8.0F, 0.0F);
        vec1 = matTransform * vecLength;

        auto vecHeight = CVector(0.0F, 0.0F, m_wHeight / 8.0F);
        vec2 = matTransform * vecHeight;
    }
    else if (m_wHeight * 0.25F == 0.0F) {
        auto vecLength = CVector(0.0F, m_wLength / 8.0F, 0.0F);
        vec1 = matTransform * vecLength;

        auto vecWidth = CVector(m_wWidth / 8.0F, 0.0F, 0.0F);
        vec2 = matTransform * vecWidth;
    }

    COcclusion::gOccluderCoors[0] = vecPos + vec1 + vec2;
    COcclusion::gOccluderCoors[1] = vecPos - vec1 + vec2;
    COcclusion::gOccluderCoors[2] = vecPos - vec1 - vec2;
    COcclusion::gOccluderCoors[3] = vecPos + vec1 - vec2;

    for (auto i = 0; i < 4; ++i) {
        COcclusion::gOccluderCoorsValid[i] = CalcScreenCoors(COcclusion::gOccluderCoors[i], &COcclusion::gOccluderCoorsOnScreen[i], &temp1, &temp2);
    }

    if (   !ProcessLineSegment(0, 1, pActiveOccluder)
        && !ProcessLineSegment(1, 2, pActiveOccluder)
        && !ProcessLineSegment(2, 3, pActiveOccluder)
        && !ProcessLineSegment(3, 0, pActiveOccluder)
        && SCREEN_WIDTH  * 0.1F  <= COcclusion::gMaxXInOccluder - COcclusion::gMinXInOccluder
        && SCREEN_HEIGHT * 0.07F <= COcclusion::gMaxYInOccluder - COcclusion::gMinYInOccluder){

        auto vecCross = CrossProduct(vec1, vec2);
        vecCross.Normalise();

        pActiveOccluder->m_aVectors[0] = vecCross;
        pActiveOccluder->m_afRadiuses[0] = DotProduct(vecCross, vecPos);
        pActiveOccluder->m_cNumVectors = 1;

        return true;
    }

    return false;
}

// 0x71E130
bool COccluder::ProcessLineSegment(int32 iIndFrom, int32 iIndTo, CActiveOccluder* pActiveOccluder)
{
    if (!COcclusion::gOccluderCoorsValid[iIndFrom] && !COcclusion::gOccluderCoorsValid[iIndTo])
        return true;

    CVector vecScreenFrom, vecScreenTo;
    if (COcclusion::gOccluderCoorsValid[iIndFrom]) {
        vecScreenFrom = COcclusion::gOccluderCoorsOnScreen[iIndFrom];
    }
    else {
        auto fFromDepth = fabs((TheCamera.m_mViewMatrix * COcclusion::gOccluderCoors[iIndFrom]).z - 1.1F);
        auto fToDepth = fabs((TheCamera.m_mViewMatrix * COcclusion::gOccluderCoors[iIndTo]).z - 1.1F);

        auto fProgress = fToDepth / (fFromDepth + fToDepth);
        vecScreenFrom = (1.0F - fProgress) * COcclusion::gOccluderCoors[iIndTo];
        vecScreenTo = vecScreenFrom + fProgress * COcclusion::gOccluderCoors[iIndFrom];

        float fTemp1, fTemp2;
        if (!CalcScreenCoors(vecScreenTo, &vecScreenFrom, &fTemp1, &fTemp2))
            return true;
    }

    if (COcclusion::gOccluderCoorsValid[iIndTo]) {
        vecScreenTo = COcclusion::gOccluderCoorsOnScreen[iIndTo];
    }
    else {
        auto fFromDepth = fabs((TheCamera.m_mViewMatrix * COcclusion::gOccluderCoors[iIndFrom]).z - 1.1F);
        auto fToDepth = fabs((TheCamera.m_mViewMatrix * COcclusion::gOccluderCoors[iIndTo]).z - 1.1F);

        auto fProgress = fToDepth / (fFromDepth + fToDepth);
        auto vecFrom = (1.0F - fProgress) * COcclusion::gOccluderCoors[iIndTo];
        auto vecTo = vecFrom + fProgress * COcclusion::gOccluderCoors[iIndFrom];

        float fTemp1, fTemp2;
        if (!CalcScreenCoors(vecTo, &vecScreenTo, &fTemp1, &fTemp2))
            return true;
    }

    COcclusion::gMinXInOccluder = std::min({ COcclusion::gMinXInOccluder, vecScreenFrom.x, vecScreenTo.x });
    COcclusion::gMaxXInOccluder = std::max({ COcclusion::gMaxXInOccluder, vecScreenFrom.x, vecScreenTo.x });
    COcclusion::gMinYInOccluder = std::min({ COcclusion::gMinYInOccluder, vecScreenFrom.y, vecScreenTo.y });
    COcclusion::gMaxYInOccluder = std::max({ COcclusion::gMaxYInOccluder, vecScreenFrom.y, vecScreenTo.y });

    auto fXSize = vecScreenTo.x - vecScreenFrom.x;
    auto fYSize = vecScreenTo.y - vecScreenFrom.y;
    auto fFromX = vecScreenFrom.x;
    auto fFromY = vecScreenFrom.y;

    if (!IsPointInsideLine(vecScreenFrom.x, vecScreenFrom.y, fXSize, fYSize, COcclusion::gCenterOnScreen.x, COcclusion::gCenterOnScreen.y, 0.0F)) {
        fFromX = vecScreenFrom.x + fXSize;
        fFromY = vecScreenFrom.y + fYSize;
        fXSize = -fXSize;
        fYSize = -fYSize;
    }

    auto& pCurLine = pActiveOccluder->m_aLines[pActiveOccluder->m_cLinesCount];
    pCurLine.m_fLength = CVector2D(fXSize, fYSize).Magnitude();

    auto fRecip = 1.0F / pCurLine.m_fLength;
    pCurLine.m_vecOrigin.Set(fFromX, fFromY);
    pCurLine.m_vecDirection.Set(fRecip * fXSize, fRecip * fYSize);

    if (DoesInfiniteLineTouchScreen(fFromX, fFromY, pCurLine.m_vecDirection.x, pCurLine.m_vecDirection.y)) {
        ++pActiveOccluder->m_cLinesCount;
        return false;
    }

    return !IsPointInsideLine(fFromX, fFromY, pCurLine.m_vecDirection.x, pCurLine.m_vecDirection.y, SCREEN_WIDTH * 0.5F, SCREEN_HEIGHT * 0.5F, 0.0F);
}

// 0x71F960
bool COccluder::NearCamera()
{
    auto fSize = std::max(m_wLength / 4.0F, m_wWidth / 4.0F);
    const auto& vecCamPos = TheCamera.GetPosition();
    auto vecPos = CVector(m_wMidX, m_wMidY, m_wMidZ) / 4.0F;

    auto fDist = DistanceBetweenPoints(vecPos, vecCamPos);
    return (fDist - fSize / 2.0F) < 250.0F;
}
