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

struct FxName32_t {
    char value[32];
};

struct FxBufferedMatrix {
    int16 rightX;
    int16 rightY;
    int16 rightZ;

    int16 upX;
    int16 upY;
    int16 upZ;

    int16 apX;
    int16 apY;
    int16 apZ;

    int16 posX;
    int16 posY;
    int16 posZ;

    static constexpr float COMPRESS_VALUE = 32767.0f;
    inline void CompressInto(RwMatrix*mat) {
        mat->right.x = (float)rightX * COMPRESS_VALUE;
        mat->right.y = (float)rightY * COMPRESS_VALUE;
        mat->right.z = (float)rightZ * COMPRESS_VALUE;
        mat->up.x    = (float)upX    * COMPRESS_VALUE;
        mat->up.y    = (float)upY    * COMPRESS_VALUE;
        mat->up.z    = (float)upZ    * COMPRESS_VALUE;
        mat->at.x    = (float)apX    * COMPRESS_VALUE;
        mat->at.y    = (float)apY    * COMPRESS_VALUE;
        mat->at.z    = (float)apZ    * COMPRESS_VALUE;
        mat->pos.x   = (float)posX   * COMPRESS_VALUE;
        mat->pos.y   = (float)posY   * COMPRESS_VALUE;
        mat->pos.z   = (float)posZ   * COMPRESS_VALUE;
    }

    inline void UncompressInto(RwMatrix* mat) { // maybe wrong
        mat->right.x = (float)rightX / COMPRESS_VALUE;
        mat->right.y = (float)rightY / COMPRESS_VALUE;
        mat->right.z = (float)rightZ / COMPRESS_VALUE;
        mat->up.x    = (float)upX    / COMPRESS_VALUE;
        mat->up.y    = (float)upY    / COMPRESS_VALUE;
        mat->up.z    = (float)upZ    / COMPRESS_VALUE;
        mat->at.x    = (float)apX    / COMPRESS_VALUE;
        mat->at.y    = (float)apY    / COMPRESS_VALUE;
        mat->at.z    = (float)apZ    / COMPRESS_VALUE;
        mat->pos.x   = (float)posX   / COMPRESS_VALUE;
        mat->pos.y   = (float)posY   / COMPRESS_VALUE;
        mat->pos.z   = (float)posZ   / COMPRESS_VALUE;
    }
};

class FxPrimBP_c {
public:
    char              field_4;
    uint8             m_nSrcBlendId;
    uint8             m_nDstBlendId;
    uint8             m_nAlphaOn;
    FxBufferedMatrix* m_pMatrixBuffered;
    RwTexture*        m_apTextures[4];
    int32             field_1C;
    TList_c<void>     m_EmitterPtrs; // TODO: Correct (T)ype
    FxInfoManager_c   m_FxInfoManager;

public:
    static void InjectHooks();

    FxPrimBP_c();
    virtual ~FxPrimBP_c() = 0;
    virtual bool Load(FILESTREAM file, int32 version, FxName32_t* textureNames) = 0;
    virtual bool LoadTextures(FxName32_t* textureNames, int32 iVersion) = 0;
    virtual FxPrim_c* CreateInstance() = 0;
    virtual void Update(float a1) = 0;

    void GetRWMatrix(RwMatrix* outMatrix);
};

VALIDATE_SIZE(FxPrimBP_c, 0x40);
