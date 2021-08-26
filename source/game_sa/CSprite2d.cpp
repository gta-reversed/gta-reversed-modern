/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"
#include <GxtChar.h>

// static variables
int& CSprite2d::nextBufferIndex = *reinterpret_cast<int*>(0xC80458);
int& CSprite2d::nextBufferVertex = *reinterpret_cast<int*>(0xC8045C);
float& CSprite2d::NearScreenZ = *reinterpret_cast<float*>(0xC80460);
float& CSprite2d::RecipNearClip = *reinterpret_cast<float*>(0xC80464);
RwD3D9Vertex* CSprite2d::maVertices = reinterpret_cast<RwD3D9Vertex*>(0xC80468);

void CSprite2d::InjectHooks()
{
    ReversibleHooks::Install("CSprite2d", "CSprite2d", 0x727230, &CSprite2d::Constructor);
    ReversibleHooks::Install("CSprite2d", "~CSprite2d", 0x7281E0, &CSprite2d::Destructor);
    
    ReversibleHooks::Install("CSprite2d", "Delete", 0x727240, &CSprite2d::Delete);
    ReversibleHooks::Install("CSprite2d", "SetTexture", 0x727270, static_cast<void(CSprite2d::*)(char*)>(&CSprite2d::SetTexture));
    ReversibleHooks::Install("CSprite2d", "SetTexture_mask", 0x7272B0, static_cast<void(CSprite2d::*)(char*, char*)>(&CSprite2d::SetTexture));
    ReversibleHooks::Install("CSprite2d", "SetAddressingUV", 0x7272E0, &CSprite2d::SetAddressingUV);
    ReversibleHooks::Install("CSprite2d", "SetAddressing", 0x727320, &CSprite2d::SetAddressing);
    ReversibleHooks::Install("CSprite2d", "SetRenderState", 0x727B30, &CSprite2d::SetRenderState);
    ReversibleHooks::Install("CSprite2d", "Draw_ffffCRGBA", 0x7282C0, static_cast<void(CSprite2d::*)(float, float, float, float, const CRGBA&)>(&CSprite2d::Draw));
    ReversibleHooks::Install("CSprite2d", "Draw_CRectCRGBA", 0x728350, static_cast<void(CSprite2d::*)(const CRect&, const CRGBA&)>(&CSprite2d::Draw));
    ReversibleHooks::Install("CSprite2d", "DrawWithBilinearOffset", 0x7283B0, &CSprite2d::DrawWithBilinearOffset);
    ReversibleHooks::Install("CSprite2d", "Draw_CRectCRGBA4", 0x7284B0, static_cast<void(CSprite2d::*)(const CRect&, const CRGBA&, const CRGBA&, const CRGBA&, const CRGBA&)>(&CSprite2d::Draw));
    ReversibleHooks::Install("CSprite2d", "Draw_ffffffffCRGBA", 0x728520, static_cast<void(CSprite2d::*)(float, float, float, float, float, float, float, float, const CRGBA&)>(&CSprite2d::Draw));
    
    ReversibleHooks::Install("CSprite2d", "SetRecipNearClip", 0x727260, &CSprite2d::SetRecipNearClip);
    ReversibleHooks::Install("CSprite2d", "InitPerFrame", 0x727350, &CSprite2d::InitPerFrame);
    ReversibleHooks::Install("CSprite2d", "IsVertexBufferEmpty", 0x727390, &CSprite2d::IsVertexBufferEmpty);
    ReversibleHooks::Install("CSprite2d", "IsVertexBufferFull", 0x7273A0, &CSprite2d::IsVertexBufferFull);
    ReversibleHooks::Install("CSprite2d", "RenderVertexBuffer", 0x7273D0, &CSprite2d::RenderVertexBuffer);
    ReversibleHooks::Install("CSprite2d", "SetVertices_CRectCRGBA4", 0x727420, static_cast<void(*)(const CRect&, const CRGBA&, const CRGBA&, const CRGBA&, const CRGBA&)>(&CSprite2d::SetVertices));
    ReversibleHooks::Install("CSprite2d", "SetVertices_ffffffffCRGBA", 0x727590, static_cast<void(*)(float, float, float, float, float, float, float, float, const CRGBA&,
        const CRGBA&, const CRGBA&, const CRGBA&)>(&CSprite2d::SetVertices));
    ReversibleHooks::Install("CSprite2d", "SetVertices_CRectCRGBA4ffffffff", 0x727710, static_cast<void(*)(const CRect&, const CRGBA&, const CRGBA&, const CRGBA&, const CRGBA&,
        float, float, float, float, float, float, float, float)>(&CSprite2d::SetVertices));
    ReversibleHooks::Install("CSprite2d", "SetVertices_iffCRGBA", 0x727890, static_cast<void(*)(int, float*, float*, const CRGBA&)>(&CSprite2d::SetVertices));
    ReversibleHooks::Install("CSprite2d", "SetVertices_ifCRGBA", 0x727920, static_cast<void(*)(int, float*, CRGBA*)>(&CSprite2d::SetVertices));
    ReversibleHooks::Install("CSprite2d", "SetMaskVertices", 0x7279B0, &CSprite2d::SetMaskVertices);
    ReversibleHooks::Install("CSprite2d", "SetVertices_RwD3D9Vertex", 0x727A00, static_cast<void(*)(RwD3D9Vertex*, const CRect&, const CRGBA&, const CRGBA&, const CRGBA&, const CRGBA&,
        float, float, float, float, float, float, float, float)>(&CSprite2d::SetVertices));
    ReversibleHooks::Install("CSprite2d", "DrawRect_CRect_CRGBA", 0x727B60, static_cast<void(*)(const CRect&, const CRGBA&)>(&CSprite2d::DrawRect));
    ReversibleHooks::Install("CSprite2d", "DrawTxRect", 0x727BE0, &CSprite2d::DrawTxRect);
    ReversibleHooks::Install("CSprite2d", "DrawRect_CRect_CRGBA4", 0x727C10, static_cast<void(*)(const CRect&, const CRGBA&, const CRGBA&, const CRGBA&, const CRGBA&)>(&CSprite2d::DrawRect));
    ReversibleHooks::Install("CSprite2d", "DrawRectXLU", 0x727C50, &CSprite2d::DrawRectXLU);
    ReversibleHooks::Install("CSprite2d", "DrawAnyRect", 0x727CC0, &CSprite2d::DrawAnyRect);
    ReversibleHooks::Install("CSprite2d", "DrawBarChart", 0x728640, &CSprite2d::DrawBarChart);
    // ReversibleHooks::Install("CSprite2d", "DrawCircleAtNearClip", 0x727D60, &CSprite2d::DrawCircleAtNearClip);
}

