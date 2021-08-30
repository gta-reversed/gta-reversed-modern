#include "StdInc.h"

uint32_t& CShinyTexts::NumShinyTexts = *(uint32_t*)0xC7C6F8;
CRegisteredShinyText(&CShinyTexts::aShinyTexts)[32] = *(CRegisteredShinyText(*)[32])0xC7D258;

void CShinyTexts::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CShinyTexts", "Init", 0x7221B0, &CShinyTexts::Init);
    Install("CShinyTexts", "RenderOutGeometryBuffer", 0x7221C0, &CShinyTexts::RenderOutGeometryBuffer);
    Install("CShinyTexts", "Render", 0x724890, &CShinyTexts::Render);
    Install("CShinyTexts", "RegisterOne", 0x724B60, &CShinyTexts::RegisterOne);
}

// 0x7221B0
void CShinyTexts::Init() {
    NumShinyTexts = 0;
}

// 0x7221C0
void CShinyTexts::RenderOutGeometryBuffer() {
    if (uiTempBufferIndicesStored) {
        LittleTest();
        if (RwIm3DTransform(aTempBufferVertices, uiTempBufferVerticesStored, nullptr, rwIM3D_VERTEXUV))
        {
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, aTempBufferIndices, uiTempBufferIndicesStored);
            RwIm3DEnd();
        }
        uiTempBufferVerticesStored = 0;
        uiTempBufferIndicesStored = 0;
    }
}

// 0x724890
void CShinyTexts::Render() {
    if (!NumShinyTexts)
        return;

    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);

    uiTempBufferIndicesStored  = 0;
    uiTempBufferVerticesStored = 0;

    RwTexture* texture{};
    for (CRegisteredShinyText& text : aShinyTexts) {
        if (uiTempBufferIndicesStored > TOTAL_TEMP_BUFFER_INDICES - 64u ||
            uiTempBufferVerticesStored > TOTAL_TEMP_BUFFER_VERTICES - 64u
        )
        {
            RenderOutGeometryBuffer();
        }

        if (!text.m_bAlwaysTrue)
            continue;

        if (texture != gpHandManTex) {
            RenderOutGeometryBuffer();
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)RwTextureGetRaster(gpHandManTex));
            texture = gpHandManTex;
        }
            
        const auto GetRealVertexIndex = [](unsigned i) { return (unsigned)uiTempBufferVerticesStored + i; };

        const RwRGBA       color  = { text.m_colorR, text.m_colorG, text.m_colorB, 12 };
        const CVector*     posn[] = { &text.m_vecCornerAA, &text.m_vecCornerAB, &text.m_vecCornerBA, &text.m_vecCornerBB };
        const RwTexCoords* uvs[]  = { &text.m_texCoorsAA, &text.m_texCoorsAB, &text.m_texCoorsBA, &text.m_texCoorsBB };
        for (unsigned i = 0u; i < 4u; i++) {
            RxObjSpace3DVertex* vertex = &aTempBufferVertices[GetRealVertexIndex(i)];

            RxObjSpace3DVertexSetPreLitColor(vertex, &color);
            RxObjSpace3DVertexSetPos(vertex, posn[i]);
            RxObjSpace3DVertexSetU(vertex, uvs[i]->u);
            RxObjSpace3DVertexSetV(vertex, uvs[i]->v);
        }

        // Relative to the 0th vertex of the current text.
        constexpr RxVertexIndex indices[] = { 0, 1, 2, 2, 1, 3 };
        for (unsigned i = 0u; i < 6u; i++) {
            aTempBufferIndices[(unsigned)uiTempBufferIndicesStored + i] = GetRealVertexIndex(indices[i]);
        }

        uiTempBufferVerticesStored += 4;
        uiTempBufferIndicesStored += 6;
    }

    RenderOutGeometryBuffer();
    NumShinyTexts = 0;

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
}

// Must be called each frame to re-draw
// They are drawn once, then deleted
void CShinyTexts::RegisterOne(CVector cornerAA, CVector cornerAB, CVector cornerBA, CVector cornerBB, float u1, float v1, float u2, float v2, float u3, float v3, float u4,
    float v4, bool alwaysTrue, unsigned char red, unsigned char green, unsigned char blue, float maxDistance) {
    if (NumShinyTexts >= MAX_SHINYTEXTS)
        return;
    const float distToCam = (TheCamera.GetPosition() - cornerAA).Magnitude();
    if (distToCam > maxDistance)
        return;

    CRegisteredShinyText& text = aShinyTexts[NumShinyTexts];

    text = {
        cornerAA,
        cornerAB,
        cornerBA,
        cornerBB,
        {u1, v1},
        {u2, v2},
        {u3, v3},
        {u4, v4},
        distToCam,
        alwaysTrue,
        red,
        green,
        blue
    };

    const float halfMaxDist = maxDistance / 2.0f;
    if (halfMaxDist < distToCam) { // TODO: Fix this mess (add CRGB type)
        const float mult = 1.0f - (distToCam - halfMaxDist) / halfMaxDist;
        text.m_colorR = (uint8)((float)red * mult);
        text.m_colorG = (uint8)((float)green * mult);
        text.m_colorB = (uint8)((float)blue * mult);
    }

    NumShinyTexts++;
}
