#pragma once

#include "CStencilShadowObjects.h"

class CStencilShadowObject {
public:
    CEntity* owner;
    signed short int m_NumShadowFaces;
    char m_Type;
    char pad;
    unsigned int m_FaceID;
    unsigned int m_SizeOfShadowFacesData;
    unsigned int m_ShadowFacesData;
    CStencilShadowObject* next;
    CStencilShadowObject* prev;

public:
    static void InjectHooks();

    CStencilShadowObject();
    ~CStencilShadowObject();

    static void Shutdown();
    static void Render(CRGBA* color);
    static void RenderForVehicle(CDummy* dummy);
    static void RenderForObject(CStencilShadowObject* object);
};

VALIDATE_SIZE(CStencilShadowObject, 0x1C);

void gRenderStencil();