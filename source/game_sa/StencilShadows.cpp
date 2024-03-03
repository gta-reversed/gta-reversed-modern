#include "StdInc.h"

#include "StencilShadowObject.h"

CStencilShadowObject* CStencilShadows::pFirstAvailableStencilShadowObject = reinterpret_cast<CStencilShadowObject *>(0xC6A168);
CStencilShadowObject* CStencilShadows::pFirstActiveStencilShadowObject = reinterpret_cast<CStencilShadowObject *>(0xC6A16C);

static inline auto* s_ShadowTrianglePointsUnk = StaticRef<RxVertexIndex*>(0xC6A170);
static inline auto* s_ShadowTrianglePoints = StaticRef<CVector*>(0xC6A170);
static inline auto* s_TransformedShadowTrianglePoints = StaticRef<CVector*>(0xC6A170);

void CStencilShadows::InjectHooks() {
    RH_ScopedClass(CStencilShadows);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x70F9E0);
    RH_ScopedInstall(Shutdown, 0x711390);
    RH_ScopedInstall(Process, 0x711D90);
    RH_ScopedInstall(GraphicsHighQuality, 0x70F9B0, {.reversed=false});
    RH_ScopedInstall(UpdateHierarchy, 0x710BC0);
    RH_ScopedInstall(RegisterStencilShadows, 0x711760, {.reversed=false});
    RH_ScopedInstall(RenderStencilShadows, 0x7113B0, {.reversed=false});
    RH_ScopedInstall(RenderForVehicle, 0x70FAE0, {.reversed=false});
    RH_ScopedInstall(RenderForObject, 0x710310, {.reversed=false});
    RH_ScopedInstall(Render, 0x710D50, {.reversed=false});
}

// 0x70F9E0
void CStencilShadows::Init() {
    ZoneScoped;

    RwD3D9SetStencilClear(0);
    pFirstAvailableStencilShadowObject = m_StencilShadowObjects.data();
    pFirstActiveStencilShadowObject = nullptr;

    for (auto&& [i, obj] : notsa::enumerate(m_StencilShadowObjects)) {
        obj.m_pOwner                = nullptr;
        obj.m_NumShadowFaces        = 0;
        obj.m_Type                  = eStencilShadowObjType::NONE;
        obj.m_SizeOfShadowFacesData = 0;
        obj.m_FaceID                = 0;
        obj.m_ShadowFacesData       = 0;

        obj.m_pPrev = i ? &m_StencilShadowObjects[i - 1] : nullptr;
        obj.m_pNext = (i != m_StencilShadowObjects.size() - 1) ? &m_StencilShadowObjects[i + 1] : nullptr;
    }
}

// 0x711390
void CStencilShadows::Shutdown() {
    for (auto* obj = pFirstActiveStencilShadowObject; obj;) {
        auto* next = obj->m_pNext;
        obj->Destroy();
        obj = next;
    }
}

// 0x710D50
void CStencilShadows::Render() {
    plugin::Call<0x710D50>();
}

// 0x7113B0
void CStencilShadows::RenderStencilShadows() {
    return plugin::Call<0x7113B0>();

    if (!GraphicsHighQuality()) {
        return;
    }

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,             RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESTENCILENABLE,            RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,                RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,                RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,            RWRSTATE(0));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,        RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,                 RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,                RWRSTATE(2u));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTIONMASK,      RWRSTATE(uint32(-1)));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTIONWRITEMASK, RWRSTATE(uint32(-1)));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTION,          RWRSTATE(8u));
    RwRenderStateSet(rwRENDERSTATESTENCILFAIL,              RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILZFAIL,             RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILPASS,              RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTIONREF,       RWRSTATE(0));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,              RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILZFAIL,             RWRSTATE(7u));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(3u));

    const auto black = CRGBA(0, 0, 0, 255);
    // RenderStencil(black); // 0x710D50

    RwRenderStateSet(rwRENDERSTATESTENCILZFAIL,             RWRSTATE(8u));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(2u));

    // RenderStencil(black);

    // WTF is up with these states?
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,        RWRSTATE(FALSE)); // same state
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,             RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,              RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESTENCILENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,                RWRSTATE(2u));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(2u));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,             RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,              RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESTENCILENABLE,            RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,                RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,        RWRSTATE(TRUE)); // same state
    RwRenderStateSet(rwRENDERSTATESRCBLEND,                 RWRSTATE(5u));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,                RWRSTATE(6u));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,                RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,            RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTIONREF,       RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTION,          RWRSTATE(4u));
    RwRenderStateSet(rwRENDERSTATESTENCILFAIL,              RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILZFAIL,             RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILPASS,              RWRSTATE(1u));

    CSprite2d::InitPerFrame();

    auto color = CRGBA(0, 0, 0, 50u);
    color.a    = (color.a * CTimeCycle::m_CurrentColours.m_nShadowStrength) >> 8;
    CRect rect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    CSprite2d::DrawRect(rect, color);

    RwRenderStateSet(rwRENDERSTATESTENCILENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,             RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,              RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,        RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,                RWRSTATE(2u));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(2u));
}

