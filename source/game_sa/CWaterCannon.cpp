#include "StdInc.h"
#include "CWaterCannon.h"

RxVertexIndex (&CWaterCannon::m_auRenderIndices)[18] = *(RxVertexIndex (*)[18])0xC80700;

void CWaterCannon::InjectHooks() {
    ReversibleHooks::Install("CWaterCannon", "Constructor", 0x728B10, &CWaterCannon::Constructor);
    ReversibleHooks::Install("CWaterCannon", "Destructor", 0x728B30, &CWaterCannon::Destructor);
    ReversibleHooks::Install("CWaterCannon", "Init", 0x728B40, &CWaterCannon::Init);
    ReversibleHooks::Install("CWaterCannon", "Update_OncePerFrame", 0x72A280, &CWaterCannon::Update_OncePerFrame);
    ReversibleHooks::Install("CWaterCannon", "Update_NewInput", 0x728C20, &CWaterCannon::Update_NewInput);
    // ReversibleHooks::Install("CWaterCannon", "PushPeds", 0x7295E0, &CWaterCannon::PushPeds);
    ReversibleHooks::Install("CWaterCannon", "Render", 0x728DA0, &CWaterCannon::Render);
}

// 0x728B10
CWaterCannon::CWaterCannon() {
    // NOP
}

CWaterCannon* CWaterCannon::Constructor() {
    this->CWaterCannon::CWaterCannon();
    return this;
}

// 0x728B30
CWaterCannon::~CWaterCannon() {
    // NOP
}

CWaterCannon* CWaterCannon::Destructor() {
    CWaterCannon::~CWaterCannon();
    return this;
}

// 0x728B40
void CWaterCannon::Init() {
    m_nId = 0;
    m_nSectionsCount = 0;
    m_nCreationTime = CTimer::m_snTimeInMilliseconds;
    m_anSectionState[0] = '\0';

    m_auRenderIndices[0] = 0;
    m_auRenderIndices[1] = 1;
    m_auRenderIndices[2] = 2;

    m_auRenderIndices[3] = 1;
    m_auRenderIndices[4] = 3;
    m_auRenderIndices[5] = 2;

    m_auRenderIndices[6] = 4;
    m_auRenderIndices[7] = 5;
    m_auRenderIndices[8] = 6;

    m_auRenderIndices[9] = 5;
    m_auRenderIndices[10] = 7;
    m_auRenderIndices[11] = 6;

    m_auRenderIndices[12] = 8;
    m_auRenderIndices[13] = 9;
    m_auRenderIndices[14] = 10;

    m_auRenderIndices[15] = 9;
    m_auRenderIndices[16] = 11;
    m_auRenderIndices[17] = 10;

    m_audio.Initialise(this);
}

bool CWaterCannon::HasActiveSection() const {
    const auto end = std::end(m_anSectionState);
    return std::find(std::begin(m_anSectionState), end, true) != end;
}

// 0x72A280
void CWaterCannon::Update_OncePerFrame(short a1) {
    if (CTimer::GetTimeMs() > m_nCreationTime + 150) {
        const auto section = (m_nSectionsCount + 1) % SECTIONS_COUNT;
        m_nSectionsCount = section;
        m_anSectionState[section] = false;
    }

    for (int i = 0; i < SECTIONS_COUNT; i++) {
        if (m_anSectionState[i]) {
            CVector& speed = m_sectionMoveSpeed[i];
            speed.z -= CTimer::ms_fTimeStep / 250.0f;

            CVector& point = m_sectionPoint[i];
            point += speed * CTimer::ms_fTimeStep;

            // Originally done in a seprate loop, but we do it here
            gFireManager.ExtinguishPointWithWater(point, 2.0f, 0.5f);
        }
    }

    if ((uint8_t)(CTimer::m_FrameCounter + a1) % 4 == 0) { // Notice cast to byte
        PushPeds();
    }

    if (!HasActiveSection()) {
        m_nId = 0;
    }
}

// 0x728C20
void CWaterCannon::Update_NewInput(CVector* start, CVector* end) {
    m_sectionPoint[m_nSectionsCount]     = *start;
    m_sectionMoveSpeed[m_nSectionsCount] = *end;
    m_anSectionState[m_nSectionsCount]   = 1;
}

// 0x7295E0
void CWaterCannon::PushPeds() {
    plugin::CallMethod<0x7295E0, CWaterCannon*>(this);
}

