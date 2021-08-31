#include "StdInc.h"
#include "CBrightLights.h"

uint32_t& CBrightLights::NumBrightLights = *(uint32_t*)0xC7C6FC;
tBrightLight (&CBrightLights::aBrightLights)[MAX_NUM_BRIGHTLIGHTS] = *(tBrightLight(*)[MAX_NUM_BRIGHTLIGHTS])0xC7CB58;

void CBrightLights::InjectHooks() {
    ReversibleHooks::Install("CBrightLights", "Init", 0x722140, &CBrightLights::Init);
    ReversibleHooks::Install("CBrightLights", "RenderOutGeometryBuffer", 0x722150, &CBrightLights::RenderOutGeometryBuffer);
    ReversibleHooks::Install("CBrightLights", "Render", 0x7241C0, &CBrightLights::Render);
    ReversibleHooks::Install("CBrightLights", "RegisterOne", 0x724770, &CBrightLights::RegisterOne);
}

// 0x722140
void CBrightLights::Init() {
    NumBrightLights = 0;
}

// 0x722150
void CBrightLights::RenderOutGeometryBuffer() {
    if (uiTempBufferIndicesStored) {
        LittleTest();
        if (RwIm3DTransform(aTempBufferVertices, uiTempBufferVerticesStored, nullptr, rwIM3D_VERTEXUV))
        {
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, aTempBufferIndices, uiTempBufferIndicesStored);
            RwIm3DEnd();
        }
        uiTempBufferVerticesStored = 0;
        uiTempBufferIndicesStored = 0;
    }
}

// 0x7241C0
void CBrightLights::Render() {
    if (!NumBrightLights)
        return;

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     (void*)nullptr);
    RwRenderStateSet(rwRENDERSTATECULLMODE,          (void*)rwCULLMODECULLNONE);

    uiTempBufferVerticesStored = 0;
    uiTempBufferIndicesStored = 0;

    for (unsigned i = 0; i < NumBrightLights; i++) {
        // Maybe render vertex buffer if running low on free items...
        if (uiTempBufferIndicesStored > TOTAL_TEMP_BUFFER_INDICES - 40u ||
            uiTempBufferVerticesStored > TOTAL_TEMP_BUFFER_VERTICES - 40u
            )
        {
            CBrightLights::RenderOutGeometryBuffer();
        }
        aBrightLights[i].Render();
    }

    RenderOutGeometryBuffer();
    NumBrightLights = 0;

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
}

// 0x724770
void CBrightLights::RegisterOne(CVector posn, CVector top, CVector right, CVector at, eBrightLightColor color, uint8_t arg5, uint8_t arg6, uint8_t arg7) {
    if (color == eBrightLightColor::BRIGHTLIGHT_NONE)
        return;

    if (NumBrightLights >= MAX_NUM_BRIGHTLIGHTS)
        return;

    const float distToCam = (TheCamera.GetPosition() - posn).Magnitude() / TheCamera.m_fLODDistMultiplier;
    if (distToCam > 60.0f)
        return;

    aBrightLights[NumBrightLights++] = {
        posn,
        top,
        right,
        at,
        distToCam,
        color,
        arg5,
        arg6,
        arg7
    };
}

CRGBA tBrightLight::GetColorRGBA() const {
    const auto GetAlpha = [this]() -> uint8 {
        if (m_fDistanceToCamera >= 45.0f)
            return (uint8)((1.0f - invLerp(45.0f, 60.0f, m_fDistanceToCamera)) * 255.0f / 2.0f);
        return (uint8)(255 / 2);
    };

    // Originally R* used:
    // const auto rnd = (uint8)((float)(uint8)rand() / 5.0f);
    const auto rnd = (uint8)CGeneral::GetRandomNumberInRange(0, 255 / 5);
    switch (m_nColor) {
    case BRIGHTLIGHT_GREEN_BIG:
    case BRIGHTLIGHT_GREEN_SMALL:
        return { rnd, 255, rnd, GetAlpha() };

    case BRIGHTLIGHT_YELLOW_BIG:
    case BRIGHTLIGHT_YELLOW_SMALL:
        return { 255, 128, rnd, GetAlpha() };

    case BRIGHTLIGHT_RED_BIG:
    case BRIGHTLIGHT_RED_SMALL:
        return { 255, rnd, rnd, GetAlpha() };

    default: { // NOTSA
        assert(0); 
        return { 255, 255, 255, 255 }; // Shouldn't reach this point.. in theory that is..
    }
    }
}

