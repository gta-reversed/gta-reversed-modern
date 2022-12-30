#include "StdInc.h"

void FxPrimBP_c::InjectHooks() {
    RH_ScopedClass(FxPrimBP_c);
    RH_ScopedCategory("Fx");

    RH_ScopedInstall(GetRWMatrix, 0x4A9DC0, { .reversed = false });
    RH_ScopedInstall(Load, 0x5C2010, { .reversed = false });
}

// 0x4A9CF0
FxPrimBP_c::FxPrimBP_c() {
    std::ranges::fill(m_apTextures, nullptr);
}

// 0x4A9D20
FxPrimBP_c::~FxPrimBP_c() {
    for (auto& texture : m_apTextures) {
        RwTextureDestroy(texture);
    }
}

// 0x4A9DC0
void FxPrimBP_c::GetRWMatrix(RwMatrix* outMatrix) {
    plugin::CallMethod<0x4A9DC0, FxPrimBP_c*, RwMatrix*>(this, outMatrix);
    return;

    if (m_pMatrixBuffered) {
        m_pMatrixBuffered->UncompressInto(outMatrix);
    } else {
        outMatrix->right = { 1.0f, 0.0f, 0.0f };
        outMatrix->up    = { 0.0f, 1.0f, 0.0f };
        outMatrix->at    = { 0.0f, 0.0f, 1.0f };
        outMatrix->pos   = { 0.0f, 0.0f, 0.0f };
    }
}

// 0x5C2010
bool FxPrimBP_c::Load(FILESTREAM file, int32 version, FxName32_t* textureNames) {
    return plugin::CallMethodAndReturn<bool, 0x5C2010, FxPrimBP_c*, FILESTREAM, int32, FxName32_t*>(this, file, version, textureNames);
}
