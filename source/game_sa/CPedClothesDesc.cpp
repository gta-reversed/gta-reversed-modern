#include "StdInc.h"

void CPedClothesDesc::InjectHooks() {
    ReversibleHooks::Install("CPedClothesDesc", "CPedClothesDesc", 0x5A8020, &CPedClothesDesc::Constructor);
//    ReversibleHooks::Install("CPedClothesDesc", "Initialise", 0x5A78F0, &CPedClothesDesc::Initialise);
//    ReversibleHooks::Install("CPedClothesDesc", "GetIsWearingBalaclava", 0x5A7950, &CPedClothesDesc::GetIsWearingBalaclava);
//    ReversibleHooks::Install("CPedClothesDesc", "HasVisibleNewHairCut", 0x5A7970, &CPedClothesDesc::HasVisibleNewHairCut);
//    ReversibleHooks::Install("CPedClothesDesc", "HasVisibleTattoo", 0x5A79D0, &CPedClothesDesc::HasVisibleTattoo);
}

CPedClothesDesc::CPedClothesDesc() {
    memset(m_anTextureKeys, 0, sizeof(m_anTextureKeys));
    m_fFatStat = 0.0f;
    m_fMuscleStat = 0.0f;
}

CPedClothesDesc* CPedClothesDesc::Constructor() {
    this->CPedClothesDesc::CPedClothesDesc();
    return this;
}

void CPedClothesDesc::Initialise() {
    plugin::CallMethod<0x5A78F0, CPedClothesDesc*>(this);
}

void CPedClothesDesc::SetModel(uint32 modelId, eClothesModelPart modelPart) {
    plugin::CallMethod<0x5A7910, CPedClothesDesc*, uint32, eClothesModelPart>(this, modelId, modelPart);
}

void CPedClothesDesc::SetModel(const char* model, eClothesModelPart modelPart) {
    plugin::CallMethod<0x5A7920, CPedClothesDesc*, const char*, eClothesModelPart>(this, model, modelPart);
}

bool CPedClothesDesc::GetIsWearingBalaclava() {
    return plugin::CallMethodAndReturn<bool, 0x5A7950>(this);
}

bool CPedClothesDesc::HasVisibleNewHairCut(int32 arg1) {
    return plugin::CallMethodAndReturn<bool, 0x5A7970, int32>(arg1);
}

bool CPedClothesDesc::HasVisibleTattoo() {
    return plugin::CallMethodAndReturn<bool, 0x5A79D0>(this);
}

void CPedClothesDesc::SetTextureAndModel(uint32 texture, uint32 model, eClothesTexturePart texturePart) {
    plugin::CallMethod<0x5A8050, CPedClothesDesc*, uint32, uint32, eClothesTexturePart>(this, texture, model, texturePart);
}

void CPedClothesDesc::SetTextureAndModel(const char* textureName, const char* modelName, eClothesTexturePart texturePart) {
    plugin::CallMethod<0x5A8080, CPedClothesDesc*, const char*, const char*, eClothesTexturePart>(this, textureName, modelName, texturePart);
}

