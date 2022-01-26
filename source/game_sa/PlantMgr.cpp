#include "StdInc.h"

#include "PlantMgr.h"

RwTexture* (&CPlantMgr::PC_PlantTextureTab0)[4] = *(RwTexture * (*)[4])0xC039A0;
RwTexture* (&CPlantMgr::PC_PlantTextureTab1)[4] = *(RwTexture * (*)[4])0xC039B0;
RwTexture* (&CPlantMgr::PC_PlantTextureTab2)[4] = *(RwTexture * (*)[4])0xC039C0;
RwTexture* (&CPlantMgr::PC_PlantTextureTab3)[4] = *(RwTexture * (*)[4])0xC039D0;

RpAtomic* (&CPlantMgr::PC_PlantModelsTab0)[4] = *(RpAtomic * (*)[4])0xC039F0;
RpAtomic* (&CPlantMgr::PC_PlantModelsTab1)[4] = *(RpAtomic * (*)[4])0xC03A00;
RpAtomic* (&CPlantMgr::PC_PlantModelsTab2)[4] = *(RpAtomic * (*)[4])0xC03A10;
RpAtomic* (&CPlantMgr::PC_PlantModelsTab3)[4] = *(RpAtomic * (*)[4])0xC03A20;

int32* (&grassTexturesPtr)[4] = *(int32 * (*)[4])0xC039E0;
int32* (&grassModelsPtr)[4] = *(int32 * (*)[4])0xC03A30;
RwTexture*& tex_gras07Si = *(RwTexture**)0xC09174;

void CPlantMgr::InjectHooks() {
    RH_ScopedClass(CPlantMgr);
    RH_ScopedCategoryRoot();

// Install("CPlantMgr", "", 0x0, &CPlantMgr::);
}

// 0x5DD910
bool CPlantMgr::Initialise() {
    return plugin::CallAndReturn<bool, 0x5DD910>();
}

void CPlantMgr::SetPlantFriendlyFlagInAtomicMI(CAtomicModelInfo* ami) {
    plugin::Call<0x5DB650, CAtomicModelInfo*>(ami);
}

// 0x5DCFA0
void CPlantMgr::Update(const CVector& cameraPosition) {
    return plugin::Call<0x5DCFA0, const CVector&>(cameraPosition);
}

// 0x5DBAE0
void CPlantMgr::Render() {
    plugin::Call<0x5DBAE0>();
}
