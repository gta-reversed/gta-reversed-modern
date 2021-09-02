/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CRect.h"
#include "CRGBA.h"
#include "CVector2D.h"
#include "RenderWare.h"

#define NUM_SPRITE_VERTICES 8

class CSprite2d {
private:
    CSprite2d* Constructor();
    CSprite2d* Destructor();

public:
    // class variables
    struct RwTexture* m_pTexture;
    // static variables
    static int32& nextBufferIndex;
    static int32& nextBufferVertex;
    static float& NearScreenZ;
    static float& RecipNearClip;
    // count: 8
    static struct RwD3D9Vertex* maVertices;
    // class functions

public:
    static void InjectHooks();

    CSprite2d();
    ~CSprite2d();

    // delete this sprite (similar to destructor)
    void Delete();
    // set texture by name from current txd
    void SetTexture(char* name);
    // set texture by name from current txd (+alpha mask name)
    void SetTexture(char* name, char* maskName);
    void SetAddressingUV(RwTextureAddressMode modeU, RwTextureAddressMode modeV);
    void SetAddressing(RwTextureAddressMode modeUV);
    // sets sprite texture as current for device rendering
    void SetRenderState();
    // draw this sprite
    void Draw(float x, float y, float width, float height, const CRGBA& color);
    void Draw(const CRect& posn, const CRGBA& color);
    void DrawWithBilinearOffset(const CRect& posn, const CRGBA& color);
    void Draw(const CRect& posn, const CRGBA& color, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);
    void Draw(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4);
    void Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA& color);
    // static functions
    static void SetRecipNearClip();
    static void InitPerFrame();
    static bool IsVertexBufferEmpty();
    static bool IsVertexBufferFull();
    static void RenderVertexBuffer();
    // different kinds of vertices' defining
    static void SetVertices(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4);
    static void SetVertices(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4);
    static void SetVertices(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);
    static void SetVertices(int32 numVerts, float* posn, float* texCoors, const CRGBA& color);
    static void SetVertices(int32 numVerts, float* posn, CRGBA* color);
    static void SetMaskVertices(int32 numVerts, float* posn, float depth);
    static void SetVertices(RwD3D9Vertex* vertices, const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);
    // draws non-textured rectangle
    static void DrawRect(const CRect& posn, const CRGBA& color);
    // this could be used for drawing textured rectangle (use SetRenderState() before this)
    static void DrawTxRect(const CRect& posn, const CRGBA& color);
    // draw non-textured rectangle, with setupable corners' colors.
    static void DrawRect(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4);
    // draws non-textured rectangle with default blending states
    static void DrawRectXLU(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4);
    // draws rectangle, texture could be set with SetRenderState().
    static void DrawAnyRect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4);
    // draws a triangle with rotation (degrees)
    static void DrawCircleAtNearClip(CVector2D const& posn, float size, const CRGBA& color, int32 angle);
    // this makes some trick with sprite z position (z = NearScreenZ + 0.000001).
    static void SetVerticesForSniper(const CRect& posn, const CRGBA& color1, const CRGBA& color2, const CRGBA& color3, const CRGBA& color4);
    static void OffsetTexCoordForBilinearFiltering(float width, float height);
    // add vertices to buffer
    static void AddToBuffer(const CRect& posn, const CRGBA& color, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);
    // non-textured polygon
    static void Draw2DPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA& color);
    // draws progress line. Progress is a value in ranges 0 - 100.
    static void DrawBarChart(float x, float y, uint16 width, uint8 height, float progress, signed char progressAdd, uint8 drawPercentage, uint8 drawBlackBorder, CRGBA color, CRGBA addColor);
};

VALIDATE_SIZE(CSprite2d, 4);