// 0x70FAE0
void CStencilShadows::RenderForVehicle(CStencilShadowObject* object) {
    plugin::Call<0x70FAE0, CStencilShadowObject*>(object);
}

// 0x710310
void CStencilShadows::RenderForObject(CStencilShadowObject* object) {
    plugin::Call<0x710310, CStencilShadowObject*>(object);
}

// 0x711D90
void CStencilShadows::Process(CVector& cameraPos) {
    ZoneScoped;

    if (!GraphicsHighQuality()) {
        return;
    }

    static uint8 s_RegisterShadowCounter{}, s_RenderForObjCounter{};

    RegisterStencilShadows(cameraPos, ++s_RegisterShadowCounter % 8);

    // why do we even do this?
    s_ShadowTrianglePointsUnk = (RxVertexIndex*)CMemoryMgr::Malloc(0x3000 * sizeof(RxVertexIndex));
    s_ShadowTrianglePoints = (CVector*)CMemoryMgr::Malloc(2048 * sizeof(CVector));
    s_TransformedShadowTrianglePoints = (CVector*)CMemoryMgr::Malloc(2'048 * sizeof(CVector));

    auto i{ 0 };
    for (auto* obj = pFirstActiveStencilShadowObject; obj; obj = obj->m_pNext) {
        switch (obj->m_Type) {
        case eStencilShadowObjType::OBJECT:
            if ((i++ % 4) == s_RenderForObjCounter) {
                RenderForObject(obj);
            }
            break;
        case eStencilShadowObjType::VEHICLE:
            RenderForVehicle(obj);
            break;
        default:
            break;
        }
    }
    s_RenderForObjCounter = (s_RenderForObjCounter + 1) % 4;

    CMemoryMgr::Free(std::exchange(s_ShadowTrianglePointsUnk, nullptr));
    CMemoryMgr::Free(std::exchange(s_ShadowTrianglePoints, nullptr));
    CMemoryMgr::Free(std::exchange(s_TransformedShadowTrianglePoints, nullptr));
}

// 0x70F9B0
bool CStencilShadows::GraphicsHighQuality() {
    return g_fx.GetFxQuality() >= FX_QUALITY_MEDIUM
        && RwRasterGetDepth(RwCameraGetRaster(Scene.m_pRwCamera)) >= 32;
}

// 0x710BC0
void CStencilShadows::UpdateHierarchy(CStencilShadowObject*& firstAvailable, CStencilShadowObject*& firstActive, CStencilShadowObject* newOne) {
    if (auto* prev = newOne->m_pPrev) {
        auto* next = newOne->m_pNext;
        if (next) {
            next->m_pPrev = prev;
            newOne->m_pPrev->m_pNext = newOne->m_pNext;
        } else {
            prev->m_pNext = nullptr;
        }
    } else {
        auto* next     = newOne->m_pNext;
        firstAvailable = next;
        if (next) {
            next->m_pPrev = nullptr;
        }
    }
    newOne->m_pNext = firstActive;
    newOne->m_pPrev = nullptr;
    firstActive     = newOne;

    if (newOne->m_pNext) {
        newOne->m_pNext->m_pPrev = newOne;
    }
}

// 0x711760
void CStencilShadows::RegisterStencilShadows(CVector& cameraPos, bool doNotCreateNew) {
}
