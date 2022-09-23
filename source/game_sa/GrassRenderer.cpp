#include "StdInc.h"

#include "GrassRenderer.h"
#include "PPTriPlantBuffer.h"

float& CGrassRenderer::m_windBending = *(float*)0xC02DB8;
float& CGrassRenderer::m_closeDist = *(float*)0xC02DBC;
CVector& CGrassRenderer::m_vecCameraPos = *(CVector*)0xC02DDC;
float& CGrassRenderer::m_farDist = *(float*)0x8D132C; // 10.0f

CPPTriPlantBuffer& gTriPlantBuf = *(CPPTriPlantBuffer*)0xC02DE8;
uint16& g_GrassCurrentScanCode = *(uint16*)0x8D1330; // -1

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
void CGrassRenderer::AddTriPlant(PPTriPlant* srcPlant, uint32 plantModelSet) {
    gTriPlantBuf.ChangeCurrentPlantModelsSet(plantModelSet);

    if (gTriPlantBuf.m_CurrentIndex + 1 > MAX_PLANTS)
        gTriPlantBuf.Flush();

    gTriPlantBuf.CopyToActive(srcPlant);
    gTriPlantBuf.IncreaseBufferIndex(plantModelSet, 1);
}

// 0x5DAD00
void CGrassRenderer::DrawTriPlants(PPTriPlant* triPlants, int32 numTriPlants, RpAtomic** plantModelsTab, RwMatrix* ltm) {
    // return plugin::Call<0x5DAD00, PPTriPlant*, int32, RpAtomic**>(plant, count, atomics);
    { // debug
        CFont::InitPerFrame();
        char buf[32]{};
        sprintf(buf, "hook %d", numTriPlants);
        CFont::PrintString(100, 200, buf);
    }

    const auto farDist = [] { // OG: located in loop
        switch (g_fx.GetFxQuality()) {
        case FX_QUALITY_LOW:
        case FX_QUALITY_MEDIUM:
        default:
            return m_farDist / 2.0f;
        case FX_QUALITY_HIGH:
        case FX_QUALITY_VERY_HIGH:
            return m_farDist;
        }
    }();
    for (const auto& plant : std::span{triPlants, (size_t)numTriPlants}) {
        const auto nearDist = DistanceBetweenPoints(m_vecCameraPos, plant.Center);
        if (nearDist > farDist + 20.0f) {
            continue;
        }

        const auto atomic = plantModelsTab[plant.model_id];
        auto frame = RpAtomicGetFrame(atomic);
        srand(plant.seed);

        RwRGBA newColorIntensity{};
        if (nearDist >= farDist) {
            const auto alpha = std::floor((farDist + 20.0f - nearDist) * (float)plant.color.a / 20.0f);
            newColorIntensity.alpha = (uint8)std::clamp(alpha, 0.0f, 255.0f);
        } else {
            newColorIntensity.alpha = plant.color.a;
        }

        // 0x5DAE61
        auto mult = std::min(float(plant.intensity), 255.0f);
        newColorIntensity.red   = uint16(mult * (float)plant.color.r) / 256;
        newColorIntensity.green = uint16(mult * (float)plant.color.g) / 256;
        newColorIntensity.blue  = uint16(mult * (float)plant.color.b) / 256;

        // 0x5DAC40
        RenderGrassTexture = plant.texture;
        RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), CPPTriPlantBuffer::SetGrassMaterialCB, &newColorIntensity);

        for (auto j = 0; j < plant.num_plants; j++) {
            CVector posn;
            sub_5DAB00(
                posn,
                &plant.V1,
                &plant.V2,
                &plant.V3,
                CGeneral::GetRandomNumberInRange(0.0f, 1.0f),
                CGeneral::GetRandomNumberInRange(0.0f, 1.0f)
            );

            if (DistanceBetweenPoints(m_vecCameraPos, posn) < m_closeDist - 2.0f) {
                CGeneral::GetRandomNumber();
                CGeneral::GetRandomNumber();
                CGeneral::GetRandomNumber();
                continue;
            }

            RwFrameTranslate(frame, &posn, rwCOMBINEREPLACE);

            const auto xy = (float)rand() * RAND_MAX_FLOAT_RECIPROCAL * plant.scale_var_xy + plant.scale.x;
            frame->modelling.right.x *= xy;
            frame->modelling.up.y *= xy;

            const auto xy1 = ((float)rand() * RAND_MAX_FLOAT_RECIPROCAL * plant.wind_bend_var + 1.0f) * (m_windBending * plant.wind_bend_scale);
            frame->modelling.at.x = xy1;
            frame->modelling.at.y = xy1;
            frame->modelling.at.z = ((float)rand() * RAND_MAX_FLOAT_RECIPROCAL * plant.scale_var_z + plant.scale.y) * frame->modelling.at.z;

            RwMatrixUpdate(&frame->modelling);
            atomic->renderCallBack(atomic);
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

// Chooses a point inside the triangle (v1,v2,v3) with specific step values
void CGrassRenderer::sub_5DAB00(CVector& outPosn, const CVector& v1, const CVector& v2, const CVector& v3, float stepA, float stepB) {
    if (stepA + stepB > 1.0f) {
        stepA = 1.0f - stepA;
        stepB = 1.0f - stepB;
    }
    outPosn = (1.0f - stepA - stepB) * v1 + stepA * v2 + stepB * v3;
}
