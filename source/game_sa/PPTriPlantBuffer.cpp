#include "StdInc.h"

#include "PPTriPlantBuffer.h"
#include "GrassRenderer.h"

RwTexture*& RenderGrassTexture = *(RwTexture**)0xC02DC0;

void CPPTriPlantBuffer::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CPPTriPlantBuffer", "Flush", 0x5DB0C0, &CPPTriPlantBuffer::Flush);
    Install("CPPTriPlantBuffer", "GetPPTriPlantPtr", 0x5DB140, &CPPTriPlantBuffer::GetPPTriPlantPtr);
    Install("CPPTriPlantBuffer", "ChangeCurrentPlantModelsSet", 0x5DB170, &CPPTriPlantBuffer::ChangeCurrentPlantModelsSet);
    Install("CPPTriPlantBuffer", "IncreaseBufferIndex", 0x5DB1A0, &CPPTriPlantBuffer::IncreaseBufferIndex);
    Install("CPPTriPlantBuffer", "GetPlantModelsTab", 0x5DACA0, &CPPTriPlantBuffer::GetPlantModelsTab);
    Install("CPPTriPlantBuffer", "SetPlantModelsTab", 0x5DAC80, &CPPTriPlantBuffer::SetPlantModelsTab);

    Install("CPPTriPlantBuffer", "SetGrassMaterialCB", 0x5DAC10, &CPPTriPlantBuffer::SetGrassMaterialCB);
}

// 0x5DB090
CPPTriPlantBuffer::CPPTriPlantBuffer() {
    m_nNumActive = 0;
    m_nType = 0;
    std::fill(std::begin(m_aAtomics), std::end(m_aAtomics), nullptr);
}

// 0x5DB0C0
void CPPTriPlantBuffer::Flush() {
    if (m_nNumActive > 0) {
        RpAtomic** atomics;
        switch (m_nType) {
        case 0:
            atomics = &m_aAtomics[0];
            break;
        case 1:
            atomics = &m_aAtomics[1];
            break;
        case 2:
            atomics = &m_aAtomics[2];
            break;
        case 3:
            atomics = &m_aAtomics[3];
            break;
        default:
            atomics = nullptr;
            break;
        }
        int32 random = rand();
        CGrassRenderer::DrawTriPlants(m_aPlants, m_nNumActive, atomics);
        m_nNumActive = 0;
        srand(random);
    }
}

// 0x5DB140
PPTriPlant* CPPTriPlantBuffer::GetPPTriPlantPtr(int32 nIncrease) {
    if (m_nNumActive + nIncrease > MAX_PLANTS)
        Flush();

    return &m_aPlants[m_nNumActive];
}

// 0x5DB170
void CPPTriPlantBuffer::ChangeCurrentPlantModelsSet(int32 type) {
    if (m_nType != type) {
        Flush();
        m_nType = type;
    }
}

// 0x5DB1A0
void CPPTriPlantBuffer::IncreaseBufferIndex(int32 type, int32 nIncrease) {
    if (m_nType == type) {
        m_nNumActive += nIncrease;
        if (m_nNumActive >= MAX_PLANTS)
            Flush();
    }
}

// 0x5DACA0
void* CPPTriPlantBuffer::GetPlantModelsTab(uint32 type) {
    if (type < 4)
        return m_aAtomics[type];
    else
        return nullptr;
}

// 0x5DAC80
void CPPTriPlantBuffer::SetPlantModelsTab(uint32 type, RpAtomic** atomics) {
    if (type < 4)
        m_aAtomics[type] = *atomics;
}

// 'data' is a pointer to RwRGBA
// 0x5DAC10
RpMaterial* CPPTriPlantBuffer::SetGrassMaterialCB(RpMaterial* material, void* data) {
    auto color = *reinterpret_cast<RwRGBA*>(data);
    RpMaterialSetColor(material, &color);
    if (RpMaterialGetTexture(material) != RenderGrassTexture) {
        RpMaterialSetTexture(material, RenderGrassTexture);
    }
    return material;
}
