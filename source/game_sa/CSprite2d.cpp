/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

// static variables
unsigned int& CSprite2d::nextBufferIndex = *(unsigned int*)0xC80458;
unsigned int& CSprite2d::nextBufferVertex = *(unsigned int*)0xC8045C;
float& CSprite2d::NearScreenZ = *(float*)0xC80460;
float& CSprite2d::RecipNearClip = *(float*)0xC80464;
RwD3D9Vertex* CSprite2d::maVertices = (RwD3D9Vertex*)0xC80468;

void CSprite2d::InjectHooks()
{
    HookInstall(0x727230, &CSprite2d::Constructor, 7);
    HookInstall(0x7281E0, &CSprite2d::DeConstructor, 7);
}

CSprite2d* CSprite2d::Constructor()
{

#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CSprite2d*))0x727230)(this);
#else
    this->CSprite2d::CSprite2d();
    return this;
#endif
}

CSprite2d* CSprite2d::DeConstructor()
{

#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CSprite2d*))0x7281E0)(this);
#else
    this->CSprite2d::~CSprite2d();
    return this;
#endif
}

// class functions
CSprite2d::CSprite2d()
{
    m_pTexture = 0;
}

CSprite2d::~CSprite2d()
{
    RwTextureDestroy(m_pTexture);
}

// delete this sprite (similar to destructor)
void CSprite2d::Delete()
{
    ((void(__thiscall*)(CSprite2d*))0x727240)(this);
}

// set texture by name from current txd
void CSprite2d::SetTexture(char* name)
{
    ((void(__thiscall*)(CSprite2d*, char*))0x727270)(this, name);
}

// set texture by name from current txd (+alpha mask name)
void CSprite2d::SetTexture(char* name, char* maskName)
{
    ((void(__thiscall*)(CSprite2d*, char*, char*))0x7272B0)(this, name, maskName);
}

void CSprite2d::SetAddressingUV(RwTextureAddressMode modeU, RwTextureAddressMode modeV)
{
    ((void(__thiscall*)(CSprite2d*, RwTextureAddressMode, RwTextureAddressMode))0x7272E0)(this, modeU, modeV);
}

void CSprite2d::SetAddressing(RwTextureAddressMode modeUV)
{
    ((void(__thiscall*)(CSprite2d*, RwTextureAddressMode))0x727320)(this, modeUV);
}

// sets sprite texture as current for device rendering
void CSprite2d::SetRenderState()
{
    ((void(__thiscall*)(CSprite2d*))0x727B30)(this);
}

// draw this sprite
void CSprite2d::Draw(float x, float y, float width, float height, CRGBA  const& color)
{
    ((void(__thiscall*)(CSprite2d*, float, float, float, float, CRGBA  const&))0x7282C0)(this, x, y, width, height, color);
}

void CSprite2d::Draw(CRect  const& posn, CRGBA  const& color)
{
    ((void(__thiscall*)(CSprite2d*, CRect  const&, CRGBA  const&))0x728350)(this, posn, color);
}

void CSprite2d::DrawWithBilinearOffset(CRect  const& posn, CRGBA  const& color)
{
    ((void(__thiscall*)(CSprite2d*, CRect  const&, CRGBA  const&))0x7283B0)(this, posn, color);
}

void CSprite2d::Draw(CRect  const& posn, CRGBA  const& color, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
{
    ((void(__thiscall*)(CSprite2d*, CRect  const&, CRGBA  const&, float, float, float, float, float, float, float, float))0x728420)(this, posn, color, u1, v1, u2, v2, u3, v3, u4, v4);
}

void CSprite2d::Draw(CRect  const& posn, CRGBA  const& color1, CRGBA  const& color2, CRGBA  const& color3, CRGBA  const& color4)
{
    ((void(__thiscall*)(CSprite2d*, CRect  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&))0x7284B0)(this, posn, color1, color2, color3, color4);
}

void CSprite2d::Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, CRGBA  const& color)
{
    ((void(__thiscall*)(CSprite2d*, float, float, float, float, float, float, float, float, CRGBA  const&))0x728520)(this, x1, y1, x2, y2, x3, y3, x4, y4, color);
}

// static functions
void CSprite2d::SetRecipNearClip()
{
    ((void(__cdecl*)())0x727260)();
}

void CSprite2d::InitPerFrame()
{
    ((void(__cdecl*)())0x727350)();
}

bool CSprite2d::IsVertexBufferEmpty()
{
    return ((bool(__cdecl*)())0x727390)();
}

bool CSprite2d::IsVertexBufferFull()
{
    return ((bool(__cdecl*)())0x7273A0)();
}

void CSprite2d::RenderVertexBuffer()
{
    ((void(__cdecl*)())0x7273D0)();
}

