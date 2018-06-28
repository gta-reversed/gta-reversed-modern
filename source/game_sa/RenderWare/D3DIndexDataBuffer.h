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

class D3DIndexDataBuffer {
public:
    unsigned int m_nFormat;
    int field_4;
    unsigned int m_nCapcacity;
    unsigned int m_nNumDatasInBuffer;
    unsigned int m_nSize;
#ifdef _D3D9_H_
    IDirect3DIndexBuffer9 **m_apIndexData;
#else
    void **m_apIndexData;
#endif

    void Clear();
    void Destroy();
    unsigned int GetTotalDataSize();
    void Resize(unsigned int newCapacity);
    void Setup(unsigned int format, int _f4, unsigned int capacity);
#ifdef _D3D9_H_
    IDirect3DIndexBuffer9* Pop();
    IDirect3DIndexBuffer9* Pop(unsigned int indexCount);
    bool Push(IDirect3DIndexBuffer9* indexBuffer);
    bool PushWithoutIncreasingCounter(IDirect3DIndexBuffer9* indexBuffer);
#else
    void* Pop();
    void* Pop(unsigned int indexCount);
    bool Push(void* indexBuffer);
    bool PushWithoutIncreasingCounter(void* indexBuffer);
#endif
};

VALIDATE_SIZE(D3DIndexDataBuffer, 0x18);