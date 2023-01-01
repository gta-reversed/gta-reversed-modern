#include "StdInc.h"
#include "RenderBuffer.hpp"

namespace RenderBuffer {
auto& s_IndicesToBeStored{ StaticRef<int32, 0xC40410>() };
auto& s_VerticesToBeStored{ StaticRef<int32, 0xC40414>() };

void InjectHooks() {
    RH_ScopedNamespace(RenderBuffer);
    RH_ScopedCategoryGlobal();

    RH_ScopedGlobalInstall(StartStoring, 0x708290);
    RH_ScopedGlobalInstall(StopStoring, 0x7077A0);
    RH_ScopedGlobalInstall(RenderStuffInBuffer, 0x707800);
    RH_ScopedGlobalInstall(ClearRenderBuffer, 0x707790);
}

// 0x708290
void StartStoring(
    int32 nIndicesNeeded,
    int32 nVerticesNeeded,
    RwImVertexIndex*& outPtrFirstIndex,
    RwIm3DVertex*& outPtrFirstVertex
) {
    assert(nIndicesNeeded  > 0 && nIndicesNeeded  <= (int32)std::size(aTempBufferIndices));
    assert(nVerticesNeeded > 0 && nVerticesNeeded <= (int32)std::size(aTempBufferVertices));

    if (uiTempBufferIndicesStored + nIndicesNeeded >= (int32)std::size(aTempBufferIndices)) {
        RenderBuffer::RenderStuffInBuffer();
    }

    if (uiTempBufferVerticesStored + nVerticesNeeded >= (int32)std::size(aTempBufferVertices)) {
        RenderBuffer::RenderStuffInBuffer();
    }

    outPtrFirstIndex = &aTempBufferIndices[uiTempBufferIndicesStored];
    outPtrFirstVertex = &aTempBufferVertices[uiTempBufferVerticesStored];

    s_IndicesToBeStored = nIndicesNeeded;
    s_VerticesToBeStored = nVerticesNeeded;
}

// 0x7077A0
void StopStoring() {
    const auto totalNumIdx = uiTempBufferIndicesStored + s_IndicesToBeStored;
    if (uiTempBufferIndicesStored >= totalNumIdx) { // Doesn't make a lot of sense, as it will only be true if `s_IndicesToBeStored` is negative, which isn't allowed.
        uiTempBufferVerticesStored += s_VerticesToBeStored;
        uiTempBufferIndicesStored  += s_IndicesToBeStored;
    } else {
        for (auto n = uiTempBufferIndicesStored; n <= totalNumIdx; n++) {
            aTempBufferIndices[n] += uiTempBufferVerticesStored;
        }
        uiTempBufferVerticesStored += s_VerticesToBeStored;
        uiTempBufferIndicesStored   = totalNumIdx;
    }
}

// 0x707800
void RenderStuffInBuffer() {
    if (uiTempBufferVerticesStored) {
        if (RwIm3DTransform(aTempBufferVertices, uiTempBufferVerticesStored, nullptr, rwIM3D_VERTEXUV)) {
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, aTempBufferIndices, uiTempBufferIndicesStored);
            RwIm3DEnd();
        }
    }
    ClearRenderBuffer();
}

// 0x707790
void ClearRenderBuffer() {
    uiTempBufferIndicesStored  = 0;
    uiTempBufferVerticesStored = 0;
}
}; // namespace RenderBuffer 
