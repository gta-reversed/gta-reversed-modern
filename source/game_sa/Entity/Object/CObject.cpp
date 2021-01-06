/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

unsigned short& CObject::nNoTempObjects = *reinterpret_cast<unsigned short*>(0xBB4A70);

CObject::CObject() : CPhysical(plugin::dummy)
{
    m_pDummyObject = nullptr;
    Init();
    m_nObjectType = eObjectCreatedBy::OBJECT_UNKNOWN;
}

CObject* CObject::Constructor()
{
    return plugin::CallMethodAndReturn<CObject*, 0x5A1D10, CObject*>(this);
}

void CObject::SetIsStatic(bool isStatic)
{
    return SetIsStatic_Reversed(isStatic);
}

void CObject::SetIsStatic_Reversed(bool isStatic)
{
    plugin::CallMethod<0x5A0760, CObject*, bool>(this, isStatic);
}

// Converted from thiscall void CObject::ProcessGarageDoorBehaviour(void) 0x44A4D0
void CObject::ProcessGarageDoorBehaviour() {
    ((void(__thiscall*)(CObject*))0x44A4D0)(this);
}

// Converted from thiscall bool CObject::CanBeDeleted(void) 0x59F120
bool CObject::CanBeDeleted() {
    return ((bool(__thiscall*)(CObject*))0x59F120)(this);
}

// Converted from thiscall void CObject::SetRelatedDummy(CDummyObject *relatedDummy) 0x59F160
void CObject::SetRelatedDummy(CDummyObject* relatedDummy) {
    ((void(__thiscall*)(CObject*, CDummyObject*))0x59F160)(this, relatedDummy);
}

void* CObject::operator new(unsigned int size)
{
    return plugin::CallAndReturn<void*, 0x5A1EE0, unsigned int>(size);
}

// Converted from cdecl void CObject::SetMatrixForTrainCrossing(CMatrix *matrix,float) 0x59F200
void CObject::SetMatrixForTrainCrossing(CMatrix* matrix, float arg1) {
    ((void(__cdecl*)(CMatrix*, float))0x59F200)(matrix, arg1);
}

// Converted from thiscall bool CObject::TryToExplode(void) 0x59F2D0
bool CObject::TryToExplode() {
    return ((bool(__thiscall*)(CObject*))0x59F2D0)(this);
}

// Converted from thiscall void CObject::SetObjectTargettable(uchar targetable) 0x59F300
void CObject::SetObjectTargettable(unsigned char targetable) {
    ((void(__thiscall*)(CObject*, unsigned char))0x59F300)(this, targetable);
}

// Converted from thiscall bool CObject::CanBeTargetted(void) 0x59F320
bool CObject::CanBeTargetted() {
    return ((bool(__thiscall*)(CObject*))0x59F320)(this);
}

// Converted from thiscall void CObject::RefModelInfo(int modelIndex) 0x59F330
void CObject::RefModelInfo(int modelIndex) {
    plugin::CallMethod<0x59F330, CObject*, int>(this, modelIndex);
}

// Converted from thiscall void CObject::SetRemapTexture(RwTexture *remapTexture, short txdIndex) 0x59F350
void CObject::SetRemapTexture(RwTexture* remapTexture, short txdIndex) {
    ((void(__thiscall*)(CObject*, RwTexture*, short))0x59F350)(this, remapTexture, txdIndex);
}

// Converted from thiscall float CObject::GetRopeHeight(void) 0x59F380
float CObject::GetRopeHeight() {
    return ((float(__thiscall*)(CObject*))0x59F380)(this);
}

// Converted from thiscall void CObject::SetRopeHeight(float height) 0x59F3A0
void CObject::SetRopeHeight(float height) {
    ((void(__thiscall*)(CObject*, float))0x59F3A0)(this, height);
}

// Converted from thiscall CEntity* CObject::GetObjectCarriedWithRope(void) 0x59F3C0
CEntity* CObject::GetObjectCarriedWithRope() {
    return ((CEntity * (__thiscall*)(CObject*))0x59F3C0)(this);
}

// Converted from thiscall void CObject::ReleaseObjectCarriedWithRope(void) 0x59F3E0
void CObject::ReleaseObjectCarriedWithRope() {
    ((void(__thiscall*)(CObject*))0x59F3E0)(this);
}

// Converted from thiscall void CObject::AddToControlCodeList(void) 0x59F400
void CObject::AddToControlCodeList() {
    ((void(__thiscall*)(CObject*))0x59F400)(this);
}

// Converted from thiscall void CObject::RemoveFromControlCodeList(void) 0x59F450
void CObject::RemoveFromControlCodeList() {
    ((void(__thiscall*)(CObject*))0x59F450)(this);
}

// Converted from thiscall void CObject::ResetDoorAngle(void) 0x59F4B0
void CObject::ResetDoorAngle() {
    ((void(__thiscall*)(CObject*))0x59F4B0)(this);
}

