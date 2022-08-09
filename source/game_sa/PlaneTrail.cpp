#include "StdInc.h"

#include "PlaneTrail.h"

void CPlaneTrail::InjectHooks() {
    RH_ScopedClass(CPlaneTrail);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x717160);
    RH_ScopedInstall(Render, 0x717180);
    RH_ScopedInstall(RegisterPoint, 0x7172D0);
}

// 0x717160
void CPlaneTrail::Init() {
    std::ranges::fill(m_timepoints, 0);
}

// 0x717180
void CPlaneTrail::Render(float intensity) {
    const int32 maxAlpha = (int32)(intensity * 110.0f);
    if (!maxAlpha)
        return;

    uint32 nVertices = 0;
    RxObjSpace3DVertex vertBuff[PLANE_TRAIL_BUFSZ];
    for (auto i = 0; i < PLANE_TRAIL_BUFSZ; i++) {
        const uint32 timeDelta = CTimer::GetTimeInMS() - m_timepoints[i];
        if (m_timepoints[i] && timeDelta <= 30'000) {
            const CVector& pos = m_positions[i];
            RxObjSpace3DVertex& vert = vertBuff[i];

            const float fAlphaMult = std::min(1.0f, (30'000.0f - (float)timeDelta) / 10'000.0f); // Clamped to 1.0f
            RwIm3DVertexSetRGBA(&vert, 0xFF, 0xFF, 0xFF, (RwUInt8)(maxAlpha * fAlphaMult));
            RwIm3DVertexSetPos(&vert, pos.x, pos.y, pos.z);

            nVertices++;
        } else {
            m_timepoints[i] = 0;
        }
    }

    if (nVertices > 1) {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
        RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
        RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(NULL));
        if (RwIm3DTransform(vertBuff, nVertices, nullptr, rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA)) {
            static RwImVertexIndex indices[] = { // From 0x8D5B98, size 32
                0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16
            };
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPELINELIST, indices, 2 * nVertices - 2);
            RwIm3DEnd();
        }
    }
}

// 0x7172D0
void CPlaneTrail::RegisterPoint(CVector pos) {
    const auto& lastUpdate = m_timepoints[0];
    const bool bDoShift = lastUpdate && CTimer::GetTimeInMS() - lastUpdate > 2000;
    if (bDoShift) {
        // Shift right
        for (auto i = PLANE_TRAIL_BUFSZ - 1; i; i--) {
            m_timepoints[i] = m_timepoints[i - 1];
            m_positions[i] = m_positions[i - 1];
        }
    }

    m_positions[0] = pos;
    if (bDoShift || !m_timepoints[0])
        m_timepoints[0] = CTimer::GetTimeInMS();
}

void CPlaneTrail::Update(CVector pos, CRGBA color, uint32_t coronaIdx, uint32_t timeModifierMs, uint8_t afterHour, uint8_t beforeHour) {
    const float fTimeProg = (float)(CTimer::m_snTimeInMilliseconds % 131072) / 20860.0f; // or * 0.000047936901.. Not sure where this comes from..
    const CVector currPos = pos * CVector(std::sin(fTimeProg), std::cos(fTimeProg), 1.0f);

    RegisterPoint(currPos);

    if (!CClock::ClockHoursInRange(afterHour, beforeHour)) {
        return;
    }

    if ((CTimer::m_snTimeInMilliseconds + timeModifierMs) & 512) {
        CCoronas::RegisterCorona(
            coronaIdx,
            nullptr,
            color.r, color.g, color.b, color.a,
            currPos,
            5.0f,
            2000.0f,
            eCoronaType::CORONATYPE_HEADLIGHT,
            eCoronaFlareType::FLARETYPE_NONE,
            false,
            false,
            false,
            0.0f,
            false,
            1.5f,
            0,
            15.0f,
            false,
            false
        );
    } else {
        CCoronas::UpdateCoronaCoors(coronaIdx, currPos, 2000.0f, 0.0f);
    }
}