CSprite2d* CSprite2d::Constructor()
{
    this->CSprite2d::CSprite2d();
    return this;
}

CSprite2d* CSprite2d::Destructor()
{
    this->CSprite2d::~CSprite2d();
    return this;
}

CSprite2d::CSprite2d()
{
    m_pTexture = nullptr;
}

CSprite2d::~CSprite2d()
{
    Delete();
}

// delete this sprite (similar to destructor)
void CSprite2d::Delete()
{
    if (m_pTexture) {
        RwTextureDestroy(m_pTexture);
        m_pTexture = nullptr;
    }
}

// set texture by name from current txd
void CSprite2d::SetTexture(char* name)
{
    Delete();
    if (name)
        m_pTexture = RwTextureRead(name, nullptr);
}

// set texture by name from current txd (+alpha mask name)
void CSprite2d::SetTexture(char* name, char* maskName)
{
    if (name && maskName)
        m_pTexture = RwTextureRead(name, maskName);
}

void CSprite2d::SetAddressingUV(RwTextureAddressMode modeU, RwTextureAddressMode modeV)
{
    if (m_pTexture) {
        RwTextureSetAddressingU(m_pTexture, modeU);
        RwTextureSetAddressingV(m_pTexture, modeV);
    }
}

void CSprite2d::SetAddressing(RwTextureAddressMode modeUV)
{
    if (m_pTexture)
        RwTextureSetAddressing(m_pTexture, modeUV);
}

