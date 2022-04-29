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
    RH_ScopedClass(CGrassRenderer);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Initialise, 0x5DD6B0);
    RH_ScopedInstall(Shutdown, 0x5DABA0);
    RH_ScopedInstall(AddTriPlant, 0x5DB1D0);
    RH_ScopedInstall(DrawTriPlants, 0x5DAD00);
    RH_ScopedInstall(FlushTriPlantBuffer, 0x5DB250);
    RH_ScopedInstall(GetPlantModelsTab, 0x5DACE0);
    RH_ScopedInstall(SetPlantModelsTab, 0x5DACC0);
    RH_ScopedInstall(SetCloseFarAlphaDist, 0x5DABE0);
    RH_ScopedInstall(SetCurrentScanCode, 0x5DABB0);
    RH_ScopedInstall(SetGlobalCameraPos, 0x5DABC0);
    RH_ScopedInstall(SetGlobalWindBending, 0x5DAC00);

    RH_ScopedInstall(sub_5DAB00, 0x5DAB00);
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
void CGrassRenderer::DrawTriPlants(PPTriPlant* plants, int32 count, RpAtomic** atomics) {
    // return plugin::Call<0x5DAD00, PPTriPlant*, int32, RpAtomic**>(plant, count, atomics);
    CFont::InitPerFrame();
    char buf[32]{};
    sprintf(buf, "hook %d", count);
    CFont::PrintString(100, 200, buf);

    const auto GetFarDist = []() -> float {
        switch (g_fx.GetFxQuality()) {
        case FXQUALITY_LOW:
        case FXQUALITY_MEDIUM:
            return m_farDist / 2.0f;
        case FXQUALITY_HIGH:
        case FXQUALITY_VERY_HIGH:
            return m_farDist;
        }
    };

    for (auto i = 0; i < count; i++) {
        const auto& plant = plants[i];

        const auto farDist = GetFarDist();
        const auto nearDist = (plant.end.m_vecMax - m_vecCameraPos).Magnitude();
        if (nearDist > farDist + 20.0f) {
            continue;
        }

        const auto atomic = atomics[plant.type];
        auto frame = RpAtomicGetFrame(atomic);
        srand(plant.randomSeed);

        RwRGBA newColorIntensity{};
        if (nearDist >= farDist) {
            const auto alpha = std::floor((farDist + 20.0f - nearDist) * plant.color.a / 20.0f);
            newColorIntensity.alpha = std::clamp(alpha, 0.0f, 255.0f);
        } else {
            newColorIntensity.alpha = plant.color.a;
        }

        // 0x5DAE61
        auto mult = std::min(float(plant.m_nColorIntensity), 255.0f);
        newColorIntensity.red   = uint16(mult * plant.color.r) / 256;
        newColorIntensity.green = uint16(mult * plant.color.g) / 256;
        newColorIntensity.blue  = uint16(mult * plant.color.b) / 256;

        // 0x5DAC40
        RenderGrassTexture = plant.m_Texture;
        RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), CPPTriPlantBuffer::SetGrassMaterialCB, &newColorIntensity);

        for (auto j = 0; j < plant.field_32; j++) {
            CVector posn;
            sub_5DAB00(
                posn,
                &plant.start.m_vecMin,
                &plant.start.m_vecMax,
                &plant.end.m_vecMin,
                CGeneral::GetRandomNumberInRange(0.0f, 1.0f),
                CGeneral::GetRandomNumberInRange(0.0f, 1.0f)
            );

            if (m_closeDist - 2.0f <= (posn - m_vecCameraPos).Magnitude()) {
                RwFrameTranslate(frame, &posn, rwCOMBINEREPLACE);

                const auto xy = (float)rand() * RAND_MAX_FLOAT_RECIPROCAL * plant.field_4C + plant.field_34;
                frame->modelling.right.x *= xy;
                frame->modelling.up.y *= xy;
                frame->modelling.at.z = ((float)rand() * RAND_MAX_FLOAT_RECIPROCAL * plant.field_50 + plant.field_38) * frame->modelling.at.z;
                const auto xy1 = ((float)rand() * RAND_MAX_FLOAT_RECIPROCAL * plant.field_58 + 1.0f) * (m_windBending * plant.m_fWindBendingModifier);
                frame->modelling.at.x = xy1;
                frame->modelling.at.y = xy1;

                RwMatrixUpdate(&frame->modelling);
                atomic->renderCallBack(atomic);
            } else {
                CGeneral::GetRandomNumber();
                CGeneral::GetRandomNumber();
                CGeneral::GetRandomNumber();
            }
        }
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

void CGrassRenderer::sub_5DAB00(CVector& outPosn, const CVector& startMin, const CVector& startMax, const CVector& endMin, float randA, float randB) {
    float f1 = randA;
    float f2 = randB;
    if (randA + randB > 1.0f) {
        f1 = 1.0f - f1;
        f2 = 1.0f - f2;
    }
    float f3 = 1.0f - f1 - f2;

    outPosn = f3 * startMin + f1 * startMax + f2 * endMin;
}
