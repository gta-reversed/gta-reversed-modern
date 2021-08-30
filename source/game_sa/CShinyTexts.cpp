#include "StdInc.h"

uint32_t& CShinyTexts::NumShinyTexts = *(uint32_t*)0xC7C6F8;
CRegisteredShinyText(&CShinyTexts::aShinyTexts)[32] = *(CRegisteredShinyText(*)[32])0xC7D258;

void CShinyTexts::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CShinyTexts", "Init", 0x7221B0, &CShinyTexts::Init);
    Install("CShinyTexts", "RenderOutGeometryBuffer", 0x7221C0, &CShinyTexts::RenderOutGeometryBuffer);
    // Install("CShinyTexts", "Render", 0x724890, &CShinyTexts::Render);
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
    plugin::Call<0x724890>();
}

void CShinyTexts::RegisterOne(CVector cornerAA, CVector cornerBA, CVector cornerBB, CVector cornerAB, float u1, float v1, float u2, float v2, float u3, float v3, float u4,
    float v4, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, float maxDistance) {
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
        {red, green, blue, alpha}
    };

    const float halfMaxDist = maxDistance / 2.0f;
    if (halfMaxDist < distToCam) {
        text.m_color *= 1.0f - (distToCam - halfMaxDist) / halfMaxDist;
        text.m_color.r = red;
    }

    NumShinyTexts++;
}