// sets sprite texture as current for device rendering
void CSprite2d::SetRenderState()
{
    if (m_pTexture)
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTextureGetRaster(m_pTexture));
    else
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
}

// draw this sprite
void CSprite2d::Draw(float x, float y, float width, float height, const CRGBA& color)
{
    CRect posn(x, y, x + width, y + height);
    Draw(posn, color);
}

void CSprite2d::Draw(const CRect& posn, const CRGBA& color)
{
    Draw(posn, color, color, color, color);
}

void CSprite2d::DrawWithBilinearOffset(const CRect &posn, const CRGBA &color)
{
    SetVertices(posn, color, color, color, color);
    RwRaster *raster = RwTextureGetRaster(m_pTexture);
    OffsetTexCoordForBilinearFiltering(static_cast<float>(RwRasterGetWidth(raster)), static_cast<float>(RwRasterGetHeight(raster)));
    SetRenderState();
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
}

void CSprite2d::Draw(const CRect& posn, const CRGBA& color, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
{
    SetVertices(posn, color, color, color, color, u1, v1, u2, v2, u3, v3, u4, v4);
    SetRenderState();
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
}

void CSprite2d::Draw(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4)
{
    SetVertices(posn, color1, color2, color3, color4);
    SetRenderState();
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
}

void CSprite2d::Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA& color)
{
    SetVertices(x1, y1, x2, y2, x3, y3, x4, y4, color, color, color, color);
    SetRenderState();
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
}

// static functions
void CSprite2d::SetRecipNearClip()
{
}

void CSprite2d::InitPerFrame()
{
    nextBufferVertex = 0;
    nextBufferIndex = 0;
    RecipNearClip = 1.0f / Scene.m_pRwCamera->nearPlane;
    NearScreenZ = RWSRCGLOBAL(dOpenDevice).zBufferNear;
}

bool CSprite2d::IsVertexBufferEmpty()
{
    return nextBufferVertex == 0;
}

bool CSprite2d::IsVertexBufferFull()
{
    return nextBufferVertex > TOTAL_RADIOSITY_VERTEX_BUFFER || nextBufferIndex > TOTAL_TEMP_BUFFER_INDICES;
}

void CSprite2d::RenderVertexBuffer()
{
    if (nextBufferVertex <= 0)
        return;

    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void*>(rwFILTERLINEAR));
    RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, aRadiosityVertexBuffer, nextBufferVertex, aTempBufferIndices, nextBufferIndex);
    nextBufferVertex = 0;
    nextBufferIndex = 0;
}

// different kinds of vertices' defining
void CSprite2d::SetVertices(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4)
{
    float offset = 1.0f / 1024.0f;
    SetVertices(posn, color1, color2, color3, color4,
              offset,       offset,
        1.f + offset,       offset,
              offset, 1.f + offset,
        1.f + offset, 1.f + offset);
}