// Converted from thiscall void CObject::LockDoor(void) 0x59F5C0
void CObject::LockDoor() {
    ((void(__thiscall*)(CObject*))0x59F5C0)(this);
}

// Converted from thiscall void CObject::Init(void) 0x59F840
void CObject::Init() {
    ((void(__thiscall*)(CObject*))0x59F840)(this);
}

// Converted from thiscall void CObject::DoBurnEffect(void) 0x59FB50
void CObject::DoBurnEffect() {
    ((void(__thiscall*)(CObject*))0x59FB50)(this);
}

// Converted from thiscall uchar CObject::GetLightingFromCollisionBelow(void) 0x59FD00
unsigned char CObject::GetLightingFromCollisionBelow() {
    return ((unsigned char(__thiscall*)(CObject*))0x59FD00)(this);
}

// Converted from thiscall void CObject::ProcessSamSiteBehaviour(void) 0x5A07D0
void CObject::ProcessSamSiteBehaviour() {
    ((void(__thiscall*)(CObject*))0x5A07D0)(this);
}

// Converted from thiscall void CObject::ProcessTrainCrossingBehaviour(void) 0x5A0B50
void CObject::ProcessTrainCrossingBehaviour() {
    ((void(__thiscall*)(CObject*))0x5A0B50)(this);
}

// Converted from thiscall void CObject::ObjectDamage(float damage,CVector *fxOrigin,CVector *fxDirection,CEntity *damager,eWeaponType weaponType) 0x5A0D90
void CObject::ObjectDamage(float damage, CVector* fxOrigin, CVector* fxDirection, CEntity* damager, eWeaponType weaponType) {
    ((void(__thiscall*)(CObject*, float, CVector*, CVector*, CEntity*, eWeaponType))0x5A0D90)(this, damage, fxOrigin, fxDirection, damager, weaponType);
}

// Converted from thiscall void CObject::Explode(void) 0x5A1340
void CObject::Explode() {
    ((void(__thiscall*)(CObject*))0x5A1340)(this);
}

// Converted from thiscall void CObject::ObjectFireDamage(float damage,CEntity *damager) 0x5A1580
void CObject::ObjectFireDamage(float damage, CEntity* damager) {
    ((void(__thiscall*)(CObject*, float, CEntity*))0x5A1580)(this, damage, damager);
}

// Converted from cdecl void CObject::TryToFreeUpTempObjects(int numObjects) 0x5A1840
void CObject::TryToFreeUpTempObjects(int numObjects) {
    ((void(__cdecl*)(int))0x5A1840)(numObjects);
}

// Converted from cdecl void CObject::DeleteAllTempObjects(void) 0x5A18B0
void CObject::DeleteAllTempObjects() {
    ((void(__cdecl*)())0x5A18B0)();
}

// Converted from cdecl void CObject::DeleteAllMissionObjects(void) 0x5A1910
void CObject::DeleteAllMissionObjects() {
    ((void(__cdecl*)())0x5A1910)();
}

// Converted from cdecl void CObject::DeleteAllTempObjectsInArea(CVector point,float radius) 0x5A1980
void CObject::DeleteAllTempObjectsInArea(CVector point, float radius) {
    ((void(__cdecl*)(CVector, float))0x5A1980)(point, radius);
}

// Converted from thiscall void CObject::GrabObjectToCarryWithRope(CPhysical *attachTo) 0x5A1AB0
void CObject::GrabObjectToCarryWithRope(CPhysical* attachTo) {
    ((void(__thiscall*)(CObject*, CPhysical*))0x5A1AB0)(this, attachTo);
}

// Converted from thiscall bool CObject::CanBeUsedToTakeCoverBehind(void) 0x5A1B60
bool CObject::CanBeUsedToTakeCoverBehind() {
    return ((bool(__thiscall*)(CObject*))0x5A1B60)(this);
}

CObject* CObject::Create(int modelIndex) {
    return ((CObject * (__cdecl*)(int))0x5A1F60)(modelIndex);
}

CObject* CObject::Create(CDummyObject* dummyObject) {
    return ((CObject * (__cdecl*)(CDummyObject*))0x5A2070)(dummyObject);
}

// Converted from thiscall void CObject::ProcessControlLogic(void) 0x5A29A0
void CObject::ProcessControlLogic() {
    ((void(__thiscall*)(CObject*))0x5A29A0)(this);
}

// Converted from cdecl bool IsObjectPointerValid_NotInWorld(CObject *object) 0x5A2B90
bool IsObjectPointerValid_NotInWorld(CObject* object) {
    return ((bool(__cdecl*)(CObject*))0x5A2B90)(object);
}

// Converted from cdecl bool IsObjectPointerValid(CObject *object) 0x5A2C20
bool IsObjectPointerValid(CObject* object) {
    return ((bool(__cdecl*)(CObject*))0x5A2C20)(object);
}
