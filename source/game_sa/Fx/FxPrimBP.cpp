#include "StdInc.h"

#include "FxPrimBP.h"
#include "FxTools.h"

void FxPrimBP_c::InjectHooks() {
    RH_ScopedClass(FxPrimBP_c);
    RH_ScopedCategory("Fx");

    RH_ScopedInstall(GetRWMatrix, 0x4A9DC0);
    RH_ScopedInstall(Load, 0x5C2010, { .reversed = false });
}

// 0x4A9CF0
FxPrimBP_c::FxPrimBP_c() {
    m_apTextures.fill(nullptr);
}

// 0x4A9D20
FxPrimBP_c::~FxPrimBP_c() {
    // FIX_BUGS: They forgot destroy third texture (texture 3 destroyed twice)
    for (auto& texture : m_apTextures) {
        RwTextureDestroy(texture);
        texture = nullptr;
    }
}

// 0x4A9DC0
void FxPrimBP_c::GetRWMatrix(RwMatrix* outMatrix) {
    // plugin::CallMethod<0x4A9DC0, FxPrimBP_c*, RwMatrix*>(this, outMatrix);
    // return;

    if (m_pMatrixBuffered) {
        m_pMatrixBuffered->UncompressInto(outMatrix);
    } else {
        // identity matrix
        outMatrix->right = { 1.0f, 0.0f, 0.0f };
        outMatrix->up    = { 0.0f, 1.0f, 0.0f };
        outMatrix->at    = { 0.0f, 0.0f, 1.0f };
        outMatrix->pos   = { 0.0f, 0.0f, 0.0f };
    }
}

// 0x5C2010
bool FxPrimBP_c::Load(FILESTREAM file, int32 version, FxName32_t* textureNames) {
    return plugin::CallMethodAndReturn<bool, 0x5C2010, FxPrimBP_c*, FILESTREAM, int32, FxName32_t*>(this, file, version, textureNames);

    char line[256], field[128];

    ReadFieldImpl(file, field, "FX_PRIM_BASE_DATA:");
    ReadFieldImpl(file, field, "NAME:");
    
    float mat[4][3];
    ReadLine(file, line, sizeof(line));
    (void)sscanf(
        line,
        "%s %f %f %f %f %f %f %f %f %f %f %f %f",
        field,
        &mat[0][0], &mat[0][1], &mat[0][2], // right
        &mat[1][0], &mat[1][1], &mat[1][2], // up
        &mat[2][0], &mat[2][1], &mat[2][2], // at
        &mat[3][0], &mat[3][1], &mat[3][2]  // pos
    );

    // if it's identity matrix, don't allocate it
    if (mat[0][0] == 1.f && mat[0][1] == 0.f && mat[0][2] == 0.f &&
        mat[1][0] == 0.f && mat[1][1] == 1.f && mat[1][2] == 0.f &&
        mat[2][0] == 0.f && mat[2][1] == 0.f && mat[2][2] == 1.f &&
        mat[3][0] == 0.f && mat[3][1] == 0.f && mat[3][2] == 0.f
    ) {
        m_pMatrixBuffered = nullptr;
    } else {
        m_pMatrixBuffered = g_fxMan.Allocate<FxBufferedMatrix>(1);
        assert(m_pMatrixBuffered);

        for (auto i = 0; i < 4; i++) {
            for (auto j = 0; j < 3; j++) {
                m_pMatrixBuffered->data[i] = int16(mat[i][j] * std::numeric_limits<int16>::max());
            }
        }
    }

    assert(textureNames);
    ReadFieldImpl(file, textureNames[0], "TEXTURE:");

    if (version > 101) {
        ReadFieldImpl(file, textureNames[1], "TEXTURE2:");
        ReadFieldImpl(file, textureNames[2], "TEXTURE3:");
        ReadFieldImpl(file, textureNames[3], "TEXTURE4:");
    }

    m_bAlphaOn    = ReadField<bool>(file, "ALPHAON:");
    m_nSrcBlendId = ReadField<uint8>(file, "SRCBLENDID:");
    m_nDstBlendId = ReadField<uint8>(file, "DSTBLENDID:");

    m_FxInfoManager.Load(file, version);
    return true;
}