void CSprite2d::SetVertices(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA& color1, const CRGBA& color2,
    const CRGBA& color3, const CRGBA& color4)
{
    RwIm2DVertexSetScreenX(&maVertices[0], x3);
    RwIm2DVertexSetScreenY(&maVertices[0], y3);
    RwIm2DVertexSetScreenZ(&maVertices[0], NearScreenZ);
    RwIm2DVertexSetRecipCameraZ(&maVertices[0], RecipNearClip);
    RwIm2DVertexSetU(&maVertices[0], 0.f, RecipNearClip);
    RwIm2DVertexSetV(&maVertices[0], 0.f, RecipNearClip);
    RwIm2DVertexSetIntRGBA(&maVertices[0], color3.r, color3.g, color3.b, color3.a);

    RwIm2DVertexSetScreenX(&maVertices[1], x4);
    RwIm2DVertexSetScreenY(&maVertices[1], y4);
    RwIm2DVertexSetScreenZ(&maVertices[1], NearScreenZ);
    RwIm2DVertexSetRecipCameraZ(&maVertices[1], RecipNearClip);
    RwIm2DVertexSetU(&maVertices[1], 1.f, RecipNearClip);
    RwIm2DVertexSetV(&maVertices[1], 0.f, RecipNearClip);
    RwIm2DVertexSetIntRGBA(&maVertices[1], color4.r, color4.g, color4.b, color4.a);

    RwIm2DVertexSetScreenX(&maVertices[2], x2);
    RwIm2DVertexSetScreenY(&maVertices[2], y2);
    RwIm2DVertexSetScreenZ(&maVertices[2], NearScreenZ);
    RwIm2DVertexSetRecipCameraZ(&maVertices[2], RecipNearClip);
    RwIm2DVertexSetU(&maVertices[2], 1.f, RecipNearClip);
    RwIm2DVertexSetV(&maVertices[2], 1.f, RecipNearClip);
    RwIm2DVertexSetIntRGBA(&maVertices[2], color2.r, color2.g, color2.b, color2.a);

    RwIm2DVertexSetScreenX(&maVertices[3], x1);
    RwIm2DVertexSetScreenY(&maVertices[3], y1);
    RwIm2DVertexSetScreenZ(&maVertices[3], NearScreenZ);
    RwIm2DVertexSetRecipCameraZ(&maVertices[3], RecipNearClip);
    RwIm2DVertexSetU(&maVertices[3], 0.f, RecipNearClip);
    RwIm2DVertexSetV(&maVertices[3], 1.f, RecipNearClip);
    RwIm2DVertexSetIntRGBA(&maVertices[3], color1.r, color1.g, color1.b, color1.a);
}

