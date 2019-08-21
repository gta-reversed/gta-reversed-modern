/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

float& CWeapon::ms_fExtinguisherAimAngle = *(float*)0x8D610C;
bool& CWeapon::bPhotographHasBeenTaken = *(bool*)0xC8A7C0;
bool& CWeapon::ms_bTakePhoto = *(bool*)0xC8A7C1;
CColModel& CWeapon::ms_PelletTestCol = *(CColModel*)0xC8A7DC;
float& fPlayerAimScale = *(float*)0x8D6110;
float& fPlayerAimScaleDist = *(float*)0x8D6114;
float& fPlayerAimRotRate = *(float*)0x8D6118;
float& SHOTGUN_SPREAD_RATE = *(float*)0x8D611C;
unsigned int& SHOTGUN_NUM_PELLETS = *(unsigned int*)0x8D6120;
unsigned int& SPAS_NUM_PELLETS = *(unsigned int*)0x8D6124;
float& PELLET_COL_SCALE_RATIO_MULT = *(float*)0x8D6128;
float* fReloadAnimSampleFraction = (float*)0x8D612C;

// Converted from cdecl void CWeapon::InitialiseWeapons(void) 0x73A300
void CWeapon::InitialiseWeapons() {
    plugin::Call<0x73A300>();
}

// Converted from cdecl void CWeapon::ShutdownWeapons(void) 0x73A330
void CWeapon::ShutdownWeapons() {
    plugin::Call<0x73A330>();
}

// Converted from cdecl void CWeapon::UpdateWeapons(void) 0x73A360
void CWeapon::UpdateWeapons() {
    plugin::Call<0x73A360>();
}

// Converted from thiscall void CWeapon::Shutdown(void) 0x73A380
void CWeapon::Shutdown() {
    plugin::CallMethod<0x73A380, CWeapon*>(this);
}

// Converted from thiscall void CWeapon::AddGunshell(CEntity *creator,CVector const&position,CVector2D const&direction,float size) 0x73A3E0
void CWeapon::AddGunshell(CEntity* creator, CVector const& position, CVector2D const& direction, float size) {
    plugin::CallMethod<0x73A3E0, CWeapon*, CEntity*, CVector const&, CVector2D const&, float>(this, creator, position, direction, size);
}

// Converted from cdecl void CWeapon::GenerateDamageEvent(CPed *victim,CEntity *creator,eWeaponType weaponType,int damageFactor,ePedPieceTypes pedPiece,int direction) 0x73A530
void CWeapon::GenerateDamageEvent(CPed* victim, CEntity* creator, eWeaponType weaponType, int damageFactor, ePedPieceTypes pedPiece, int direction) {
    plugin::Call<0x73A530, CPed*, CEntity*, eWeaponType, int, ePedPieceTypes, int>(victim, creator, weaponType, damageFactor, pedPiece, direction);
}

// Converted from thiscall bool CWeapon::LaserScopeDot(CVector *outCoord,float *outSize) 0x73A8D0
bool CWeapon::LaserScopeDot(CVector* outCoord, float* outSize) {
    return plugin::CallMethodAndReturn<bool, 0x73A8D0, CWeapon*, CVector*, float*>(this, outCoord, outSize);
}

// Converted from thiscall bool CWeapon::FireSniper(CPed *creator, CEntity *victim, CVector *target) 0x73AAC0
bool CWeapon::FireSniper(CPed* creator, CEntity* victim, CVector* target) {
    return plugin::CallMethodAndReturn<bool, 0x73AAC0, CWeapon*, CPed*, CEntity*, CVector*>(this, creator, victim, target);
}

// Converted from thiscall void CWeapon::Reload(CPed *owner) 0x73AEB0
void CWeapon::Reload(CPed* owner) {
    plugin::CallMethod<0x73AEB0, CWeapon*, CPed*>(this, owner);
}

// Converted from cdecl void FireOneInstantHitRound(CVector *startPoint,CVector *endPoint,int intensity) 0x73AF00
void FireOneInstantHitRound(CVector* startPoint, CVector* endPoint, int intensity) {
    plugin::Call<0x73AF00, CVector*, CVector*, int>(startPoint, endPoint, intensity);
}

// Converted from thiscall bool CWeapon::IsTypeMelee(void) 0x73B1C0
bool CWeapon::IsTypeMelee() {
    return plugin::CallMethodAndReturn<bool, 0x73B1C0, CWeapon*>(this);
}

