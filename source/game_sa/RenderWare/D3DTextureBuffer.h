/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#ifdef _DX9_SDK_INSTALLED
#include "d3d9.h"
#endif

class D3DTextureBuffer {
public:
    uint32 m_nFormat;
    uint32 m_nWidth;
    int32  m_nLevels; // -1 - not defined, 0 - full-chain, 1 - one level
    uint32 m_nCapcacity;
    uint32 m_nNumTexturesInBuffer;
    uint32 m_nSize;
#ifdef _D3D9_H_
    IDirect3DTexture9 **m_apTextures;
#else
    void **m_apTextures;
#endif

    void Clear();
    void Destroy();
    uint32 GetTotalDataSize();
    void Resize(uint32 newCapacity);
    void Setup(uint32 format, int32 width, int32 bOneLevel, uint32 capacity);
#ifdef _D3D9_H_
    IDirect3DTexture9* Pop();
    IDirect3DTexture9* Pop(uint32 format, int32 width, int32 height, int32 bOneLevel);
    bool Push(IDirect3DTexture9* texture);
    bool PushWithoutIncreasingCounter(IDirect3DTexture9* texture);
#else
    void* Pop();
    void* Pop(uint32 format, int32 width, int32 height, int32 bOneLevel);
    bool Push(void* texture);
    bool PushWithoutIncreasingCounter(void* texture);
#endif
};

VALIDATE_SIZE(D3DTextureBuffer, 0x1C);