void CSprite2d::SetVertices(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4,
    float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
{
    SetVertices(maVertices, posn, color1, color2, color3, color4, u1, v1, u2, v2, u3, v3, u4, v4);
}

void CSprite2d::SetVertices(int numVerts, float* posn, float* texCoors, const CRGBA& color)
{
    for (int i = 0; i < numVerts; ++i) {
        RwIm2DVertexSetScreenX(&maVertices[i], posn[i * 2]);
        RwIm2DVertexSetScreenY(&maVertices[i], posn[i * 2 + 1]);
        RwIm2DVertexSetScreenZ(&maVertices[i], NearScreenZ + 0.0001f);
        RwIm2DVertexSetRecipCameraZ(&maVertices[i], RecipNearClip);
        RwIm2DVertexSetU(&maVertices[i], texCoors[i * 2], RecipNearClip);
        RwIm2DVertexSetV(&maVertices[i], texCoors[i * 2 + 1], RecipNearClip);
        RwIm2DVertexSetIntRGBA(&maVertices[i], color.r, color.g, color.b, color.a);
    }
}

void CSprite2d::SetVertices(int numVerts, float* posn, CRGBA* color)
{
    for (int i = 0; i < numVerts; ++i) {
        RwIm2DVertexSetScreenX(&maVertices[i], posn[i * 2]);
        RwIm2DVertexSetScreenY(&maVertices[i], posn[i * 2 + 1]);
        RwIm2DVertexSetScreenZ(&maVertices[i], NearScreenZ);
        RwIm2DVertexSetRecipCameraZ(&maVertices[i], RecipNearClip);
        RwIm2DVertexSetU(&maVertices[i], 1.f, RecipNearClip);
        RwIm2DVertexSetV(&maVertices[i], 1.f, RecipNearClip);
        RwIm2DVertexSetIntRGBA(&maVertices[i], color[i].r, color[i].g, color[i].b, color[i].a);
    }
}

void CSprite2d::SetMaskVertices(int numVerts, float* posn, float depth)
{
    for (int i = 0; i < numVerts; ++i) {
        RwIm2DVertexSetScreenX(&maVertices[i], posn[i * 2]);
        RwIm2DVertexSetScreenY(&maVertices[i], posn[i * 2 + 1]);
        RwIm2DVertexSetScreenZ(&maVertices[i], depth);
        RwIm2DVertexSetRecipCameraZ(&maVertices[i], RecipNearClip);
        RwIm2DVertexSetIntRGBA(&maVertices[i], 0, 0, 0, 0);
    }
}

void CSprite2d::SetVertices(RwD3D9Vertex* vertices, const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4,
    float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
{
    RwIm2DVertexSetScreenX(&vertices[0], posn.left);
    RwIm2DVertexSetScreenY(&vertices[0], posn.top);
    RwIm2DVertexSetScreenZ(&vertices[0], NearScreenZ);
    RwIm2DVertexSetRecipCameraZ(&vertices[0], RecipNearClip);
    RwIm2DVertexSetU(&vertices[0], u1, RecipNearClip);
    RwIm2DVertexSetV(&vertices[0], v1, RecipNearClip);
    RwIm2DVertexSetIntRGBA(&vertices[0], color3.r, color3.g, color3.b, color3.a);

    RwIm2DVertexSetScreenX(&vertices[1], posn.right);
    RwIm2DVertexSetScreenY(&vertices[1], posn.top);
    RwIm2DVertexSetScreenZ(&vertices[1], NearScreenZ);
    RwIm2DVertexSetRecipCameraZ(&vertices[1], RecipNearClip);
    RwIm2DVertexSetU(&vertices[1], u2, RecipNearClip);
    RwIm2DVertexSetV(&vertices[1], v2, RecipNearClip);
    RwIm2DVertexSetIntRGBA(&vertices[1], color4.r, color4.g, color4.b, color4.a);

    RwIm2DVertexSetScreenX(&vertices[2], posn.right);
    RwIm2DVertexSetScreenY(&vertices[2], posn.bottom);
    RwIm2DVertexSetScreenZ(&vertices[2], NearScreenZ);
    RwIm2DVertexSetRecipCameraZ(&vertices[2], RecipNearClip);
    RwIm2DVertexSetU(&vertices[2], u4, RecipNearClip);
    RwIm2DVertexSetV(&vertices[2], v4, RecipNearClip);
    RwIm2DVertexSetIntRGBA(&vertices[2], color2.r, color2.g, color2.b, color2.a);

    RwIm2DVertexSetScreenX(&vertices[3], posn.left);
    RwIm2DVertexSetScreenY(&vertices[3], posn.bottom);
    RwIm2DVertexSetScreenZ(&vertices[3], NearScreenZ);
    RwIm2DVertexSetRecipCameraZ(&vertices[3], RecipNearClip);
    RwIm2DVertexSetU(&vertices[3], u3, RecipNearClip);
    RwIm2DVertexSetV(&vertices[3], v3, RecipNearClip);
    RwIm2DVertexSetIntRGBA(&vertices[3], color1.r, color1.g, color1.b, color1.a);
}

// draws non-textured rectangle
void CSprite2d::DrawRect(const CRect& posn, const CRGBA& color)
{
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
    SetVertices(posn, color, color, color, color);
    if (color.a == 255)
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(FALSE));
    else
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(TRUE));
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(FALSE));
}

//this could be used for drawing textured rectangle (use SetRenderState() before this)
void CSprite2d::DrawTxRect(const CRect& posn, const CRGBA& color)
{
    CSprite2d::SetVertices(posn, color, color, color, color);
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
}

