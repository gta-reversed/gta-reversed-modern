#include "StdInc.h"

RwTexture*& CCustomRoadsignMgr::pCharsetTex = *(RwTexture**)0xC3EF84;
RwUInt8*& CCustomRoadsignMgr::pCharsetLockedRaster = *(RwUInt8**)0xC3EF88;
RwUInt8*& CCustomRoadsignMgr::pCharsetLockedPallete = *(RwUInt8**)0xC3EF8C;

void CCustomRoadsignMgr::InjectHooks()
{
    RH_ScopedClass(CCustomRoadsignMgr);
    RH_ScopedCategoryRoot();

    RH_ScopedInstall(Initialise, 0x6FE120);
    RH_ScopedInstall(Shutdown, 0x6FE180);
    RH_ScopedInstall(CreateRoadsignTexture, 0x6FECA0);
    RH_ScopedInstall(CreateRoadsignAtomicA, 0x6FEDA0);
    RH_ScopedInstall(CreateRoadsignAtomic, 0x6FF2D0);
    RH_ScopedInstall(RenderRoadsignAtomic, 0x6FF350);
    RH_ScopedInstall(SetupRoadsignAtomic, 0x6FED60);
    RH_ScopedInstall(SetAtomicAlpha, 0x6FE240);
    RH_ScopedInstall(RoadsignGenerateTextRaster, 0x6FEB70);
}

bool CCustomRoadsignMgr::Initialise()
{
    const auto iTxdSlot = CTxdStore::FindTxdSlot("particle");
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(iTxdSlot);

    auto* pTexture = RwTextureRead("roadsignfont", nullptr);
    RwTextureSetFilterMode(pTexture, rwFILTERNEAREST);
    RwTextureSetAddressing(pTexture, rwTEXTUREADDRESSCLAMP);
    CCustomRoadsignMgr::pCharsetTex = pTexture;

    CTxdStore::PopCurrentTxd();
    CCustomRoadsignMgr::pCharsetLockedRaster = RwRasterLock(RwTextureGetRaster(pTexture), 0, rwRASTERLOCKREAD);
    return true;
}

void CCustomRoadsignMgr::Shutdown()
{
    if (!CCustomRoadsignMgr::pCharsetTex)
        return;

    auto* pRaster = RwTextureGetRaster(CCustomRoadsignMgr::pCharsetTex);

    if (CCustomRoadsignMgr::pCharsetLockedPallete)
    {
        RwRasterUnlockPalette(pRaster);
        CCustomRoadsignMgr::pCharsetLockedPallete = nullptr;
    }

    if(CCustomRoadsignMgr::pCharsetLockedRaster)
    {
        RwRasterUnlock(pRaster);
        CCustomRoadsignMgr::pCharsetLockedRaster = nullptr;
    }

    RwTextureDestroy(CCustomRoadsignMgr::pCharsetTex);
    CCustomRoadsignMgr::pCharsetTex = nullptr;
}

RwTexture* CCustomRoadsignMgr::CreateRoadsignTexture(char* pName, int32 numOfChars)
{
    auto* pRaster = RwRasterCreate(SIGN_CHAR_WIDTH * numOfChars, SIGN_CHAR_HEIGHT, 32, rwRASTERFORMAT8888 | rwRASTERPIXELLOCKEDWRITE);
    assert(pRaster); //TODO: Remove if crash cause is found
    if (!pRaster)
        return nullptr;

    auto* pCharsetRaster = RwTextureGetRaster(CCustomRoadsignMgr::pCharsetTex);
    assert(pCharsetRaster); //TODO: Remove if crash cause is found
    if (!pCharsetRaster)
    {
        RwRasterDestroy(pRaster);
        return nullptr;
    }

    const auto bGenerated = RoadsignGenerateTextRaster(pName, numOfChars, pCharsetRaster, 0, pRaster);
    assert(bGenerated); //TODO: Remove if crash cause is found
    if (!bGenerated)
    {
        RwRasterDestroy(pRaster);
        return nullptr;
    }

    auto* pTexture = RwTextureCreate(pRaster);
    assert(pTexture); //TODO: Remove if crash cause is found
    if (!pTexture)
    {
        RwRasterDestroy(pRaster);
        return nullptr;
    }

    char nameCopy[12] {};
    strncpy(nameCopy, pName, 10);
    RwTextureSetName(pTexture, nameCopy);
    RwTextureSetFilterMode(pTexture, rwFILTERLINEAR);
    return pTexture;
}

