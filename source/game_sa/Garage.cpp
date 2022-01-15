#include "StdInc.h"

void CGarage::InjectHooks()
{
    ReversibleHooks::Install("CGarage", "BuildRotatedDoorMatrix", 0x4479F0, &CGarage::BuildRotatedDoorMatrix);

    // Constructors (1x)
    // ReversibleHooks::Install("CGarage", "CGarage", 0x4470E0, &CGarage::Constructor);

    // Destructors (1x)
    // ReversibleHooks::Install("CGarage", "~CGarage", 0x447110, &CGarage::Destructor);


    // Methods (15x)    
    // ReversibleHooks::Install("CGarage", "TidyUpGarageClose", 0x449D10, &CGarage::TidyUpGarageClose);
    // ReversibleHooks::Install("CGarage", "TidyUpGarage", 0x449C50, &CGarage::TidyUpGarage);
    // ReversibleHooks::Install("CGarage", "StoreAndRemoveCarsForThisHideOut", 0x449900, &CGarage::StoreAndRemoveCarsForThisHideOut);
    // ReversibleHooks::Install("CGarage", "RemoveCarsBlockingDoorNotInside", 0x449690, &CGarage::RemoveCarsBlockingDoorNotInside);
    // ReversibleHooks::Install("CGarage", "IsEntityTouching3D", 0x448EE0, &CGarage::IsEntityTouching3D);
    // ReversibleHooks::Install("CGarage", "IsEntityEntirelyOutside", 0x448D30, &CGarage::IsEntityEntirelyOutside);
    // ReversibleHooks::Install("CGarage", "IsStaticPlayerCarEntirelyInside", 0x44A830, &CGarage::IsStaticPlayerCarEntirelyInside);
    // ReversibleHooks::Install("CGarage", "IsEntityEntirelyInside3D", 0x448BE0, &CGarage::IsEntityEntirelyInside3D);
    // ReversibleHooks::Install("CGarage", "IsPointInsideGarage", 0x448740, static_cast<bool(CGarage::*)(CVector)>(&CGarage::IsPointInsideGarage));
    // ReversibleHooks::Install("CGarage", "PlayerArrestedOrDied", 0x4486C0, &CGarage::PlayerArrestedOrDied);
    // ReversibleHooks::Install("CGarage", "Close", 0x447D70, &CGarage::Close);
    // ReversibleHooks::Install("CGarage", "Open", 0x447D50, &CGarage::Open);
    // ReversibleHooks::Install("CGarage", "InitDoorsAtStart", 0x447600, &CGarage::InitDoorsAtStart);
    // ReversibleHooks::Install("CGarage", "IsPointInsideGarage", 0x4487D0, static_cast<bool(CGarage::*)(CVector, float)>(&CGarage::IsPointInsideGarage));
    // ReversibleHooks::Install("CGarage", "Update", 0x44AA50, &CGarage::Update);
}

// 0x4470E0
CGarage* CGarage::Constructor() {
    this->CGarage::CGarage();
    return this;
}

// 0x447110
CGarage* CGarage::Destructor() {
    this->CGarage::~CGarage();
    return this;
}

void CGarage::BuildRotatedDoorMatrix(CEntity* pEntity, float fDoorPosition)
{
    const auto fAngle = fDoorPosition * -HALF_PI;
    const auto fSin = sin(fAngle);
    const auto fCos = cos(fAngle);
    CMatrix& matrix = pEntity->GetMatrix();

    const auto& vecForward = matrix.GetForward();
    matrix.GetUp() = CVector(-fSin * vecForward.y, fSin * vecForward.x, fCos);
    matrix.GetRight() = CrossProduct(vecForward, matrix.GetUp());
}


// Methods
// 0x449D10
void CGarage::TidyUpGarageClose() {
    plugin::CallMethod<0x449D10, CGarage*>(this);
}

// 0x449C50
void CGarage::TidyUpGarage() {
    plugin::CallMethod<0x449C50, CGarage*>(this);
}