// Converted from thiscall bool CWeapon::IsType2Handed(void) 0x73B1E0
bool CWeapon::IsType2Handed() {
    return plugin::CallMethodAndReturn<bool, 0x73B1E0, CWeapon*>(this);
}

// Converted from thiscall bool CWeapon::IsTypeProjectile(void) 0x73B210
bool CWeapon::IsTypeProjectile() {
    return plugin::CallMethodAndReturn<bool, 0x73B210, CWeapon*>(this);
}

// Converted from cdecl bool CWeapon::CanBeUsedFor2Player(eWeaponType weaponType) 0x73B240
bool CWeapon::CanBeUsedFor2Player(eWeaponType weaponType) {
    return plugin::CallAndReturn<bool, 0x73B240, eWeaponType>(weaponType);
}

// Converted from thiscall bool CWeapon::HasWeaponAmmoToBeUsed(void) 0x73B2A0
bool CWeapon::HasWeaponAmmoToBeUsed() {
    return plugin::CallMethodAndReturn<bool, 0x73B2A0, CWeapon*>(this);
}

// Converted from cdecl bool CWeapon::ProcessLineOfSight(CVector const&startPoint,CVector const&endPoint,CColPoint &outColPoint,CEntity *&outEntity,eWeaponType weaponType,CEntity *,bool buildings,bool vehicles,bool peds,bool objects,bool dummies,bool,bool doIgnoreCameraCheck) 0x73B300
bool CWeapon::ProcessLineOfSight(CVector const& startPoint, CVector const& endPoint, CColPoint& outColPoint, CEntity*& outEntity, eWeaponType weaponType, CEntity* arg5, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool arg11, bool doIgnoreCameraCheck) {
    return plugin::CallAndReturn<bool, 0x73B300, CVector const&, CVector const&, CColPoint&, CEntity*&, eWeaponType, CEntity*, bool, bool, bool, bool, bool, bool, bool>(startPoint, endPoint, outColPoint, outEntity, weaponType, arg5, buildings, vehicles, peds, objects, dummies, arg11, doIgnoreCameraCheck);
}

// Converted from thiscall void CWeapon::StopWeaponEffect(void) 0x73B360
void CWeapon::StopWeaponEffect() {
    plugin::CallMethod<0x73B360, CWeapon*>(this);
}

// Converted from cdecl float CWeapon::TargetWeaponRangeMultiplier(CEntity *victim,CEntity *weaponOwner) 0x73B380
float CWeapon::TargetWeaponRangeMultiplier(CEntity* victim, CEntity* weaponOwner) {
    return plugin::CallAndReturn<float, 0x73B380, CEntity*, CEntity*>(victim, weaponOwner);
}

// Converted from thiscall void CWeapon::CWeapon(eWeaponType weaponType,int ammo) 0x73B430
CWeapon::CWeapon(eWeaponType weaponType, int ammo) {
    plugin::CallMethod<0x73B430, CWeapon*, eWeaponType, int>(this, weaponType, ammo);
}

// Converted from thiscall void CWeapon::Initialise(eWeaponType weaponType,int ammo,CPed *owner) 0x73B4A0
void CWeapon::Initialise(eWeaponType weaponType, int ammo, CPed* owner) {
    plugin::CallMethod<0x73B4A0, CWeapon*, eWeaponType, int, CPed*>(this, weaponType, ammo, owner);
}

// Converted from thiscall void CWeapon::DoBulletImpact(CEntity *owner,CEntity *victim,CVector *startPoint,CVector *endPoint,CColPoint *colPoint,int) 0x73B550
void CWeapon::DoBulletImpact(CEntity* owner, CEntity* victim, CVector* startPoint, CVector* endPoint, CColPoint* colPoint, int arg5) {
    plugin::CallMethod<0x73B550, CWeapon*, CEntity*, CEntity*, CVector*, CVector*, CColPoint*, int>(this, owner, victim, startPoint, endPoint, colPoint, arg5);
}

// Converted from thiscall bool CWeapon::TakePhotograph(CEntity *owner, CVector *point) 0x73C1F0
bool CWeapon::TakePhotograph(CEntity* owner, CVector* point) {
    return plugin::CallMethodAndReturn<bool, 0x73C1F0, CWeapon*, CEntity*, CVector*>(this, owner, point);
}