// 0x728DA0
void CWaterCannon::Render() {
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,        (void*)nullptr);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    (void*)rwALPHATESTFUNCTIONGREATER);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void*)FALSE);

    size_t prevIdx = m_nSectionsCount % SECTIONS_COUNT;
    size_t currIdx = prevIdx == 0 ? SECTIONS_COUNT - 1 : prevIdx - 1;

    bool hasCalculatedMatrix = false;

    CVector right{}, fwd{}, up{};

    m_audio.ClearSplashInfo();

    for (int i = 0; i < SECTIONS_COUNT; i++) {
        if (IsSectionActive(prevIdx) && IsSectionActive(currIdx)) {
            CVector prevPosn = GetSectionPosn(prevIdx);
            CVector currPosn = GetSectionPosn(currIdx);

            const CVector currToPrevDir = prevPosn - currPosn;
            if (currToPrevDir.SquaredMagnitude() < 25.0f) {
                if (!hasCalculatedMatrix) {
                    hasCalculatedMatrix = true;

                    up = Normalized(CrossProduct(prevPosn - currPosn, TheCamera.GetForward())) / 20.0f;
                    right = Normalized(CVector::Random(0.0f, 1.0f)) / 20.0f;
                    fwd = Normalized(CVector::Random(0.0f, 1.0f)) / 20.0f;
                }

                const float dist = (float)(i * i) / (float)SECTIONS_COUNT + 3.0f;

                RxObjSpace3DVertex vertices[12];

                // Set alpha depending on current `i`. The higher, the lower the alpha.
                const float progress = (float)i / (float)SECTIONS_COUNT;
                const auto  alpha = (RwUInt8)(64.0f * (1.0f - progress));
                RwRGBA color{ 0xC8, 0xC8, 0xFF, alpha };
                for (auto& v : vertices) {
                    RxObjSpace3DVertexSetPreLitColor(&v, &color);
                }

                const CVector thisUp = up * dist, thisRight = right * dist, thisFwd = fwd * dist;
                const CVector pos[std::size(vertices)] = {
                    currPosn - thisUp,
                    currPosn + thisUp,
                    prevPosn - thisUp,
                    prevPosn + thisUp,

                    currPosn - thisRight,
                    currPosn + thisRight,
                    prevPosn - thisRight,
                    prevPosn + thisRight,

                    currPosn - thisFwd,
                    currPosn + thisFwd,
                    prevPosn - thisFwd,
                    prevPosn + thisFwd,
                };
                for (int v = 0; v < std::size(vertices); v++) {
                    RxObjSpace3DVertexSetPos(&vertices[v], &pos[v]);
                }

                CColPoint colPoint{};
                CEntity* hitEntity{};
                const bool hasSectionHit = CWorld::ProcessLineOfSight(prevPosn, currPosn, colPoint, hitEntity, true, true, false, false, false, false, false, false);
                if (hasSectionHit) {
                    FxPrtMult_c prtinfo{ 1.0, 1.0, 1.0, 0.15000001, 0.75, 1.0, 0.2 };
                    CVector direction = colPoint.m_vecNormal * 3.0f * CVector::Random(0.2f, 1.8f);

                    for (int n = 0; n < 2; n++) {
                        const float unk = n / (CTimer::ms_fTimeStep / 50 * 1000.0f); // TODO: This 50 divider seems very common..

                        g_fx.m_pPrtWatersplash->AddParticle(&colPoint.m_vecPoint, &direction, unk, &prtinfo, -1.0f, 1.2f, 0.6f, 0);

                        CVector retadedSignature = direction * 0.6f;
                        g_fx.m_pPrtWatersplash->AddParticle(&colPoint.m_vecPoint, &retadedSignature, unk, &prtinfo, -1.0f, 1.2f, 0.6f, 0);
                    }

                    m_audio.SetSplashInfo(colPoint.m_vecPoint, direction.Magnitude());

                    break;
                }


                if (RwIm3DTransform(vertices, std::size(vertices), nullptr, rwIM3D_VERTEXRGBA))
                {
                    RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, m_auRenderIndices, std::size(m_auRenderIndices));
                    RwIm3DEnd();
                }

                if (hasSectionHit)
                    break;
            }
        }
        currIdx = prevIdx;
        if (prevIdx == 0)
            prevIdx = SECTIONS_COUNT - 1;
        else
            prevIdx--;
    }

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         (void*)FALSE);
}

// NOTSA
bool CWaterCannon::IsSectionActive(size_t idx) {
    return m_anSectionState[idx];
}

CVector& CWaterCannon::GetSectionPosn(size_t idx) {
    return m_sectionPoint[idx];
}