// 0x449900
void CGarage::StoreAndRemoveCarsForThisHideOut(CStoredCar* car, int32 maxSlot) {
    plugin::CallMethod<0x449900, CGarage*, CStoredCar*, int32>(this, car, maxSlot);
}

// 0x449690
void CGarage::RemoveCarsBlockingDoorNotInside() {
    plugin::CallMethod<0x449690, CGarage*>(this);
}

// 0x448EE0
bool CGarage::IsEntityTouching3D(CEntity* entity) {
    return plugin::CallMethodAndReturn<bool, 0x448EE0, CGarage*, CEntity*>(this, entity);
}

// 0x448D30
bool CGarage::IsEntityEntirelyOutside(CEntity* entity, float radius) {
    return plugin::CallMethodAndReturn<bool, 0x448D30, CGarage*, CEntity*, float>(this, entity, radius);
}

// 0x44A830
bool CGarage::IsStaticPlayerCarEntirelyInside() {
    return plugin::CallMethodAndReturn<bool, 0x44A830, CGarage*>(this);
}

// 0x448BE0
bool CGarage::IsEntityEntirelyInside3D(CEntity* entity, float radius) {
    return plugin::CallMethodAndReturn<bool, 0x448BE0, CGarage*, CEntity*, float>(this, entity, radius);
}

// 0x448740
bool CGarage::IsPointInsideGarage(CVector point) {
    return plugin::CallMethodAndReturn<bool, 0x448740, CGarage*, CVector>(this, point);
}

// 0x4486C0
uint8 CGarage::PlayerArrestedOrDied() {
    return plugin::CallMethodAndReturn<uint8, 0x4486C0, CGarage*>(this);
}

// 0x447D70
void CGarage::Close() {
    plugin::CallMethod<0x447D70, CGarage*>(this);
}

// 0x447D50
int8_t CGarage::Open() {
    return plugin::CallMethodAndReturn<int8_t, 0x447D50, CGarage*>(this);
}

// 0x447600
void CGarage::InitDoorsAtStart() {
    plugin::CallMethod<0x447600, CGarage*>(this);
}

// 0x4487D0
bool CGarage::IsPointInsideGarage(CVector point, float radius) {
    return plugin::CallMethodAndReturn<bool, 0x4487D0, CGarage*, CVector, float>(this, point, radius);
}

// 0x44AA50
void CGarage::Update(int32 thisGarageId) {
    plugin::CallMethod<0x44AA50, CGarage*>(this, thisGarageId);
}

void CSaveGarage::CopyGarageIntoSaveGarage(const CGarage& v) {
    type = v.m_nType;
    doorState = v.m_nDoorState;
    flags = v.m_nFlags;
    pos = v.m_vPosn;
    dirA = v.m_vDirectionA;
    dirB = v.m_vDirectionB;
    topZ = v.m_fTopZ;
    width = v.m_fWidth;
    height = v.m_fHeight;
    leftCoord = v.m_fLeftCoord;
    rightCoord = v.m_fRightCoord;
    frontCoord = v.m_fFrontCoord;
    backCoord = v.m_fBackCoord;
    doorPos = v.m_fDoorPosition;
    timeToOpen = v.m_dwTimeToOpen;
    originalType = v.m_nOriginalType;
    strcpy_s(name, v.m_anName);
}

void CSaveGarage::CopyGarageOutOfSaveGarage(CGarage& v) const {
    v.m_nType = type;
    v.m_nDoorState = doorState;
    v.m_nFlags = flags;
    v.m_vPosn = pos;
    v.m_vDirectionA = dirA;
    v.m_vDirectionB = dirB;
    v.m_fTopZ = topZ;
    v.m_fWidth = width;
    v.m_fHeight = height;
    v.m_fLeftCoord = leftCoord;
    v.m_fRightCoord = rightCoord;
    v.m_fFrontCoord = frontCoord;
    v.m_fBackCoord = backCoord;
    v.m_fDoorPosition = doorPos;
    v.m_dwTimeToOpen = timeToOpen;
    v.m_nOriginalType = originalType;
    strcpy_s(v.m_anName, name);
}