RwTexture* CCustomRoadsignMgr::SetupRoadsignAtomic(RpAtomic* pAtomic, char* pName, int32 numOfChars)
{
    auto* pTexture = CCustomRoadsignMgr::CreateRoadsignTexture(pName, numOfChars);
    if (!pTexture)
        return nullptr;

    RpGeometryForAllMaterials(RpAtomicGetGeometry(pAtomic), RoadsignSetMaterialTextureCB, pTexture);
    return reinterpret_cast<RwTexture*>(pAtomic); //BUG? This method isn't used anywhere anyways
}

RpAtomic* CCustomRoadsignMgr::SetAtomicAlpha(RpAtomic* pAtomic, uint8 alpha)
{
    RpGeometryForAllMaterials(RpAtomicGetGeometry(pAtomic), RoadsignSetMaterialAlphaCB, reinterpret_cast<void*>(alpha));
    return pAtomic;
}

RpAtomic* CCustomRoadsignMgr::CreateRoadsignAtomicA(float fWidth, float fHeight, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int32 lettersPerLine, uint8 ucPallete)
{
    char* apLines[]{ pLine1, pLine2, pLine3, pLine4 };
    RpMaterial* apMaterials[4]{};

    bool bFailed = false;
    for (auto ind = 0; ind < numLines; ++ind)
    {
        auto* pMaterial = RpMaterialCreate();
        assert(pMaterial); //TODO: Remove if crash cause is found
        if (!pMaterial)
        {
            bFailed = true;
            break;
        }

        auto color = CRGBA();
        color.a = 255u;
        if (ucPallete == 1)
            color.Set(0u, 0u, 0u);
        else if (ucPallete == 2)
            color.Set(128u, 128u, 128u);
        else if (ucPallete == 3)
            color.Set(255u, 0u, 0u);
        else
            color.Set(255u, 255u, 255u);

        auto rwColor = color.ToRwRGBA();
        RpMaterialSetColor(pMaterial, &rwColor);

        auto* pTexture = CCustomRoadsignMgr::CreateRoadsignTexture(apLines[ind], lettersPerLine);
        assert(pTexture); //TODO: Remove if crash cause is found
        if (!pTexture)
        {
            bFailed = true;
            break;
        }

        RpMaterialSetTexture(pMaterial, pTexture);
        RwTextureDestroy(pTexture); // decrement refcounter so the material is sole owner of the texture
        apMaterials[ind] = pMaterial;

        auto surfProps = RwSurfaceProperties{ 0.3F, 0.3F, 0.7F };
        RpMaterialSetSurfaceProperties(pMaterial, &surfProps);
    }

    if (!bFailed)
    {
        do
        {
            auto* pGeometry = RpGeometryCreate(4 * numLines, 2 * numLines, rpGEOMETRYMODULATEMATERIALCOLOR | rpGEOMETRYPRELIT | rpGEOMETRYTEXTURED | rpGEOMETRYPOSITIONS);
            assert(pGeometry); //TODO: Remove if crash cause is found
            if (!pGeometry)
                break; // Go to cleanup

            auto* pMorphTarget = RpGeometryGetMorphTarget(pGeometry, 0);
            const auto fLineHeight = fHeight / static_cast<float>(numLines);
            const auto fUsedLineHeight = fLineHeight * 0.95F;
            const auto fNegHalfWidth = fWidth * -0.5F;
            for (auto iLine = 0 ; iLine < numLines; ++iLine)
            {
                auto* pVerts = &RpMorphTargetGetVertices(pMorphTarget)[iLine * 4];
                //TODO/BUG? This seems like base init of values, that is overriden completely just a bit later
                /*pVerts[0] = { 0.0F, 0.0F, 0.0F };
                pVerts[1] = { xScale, 0.0F, 0.0F };
                pVerts[2] = { xScale, fLineY * 0.95F, 0.0F };
                pVerts[3] = { 0.0F, fLineY * 0.95F , 0.0F };*/ 

                auto fNewY = 0.0F;
                switch(numLines)
                {
                case 1:
                    fNewY = fLineHeight * -0.5F;
                    break;

                case 2:
                    if (iLine == 0)
                        fNewY = 0.0F;
                    else if (iLine == 1)
                        fNewY = fLineHeight * -1.0F;
                    break;

                case 3:
                    if (iLine == 0)
                        fNewY = fLineHeight * 0.5F;
                    else if (iLine == 1)
                        fNewY = fLineHeight * -0.5F;
                    else if (iLine == 2)
                        fNewY = fLineHeight * -1.5F;
                    break;

                case 4:
                    if (iLine == 0)
                        fNewY = fLineHeight;
                    else if (iLine == 1)
                        fNewY = 0.0F;
                    else if (iLine == 2)
                        fNewY = fLineHeight * -1.0F;
                    else if (iLine == 3)
                        fNewY = fLineHeight * -2.0F;
                    break;
                }

                // Adjust the verts based on the above calculations
                pVerts[0] = { fNegHalfWidth, fNewY, 0.0F };
                pVerts[1] = { fNegHalfWidth + fWidth, fNewY, 0.0F };
                pVerts[2] = { fNegHalfWidth + fWidth, fNewY + fUsedLineHeight, 0.0F };
                pVerts[3] = { fNegHalfWidth, fNewY + fUsedLineHeight, 0.0F };
            }

            for (auto iLine = 0; iLine < numLines; ++iLine)
            {
                auto* pTexCoords = &RpGeometryGetVertexTexCoords(pGeometry, rwTEXTURECOORDINATEINDEX0)[iLine * 4];
                pTexCoords[0] = { 0.0F, 1.0F };
                pTexCoords[1] = { 1.0F, 1.0F };
                pTexCoords[2] = { 1.0F, 0.0F };
                pTexCoords[3] = { 0.0F, 0.0F };
            }

            for (auto iLine = 0; iLine < numLines; ++iLine)
            {
                auto* pColors = &RpGeometryGetPreLightColors(pGeometry)[iLine * 4];
                pColors[0] = { 255u, 255u, 255u, 255u };
                pColors[1] = { 255u, 255u, 255u, 255u };
                pColors[2] = { 255u, 255u, 255u, 255u };
                pColors[3] = { 255u, 255u, 255u, 255u };
            }

            for (auto iLine = 0; iLine < numLines; ++iLine)
            {
                const auto iVert = iLine * 4;
                auto* pTriangles = &RpGeometryGetTriangles(pGeometry)[iLine * 2];
                RpGeometryTriangleSetVertexIndices(pGeometry, &pTriangles[0], iVert, iVert + 1, iVert + 2);
                RpGeometryTriangleSetMaterial(pGeometry, &pTriangles[0], apMaterials[iLine]);
                RpGeometryTriangleSetVertexIndices(pGeometry, &pTriangles[1], iVert, iVert + 2, iVert + 3);
                RpGeometryTriangleSetMaterial(pGeometry, &pTriangles[1], apMaterials[iLine]);

                RpMaterialDestroy(apMaterials[iLine]);
                apMaterials[iLine] = nullptr;
            }

            RwSphere bndSphere;
            RpMorphTargetCalcBoundingSphere(pMorphTarget, &bndSphere);
            RpMorphTargetSetBoundingSphere(pMorphTarget, &bndSphere);
            RpGeometryUnlock(pGeometry);
            auto* pAtomic = RpAtomicCreate();
            assert(pAtomic); //TODO: Remove if crash cause is found
            if (!pAtomic)
            {
                RpGeometryDestroy(pGeometry);
                break; // Go to cleanup
            }

            if (!RpAtomicSetGeometry(pAtomic, pGeometry, 0))
            {
                assert(false); //TODO: Remove if crash cause is found
                RpGeometryDestroy(pGeometry);
                RpAtomicDestroy(pAtomic);
                break; // Go to cleanup
            }

            RpGeometryDestroy(pGeometry);
            RpAtomicSetFlags(pAtomic, rpATOMICRENDER);
            auto* pFrame = RwFrameCreate();
            RwFrameSetIdentity(pFrame);
            RpAtomicSetFrame(pAtomic, pFrame);
            return pAtomic;

        } while (false); // So we can easily break out of the logic to destroy materials, would be nice to make it cleaner
    }


    for(auto& pMaterial : apMaterials)
        if (pMaterial)
            RpMaterialDestroy(pMaterial);

    return nullptr;
}