// draw non-textured rectangle, with setupable corners' colors.
void CSprite2d::DrawRect(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4)
{
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
    SetVertices(posn, color1, color2, color3, color4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
}

// draws non-textured rectangle with default blending states
void CSprite2d::DrawRectXLU(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4)
{
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(rwBLENDINVSRCALPHA));
    DrawRect(posn, color1, color2, color3, color4);
}

// draws rectangle, texture could be set with SetRenderState().
void CSprite2d::DrawAnyRect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA& color1, const CRGBA& color2,
    const CRGBA& color3, const CRGBA& color4)
{
    SetVertices(x1, y1, x2, y2, x3, y3, x4, y4, color1, color2, color3, color4);
    if (color1.a == 0xFF && color2.a == 0xFF && color3.a == 0xFF && color4.a == 0xFF)
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(FALSE));
    else
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(TRUE));
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
}

// draws a triangle with rotation (degrees)
void CSprite2d::DrawCircleAtNearClip(const CVector2D& posn, float size, const CRGBA& color, int angle)
{
    ((void(__cdecl*)(const CVector2D&, float, const CRGBA&, int))0x727D60)(posn, size, color, angle);
    
    /* NOT TESTED
    RwIm2DVertexSetScreenX(&maVertices[0], posn.x);
    RwIm2DVertexSetScreenY(&maVertices[0], posn.y);
    RwIm2DVertexSetScreenZ(&maVertices[0], NearScreenZ);
    RwIm2DVertexSetRecipCameraZ(&maVertices[0], RecipNearClip);
    RwIm2DVertexSetU(&maVertices[0], 0.5f, RecipNearClip);
    RwIm2DVertexSetV(&maVertices[0], 0.5f, RecipNearClip);
    RwIm2DVertexSetIntRGBA(&maVertices[0], color.r, color.g, color.b, color.a);

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(TRUE));

    float posna = 360.f / static_cast<float>(angle);
    float step = posna * DegreesToRadians(1.f) * (256.f / DegreesToRadians(360.f)); // posna * 35 / 45
    for (int i = 0; i < angle; ++i)
    {
        for (int l = 1; l <= 2; ++l) {
            unsigned char idx = static_cast<unsigned char>(static_cast<float>(i + l - 1) * step);
            RwIm2DVertexSetScreenX(&maVertices[l], size * CMaths::ms_SinTable[idx + 64] + posn.x);
            RwIm2DVertexSetScreenY(&maVertices[l], size * CMaths::ms_SinTable[idx] + posn.y);
            RwIm2DVertexSetScreenZ(&maVertices[l], NearScreenZ);
            RwIm2DVertexSetRecipCameraZ(&maVertices[l], RecipNearClip);
            RwIm2DVertexSetIntRGBA(&maVertices[l], color.r, color.g, color.b, color.a);
            RwIm2DVertexSetU(&maVertices[l], (CMaths::ms_SinTable[idx + 64] + 1.f) * 0.5f, RecipNearClip);
            RwIm2DVertexSetV(&maVertices[l], (CMaths::ms_SinTable[idx] + 1.f) * 0.5f, RecipNearClip);
        }
        RWSRCGLOBAL(dOpenDevice).fpIm2DRenderTriangle(maVertices, 3, 2, 1, 0);
    } */
}

// this makes some trick with sprite z position (z = NearScreenZ + 0.000001).
void CSprite2d::SetVerticesForSniper(CRect  const& posn, CRGBA  const& color1, CRGBA  const& color2, CRGBA  const& color3, CRGBA  const& color4)
{
    ((void(__cdecl*)(CRect  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&))0x727FD0)(posn, color1, color2, color3, color4);
}

void CSprite2d::OffsetTexCoordForBilinearFiltering(float width, float height)
{
    ((void(__cdecl*)(float, float))0x728150)(width, height);
}

