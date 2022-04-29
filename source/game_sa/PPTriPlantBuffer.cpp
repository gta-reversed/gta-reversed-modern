#include "StdInc.h"

#include "PPTriPlantBuffer.h"
#include "GrassRenderer.h"

RwTexture*& RenderGrassTexture = *(RwTexture**)0xC02DC0;

void CPPTriPlantBuffer::InjectHooks() {
    RH_ScopedClass(CPPTriPlantBuffer);
    RH_ScopedCategoryGlobal();

    return;
    RH_ScopedInstall(Flush, 0x5DB0C0);
    RH_ScopedInstall(GetPPTriPlantPtr, 0x5DB140);
    RH_ScopedInstall(ChangeCurrentPlantModelsSet, 0x5DB170);
    RH_ScopedInstall(IncreaseBufferIndex, 0x5DB1A0);
    RH_ScopedInstall(GetPlantModelsTab, 0x5DACA0);
    RH_ScopedInstall(SetPlantModelsTab, 0x5DAC80);
    RH_ScopedInstall(SetGrassMaterialCB, 0x5DAC10);
}

// 0x5DB090
CPPTriPlantBuffer::CPPTriPlantBuffer() {
    m_nNumActive = 0;
    m_nType = 0;
    std::ranges::fill(m_aAtomics, nullptr);
}

// 0x5DB0C0
void CPPTriPlantBuffer::Flush() {
    if (m_nNumActive <= 0)
        return;

    auto atomics = [this] {
        switch (m_nType) {
        case 0:
            return m_aAtomics[0];
        case 1:
            return m_aAtomics[1];
        case 2:
            return m_aAtomics[2];
        case 3:
            return m_aAtomics[3];
        default:
            return (RpAtomic**)nullptr; // todo: ?
        }
    }();

    int32 random = CGeneral::GetRandomNumber();
    CGrassRenderer::DrawTriPlants(m_aPlants, m_nNumActive, atomics);
    m_nNumActive = 0;
    srand(random);
}

// 0x5DB140
PPTriPlant* CPPTriPlantBuffer::GetPPTriPlantPtr(int32 nIncrease) {
    if (m_nNumActive + nIncrease > MAX_PLANTS)
        Flush();

    return &m_aPlants[m_nNumActive];
}

// 0x5DB170
void CPPTriPlantBuffer::ChangeCurrentPlantModelsSet(int32 type) {
    if (m_nType == type)
        return;

    Flush();
    m_nType = type;
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
    if (type < std::size(m_aAtomics))
        return m_aAtomics[type];
    else
        return nullptr;
}

// 0x5DAC80
void CPPTriPlantBuffer::SetPlantModelsTab(uint32 type, RpAtomic** atomics) {
    if (type < std::size(m_aAtomics))
        m_aAtomics[type] = atomics;
}

// 'data' is a pointer to RwRGBA
// 0x5DAC10
RpMaterial* CPPTriPlantBuffer::SetGrassMaterialCB(RpMaterial* material, void* data) {
    const auto color = *reinterpret_cast<RwRGBA*>(data);
    RpMaterialSetColor(material, &color);
    if (RpMaterialGetTexture(material) != RenderGrassTexture) {
        RpMaterialSetTexture(material, RenderGrassTexture);
    }
    return material;
}
