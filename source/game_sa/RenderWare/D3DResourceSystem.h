/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "D3DTextureBuffer.h"
#include "D3DIndexDataBuffer.h"
#ifdef _DX9_SDK_INSTALLED
#include "d3d9.h"
#endif

class D3DResourceSystem {
public:
    static bool &UseD3DResourceBuffering;
    static unsigned int &FreeTextureBufferIndex;
    static D3DTextureBuffer &TextureBuffer;
    static D3DIndexDataBuffer &IndexDataBuffer;

    static void CancelBuffering();
    static unsigned int GetTotalIndexDataSize();
    static unsigned int GetTotalPixelsSize();
    static void Init();
    static void SetUseD3DResourceBuffering(bool bUse);
    static void Shutdown();
    static void TidyUpD3DIndexBuffers(unsigned int count);
    static void TidyUpD3DTextures(unsigned int count);

#ifdef _D3D9_H_
    static HRESULT CreateIndexBuffer(unsigned int numIndices, unsigned int format, IDirect3DIndexBuffer9** ppIndexBuffer);
    static HRESULT CreateTexture(int width, int height, unsigned int format, IDirect3DTexture9** ppTexture);
    static void DestroyIndexBuffer(IDirect3DIndexBuffer9* pIndexBuffer);
    static void DestroyTexture(IDirect3DTexture9* pTexture);
#else
    static int CreateIndexBuffer(unsigned int numIndices, unsigned int format, void** ppIndexBuffer);
    static int CreateTexture(int width, int height, unsigned int format, void** ppTexture);
    static void DestroyIndexBuffer(void* pIndexBuffer);
    static void DestroyTexture(void* pTexture);
#endif
};