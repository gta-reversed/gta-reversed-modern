#include "StdInc.h"

#include "BreakObject_c.h"

void BreakObject_c::InjectHooks() {
    RH_ScopedClass(BreakObject_c);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(CalcGroupCenter, 0x59D190);
    RH_ScopedInstall(SetGroupData, 0x59D570);
    RH_ScopedInstall(SetBreakInfo, 0x59D7F0);
    RH_ScopedInstall(Exit, 0x59DDD0);
    RH_ScopedInstall(DoCollisionResponse, 0x59DE40);
    RH_ScopedInstall(DoCollision, 0x59E1F0);
    RH_ScopedInstall(Update, 0x59E220);
    RH_ScopedInstall(Render, 0x59E480);
    RH_ScopedInstall(Init, 0x59E750);
}

// 0x59D170
BreakObject_c::BreakObject_c() {
    m_JustFaces = false;
    m_bActive = false;
    m_BreakGroup = nullptr;
}

// 0x59E750
bool BreakObject_c::Init(CObject* object, CVector* posn, float fVelocityRand, int32 bJustFaces) {
    return plugin::CallMethodAndReturn<bool, 0x59E750, BreakObject_c*, CObject*, CVector*, float, int32>(this, object, posn, fVelocityRand, bJustFaces);
}

// 0x59DDD0
void BreakObject_c::Exit() {
    plugin::CallMethod<0x59DDD0, BreakObject_c*>(this);
}

// 0x59D190
void BreakObject_c::CalcGroupCenter(BreakGroup_t* group) {
    plugin::Call<0x59D190, BreakGroup_t*>(group);
}

// Methods
// 0x59D570
void BreakObject_c::SetGroupData(RwMatrix* matrix, CVector* posn, float a5) {
    plugin::CallMethod<0x59D570, BreakObject_c*, RwMatrixTag*, CVector*, float>(this, matrix, posn, a5);
}

// 0x59D7F0
void BreakObject_c::SetBreakInfo(BreakInfo_t* info, int32 bJustFaces) {
    plugin::CallMethod<0x59D7F0, BreakObject_c*, BreakInfo_t*, int32>(this, info, bJustFaces);
}

// 0x59DE40
void BreakObject_c::DoCollisionResponse(BreakGroup_t* group, float a2, CVector* posn, float a4) {
    plugin::CallMethod<0x59DE40, BreakObject_c*, BreakGroup_t*, float, CVector*, float>(this, group, a2, posn, a4);
}

// 0x59E1F0
void BreakObject_c::DoCollision(BreakGroup_t* group, float a2) {
    plugin::CallMethod<0x59E1F0, BreakObject_c*, BreakGroup_t*, float>(this, group, a2);
}

// 0x59E220
void BreakObject_c::Update(float timeStep) {
    plugin::CallMethod<0x59E220, BreakObject_c*, float>(this, timeStep);
}

// 0x59E480
void BreakObject_c::Render(bool a1) {
    plugin::CallMethod<0x59E480, BreakObject_c*>(this, a1);
}