RpAtomic* CCustomRoadsignMgr::CreateRoadsignAtomic(float xScale, float yScale, signed int numLines, char* pLine1, char* pLine2, char* pLine3, char* pLine4, int32 lettersPerLine, uint8 ucPallete)
{
    char dummy = ' ';
    auto* usedLine1 = pLine1 ? pLine1 : &dummy;
    auto* usedLine2 = pLine2 ? pLine2 : &dummy;
    auto* usedLine3 = pLine3 ? pLine3 : &dummy;
    auto* usedLine4 = pLine4 ? pLine4 : &dummy;

    auto* pAtomic = CCustomRoadsignMgr::CreateRoadsignAtomicA(xScale, yScale, numLines, usedLine1, usedLine2, usedLine3, usedLine4, lettersPerLine, ucPallete);
    assert(pAtomic); //TODO: Remove if crash cause is found
    return pAtomic;
}

RpAtomic* CCustomRoadsignMgr::RenderRoadsignAtomic(RpAtomic* pAtomic, CVector const& vecPos)
{
    auto* pFrame = RpAtomicGetFrame(pAtomic);
    auto vecDist = vecPos - *RwMatrixGetPos(RwFrameGetMatrix(pFrame));
    const auto fDistSquared = vecDist.SquaredMagnitude();
    if (fDistSquared > 250000.0F) // 500 units away
        return pAtomic;

    if (fDistSquared >= 1600.0F) { // Fade out above 40 units away
        const auto fFade =  1.0F - invLerp(1600, 250000, fDistSquared);
        const auto ucAlpha = static_cast<RwUInt8>(lerp(0.0F, 254.0F, fFade));
        CCustomRoadsignMgr::SetAtomicAlpha(pAtomic, ucAlpha);
        RpAtomicRender(pAtomic);
        return pAtomic;
    }

    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(100u));
    CCustomRoadsignMgr::SetAtomicAlpha(pAtomic, 255u);
    RpAtomicRender(pAtomic);
    return pAtomic;

}

