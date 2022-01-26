#include "StdInc.h"

#include "WaterCannon.h"
#include "FireManager.h"
#include <ranges>

void CWaterCannon::InjectHooks() {
    RH_ScopedInstall(Constructor, 0x728B10);
    RH_ScopedInstall(Destructor, 0x728B30);
    RH_ScopedInstall(Init, 0x728B40);
    RH_ScopedInstall(Update_OncePerFrame, 0x72A280);
    RH_ScopedInstall(Update_NewInput, 0x728C20);
    RH_ScopedInstall(PushPeds, 0x7295E0);
    RH_ScopedInstall(Render, 0x728DA0);
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
    m_nCreationTime = CTimer::GetTimeInMS();
    std::ranges::fill(m_anSectionState, false);
    m_auRenderIndices = { 0, 1, 2, 1, 3, 2, 4, 5, 6, 5, 7, 6, 8, 9, 10, 9, 11, 10 };
    m_audio.Initialise(this);
}

bool CWaterCannon::HasActiveSection() const {
    const auto end = std::end(m_anSectionState);
    return std::find(std::begin(m_anSectionState), end, true) != end;
}

// 0x72A280
void CWaterCannon::Update_OncePerFrame(int16 a1) {
    if (CTimer::GetTimeInMS() > m_nCreationTime + 150) {
        const auto section = (m_nSectionsCount + 1) % SECTIONS_COUNT;
        m_nSectionsCount = section;
        m_anSectionState[section] = false;
    }

    for (int i = 0; i < SECTIONS_COUNT; i++) {
        if (m_anSectionState[i]) {
            CVector& speed = m_sectionMoveSpeed[i];
            speed.z -= CTimer::GetTimeStep() / 250.0f;

            CVector& point = m_sectionPoint[i];
            point += speed * CTimer::GetTimeStep();

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

// NOTSA
CBoundingBox CWaterCannon::GetSectionsBoundingBox() const {
    // Ik, ik junk code, can't do better

    // R* originally used 10000 here, but thats bug prone (if map size gets increased)
    CVector min{ FLT_MAX, FLT_MAX, FLT_MAX }, max{ FLT_MIN, FLT_MIN, FLT_MIN };  
    for (size_t i = 0; i < SECTIONS_COUNT; i++) {
        if (!IsSectionActive(i))
            continue;

        const auto Do = [posn = GetSectionPosn(i)](CVector& out, auto pr) {
            out = CVector{
                pr(out.x, posn.x),
                pr(out.y, posn.y),
                pr(out.z, posn.z)
            };
        };
        Do(min, [](float a, float b) { return std::min(a, b); });
        Do(max, [](float a, float b) { return std::max(a, b); });
    }
    return { min, max };
}

// 0x7295E0
void CWaterCannon::PushPeds() {
    const auto sectionsBounding = GetSectionsBoundingBox();
    for (int pedIdx = 0; pedIdx < CPools::ms_pPedPool->m_nSize; pedIdx++) {
        CPed* ped = CPools::ms_pPedPool->GetAt(pedIdx);
        if (!ped)
            continue;

        CVector pedPosn = ped->GetPosition();
        if (!sectionsBounding.IsPointWithin(pedPosn))
            continue;

        if (ped->physicalFlags.bMakeMassTwiceAsBig)
            continue;

        for (int i = 0; i < SECTIONS_COUNT; i++) {
            const CVector secPosn = GetSectionPosn(i);

            if ((pedPosn - secPosn).SquaredMagnitude() >= 5.0f)
                continue;

            const CVector secMoveSpeed = GetSectionMoveSpeed(i);

            {
                CEventHitByWaterCannon event(secPosn, secMoveSpeed);
                ped->GetEventGroup().Add(&event, false);
            }

            ped->bWasStanding = false;
            ped->bIsStanding = false;

            ped->ApplyMoveForce({ 0.0f, 0.0f, CTimer::GetTimeStep() });

            {
                // TODO: Refactor... Ugly code
                const CVector2D applyableMoveSpeed = (secMoveSpeed / 10.0f - ped->m_vecMoveSpeed) / 10.0f;

                // Check if directions are the same (eg, + / +, - / -),
                // differring sign bits will always yield a negativ result
                /// (unless 0, but that is handled by > (instead of >=))
                if (secMoveSpeed.x * applyableMoveSpeed.x > 0.0f) 
                    ped->m_vecMoveSpeed.x = applyableMoveSpeed.x + secMoveSpeed.x;

                if (secMoveSpeed.y * applyableMoveSpeed.y > 0.0f)
                    ped->m_vecMoveSpeed.y = applyableMoveSpeed.y + secMoveSpeed.y;
            }

            FxPrtMult_c prtInfo{ 1.0f, 1.0f, 1.0f, 0.6f, 0.75f, 0.0f, 0.2f };

            CVector particleVelocity = ped->m_vecMoveSpeed * 0.3f;
            g_fx.m_pPrtSmokeII3expand->AddParticle(&pedPosn, &particleVelocity, 0.0f, &prtInfo, -1.0f, 1.2f, 0.6f, false);

            CVector particleVelocity2 = ped->m_vecMoveSpeed * -0.3f;
            particleVelocity2.z += 0.5f;
            g_fx.m_pPrtSmokeII3expand->AddParticle(&pedPosn, &particleVelocity2, 0.0f, &prtInfo, -1.0f, 1.2f, 0.6f, false);

            break;
        }
    }
}

// 0x728DA0
void CWaterCannon::Render() {
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,        RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(0));

    size_t prevIdx = m_nSectionsCount % SECTIONS_COUNT;
    size_t currIdx = prevIdx == 0 ? SECTIONS_COUNT - 1 : prevIdx - 1;

    bool hasCalculatedMatrix = false;

    CVector right{}, fwd{}, up{};

    m_audio.ClearSplashInfo();

    for (int i = 0; i < SECTIONS_COUNT; i++) {
        if (IsSectionActive(prevIdx) && IsSectionActive(currIdx)) {
            const CVector prevPosn = GetSectionPosn(prevIdx);
            const CVector currPosn = GetSectionPosn(currIdx);

            const CVector currToPrevDir = prevPosn - currPosn;
            if (currToPrevDir.SquaredMagnitude() < 25.0f) {
                if (!hasCalculatedMatrix) {
                    hasCalculatedMatrix = true;

                    up = Normalized(CrossProduct(prevPosn - currPosn, TheCamera.GetForward())) / 20.0f;
                    right = Normalized(CVector::Random(0.0f, 1.0f)) / 20.0f;
                    fwd = Normalized(CVector::Random(0.0f, 1.0f)) / 20.0f;
                }

                const float size = (float)(i * i) / (float)SECTIONS_COUNT + 3.0f;

                RxObjSpace3DVertex vertices[12];

                // Set alpha depending on current `i`. The higher, the lower the alpha.
                const float progress = (float)i / (float)SECTIONS_COUNT;
                const auto  alpha = (RwUInt8)(64.0f * (1.0f - progress));
                RwRGBA color{ 200, 200, 255, alpha };
                for (auto& v : vertices) {
                    RxObjSpace3DVertexSetPreLitColor(&v, &color);
                }

                const CVector thisUp = up * size, thisRight = right * size, thisFwd = fwd * size;
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
                for (size_t v = 0; v < std::size(vertices); v++) {
                    RxObjSpace3DVertexSetPos(&vertices[v], &pos[v]);
                }

                CColPoint colPoint{};
                CEntity* hitEntity{};
                const bool hasSectionHit = CWorld::ProcessLineOfSight(prevPosn, currPosn, colPoint, hitEntity, true, true, false, false, false, false, false, false);
                if (hasSectionHit) {
                    FxPrtMult_c prtinfo{ 1.0f, 1.0f, 1.0f, 0.15f, 0.75f, 1.0f, 0.2f };
                    CVector direction = colPoint.m_vecNormal * 3.0f * CVector::Random(0.2f, 1.8f);

                    for (int n = 0; n < 2; n++) {
                        const auto unk = (float)(n / CTimer::GetTimeStepInMS());

                        g_fx.m_pPrtWatersplash->AddParticle(&colPoint.m_vecPoint, &direction, unk, &prtinfo, -1.0f, 1.2f, 0.6f, 0);

                        CVector retadedSignature = direction * 0.6f;
                        g_fx.m_pPrtWatersplash->AddParticle(&colPoint.m_vecPoint, &retadedSignature, unk, &prtinfo, -1.0f, 1.2f, 0.6f, 0);
                    }

                    m_audio.SetSplashInfo(colPoint.m_vecPoint, direction.Magnitude());

                    break;
                }


                if (RwIm3DTransform(vertices, std::size(vertices), nullptr, rwIM3D_VERTEXRGBA))
                {
                    RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, m_auRenderIndices.data(), m_auRenderIndices.size());
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

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(FALSE));
}

// NOTSA
bool CWaterCannon::IsSectionActive(size_t idx) const {
    return m_anSectionState[idx];
}

CVector CWaterCannon::GetSectionPosn(size_t idx) const {
    return m_sectionPoint[idx];
}

CVector CWaterCannon::GetSectionMoveSpeed(size_t idx) const {
    return m_sectionMoveSpeed[idx];
}