void tBrightLight::Render() const {
    // Get absolute vertex index in buffer (relative to the current number of vertices)
    const auto GetVertexRealIdx = [](unsigned i) {
        return (unsigned)uiTempBufferVerticesStored + i;
    };

    // Get vertex pointer, i is passed to `GetVertexRealIdx`
    const auto GetVertex = [=](unsigned i) {
        return &aTempBufferVertices[GetVertexRealIdx(i)];
    };

    // Set position of vertex, workaround for taking a temporary's address
    const auto SetVertexPosition = [=](unsigned i, CVector posn) {
        RxObjSpace3DVertexSetPos(GetVertex(i), &posn);
    };

    // Push a vertex index. `vertIdx` is passed to `GetVertexRealIdx`
    auto PushVerexIndex = [=, idx = 0](unsigned vertIdx) mutable {
        aTempBufferIndices[(unsigned)uiTempBufferIndicesStored + idx++] = GetVertexRealIdx(vertIdx);
    };

    const RwRGBA color = GetColorRGBA().ToRwRGBA();
    switch (m_nColor) {
    case BRIGHTLIGHT_GREEN_BIG:
    case BRIGHTLIGHT_YELLOW_BIG:
    case BRIGHTLIGHT_RED_BIG: {
        // 0x5C0A7C
        constexpr float TrafficLightsUp[] = { 0.162f, 0.162f, 0.0f, -0.162f, -0.162f, 0.0f };

        // 0x5C0A94 
        constexpr float TrafficLightsSide[] = { -0.09f, 0.09f, 0.162f, 0.09f, -0.09f, -0.162f };

        for (unsigned i = 0; i < 6; i++) {
            RxObjSpace3DVertexSetPreLitColor(GetVertex(i), &color);

            SetVertexPosition(i,
                  m_vecPosition
                + m_vecRight * TrafficLightsUp[i]
                + m_vecTop * TrafficLightsSide[i]
            );
        }

        // 0x8D5DBC
        constexpr RxVertexIndex TrafficLightIndices[] = { 0, 1, 5, 1, 2, 3, 1, 3, 4, 1, 4, 5 };
        for (unsigned i = 0; i < 12; i++)
            PushVerexIndex(TrafficLightIndices[i]);

        uiTempBufferIndicesStored += 12;
        uiTempBufferVerticesStored += 6;
        break;
    }
    case BRIGHTLIGHT_GREEN_SMALL:
    case BRIGHTLIGHT_YELLOW_SMALL:
    case BRIGHTLIGHT_RED_SMALL: {
        constexpr unsigned segCount = 8;
        constexpr float    segAngleStep = 2 * rwPI / (float)(segCount);
        constexpr float    segSize = 0.1f;
        for (unsigned i = 0; i < segCount; i++) {
            RxObjSpace3DVertexSetPreLitColor(GetVertex(i), &color);

            const float angle = segAngleStep * (float)(i);
            SetVertexPosition(i,
                  m_vecPosition
                + m_vecRight * std::cos(angle) * segSize
                + m_vecTop * std::sin(angle) * segSize
            );
        }

        for (unsigned i = 1; i <= 6; i++) {
            PushVerexIndex(0);
            PushVerexIndex(i);
            PushVerexIndex(i + 1);
        }

        uiTempBufferIndicesStored += 18;
        uiTempBufferVerticesStored += segCount;
        break;
    }
    default: {
        assert(0); // NOTSA
        break;
    }
    }
}