RpMaterial* RoadsignSetMaterialAlphaCB(RpMaterial* material, void* data)
{
    RpMaterialGetColor(material)->alpha = (RwUInt8)data;
    return material;
}

RpMaterial* RoadsignSetMaterialTextureCB(RpMaterial* material, void* data)
{
    RpMaterialSetTexture(material, static_cast<RwTexture*>(data));
    return material;
}

bool RoadsignGenerateTextRaster(char* roadName, int32 numLetters, RwRaster* charsetRaster, int32 unused, RwRaster* signRaster)
{
    auto* signLock = reinterpret_cast<RwRGBA*>(RwRasterLock(signRaster, 0, rwRASTERLOCKWRITE | rwRASTERLOCKNOFETCH));
    if (!signLock)
        return false;

    if (!CCustomRoadsignMgr::pCharsetLockedRaster)
        return false;

    const auto charStride = charsetRaster->stride; //TODO: Missing RwRasterGetStride macro;
    if (!charStride)
        return false;
    
    const auto signStride = signRaster->stride; //TODO: Same as above
    if (!signStride)
        return false;

    const auto usedCharStride = charStride / SIGN_PIXEL_BYTES; // Those 3 are used to make pointer math easier
    const auto usedSignStride = signStride / SIGN_PIXEL_BYTES;
    auto* pCharsetLock = reinterpret_cast<RwRGBA*>(CCustomRoadsignMgr::pCharsetLockedRaster);

    for (auto ind = 0; ind < numLetters; ++ind)
    {
        int32 col = 1, row = 1;
        RoadsignGetLineAndRow(roadName[ind], &col, &row);
        auto* pCharsetPixels = &pCharsetLock[usedCharStride * SIGN_CHAR_HEIGHT * row + SIGN_CHAR_WIDTH * col];
        auto* pSignPixels = &signLock[ind * SIGN_CHAR_WIDTH];
        for (auto iRow = 0; iRow < SIGN_CHAR_HEIGHT; ++iRow)
        {
            for (auto iCol = 0; iCol < SIGN_CHAR_WIDTH; ++iCol)
                pSignPixels[iCol] = pCharsetPixels[iCol]; // Copy pixels one by one

            pSignPixels += usedSignStride;
            pCharsetPixels += usedCharStride;
        }
    }

    RwRasterUnlock(signRaster);
    return true;
}

