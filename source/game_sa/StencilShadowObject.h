#pragma once

class CStencilShadowObject {
public:
    CEntity*              m_pOwner;
    int16                 m_NumShadowFaces;
    char                  m_Type;
    uint32                m_FaceID;
    uint32                m_SizeOfShadowFacesData;
    uint32                m_ShadowFacesData;
    CStencilShadowObject* m_pNext;
    CStencilShadowObject* m_pPrev;

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

bool gRenderStencil();
