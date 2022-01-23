#include "StdInc.h"

#include "GrassRenderer.h"
#include "PPTriPlantBuffer.h"

float& CGrassRenderer::m_windBending = *(float*)0xC02DB8;
float& CGrassRenderer::m_closeDist = *(float*)0xC02DBC;
CVector& CGrassRenderer::m_vecCameraPos = *(CVector*)0xC02DDC;
float& CGrassRenderer::m_farDist = *(float*)0x8D132C; // 10.0f

CPPTriPlantBuffer& gTriPlantBuf = *(CPPTriPlantBuffer*)0xC02DE8;
uint16& g_GrassCurrentScanCode = *(uint16*)0x8D1330; // 65535 or -1

void CGrassRenderer::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CGrassRenderer", "Initialise", 0x5DD6B0, &CGrassRenderer::Initialise);
    Install("CGrassRenderer", "Shutdown", 0x5DABA0, &CGrassRenderer::Shutdown);
    Install("CGrassRenderer", "AddTriPlant", 0x5DB1D0, &CGrassRenderer::AddTriPlant);
    // Install("CGrassRenderer", "DrawTriPlants", 0x5DAD00, &CGrassRenderer::DrawTriPlants);
    Install("CGrassRenderer", "FlushTriPlantBuffer", 0x5DB250, &CGrassRenderer::FlushTriPlantBuffer);
    Install("CGrassRenderer", "GetPlantModelsTab", 0x5DACE0, &CGrassRenderer::GetPlantModelsTab);
    Install("CGrassRenderer", "SetPlantModelsTab", 0x5DACC0, &CGrassRenderer::SetPlantModelsTab);
    Install("CGrassRenderer", "SetCloseFarAlphaDist", 0x5DABE0, &CGrassRenderer::SetCloseFarAlphaDist);
    Install("CGrassRenderer", "SetCurrentScanCode", 0x5DABB0, &CGrassRenderer::SetCurrentScanCode);
    Install("CGrassRenderer", "SetGlobalCameraPos", 0x5DABC0, &CGrassRenderer::SetGlobalCameraPos);
    Install("CGrassRenderer", "SetGlobalWindBending", 0x5DAC00, &CGrassRenderer::SetGlobalWindBending);

    Install("CGrassRenderer", "sub_5DAB00", 0x5DAB00, &CGrassRenderer::sub_5DAB00);
}

// 0x5DD6B0
bool CGrassRenderer::Initialise() {
    return true;
}

// 0x5DABA0
void CGrassRenderer::Shutdown() {
    // NOP
}

// 0x5DB1D0
void CGrassRenderer::AddTriPlant(PPTriPlant* plant, uint32 type) {
    gTriPlantBuf.ChangeCurrentPlantModelsSet(type);

    if (gTriPlantBuf.m_nNumActive + 1 > MAX_PLANTS)
        gTriPlantBuf.Flush();

    gTriPlantBuf.CopyToActive(plant);
    gTriPlantBuf.IncreaseBufferIndex(type, 1);
}

