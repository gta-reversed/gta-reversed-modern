#pragma once

class CLines {
public:
    static void InjectHooks();

    static void RenderLineNoClipping(float startX, float startY, float startZ, float endX, float endY, float endZ, uint32 startColor, uint32 endColor);
    static void RenderLineWithClipping(float startX, float startY, float startZ, float endX, float endY, float endZ, uint32 startColor, uint32 endColor);
    static void ImmediateLine2D(int startX, int startY, int endX, int endY, uint8 startR, uint8 startG, uint8 startB, uint8 startA, uint8 endR, uint8 endG, uint8 endB, uint8 endA);

public:
    // NOTSA wrappers
    static void RenderLineNoClipping(const CVector& start, const CVector& end, uint32 startColor, uint32 endColor) {
        RenderLineNoClipping(start.x, start.y, start.z, end.x, end.y, end.z, startColor, endColor);
    }

    static void RenderLineWithClipping(const CVector& start, const CVector& end, uint32 startColor, uint32 endColor) {
        RenderLineWithClipping(start.x, start.y, start.z, end.x, end.y, end.z, startColor, endColor);
    }

    static void ImmediateLine2D(const CVector2D& start, const CVector2D& end, const CRGBA& startColor, const CRGBA& endColor) {
        ImmediateLine2D(
            start.x, start.y,
            end.x, end.y,
            startColor.r, startColor.g, startColor.b, startColor.a,
            endColor.r, endColor.g, endColor.b, endColor.a
        );
    }
};