void RoadsignGetLineAndRow(char cLetter, int32* line, int32* row)
{
    switch (cLetter)
    {
    case '!':
        *line = 0;
        *row = 0;
        break;
    case '#':
        *line = 3;
        *row = 21;
        break;
    case '$':
        *line = 0;
        *row = 22;
        break;
    case '%':
        *line = 2;
        *row = 21;
        break;
    case '&':
        *line = 2;
        *row = 0;
        break;
    case '(':
        *line = 0;
        *row = 1;
        break;
    case ')':
        *line = 1;
        *row = 1;
        break;
    case '*':
        *line = 1;
        *row = 22;
        break;
    case '+':
        *line = 2;
        *row = 1;
        break;
    case '-':
        *line = 0;
        *row = 2;
        break;
    case '.':
        *line = 1;
        *row = 2;
        break;
    case '0':
        *line = 3;
        *row = 2;
        break;
    case '1':
        *line = 0;
        *row = 3;
        break;
    case '2':
        *line = 1;
        *row = 3;
        break;
    case '3':
        *line = 2;
        *row = 3;
        break;
    case '4':
        *line = 3;
        *row = 3;
        break;
    case '5':
        *line = 0;
        *row = 4;
        break;
    case '6':
        *line = 1;
        *row = 4;
        break;
    case '7':
        *line = 2;
        *row = 4;
        break;
    case '8':
        *line = 3;
        *row = 4;
        break;
    case '9':
        *line = 0;
        *row = 5;
        break;
    case ':':
        *line = 2;
        *row = 5;
        break;
    case ';':
        *line = 1;
        *row = 5;
        break;
    case '<':
        *line = 2;
        *row = 20;
        break;
    case '>':
        *line = 3;
        *row = 20;
        break;
    case '?':
        *line = 3;
        *row = 5;
        break;
    case '@':
        *line = 2;
        *row = 22;
        break;
    case 'A':
        *line = 0;
        *row = 6;
        break;
    case 'B':
        *line = 1;
        *row = 6;
        break;
    case 'C':
        *line = 2;
        *row = 6;
        break;
    case 'D':
        *line = 3;
        *row = 6;
        break;
    case 'E':
        *line = 0;
        *row = 7;
        break;
    case 'F':
        *line = 1;
        *row = 7;
        break;
    case 'G':
        *line = 2;
        *row = 7;
        break;
    case 'H':
        *line = 3;
        *row = 7;
        break;
    case 'I':
        *line = 0;
        *row = 8;
        break;
    case 'J':
        *line = 1;
        *row = 8;
        break;
    case 'K':
        *line = 2;
        *row = 8;
        break;
    case 'L':
        *line = 3;
        *row = 8;
        break;
    case 'M':
        *line = 0;
        *row = 9;
        break;
    case 'N':
        *line = 1;
        *row = 9;
        break;
    case 'O':
        *line = 2;
        *row = 9;
        break;
    case 'P':
        *line = 3;
        *row = 9;
        break;
    case 'Q':
        *line = 0;
        *row = 10;
        break;
    case 'R':
        *line = 1;
        *row = 10;
        break;
    case 'S':
        *line = 2;
        *row = 10;
        break;
    case 'T':
        *line = 3;
        *row = 10;
        break;
    case 'U':
        *line = 0;
        *row = 11;
        break;
    case 'V':
        *line = 1;
        *row = 11;
        break;
    case 'W':
        *line = 2;
        *row = 11;
        break;
    case 'X':
        *line = 3;
        *row = 11;
        break;
    case 'Y':
        *line = 0;
        *row = 12;
        break;
    case 'Z':
        *line = 1;
        *row = 12;
        break;
    case '[':
        *line = 2;
        *row = 12;
        break;
    case ']':
        *line = 0;
        *row = 13;
        break;
    case '^':
        *line = 0;
        *row = 21;
        break;
    case 'a':
        *line = 1;
        *row = 13;
        break;
    case 'b':
        *line = 2;
        *row = 13;
        break;
    case 'c':
        *line = 3;
        *row = 13;
        break;
    case 'd':
        *line = 0;
        *row = 14;
        break;
    case 'e':
        *line = 1;
        *row = 14;
        break;
    case 'f':
        *line = 2;
        *row = 14;
        break;
    case 'g':
        *line = 3;
        *row = 14;
        break;
    case 'h':
        *line = 0;
        *row = 15;
        break;
    case 'i':
        *line = 1;
        *row = 15;
        break;
    case 'j':
        *line = 2;
        *row = 15;
        break;
    case 'k':
        *line = 3;
        *row = 15;
        break;
    case 'l':
        *line = 0;
        *row = 16;
        break;
    case 'm':
        *line = 1;
        *row = 16;
        break;
    case 'n':
        *line = 2;
        *row = 16;
        break;
    case 'o':
        *line = 3;
        *row = 16;
        break;
    case 'p':
        *line = 0;
        *row = 17;
        break;
    case 'q':
        *line = 1;
        *row = 17;
        break;
    case 'r':
        *line = 2;
        *row = 17;
        break;
    case 's':
        *line = 3;
        *row = 17;
        break;
    case 't':
        *line = 0;
        *row = 18;
        break;
    case 'u':
        *line = 1;
        *row = 18;
        break;
    case 'v':
        *line = 2;
        *row = 18;
        break;
    case 'w':
        *line = 3;
        *row = 18;
        break;
    case 'x':
        *line = 0;
        *row = 19;
        break;
    case 'y':
        *line = 1;
        *row = 19;
        break;
    case 'z':
        *line = 2;
        *row = 19;
        break;
    case '{':
        *line = 0;
        *row = 23;
        break;
    case '|':
        *line = 3;
        *row = 22;
        break;
    case '}':
        *line = 2;
        *row = 23;
        break;
    case '~':
        *line = 1;
        *row = 21;
        break;
    default:
        *line = 0;
        *row = 26;
        break;
    }
}
