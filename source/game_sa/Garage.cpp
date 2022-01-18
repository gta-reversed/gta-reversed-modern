#include "StdInc.h"

#include "Garage.h"

void CGarage::InjectHooks()
{
    using namespace ReversibleHooks;
    Install("CGarage", "BuildRotatedDoorMatrix", 0x4479F0, &CGarage::BuildRotatedDoorMatrix);
    // Install("CGarage", "TidyUpGarageClose", 0x449D10, &CGarage::TidyUpGarageClose);
    // Install("CGarage", "TidyUpGarage", 0x449C50, &CGarage::TidyUpGarage);
    // Install("CGarage", "StoreAndRemoveCarsForThisHideOut", 0x449900, &CGarage::StoreAndRemoveCarsForThisHideOut);
    // Install("CGarage", "RemoveCarsBlockingDoorNotInside", 0x449690, &CGarage::RemoveCarsBlockingDoorNotInside);
    // Install("CGarage", "IsEntityTouching3D", 0x448EE0, &CGarage::IsEntityTouching3D);
    // Install("CGarage", "IsEntityEntirelyOutside", 0x448D30, &CGarage::IsEntityEntirelyOutside);
    // Install("CGarage", "IsStaticPlayerCarEntirelyInside", 0x44A830, &CGarage::IsStaticPlayerCarEntirelyInside);
    // Install("CGarage", "IsEntityEntirelyInside3D", 0x448BE0, &CGarage::IsEntityEntirelyInside3D);
    // Install("CGarage", "IsPointInsideGarage", 0x448740, static_cast<bool(CGarage::*)(CVector)>(&CGarage::IsPointInsideGarage));
    // Install("CGarage", "PlayerArrestedOrDied", 0x4486C0, &CGarage::PlayerArrestedOrDied);
    Install("CGarage", "OpenThisGarage", 0x447D50, &CGarage::OpenThisGarage);
    Install("CGarage", "CloseThisGarage", 0x447D70, &CGarage::CloseThisGarage);
    // Install("CGarage", "InitDoorsAtStart", 0x447600, &CGarage::InitDoorsAtStart);
    // Install("CGarage", "IsPointInsideGarage", 0x4487D0, static_cast<bool(CGarage::*)(CVector, float)>(&CGarage::IsPointInsideGarage));
    // Install("CGarage", "Update", 0x44AA50, &CGarage::Update);
}

// 0x4479F0
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
eGarageDoorState CGarage::PlayerArrestedOrDied() {
    return plugin::CallMethodAndReturn<eGarageDoorState, 0x4486C0, CGarage*>(this);
}

// 0x447D50
void CGarage::OpenThisGarage() {
  if ( m_nDoorState == GARAGE_DOOR_CLOSED
    || m_nDoorState == GARAGE_DOOR_CLOSING
    || m_nDoorState == GARAGE_DOOR_CLOSED_DROPPED_CAR)
  {
    m_nDoorState = GARAGE_DOOR_OPENING;
  }
}

// 0x447D70
void CGarage::CloseThisGarage() {
    if (m_nDoorState == GARAGE_DOOR_OPEN || m_nDoorState == GARAGE_DOOR_OPENING)
        m_nDoorState = GARAGE_DOOR_CLOSING;
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
void CGarage::Update(int32 garageId) {
    plugin::CallMethod<0x44AA50, CGarage*>(this, garageId);
}

void CSaveGarage::CopyGarageIntoSaveGarage(const CGarage& g) {
    type         = g.m_nType;
    doorState    = g.m_nDoorState;
    flags        = g.m_nFlags;
    pos          = g.m_vPosn;
    dirA         = g.m_vDirectionA;
    dirB         = g.m_vDirectionB;
    topZ         = g.m_fTopZ;
    width        = g.m_fWidth;
    height       = g.m_fHeight;
    leftCoord    = g.m_fLeftCoord;
    rightCoord   = g.m_fRightCoord;
    frontCoord   = g.m_fFrontCoord;
    backCoord    = g.m_fBackCoord;
    doorPos      = g.m_fDoorPosition;
    timeToOpen   = g.m_nTimeToOpen;
    originalType = g.m_nOriginalType;
    strcpy_s(name, g.m_anName);
}

void CSaveGarage::CopyGarageOutOfSaveGarage(CGarage& g) const {
    g.m_nType         = type;
    g.m_nDoorState    = doorState;
    g.m_nFlags        = flags;
    g.m_vPosn         = pos;
    g.m_vDirectionA   = dirA;
    g.m_vDirectionB   = dirB;
    g.m_fTopZ         = topZ;
    g.m_fWidth        = width;
    g.m_fHeight       = height;
    g.m_fLeftCoord    = leftCoord;
    g.m_fRightCoord   = rightCoord;
    g.m_fFrontCoord   = frontCoord;
    g.m_fBackCoord    = backCoord;
    g.m_fDoorPosition = doorPos;
    g.m_nTimeToOpen  = timeToOpen;
    g.m_nOriginalType = originalType;
    strcpy_s(g.m_anName, name);
}
