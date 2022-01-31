#pragma once

class CStencilShadowObject {
public:
    CEntity*              owner;
    int16                 m_NumShadowFaces;
    char                  m_Type;
    char                  pad;
    uint32                m_FaceID;
    uint32                m_SizeOfShadowFacesData;
    uint32                m_ShadowFacesData;
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
