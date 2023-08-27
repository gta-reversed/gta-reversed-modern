/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "List_c.h"
#include "FxInfoManager.h"

class FxPrim_c;
class FxPrimBP_c;

// struct FxName32_t {
//    char value[32];
// };
using FxName32_t = char[32];

struct FxBufferedMatrix {
    union {
        struct {
            CompressedVector right;
            CompressedVector up;
            CompressedVector at;
            CompressedVector pos;
        };
        int16 data[12];
    };

    void CompressInto(RwMatrix* mat) {
        mat->right = CompressFxVector(right);
        mat->up    = CompressFxVector(up);
        mat->at    = CompressFxVector(at);
        mat->pos   = CompressFxVector(pos);
    }

    void UncompressInto(RwMatrix* out) {
        out->right = UncompressFxVector(right);
        out->up    = UncompressFxVector(up);
        out->at    = UncompressFxVector(at);
        out->pos   = UncompressFxVector(pos);
    }

    int16 operator[](size_t i) const {
        return (&right.x)[i];
    }

    int16& operator[](size_t i) {
        return (&right.x)[i];
    }
};

class FxPrimBP_c {
public:
    int8                      m_Type;
    uint8                     m_nSrcBlendId;
    uint8                     m_nDstBlendId;
    bool                      m_bAlphaOn;
    FxBufferedMatrix*         m_pMatrixBuffered; // int16* m_matVals;
    std::array<RwTexture*, 4> m_apTextures;
    int32 m_TxdIndex;
    TList_c<Particle_c>       m_Particles;
    FxInfoManager_c           m_FxInfoManager;

public:
    static void InjectHooks();

    FxPrimBP_c();
    virtual ~FxPrimBP_c() = 0;
    virtual bool Load(FILESTREAM file, int32 version, FxName32_t* textureNames) = 0;
    virtual bool LoadTextures(FxName32_t* textureNames, int32 version) = 0;
    virtual FxPrim_c* CreateInstance() = 0;
    virtual void Update(float a1) = 0;
    virtual void Render(RwCamera* camera, uint32 a2, float a3, bool bCanRenderHeatHaze) = 0;
    virtual bool FreePrtFromPrim(FxSystem_c* system) = 0;

    void GetRWMatrix(RwMatrix* outMatrix);
};

VALIDATE_SIZE(FxPrimBP_c, 0x40);
