/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#ifdef _DX9_SDK_INSTALLED
#include "d3d9.h"
#endif

class D3DTextureBuffer {
public:
    unsigned int m_nFormat;
    unsigned int m_nWidth;
    int          m_nLevels; // -1 - not defined, 0 - full-chain, 1 - one level
    unsigned int m_nCapcacity;
    unsigned int m_nNumTexturesInBuffer;
    unsigned int m_nSize;
#ifdef _D3D9_H_
    IDirect3DTexture9 **m_apTextures;
#else
    void **m_apTextures;
#endif

    void Clear();
    void Destroy();
    unsigned int GetTotalDataSize();
    void Resize(unsigned int newCapacity);
    void Setup(unsigned int format, int width, int bOneLevel, unsigned int capacity);
#ifdef _D3D9_H_
    IDirect3DTexture9* Pop();
    IDirect3DTexture9* Pop(unsigned int format, int width, int height, int bOneLevel);
    bool Push(IDirect3DTexture9* texture);
    bool PushWithoutIncreasingCounter(IDirect3DTexture9* texture);
#else
    void* Pop();
    void* Pop(unsigned int format, int width, int height, int bOneLevel);
    bool Push(void* texture);
    bool PushWithoutIncreasingCounter(void* texture);
#endif
};

VALIDATE_SIZE(D3DTextureBuffer, 0x1C);