// Converted from thiscall void CWeapon::SetUpPelletCol(int numPellets,CEntity *owner,CEntity *victim,CVector &point,CColPoint &colPoint,CMatrix &outMatrix) 0x73C710
void CWeapon::SetUpPelletCol(int numPellets, CEntity* owner, CEntity* victim, CVector& point, CColPoint& colPoint, CMatrix& outMatrix) {
    plugin::CallMethod<0x73C710, CWeapon*, int, CEntity*, CEntity*, CVector&, CColPoint&, CMatrix&>(this, numPellets, owner, victim, point, colPoint, outMatrix);
}

// Converted from thiscall void CWeapon::FireInstantHitFromCar2(CVector startPoint,CVector endPoint,CVehicle *vehicle,CEntity *owner) 0x73CBA0
void CWeapon::FireInstantHitFromCar2(CVector startPoint, CVector endPoint, CVehicle* vehicle, CEntity* owner) {
    plugin::CallMethod<0x73CBA0, CWeapon*, CVector, CVector, CVehicle*, CEntity*>(this, startPoint, endPoint, vehicle, owner);
}

// Converted from cdecl void CWeapon::DoDoomAiming(CEntity *owner,CVector *start,CVector *end) 0x73CDC0
void CWeapon::DoDoomAiming(CEntity* owner, CVector* start, CVector* end) {
    plugin::Call<0x73CDC0, CEntity*, CVector*, CVector*>(owner, start, end);
}

// Converted from cdecl void CWeapon::DoTankDoomAiming(CEntity *vehicle,CEntity *owner,CVector *startPoint,CVector *endPoint) 0x73D1E0
void CWeapon::DoTankDoomAiming(CEntity* vehicle, CEntity* owner, CVector* startPoint, CVector* endPoint) {
    plugin::Call<0x73D1E0, CEntity*, CEntity*, CVector*, CVector*>(vehicle, owner, startPoint, endPoint);
}

// Converted from cdecl void CWeapon::DoDriveByAutoAiming(CEntity *owner,CVehicle *vehicle,CVector *startPoint,CVector *endPoint,bool canAimVehicles) 0x73D720
void CWeapon::DoDriveByAutoAiming(CEntity* owner, CVehicle* vehicle, CVector* startPoint, CVector* endPoint, bool canAimVehicles) {
    plugin::Call<0x73D720, CEntity*, CVehicle*, CVector*, CVector*, bool>(owner, vehicle, startPoint, endPoint, canAimVehicles);
}

// Converted from thiscall void CWeapon::Update(CPed *owner) 0x73DB40
void CWeapon::Update(CPed* owner) {
    plugin::CallMethod<0x73DB40, CWeapon*, CPed*>(this, owner);
}

// Converted from thiscall bool CWeapon::CanBeUsedFor2Player(void) 0x73DEF0
bool CWeapon::CanBeUsedFor2Player() {
    return plugin::CallMethodAndReturn<bool, 0x73DEF0, CWeapon*>(this);
}

// Converted from cdecl void CWeapon::FindNearestTargetEntityWithScreenCoors(float screenX,float screenY,float range,CVector point,float *outX,float *outY) 0x73E240
void CWeapon::FindNearestTargetEntityWithScreenCoors(float screenX, float screenY, float range, CVector point, float* outX, float* outY) {
    plugin::Call<0x73E240, float, float, float, CVector, float*, float*>(screenX, screenY, range, point, outX, outY);
}

// Converted from cdecl float CWeapon::EvaluateTargetForHeatSeekingMissile(CEntity *entity,CVector &posn,CVector &direction,float distanceMultiplier,bool fromVehicle,CEntity *lastEntity) 0x73E560
float CWeapon::EvaluateTargetForHeatSeekingMissile(CEntity* entity, CVector& posn, CVector& direction, float distanceMultiplier, bool fromVehicle, CEntity* lastEntity) {
    return plugin::CallAndReturn<float, 0x73E560, CEntity*, CVector&, CVector&, float, bool, CEntity*>(entity, posn, direction, distanceMultiplier, fromVehicle, lastEntity);
}

// Converted from thiscall void CWeapon::DoWeaponEffect(CVector origin,CVector target) 0x73E690
void CWeapon::DoWeaponEffect(CVector origin, CVector target) {
    plugin::CallMethod<0x73E690, CWeapon*, CVector, CVector>(this, origin, target);
}

// Converted from thiscall bool CWeapon::FireAreaEffect(CEntity *firingEntity,CVector *origin, CEntity *targetEntity, CVector *target) 0x73E800
bool CWeapon::FireAreaEffect(CEntity* firingEntity, CVector* origin, CEntity* targetEntity, CVector* target) {
    return plugin::CallMethodAndReturn<bool, 0x73E800, CWeapon*, CEntity*, CVector*, CEntity*, CVector*>(this, firingEntity, origin, targetEntity, target);
}