// different kinds of vertices' defining
void CSprite2d::SetVertices(CRect  const& posn, CRGBA  const& color1, CRGBA  const& color2, CRGBA  const& color3, CRGBA  const& color4)
{
    ((void(__cdecl*)(CRect  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&))0x727420)(posn, color1, color2, color3, color4);
}

void CSprite2d::SetVertices(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, CRGBA  const& color1, CRGBA  const& color2, CRGBA  const& color3, CRGBA  const& color4)
{
    ((void(__cdecl*)(float, float, float, float, float, float, float, float, CRGBA  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&))0x727590)(x1, y1, x2, y2, x3, y3, x4, y4, color1, color2, color3, color4);
}

void CSprite2d::SetVertices(CRect  const& posn, CRGBA  const& color1, CRGBA  const& color2, CRGBA  const& color3, CRGBA  const& color4, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
{
    ((void(__cdecl*)(CRect  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&, float, float, float, float, float, float, float, float))0x727710)(posn, color1, color2, color3, color4, u1, v1, u2, v2, u3, v3, u4, v4);
}

void CSprite2d::SetVertices(int numVerts, float* posn, float* texCoors, CRGBA  const& color)
{
    ((void(__cdecl*)(int, float*, float*, CRGBA  const&))0x727890)(numVerts, posn, texCoors, color);
}

void CSprite2d::SetVertices(int numVerts, float* posn, CRGBA* color)
{
    ((void(__cdecl*)(int, float*, CRGBA*))0x727920)(numVerts, posn, color);
}

void CSprite2d::SetMaskVertices(int numVerts, float* posn, float depth)
{
    ((void(__cdecl*)(int, float*, float))0x7279B0)(numVerts, posn, depth);
}

void CSprite2d::SetVertices(RwD3D9Vertex* vertices, CRect  const& posn, CRGBA  const& color1, CRGBA  const& color2, CRGBA  const& color3, CRGBA  const& color4, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
{
    ((void(__cdecl*)(RwD3D9Vertex*, CRect  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&, float, float, float, float, float, float, float, float))0x727A00)(vertices, posn, color1, color2, color3, color4, u1, v1, u2, v2, u3, v3, u4, v4);
}

// draws non-textured rectangle
void CSprite2d::DrawRect(CRect  const& posn, CRGBA  const& color)
{
    ((void(__cdecl*)(CRect  const&, CRGBA  const&))0x727B60)(posn, color);
}

//this could be used for drawing textured rectangle (use SetRenderState() before this)
void CSprite2d::DrawTxRect(CRect  const& posn, CRGBA  const& color)
{
    ((void(__cdecl*)(CRect  const&, CRGBA  const&))0x727BE0)(posn, color);
}

// draw non-textured rectangle, with setupable corners' colors.
void CSprite2d::DrawRect(CRect  const& posn, CRGBA  const& color1, CRGBA  const& color2, CRGBA  const& color3, CRGBA  const& color4)
{
    ((void(__cdecl*)(CRect  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&))0x727C10)(posn, color1, color2, color3, color4);
}

// draws non-textured rectangle with default blending states
void CSprite2d::DrawRectXLU(CRect  const& posn, CRGBA  const& color1, CRGBA  const& color2, CRGBA  const& color3, CRGBA  const& color4)
{
    ((void(__cdecl*)(CRect  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&))0x727C50)(posn, color1, color2, color3, color4);
}

// draws rectangle, texture could be set with SetRenderState().
void CSprite2d::DrawAnyRect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, CRGBA  const& color1, CRGBA  const& color2, CRGBA  const& color3, CRGBA  const& color4)
{
    ((void(__cdecl*)(float, float, float, float, float, float, float, float, CRGBA  const&, CRGBA  const&, CRGBA  const&, CRGBA  const&))0x727CC0)(x1, y1, x2, y2, x3, y3, x4, y4, color1, color2, color3, color4);
}

// draws a triangle with rotation (degrees)
void CSprite2d::DrawCircleAtNearClip(CVector2D  const& posn, float size, CRGBA  const& color, int angle)
{
    ((void(__cdecl*)(CVector2D  const&, float, CRGBA  const&, int))0x727D60)(posn, size, color, angle);
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
void CSprite2d::DrawBarChart(float x, float y, unsigned short width, unsigned char height, float progress,
    signed char progressAdd, unsigned char drawPercentage, unsigned char drawBlackBorder,
    CRGBA color, CRGBA addColor)
{
    ((void(__cdecl*)(float, float, unsigned short, unsigned char, float, signed char, unsigned char,
        unsigned char, CRGBA, CRGBA))0x728640)(x, y, width, height, progress, progressAdd, drawPercentage,
            drawBlackBorder, color, addColor);
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
