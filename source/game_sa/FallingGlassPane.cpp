#include "StdInc.h"
#include "FallingGlassPane.h"

void CFallingGlassPane::InjectHooks() {
    ReversibleHooks::Install("CFallingGlassPane", "CFallingGlassPane", 0x71A8B0, &CFallingGlassPane::Constructor);
    ReversibleHooks::Install("CFallingGlassPane", "~CFallingGlassPane", 0x71A8C0, &CFallingGlassPane::Destructor);
    ReversibleHooks::Install("CFallingGlassPane", "Update", 0x71AA10, &CFallingGlassPane::Update);
    ReversibleHooks::Install("CFallingGlassPane", "Render", 0x71B100, &CFallingGlassPane::Render);
}

// 0x71A8B0
CFallingGlassPane::CFallingGlassPane() {}

// 0x71A8B0
CFallingGlassPane* CFallingGlassPane::Constructor() {
    this->CFallingGlassPane::CFallingGlassPane();
    return this;
}

// 0x71A8C0
CFallingGlassPane::~CFallingGlassPane() {}

// 0x71A8C0
CFallingGlassPane* CFallingGlassPane::Destructor() {
    this->CFallingGlassPane::~CFallingGlassPane();
    return this;
}

// 0x71AA10
void CFallingGlassPane::Update() {
    if (CTimer::GetTimeInMS() < createdTime)
        return;

    auto& pos = matrix.GetPosition();

    if (field_6F) {
        pos += CTimer::GetTimeStep() * 0.35f * velocity;
        velocity.z -= CTimer::GetTimeStep() / 100.f;
    } else {
        pos += CTimer::GetTimeStep() * velocity;
        velocity.z -= CTimer::GetTimeStep() / 50.f;
    }

    matrix.GetRight()   += CrossProduct(randomNumbers, matrix.GetRight());
    matrix.GetForward() += CrossProduct(randomNumbers, matrix.GetForward());
    matrix.GetUp()      += CrossProduct(randomNumbers, matrix.GetUp());

    if (pos.z < groundZ) {
        existFlag = false;
        AudioEngine.ReportGlassCollisionEvent(AE_GLASS_HIT_GROUND, { pos.x, pos.y, groundZ });
        if (!field_6F) {
            RwRGBA color{ 255, 255, 255, 32 };
            for (auto i = 0; i < 4; i++) {
                g_fx.AddGlass(pos, color, CGeneral::GetRandomNumberInRange(0.02f, 0.06f), 1);
            }
        }
    }
}

auto CFallingGlassPane::CalculateHiHlightPolyColor() {
    const auto alpha       = (float)CGlass::CalcAlphaWithNormal(Normalized(matrix.GetForward()));
    const auto delta       = (float)std::clamp(CTimer::GetTimeInMS() - createdTime, 0u, 500u);
    const auto scaledAlpha = (unsigned)(alpha * delta / 500.f);
    const auto final       = field_6F ? std::max(64u, scaledAlpha) : scaledAlpha;
    return RwRGBA(final, final, final, final);
}

auto CFallingGlassPane::CalculateShatterPolyColor() {
    const auto camDist = (matrix.GetPosition() - TheCamera.GetPosition()).Magnitude();
    if (camDist > 30.f) {
        const auto alpha = (uint8)((1.0f - (camDist - 30.f) / 10.f) * 140.f);
        return RwRGBA(alpha, alpha, alpha, alpha);
    }
    return RwRGBA(140u, 140u, 140u, 140u);
}

// 0x71B100
void CFallingGlassPane::Render() {
    constexpr RwImVertexIndex indices[]{ 0u, 1u, 2u, 0u, 2u, 1u };

    // Render HiLightPoly's
    CVector vertices[3]{};
    {
        const auto color = CalculateHiHlightPolyColor();
        constexpr RwTexCoords uv[3] = {
            {0.5f, 0.5f},
            {0.5f, 0.6f},
            {0.6f, 0.6f},
        };
        for (auto i = 0u; i < 3u; i++) {
            auto& vertex = aTempBufferVertices[CGlass::H1iLightPolyVerticesIdx + i];

            const auto pos2DOS = CGlass::PanePolyPositions[nPieceIndex][i] - CGlass::PanePolyCenterPositions[nPieceIndex];
            vertices[i] = MultiplyMatrixWithVector(matrix, { pos2DOS.x, 0.f, pos2DOS.y });
            RxObjSpace3DVertexSetPos(&vertex, &vertices[i]);

            RxObjSpace3DVertexSetU(&vertex, uv[i].u);
            RxObjSpace3DVertexSetV(&vertex, uv[i].v);

            RxObjSpace3DVertexSetPreLitColor(&vertex, &color);
        }

        // Store indices
        uint32 i = CGlass::HiLightPolyIndicesIdx;
        for (const auto idx : indices) {
            aTempBufferIndices[i++] = (RwImVertexIndex)(CGlass::H1iLightPolyVerticesIdx + idx);
        }

        CGlass::H1iLightPolyVerticesIdx += 3;
        CGlass::HiLightPolyIndicesIdx += 6;
    }

    if (bRenderShatter) {
        const auto color = CalculateShatterPolyColor();
        for (auto i = 0u; i < 3u; i++) {
            auto& vertex = aTempBufferVertices[CGlass::ShatteredVerticesBaseIdx + i];

            RxObjSpace3DVertexSetPos(&vertex, &vertices[i]);
            RxObjSpace3DVertexSetPreLitColor(&vertex, &color);

            const auto uv = CGlass::PanePolyPositions[nPieceIndex][i] * size * 4.f;
            RxObjSpace3DVertexSetU(&vertex, uv.x);
            RxObjSpace3DVertexSetV(&vertex, uv.y);
        }

        uint32 i = CGlass::ShatteredVerticesBaseIdx;
        for (const auto idx : indices) {
            aTempBufferIndices[i++] = (RwImVertexIndex)(CGlass::ShatteredVerticesBaseIdx - 1024u - idx);
        }
    }
}