// Converted from thiscall bool CWeapon::FireInstantHitFromCar(CVehicle *vehicle,bool leftSide,bool rightSide) 0x73EC40
bool CWeapon::FireInstantHitFromCar(CVehicle* vehicle, bool leftSide, bool rightSide) {
    return plugin::CallMethodAndReturn<bool, 0x73EC40, CWeapon*, CVehicle*, bool, bool>(this, vehicle, leftSide, rightSide);
}

// Converted from cdecl bool CWeapon::CheckForShootingVehicleOccupant(CEntity **pCarEntity,CColPoint *colPoint,eWeaponType weaponType,CVector const&origin,CVector const&target) 0x73F480
bool CWeapon::CheckForShootingVehicleOccupant(CEntity** pCarEntity, CColPoint* colPoint, eWeaponType weaponType, CVector const& origin, CVector const& target) {
    return plugin::CallAndReturn<bool, 0x73F480, CEntity**, CColPoint*, eWeaponType, CVector const&, CVector const&>(pCarEntity, colPoint, weaponType, origin, target);
}

// Converted from cdecl CEntity* CWeapon::PickTargetForHeatSeekingMissile(CVector origin,CVector direction,float distanceMultiplier,CEntity *ignoreEntity,bool fromVehicle,CEntity *lastEntity) 0x73F910
CEntity* CWeapon::PickTargetForHeatSeekingMissile(CVector origin, CVector direction, float distanceMultiplier, CEntity* ignoreEntity, bool fromVehicle, CEntity* lastEntity) {
    return plugin::CallAndReturn<CEntity*, 0x73F910, CVector, CVector, float, CEntity*, bool, CEntity*>(origin, direction, distanceMultiplier, ignoreEntity, fromVehicle, lastEntity);
}

// Converted from thiscall void CWeapon::FireFromCar(CVehicle *vehicle,bool leftSide,bool rightSide) 0x73FA20
void CWeapon::FireFromCar(CVehicle* vehicle, bool leftSide, bool rightSide) {
    plugin::CallMethod<0x73FA20, CWeapon*, CVehicle*, bool, bool>(this, vehicle, leftSide, rightSide);
}

// Converted from thiscall bool CWeapon::FireInstantHit(CEntity *firingEntity,CVector *origin, CVector *muzzlePosn, CEntity *targetEntity, CVector *target, CVector *originForDriveBy, bool, bool muzzle) 0x73FB10
bool CWeapon::FireInstantHit(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity, CVector* target, CVector* originForDriveBy, bool arg6, bool muzzle) {
    return plugin::CallMethodAndReturn<bool, 0x73FB10, CWeapon*, CEntity*, CVector*, CVector*, CEntity*, CVector*, CVector*, bool, bool>(this, firingEntity, origin, muzzlePosn, targetEntity, target, originForDriveBy, arg6, muzzle);
}

// Converted from thiscall bool CWeapon::FireProjectile(CEntity *firingEntity,CVector *origin, CEntity *targetEntity, CVector *target,float force) 0x741360
bool CWeapon::FireProjectile(CEntity* firingEntity, CVector* origin, CEntity* targetEntity, CVector* target, float force) {
    return plugin::CallMethodAndReturn<bool, 0x741360, CWeapon*, CEntity*, CVector*, CEntity*, CVector*, float>(this, firingEntity, origin, targetEntity, target, force);
}

// Converted from thiscall bool CWeapon::FireM16_1stPerson(CEntity *owner) 0x741C00
bool CWeapon::FireM16_1stPerson(CEntity* owner) {
    return plugin::CallMethodAndReturn<bool, 0x741C00, CWeapon*, CEntity*>(this, owner);
}

// Converted from thiscall bool CWeapon::Fire(CEntity *firingEntity,CVector *origin, CVector *muzzlePosn, CEntity *targetEntity, CVector *target, CVector *originForDriveBy) 0x742300
bool CWeapon::Fire(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity, CVector* target, CVector* originForDriveBy) {
    return plugin::CallMethodAndReturn<bool, 0x742300, CWeapon*, CEntity*, CVector*, CVector*, CEntity*, CVector*, CVector*>(this, firingEntity, origin, muzzlePosn, targetEntity, target, originForDriveBy);
}