// 0x5DAD00
void CGrassRenderer::DrawTriPlants(PPTriPlant* plant, int32 count, RpAtomic** atomics) {
    return plugin::Call<0x5DAD00, PPTriPlant*, int32, RpAtomic**>(plant, count, atomics);

    for (auto i = 0; i < count; i++) {
        const auto magnitude = CVector({plant->end.m_vecMax - m_vecCameraPos}).Magnitude();
        float distance = g_fx.GetFxQuality() < FXQUALITY_HIGH ? m_farDist / 2 : m_farDist;

        RwRGBA colorIntensity;
        float colorIntensityVal = distance + 20.0f;
        memcpy(&colorIntensity, &colorIntensityVal, sizeof(float));

        RwRGBA newColorIntensity;

        if (magnitude >= distance) {
            newColorIntensity.alpha = std::clamp(floor((plant->color.a - magnitude) * plant->color.a * 0.05f), 0.0f, 255.0f);
        } else {
            newColorIntensity.alpha = plant->color.a;
        }

        // colorIntensity = plant->colorIntensity;
        auto mult = std::min<uint8>(plant->colorIntensity, 255.0f);

        newColorIntensity.red   = (mult * plant->color.r) >> 8;
        newColorIntensity.green = (mult * plant->color.g) >> 8;
        newColorIntensity.blue  = (mult * plant->color.b) >> 8;

        const auto atomic = atomics[plant->type];
        auto frame = RpAtomicGetFrame(atomic);
        srand(plant->randomSeed);

        { // 0x5DAC40
        RenderGrassTexture = plant->texture;
        RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), CPPTriPlantBuffer::SetGrassMaterialCB, &newColorIntensity);
        }

        if (plant->field_32) {
            auto f32 = plant->field_32;
            do {
                CVector posn;
                sub_5DAB00(
                    posn,
                    &plant->start.m_vecMin,
                    &plant->start.m_vecMax,
                    &plant->end.m_vecMin,
                    (float)rand() * RAND_MAX_FLOAT_RECIPROCAL,
                    (float)rand() * RAND_MAX_FLOAT_RECIPROCAL
                );

                if (m_closeDist - 2.0f <= CVector({posn - m_vecCameraPos}).Magnitude()) {
                    RwFrameTranslate(frame, &posn, rwCOMBINEREPLACE);

                    const auto xy = (float)rand() * RAND_MAX_FLOAT_RECIPROCAL * plant->field_4C + plant->field_34;
                    frame->modelling.right.x *= xy;
                    frame->modelling.up.y *= xy;
                    frame->modelling.at.z = ((float)rand() * RAND_MAX_FLOAT_RECIPROCAL * plant->field_50 + plant->field_38) * frame->modelling.at.z;
                    const auto xy1 = ((float)rand() * RAND_MAX_FLOAT_RECIPROCAL * plant->field_58 + 1.0) * (m_windBending * plant->m_fWindBendingModifier);
                    frame->modelling.at.x = xy1;
                    frame->modelling.at.y = xy1;

                    RwMatrixUpdate(&frame->modelling);
                    atomic->renderCallBack(atomic);
                } else {
                    rand();
                    rand();
                    rand();
                }
                f32 -= 1;
            } while (f32);
        }

        plant++;
    }
}

// 0x5DB250
void CGrassRenderer::FlushTriPlantBuffer() {
    gTriPlantBuf.Flush();
}

// 0x5DACE0
void* CGrassRenderer::GetPlantModelsTab(uint32 type) {
    return gTriPlantBuf.GetPlantModelsTab(type);
}

// 0x5DACC0
void CGrassRenderer::SetPlantModelsTab(uint32 type, RpAtomic** atomics) {
    gTriPlantBuf.SetPlantModelsTab(type, atomics);
}

// 0x5DABE0
void CGrassRenderer::SetCloseFarAlphaDist(float fCloseDist, float fFarDist) {
    m_closeDist = fCloseDist;
    m_farDist   = fFarDist;
}

// 0x5DABB0
void CGrassRenderer::SetCurrentScanCode(uint16 scanCode) {
    g_GrassCurrentScanCode = scanCode;
}

// 0x5DABC0
void CGrassRenderer::SetGlobalCameraPos(const CVector& cameraPosn) {
    m_vecCameraPos = cameraPosn;
}

// 0x5DAC00
void CGrassRenderer::SetGlobalWindBending(float bending) {
    m_windBending = bending;
}

void CGrassRenderer::sub_5DAB00(CVector& outPosn, CVector* startMin, CVector* startMax, CVector* endMin, float randA, float randB) {
    float f1 = randA;
    float f2 = randB;
    if (randA + randB > 1.0f) {
        f1 = 1.0f - f1;
        f2 = 1.0f - f2;
    }
    float f3 = 1.0f - f1 - f2;

    outPosn.x = f3 * startMin->x + f1 * startMax->x + f2 * endMin->x;
    outPosn.y = f3 * startMin->y + f1 * startMax->y + f2 * endMin->y;
    outPosn.z = f3 * startMin->z + f1 * startMax->z + f2 * endMin->z;
}
