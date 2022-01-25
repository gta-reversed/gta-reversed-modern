#include "StdInc.h"

int32& CWindModifiers::Number = *(int32*)0xC81450;
CWindModifier (&CWindModifiers::Array)[MAX_NUM_MODIFIERS] = *(CWindModifier(*)[MAX_NUM_MODIFIERS])0xC81458;

void CWindModifiers::InjectHooks() {
//    Install("CWindModifiers", "FindWindModifier", 0x0, &CWindModifiers::FindWindModifier);
//    Install("CWindModifiers", "RegisterOne", 0x0, &CWindModifiers::RegisterOne);
}

void CWindModifiers::FindWindModifier(CVector vecPos, float* pOutX, float* pOutY) {
    plugin::Call<0x72C950, CVector, float*, float*>(vecPos, pOutX, pOutY);
}

void CWindModifiers::RegisterOne(CVector vecPos, int32 iActive, float fPower) {
    plugin::Call<0x72C8B0, CVector, int32, float>(vecPos, iActive, fPower);
}