// add vertices to buffer
void CSprite2d::AddToBuffer(CRect  const& posn, CRGBA  const& color, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
{
    ((void(__cdecl*)(CRect  const&, CRGBA  const&, float, float, float, float, float, float, float, float))0x728200)(posn, color, u1, v1, u2, v2, u3, v3, u4, v4);
}

// non-textured polygon
void CSprite2d::Draw2DPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, CRGBA  const& color)
{
    ((void(__cdecl*)(float, float, float, float, float, float, float, float, CRGBA  const&))0x7285B0)(x1, y1, x2, y2, x3, y3, x4, y4, color);
}

// draws progress line. Progress is a value in ranges 0 - 100.
// ----------------------
// | +++++++++++--------|
// ----------------------
// 0x728640
void CSprite2d::DrawBarChart(float x, float y, unsigned short width, unsigned char height, float progress,
    signed char progressAdd, unsigned char drawPercentage, unsigned char drawBlackBorder,
    CRGBA color, CRGBA addColor)
{
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)nullptr);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEFLAT);

    progress = std::max(0.0f, progress);

    const float maxX = x + (float)width;
    const float unclampedCurrX = x + (float)width * progress / 100.0f;
    const float currX = std::min(unclampedCurrX, maxX);
    DrawRect({
        x,
        y,
        std::min(maxX, currX),
        y + height
    }, color);

    CRGBA loadingBarBgColor = color / 2.0f;
    loadingBarBgColor.a = 255;
    DrawRect({
        std::min(maxX, currX),
        y,
        maxX,
        y + height
    }, loadingBarBgColor);

    if (progressAdd) {
        addColor.a = color.a;
        DrawRect({
            std::max(x - 1.0f, std::min(maxX, currX) - (float)progressAdd),
            y,
            std::min(maxX, currX),
            y + height
        }, addColor);
    }

    if (drawBlackBorder) {
        const float w = 2 * SCREEN_WIDTH_UNIT, h = 2 * SCREEN_HEIGHT_UNIT;
        const CRect rects[] = {
            //left,   top,        right,      bottom
            { x,      y,          maxX,       y + h },           // Top
            { x,      y + height, maxX,       y + height - h },   // Bottom
            { x,      y,          x + w,      y + height },      // Left
            { maxX,   y,          maxX - w,   y + height }       // Right
        };

        for (const CRect& rect : rects) {
            DrawRect(rect, { 0, 0, 0, color.a });
        }
    }

    // unused
    if (drawPercentage) {
        char text[12];
        sprintf(text, "%d%%", (unsigned)progress);

        GxtChar gxtText[12];
        AsciiToGxtChar(text, gxtText);

        CFont::SetWrapx(x);
        CFont::SetRightJustifyWrap(maxX);
        CFont::SetColor({ 0, 0, 0, color.a });
        CFont::SetEdge(0);
        CFont::SetFontStyle(FONT_SUBTITLES);
        CFont::SetScale(height * 0.03f, height / 0.04f);

        float textX = unclampedCurrX;
        if (x + 50.0f <= unclampedCurrX) {
            CFont::SetOrientation(eFontAlignment::ALIGN_RIGHT);
        } else {
            CFont::SetOrientation(eFontAlignment::ALIGN_LEFT);
            textX += 5.0f;
        }
        CFont::PrintString(textX, y + 2.0f, gxtText);
    }
}

#define DrawBarChart(x, y, width, height, progress, progressAdd, drawPercentage, \
    drawBlackBorder, color, addColor) ((void (__cdecl *)(float, float, unsigned short,\
    unsigned char, float, signed char, unsigned char, unsigned char, int, int))0x728640)\
    (x, y, width, height, progress, progressAdd, drawPercentage, drawBlackBorder, color,\
    addColor);

void Draw()
{
    DrawBarChart(300.0, 100.0, 300, 50, 60.0, 0, false, true, 0xFF0000FF, 0);
}
