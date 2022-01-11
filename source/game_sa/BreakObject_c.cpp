#include "StdInc.h"

#include "BreakObject_c.h"

void BreakObject_c::InjectHooks() {
    using namespace ReversibleHooks;
    Install("BreakObject_c", "CalcGroupCenter", 0x59D190, &BreakObject_c::CalcGroupCenter);
    Install("BreakObject_c", "SetGroupData", 0x59D570, &BreakObject_c::SetGroupData);
    Install("BreakObject_c", "SetBreakInfo", 0x59D7F0, &BreakObject_c::SetBreakInfo);
    Install("BreakObject_c", "Exit", 0x59DDD0, &BreakObject_c::Exit);
    Install("BreakObject_c", "DoCollisionResponse", 0x59DE40, &BreakObject_c::DoCollisionResponse);
    Install("BreakObject_c", "DoCollision", 0x59E1F0, &BreakObject_c::DoCollision);
    Install("BreakObject_c", "Update", 0x59E220, &BreakObject_c::Update);
    Install("BreakObject_c", "Render", 0x59E480, &BreakObject_c::Render);
    Install("BreakObject_c", "Init", 0x59E750, &BreakObject_c::Init);
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
    plugin::CallMethod<0x59E480>(this, a1);
}
