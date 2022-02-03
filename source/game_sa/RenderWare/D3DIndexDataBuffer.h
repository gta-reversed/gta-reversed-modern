/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#ifdef _DX9_SDK_INSTALLED
#include "d3d9.h"
#endif

class D3DIndexDataBuffer {
public:
    uint32 m_nFormat;
    int32  field_4;
    uint32 m_nCapcacity;
    uint32 m_nNumDatasInBuffer;
    uint32 m_nSize;
#ifdef _D3D9_H_
    IDirect3DIndexBuffer9 **m_apIndexData;
#else
    void **m_apIndexData;
#endif

    void Clear();
    void Destroy();
    uint32 GetTotalDataSize();
    void Resize(uint32 newCapacity);
    void Setup(uint32 format, int32 _f4, uint32 capacity);
#ifdef _D3D9_H_
    IDirect3DIndexBuffer9* Pop();
    IDirect3DIndexBuffer9* Pop(uint32 indexCount);
    bool Push(IDirect3DIndexBuffer9* indexBuffer);
    bool PushWithoutIncreasingCounter(IDirect3DIndexBuffer9* indexBuffer);
#else
    void* Pop();
    void* Pop(uint32 indexCount);
    bool Push(void* indexBuffer);
    bool PushWithoutIncreasingCounter(void* indexBuffer);
#endif
};

VALIDATE_SIZE(D3DIndexDataBuffer, 0x18);