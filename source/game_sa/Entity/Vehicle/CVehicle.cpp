/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

float& CVehicle::WHEELSPIN_TARGET_RATE = *(float*)0x8D3498;
float& CVehicle::WHEELSPIN_INAIR_TARGET_RATE = *(float*)0x8D349C;
float& CVehicle::WHEELSPIN_RISE_RATE = *(float*)0x8D34A0;
float& CVehicle::WHEELSPIN_FALL_RATE = *(float*)0x8D34A4;
float& CVehicle::m_fAirResistanceMult = *(float*)0x8D34A8;
float& CVehicle::ms_fRailTrackResistance = *(float*)0x8D34AC;
float& CVehicle::ms_fRailTrackResistanceDefault = *(float*)0x8D34B0;
bool& CVehicle::bDisableRemoteDetonation = *(bool*)0xC1CC00;
bool& CVehicle::bDisableRemoteDetonationOnContact = *(bool*)0xC1CC01;
bool& CVehicle::m_bEnableMouseSteering = *(bool*)0xC1CC02;
bool& CVehicle::m_bEnableMouseFlying = *(bool*)0xC1CC03;
int& CVehicle::m_nLastControlInput = *(int*)0xC1CC04;
CColModel** CVehicle::m_aSpecialColVehicle = (CColModel * *)0xC1CC08;
bool& CVehicle::ms_forceVehicleLightsOff = *(bool*)0xC1CC18;
bool& CVehicle::s_bPlaneGunsEjectShellCasings = *(bool*)0xC1CC19;
CColModel* CVehicle::m_aSpecialColModel = (CColModel*)0xC1CC78;
float& fBurstTyreMod = *(float*)0x8D34B4;
float& fBurstSpeedMax = *(float*)0x8D34B8;
float& CAR_NOS_EXTRA_SKID_LOSS = *(float*)0x8D34BC;
float& WS_TRAC_FRAC_LIMIT = *(float*)0x8D34C0;
float& WS_ALREADY_SPINNING_LOSS = *(float*)0x8D34C4;
float& fBurstBikeTyreMod = *(float*)0x8D34C8;
float& fBurstBikeSpeedMax = *(float*)0x8D34CC;
float& fTweakBikeWheelTurnForce = *(float*)0x8D34D0;
float& AUTOGYRO_ROTORSPIN_MULT = *(float*)0x8D34D4;
float& AUTOGYRO_ROTORSPIN_MULTLIMIT = *(float*)0x8D34D8;
float& AUTOGYRO_ROTORSPIN_DAMP = *(float*)0x8D34DC;
float& AUTOGYRO_ROTORLIFT_MULT = *(float*)0x8D34E0;
float& AUTOGYRO_ROTORLIFT_FALLOFF = *(float*)0x8D34E4;
float& AUTOGYRO_ROTORTILT_ANGLE = *(float*)0x8D34E8;
float& ROTOR_SEMI_THICKNESS = *(float*)0x8D34EC;
float* fSpeedMult = (float*)0x8D34F8;
float& fDamagePosSpeedShift = *(float*)0x8D3510;
unsigned int* aDriveAnimIdsLow = (unsigned int*)0x8D3514;
unsigned int* aDriveAnimIdsBoat = (unsigned int*)0x8D3524;
unsigned int* aDriveAnimIdsBad = (unsigned int*)0x8D3534;
unsigned int* aDriveAnimIdsBadSlow = (unsigned int*)0x8D3544;
unsigned int* aDriveAnimIdsStd = (unsigned int*)0x8D3554;
unsigned int* aDriveAnimIdsStdSlow = (unsigned int*)0x8D3564;
unsigned int* aDriveAnimIdsPro = (unsigned int*)0x8D3574;
unsigned int* aDriveAnimIdsProSlow = (unsigned int*)0x8D3584;
unsigned int* aDriveAnimIdsTruck = (unsigned int*)0x8D3594;
unsigned int* aDriveAnimIdsKart = (unsigned int*)0x8D35A4;
float& DIFF_LIMIT = *(float*)0x8D35B4;
float& DIFF_SPRING_MULT_X = *(float*)0x8D35B8;
float& DIFF_SPRING_MULT_Y = *(float*)0x8D35BC;
float& DIFF_SPRING_MULT_Z = *(float*)0x8D35C0;
float& DIFF_SPRING_COMPRESS_MULT = *(float*)0x8D35C4;
CVector* VehicleGunOffset = (CVector*)0x8D35D4;
char*& HandlingFilename = *(char**)0x8D3970;
char(*VehicleNames)[14] = (char(*)[14])0x8D3978;

void CVehicle::InjectHooks()
{
    HookInstall(0x6D1C40, (bool(CVehicle::*)(CPed*))(&CVehicle::IsDriver), 7);
    HookInstall(0x6D1C60, (bool(CVehicle::*)(int))(&CVehicle::IsDriver), 7);
    HookInstall(0x6DE240, &CVehicle::AddExhaustParticles, 7);
}

void* CVehicle::operator new(unsigned int size) {
    return ((void* (__cdecl*)(unsigned int))0x6E2D50)(size);
}

void CVehicle::operator delete(void* data) {
    ((void(__cdecl*)(void*))0x6E2D90)(data);
}

// Converted from void CVehicle::ProcessControlCollisionCheck(void) 0x871EDC
void CVehicle::ProcessControlCollisionCheck()
{
    ((void(__thiscall*)(CVehicle*))(*(void***)this)[23])(this);
}

// Converted from void CVehicle::ProcessControlInputs(uchar playerNum) 0x871EE0
void CVehicle::ProcessControlInputs(unsigned char playerNum)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))(*(void***)this)[24])(this, playerNum);
}

// Converted from void CVehicle::GetComponentWorldPosition(int componentId,CVector &posnOut) 0x871EE4
void CVehicle::GetComponentWorldPosition(int componentId, CVector& posnOut)
{
    ((void(__thiscall*)(CVehicle*, int, CVector&))(*(void***)this)[25])(this, componentId, posnOut);
}

// Converted from bool CVehicle::IsComponentPresent(int componentId) 0x871EE8
bool CVehicle::IsComponentPresent(int componentId)
{
    return ((bool(__thiscall*)(CVehicle*, int))(*(void***)this)[26])(this, componentId);
}

// Converted from void CVehicle::OpenDoor(CPed *ped,int componentId,eDoors door,float doorOpenRatio,bool playSound) 0x871EEC
void CVehicle::OpenDoor(CPed* ped, int componentId, eDoors door, float doorOpenRatio, bool playSound)
{
    ((void(__thiscall*)(CVehicle*, CPed*, int, eDoors, float, bool))(*(void***)this)[27])(this, ped, componentId, door, doorOpenRatio, playSound);
}

// Converted from void CVehicle::ProcessOpenDoor(CPed *ped,uint doorComponentId,uint,uint,float) 0x871EF0
void CVehicle::ProcessOpenDoor(CPed* ped, unsigned int doorComponentId, unsigned int arg2, unsigned int arg3, float arg4)
{
    ((void(__thiscall*)(CVehicle*, CPed*, unsigned int, unsigned int, unsigned int, float))(*(void***)this)[28])(this, ped, doorComponentId, arg2, arg3, arg4);
}

// Converted from float CVehicle::GetDooorAngleOpenRatio(uint door) 0x871EF4
float CVehicle::GetDooorAngleOpenRatio(unsigned int door)
{
    return ((float(__thiscall*)(CVehicle*, unsigned int))(*(void***)this)[29])(this, door);
}

// Converted from float CVehicle::GetDooorAngleOpenRatio(eDoors door) 0x871EF8
float CVehicle::GetDooorAngleOpenRatio(eDoors door)
{
    return ((float(__thiscall*)(CVehicle*, eDoors))(*(void***)this)[30])(this, door);
}

// Converted from bool CVehicle::IsDoorReady(uint door) 0x871EFC
bool CVehicle::IsDoorReady(unsigned int door)
{
    return ((bool(__thiscall*)(CVehicle*, unsigned int))(*(void***)this)[31])(this, door);
}

// Converted from bool CVehicle::IsDoorReady(eDoors door) 0x871F00
bool CVehicle::IsDoorReady(eDoors door)
{
    return ((bool(__thiscall*)(CVehicle*, eDoors))(*(void***)this)[32])(this, door);
}

// Converted from bool CVehicle::IsDoorFullyOpen(uint door) 0x871F04
bool CVehicle::IsDoorFullyOpen(unsigned int door)
{
    return ((bool(__thiscall*)(CVehicle*, unsigned int))(*(void***)this)[33])(this, door);
}

// Converted from bool CVehicle::IsDoorFullyOpen(eDoors door) 0x871F08
bool CVehicle::IsDoorFullyOpen(eDoors door)
{
    return ((bool(__thiscall*)(CVehicle*, eDoors))(*(void***)this)[34])(this, door);
}

// Converted from bool CVehicle::IsDoorClosed(uint door) 0x871F0C
bool CVehicle::IsDoorClosed(unsigned int door)
{
    return ((bool(__thiscall*)(CVehicle*, unsigned int))(*(void***)this)[35])(this, door);
}

// Converted from bool CVehicle::IsDoorClosed(eDoors door) 0x871F10
bool CVehicle::IsDoorClosed(eDoors door)
{
    return ((bool(__thiscall*)(CVehicle*, eDoors))(*(void***)this)[36])(this, door);
}

// Converted from bool CVehicle::IsDoorMissing(uint door) 0x871F14
bool CVehicle::IsDoorMissing(unsigned int door)
{
    return ((bool(__thiscall*)(CVehicle*, unsigned int))(*(void***)this)[37])(this, door);
}

// Converted from bool CVehicle::IsDoorMissing(eDoors door) 0x871F18
bool CVehicle::IsDoorMissing(eDoors door)
{
    return ((bool(__thiscall*)(CVehicle*, eDoors))(*(void***)this)[38])(this, door);
}

// Converted from bool CVehicle::IsOpenTopCar(void) 0x871F1C
bool CVehicle::IsOpenTopCar()
{
    return ((bool(__thiscall*)(CVehicle*))(*(void***)this)[39])(this);
}

// Converted from void CVehicle::RemoveRefsToVehicle(CEntity *entity) 0x871F20
void CVehicle::RemoveRefsToVehicle(CEntity* entity)
{
    ((void(__thiscall*)(CVehicle*, CEntity*))(*(void***)this)[40])(this, entity);
}

// Converted from void CVehicle::BlowUpCar(CEntity *damager,uchar bHideExplosion) 0x871F24
void CVehicle::BlowUpCar(CEntity* damager, unsigned char bHideExplosion)
{
    ((void(__thiscall*)(CVehicle*, CEntity*, unsigned char))(*(void***)this)[41])(this, damager, bHideExplosion);
}

// Converted from void CVehicle::BlowUpCarCutSceneNoExtras(bool bNoCamShake, bool bNoSpawnFlyingComps, bool bDetachWheels, bool bExplosionSound) 0x871F28
void CVehicle::BlowUpCarCutSceneNoExtras(bool bNoCamShake, bool bNoSpawnFlyingComps, bool bDetachWheels, bool bExplosionSound)
{
    ((void(__thiscall*)(CVehicle*, bool, bool, bool, bool))(*(void***)this)[42])(this, bNoCamShake, bNoSpawnFlyingComps, bDetachWheels, bExplosionSound);
}

// Converted from bool CVehicle::SetUpWheelColModel(CColModel *wheelCol) 0x871F2C
bool CVehicle::SetUpWheelColModel(CColModel* wheelCol)
{
    return ((bool(__thiscall*)(CVehicle*, CColModel*))(*(void***)this)[43])(this, wheelCol);
}

// Converted from bool CVehicle::BurstTyre(uchar tyreComponentId,bool bPhysicalEffect) 0x871F30
bool CVehicle::BurstTyre(unsigned char tyreComponentId, bool bPhysicalEffect)
{
    return ((bool(__thiscall*)(CVehicle*, unsigned char, bool))(*(void***)this)[44])(this, tyreComponentId, bPhysicalEffect);
}

// Converted from bool CVehicle::IsRoomForPedToLeaveCar(uint,CVector *) 0x871F34
bool CVehicle::IsRoomForPedToLeaveCar(unsigned int arg0, CVector* arg1)
{
    return ((bool(__thiscall*)(CVehicle*, unsigned int, CVector*))(*(void***)this)[45])(this, arg0, arg1);
}

// Converted from void CVehicle::ProcessDrivingAnims(CPed *driver,uchar) 0x871F38
void CVehicle::ProcessDrivingAnims(CPed* driver, unsigned char arg1)
{
    ((void(__thiscall*)(CVehicle*, CPed*, unsigned char))(*(void***)this)[46])(this, driver, arg1);
}

// Converted from CRideAnimData* CVehicle::GetRideAnimData(void) 0x871F3C
CRideAnimData* CVehicle::GetRideAnimData()
{
    return ((CRideAnimData * (__thiscall*)(CVehicle*))(*(void***)this)[47])(this);
}

// Converted from void CVehicle::SetupSuspensionLines(void) 0x871F40
void CVehicle::SetupSuspensionLines()
{
    ((void(__thiscall*)(CVehicle*))(*(void***)this)[48])(this);
}

// Converted from CVector CVehicle::AddMovingCollisionSpeed(CVector &) 0x871F44
CVector* CVehicle::AddMovingCollisionSpeed(CVector* out, CVector& vecDistance)
{
    return ((CVector * (__thiscall*)(CVehicle*, CVector*, CVector&))(*(void***)this)[49])(this, out, vecDistance);
}

// Converted from void CVehicle::Fix(void) 0x871F48
void CVehicle::Fix()
{
    ((void(__thiscall*)(CVehicle*))(*(void***)this)[50])(this);
}

// Converted from void CVehicle::SetupDamageAfterLoad(void) 0x871F4C
void CVehicle::SetupDamageAfterLoad()
{
    ((void(__thiscall*)(CVehicle*))(*(void***)this)[51])(this);
}

// Converted from void CVehicle::DoBurstAndSoftGroundRatios(void) 0x871F50
void CVehicle::DoBurstAndSoftGroundRatios()
{
    ((void(__thiscall*)(CVehicle*))(*(void***)this)[52])(this);
}

// Converted from float CVehicle::GetHeightAboveRoad(void) 0x871F54
float CVehicle::GetHeightAboveRoad()
{
    return ((float(__thiscall*)(CVehicle*))(*(void***)this)[53])(this);
}

// Converted from void CVehicle::PlayCarHorn(void) 0x871F58
void CVehicle::PlayCarHorn()
{
    ((void(__thiscall*)(CVehicle*))(*(void***)this)[54])(this);
}

// Converted from int CVehicle::GetNumContactWheels(void) 0x871F5C
int CVehicle::GetNumContactWheels()
{
    return ((int(__thiscall*)(CVehicle*))(*(void***)this)[55])(this);
}

// Converted from void CVehicle::VehicleDamage(float damageIntensity,ushort collisionComponent,CEntity *damager,CVector *vecCollisionCoors,CVector *vecCollisionDirection,eWeaponType weapon) 0x871F60
void CVehicle::VehicleDamage(float damageIntensity, unsigned short collisionComponent, CEntity* damager, CVector* vecCollisionCoors, CVector* vecCollisionDirection, eWeaponType weapon)
{
    ((void(__thiscall*)(CVehicle*, float, unsigned short, CEntity*, CVector*, CVector*, eWeaponType))(*(void***)this)[56])(this, damageIntensity, collisionComponent, damager, vecCollisionCoors, vecCollisionDirection, weapon);
}

// Converted from bool CVehicle::CanPedStepOutCar(bool) 0x871F64
bool CVehicle::CanPedStepOutCar(bool arg0)
{
    return ((bool(__thiscall*)(CVehicle*, bool))(*(void***)this)[57])(this, arg0);
}

// Converted from bool CVehicle::CanPedJumpOutCar(CPed *ped) 0x871F68
bool CVehicle::CanPedJumpOutCar(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))(*(void***)this)[58])(this, ped);
}

// Converted from bool CVehicle::GetTowHitchPos(CVector &posnOut,bool,CVehicle*) 0x871F6C
bool CVehicle::GetTowHitchPos(CVector& posnOut, bool arg1, CVehicle* arg2)
{
    return ((bool(__thiscall*)(CVehicle*, CVector&, bool, CVehicle*))(*(void***)this)[59])(this, posnOut, arg1, arg2);
}

// Converted from bool CVehicle::GetTowBarPos(CVector &posnOut,bool,CVehicle*) 0x871F70
bool CVehicle::GetTowBarPos(CVector& posnOut, bool arg1, CVehicle* arg2)
{
    return ((bool(__thiscall*)(CVehicle*, CVector&, bool, CVehicle*))(*(void***)this)[60])(this, posnOut, arg1, arg2);
}

// Converted from bool CVehicle::SetTowLink(CVehicle*,bool) 0x871F74
bool CVehicle::SetTowLink(CVehicle* arg0, bool arg1)
{
    return ((bool(__thiscall*)(CVehicle*, CVehicle*, bool))(*(void***)this)[61])(this, arg0, arg1);
}

// Converted from bool CVehicle::BreakTowLink(void) 0x871F78
bool CVehicle::BreakTowLink()
{
    return ((bool(__thiscall*)(CVehicle*))(*(void***)this)[62])(this);
}

// Converted from float CVehicle::FindWheelWidth(bool bRear) 0x871F7C
float CVehicle::FindWheelWidth(bool bRear)
{
    return ((float(__thiscall*)(CVehicle*, bool))(*(void***)this)[63])(this, bRear);
}

// Converted from bool CVehicle::Save(void) 0x871F80
bool CVehicle::Save()
{
    return ((bool(__thiscall*)(CVehicle*))(*(void***)this)[64])(this);
}

// Converted from bool CVehicle::Load(void) 0x871F84
bool CVehicle::Load()
{
    return ((bool(__thiscall*)(CVehicle*))(*(void***)this)[65])(this);
}

// Converted from stdcall void CVehicle::Shutdown(void) 0x6D0B40
void CVehicle::Shutdown()
{
    ((void(__cdecl*)())0x6D0B40)();
}

// Converted from thiscall int CVehicle::GetRemapIndex(void) 0x6D0B70
int CVehicle::GetRemapIndex()
{
    return ((int(__thiscall*)(CVehicle*))0x6D0B70)(this);
}

// Converted from thiscall void CVehicle::SetRemapTexDictionary(int txdId) 0x6D0BC0
void CVehicle::SetRemapTexDictionary(int txdId)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D0BC0)(this, txdId);
}

// Converted from thiscall void CVehicle::SetRemap(int remapIndex) 0x6D0C00
void CVehicle::SetRemap(int remapIndex)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D0C00)(this, remapIndex);
}

// Converted from thiscall void CVehicle::SetCollisionLighting(uchar lighting) 0x6D0CA0
void CVehicle::SetCollisionLighting(unsigned char lighting)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D0CA0)(this, lighting);
}

// Converted from thiscall void CVehicle::UpdateLightingFromStoredPolys(void) 0x6D0CC0
void CVehicle::UpdateLightingFromStoredPolys()
{
    ((void(__thiscall*)(CVehicle*))0x6D0CC0)(this);
}

// Converted from thiscall void CVehicle::CalculateLightingFromCollision(void) 0x6D0CF0
void CVehicle::CalculateLightingFromCollision()
{
    ((void(__thiscall*)(CVehicle*))0x6D0CF0)(this);
}

// Converted from thiscall void CVehicle::ResetAfterRender(void) 0x6D0E20
void CVehicle::ResetAfterRender()
{
    ((void(__thiscall*)(CVehicle*))0x6D0E20)(this);
}

// Converted from thiscall int CVehicle::GetVehicleAppearance(void) 0x6D1080
int CVehicle::GetVehicleAppearance()
{
    return ((int(__thiscall*)(CVehicle*))0x6D1080)(this);
}

// Converted from thiscall bool CVehicle::CustomCarPlate_TextureCreate(CVehicleModelInfo *model) 0x6D10E0
bool CVehicle::CustomCarPlate_TextureCreate(CVehicleModelInfo* model)
{
    return ((bool(__thiscall*)(CVehicle*, CVehicleModelInfo*))0x6D10E0)(this, model);
}

// Converted from thiscall void CVehicle::CustomCarPlate_TextureDestroy(void) 0x6D1150
void CVehicle::CustomCarPlate_TextureDestroy()
{
    ((void(__thiscall*)(CVehicle*))0x6D1150)(this);
}

// Converted from thiscall bool CVehicle::CanBeDeleted(void) 0x6D1180
bool CVehicle::CanBeDeleted()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1180)(this);
}

// Converted from thiscall float CVehicle::ProcessWheelRotation(tWheelState wheelState,CVector const&,CVector const&,float) 0x6D1230
float CVehicle::ProcessWheelRotation(tWheelState wheelState, CVector const& arg1, CVector const& arg2, float arg3)
{
    return ((float(__thiscall*)(CVehicle*, tWheelState, CVector const&, CVector const&, float))0x6D1230)(this, wheelState, arg1, arg2, arg3);
}

// Converted from thiscall bool CVehicle::CanVehicleBeDamaged(CEntity *damager,eWeaponType weapon,uchar *) 0x6D1280
bool CVehicle::CanVehicleBeDamaged(CEntity* damager, eWeaponType weapon, unsigned char* arg2)
{
    return ((bool(__thiscall*)(CVehicle*, CEntity*, eWeaponType, unsigned char*))0x6D1280)(this, damager, weapon, arg2);
}

// Converted from thiscall void CVehicle::ProcessDelayedExplosion(void) 0x6D1340
void CVehicle::ProcessDelayedExplosion()
{
    ((void(__thiscall*)(CVehicle*))0x6D1340)(this);
}

// Converted from thiscall bool CVehicle::AddPassenger(CPed *passenger) 0x6D13A0
bool CVehicle::AddPassenger(CPed* passenger)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D13A0)(this, passenger);
}

// Converted from thiscall bool CVehicle::AddPassenger(CPed *passenger,uchar seatNumber) 0x6D14D0
bool CVehicle::AddPassenger(CPed* passenger, unsigned char seatNumber)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*, unsigned char))0x6D14D0)(this, passenger, seatNumber);
}

// Converted from thiscall void CVehicle::RemovePassenger(CPed *passenger) 0x6D1610
void CVehicle::RemovePassenger(CPed* passenger)
{
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D1610)(this, passenger);
}

// Converted from thiscall void CVehicle::SetDriver(CPed *driver) 0x6D16A0
void CVehicle::SetDriver(CPed* driver)
{
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D16A0)(this, driver);
}

// Converted from thiscall void CVehicle::RemoveDriver(bool) 0x6D1950
void CVehicle::RemoveDriver(bool arg0)
{
    ((void(__thiscall*)(CVehicle*, bool))0x6D1950)(this, arg0);
}

// Converted from thiscall CPed* CVehicle::SetUpDriver(int pedType,bool,bool) 0x6D1A50
CPed* CVehicle::SetUpDriver(int pedType, bool arg1, bool arg2)
{
    return ((CPed * (__thiscall*)(CVehicle*, int, bool, bool))0x6D1A50)(this, pedType, arg1, arg2);
}

// Converted from thiscall CPed* CVehicle::SetupPassenger(int seatNumber,int pedType,bool,bool) 0x6D1AA0
CPed* CVehicle::SetupPassenger(int seatNumber, int pedType, bool arg2, bool arg3)
{
    return ((CPed * (__thiscall*)(CVehicle*, int, int, bool, bool))0x6D1AA0)(this, seatNumber, pedType, arg2, arg3);
}

// Converted from thiscall bool CVehicle::IsPassenger(CPed *ped) 0x6D1BD0
bool CVehicle::IsPassenger(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D1BD0)(this, ped);
}

// Converted from thiscall bool CVehicle::IsPassenger(int modelIndex) 0x6D1C00
bool CVehicle::IsPassenger(int modelIndex)
{
    return ((bool(__thiscall*)(CVehicle*, int))0x6D1C00)(this, modelIndex);
}

bool CVehicle::IsDriver(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
  return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D1C40)(this, ped);
#else
    if (ped)
        return ped == m_pDriver;
    return false;
#endif
}

bool CVehicle::IsDriver(int modelIndex)
{
#ifdef USE_DEFAULT_FUNCTIONS
  return ((bool(__thiscall*)(CVehicle*, int))0x6D1C60)(this, modelIndex);
#else
    return m_pDriver && m_pDriver->m_nModelIndex == modelIndex;
#endif
}

// Converted from thiscall void CVehicle::KillPedsInVehicle(void) 0x6D1C80
void CVehicle::KillPedsInVehicle()
{
    ((void(__thiscall*)(CVehicle*))0x6D1C80)(this);
}

// Converted from thiscall bool CVehicle::IsUpsideDown(void) 0x6D1D90
bool CVehicle::IsUpsideDown()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1D90)(this);
}

// Converted from thiscall bool CVehicle::IsOnItsSide(void) 0x6D1DD0
bool CVehicle::IsOnItsSide()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1DD0)(this);
}

// Converted from thiscall bool CVehicle::CanPedOpenLocks(CPed *ped) 0x6D1E20
bool CVehicle::CanPedOpenLocks(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D1E20)(this, ped);
}

// Converted from thiscall bool CVehicle::CanDoorsBeDamaged(void) 0x6D1E60
bool CVehicle::CanDoorsBeDamaged()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1E60)(this);
}

// Converted from thiscall bool CVehicle::CanPedEnterCar(void) 0x6D1E80
bool CVehicle::CanPedEnterCar()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1E80)(this);
}

// Converted from thiscall void CVehicle::ProcessCarAlarm(void) 0x6D21F0
void CVehicle::ProcessCarAlarm()
{
    ((void(__thiscall*)(CVehicle*))0x6D21F0)(this);
}

// Converted from stdcall void DestroyVehicleAndDriverAndPassengers(CVehicle *vehicle) 0x6D2250
void DestroyVehicleAndDriverAndPassengers(CVehicle* vehicle)
{
    ((void(__cdecl*)(CVehicle*))0x6D2250)(vehicle);
}

// Converted from thiscall bool CVehicle::IsVehicleNormal(void) 0x6D22F0
bool CVehicle::IsVehicleNormal()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D22F0)(this);
}

// Converted from thiscall void CVehicle::ChangeLawEnforcerState(uchar state) 0x6D2330
void CVehicle::ChangeLawEnforcerState(unsigned char state)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D2330)(this, state);
}

// Converted from thiscall bool CVehicle::IsLawEnforcementVehicle(void) 0x6D2370
bool CVehicle::IsLawEnforcementVehicle()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D2370)(this);
}

// Converted from thiscall bool CVehicle::ShufflePassengersToMakeSpace(void) 0x6D2450
bool CVehicle::ShufflePassengersToMakeSpace()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D2450)(this);
}

// Converted from thiscall void CVehicle::ExtinguishCarFire(void) 0x6D2460
void CVehicle::ExtinguishCarFire()
{
    ((void(__thiscall*)(CVehicle*))0x6D2460)(this);
}

// Converted from thiscall void CVehicle::ActivateBomb(void) 0x6D24F0
void CVehicle::ActivateBomb()
{
    ((void(__thiscall*)(CVehicle*))0x6D24F0)(this);
}

// Converted from thiscall void CVehicle::ActivateBombWhenEntered(void) 0x6D2570
void CVehicle::ActivateBombWhenEntered()
{
    ((void(__thiscall*)(CVehicle*))0x6D2570)(this);
}

// Converted from thiscall bool CVehicle::CarHasRoof(void) 0x6D25D0
bool CVehicle::CarHasRoof()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D25D0)(this);
}

// Converted from thiscall float CVehicle::HeightAboveCeiling(float,eFlightModel) 0x6D2600
float CVehicle::HeightAboveCeiling(float arg0, eFlightModel arg1)
{
    return ((float(__thiscall*)(CVehicle*, float, eFlightModel))0x6D2600)(this, arg0, arg1);
}

// Converted from stdcall RwObject* SetVehicleAtomicVisibilityCB(RwObject *object,void *data) 0x6D2690
RwObject* SetVehicleAtomicVisibilityCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D2690)(object, data);
}

// Converted from stdcall RwFrame* SetVehicleAtomicVisibilityCB(RwFrame *component,void *data) 0x6D26D0
RwFrame* SetVehicleAtomicVisibilityCB(RwFrame* component, void* data)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x6D26D0)(component, data);
}

// Converted from thiscall void CVehicle::SetComponentVisibility(RwFrame *component,uint visibilityState) 0x6D2700
void CVehicle::SetComponentVisibility(RwFrame* component, unsigned int visibilityState)
{
    ((void(__thiscall*)(CVehicle*, RwFrame*, unsigned int))0x6D2700)(this, component, visibilityState);
}

// Converted from thiscall void CVehicle::ApplyBoatWaterResistance(tBoatHandlingData *boatHandling,float) 0x6D2740
void CVehicle::ApplyBoatWaterResistance(tBoatHandlingData* boatHandling, float arg1)
{
    ((void(__thiscall*)(CVehicle*, tBoatHandlingData*, float))0x6D2740)(this, boatHandling, arg1);
}

// Converted from stdcall RpMaterial* SetCompAlphaCB(RpMaterial *material,void *data) 0x6D2950
RpMaterial* SetCompAlphaCB(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x6D2950)(material, data);
}

// Converted from thiscall void CVehicle::SetComponentAtomicAlpha(RpAtomic *atomic,int alpha) 0x6D2960
void CVehicle::SetComponentAtomicAlpha(RpAtomic* atomic, int alpha)
{
    ((void(__cdecl*)(RpAtomic*, int))0x6D2960)(atomic, alpha);
}

// Converted from thiscall void CVehicle::UpdateClumpAlpha(void) 0x6D2980
void CVehicle::UpdateClumpAlpha()
{
    ((void(__thiscall*)(CVehicle*))0x6D2980)(this);
}

// Converted from thiscall void CVehicle::UpdatePassengerList(void) 0x6D29E0
void CVehicle::UpdatePassengerList()
{
    ((void(__thiscall*)(CVehicle*))0x6D29E0)(this);
}

// Converted from thiscall CPed* CVehicle::PickRandomPassenger(void) 0x6D2A10
CPed* CVehicle::PickRandomPassenger()
{
    return ((CPed * (__thiscall*)(CVehicle*))0x6D2A10)(this);
}

// Converted from thiscall void CVehicle::AddDamagedVehicleParticles(void) 0x6D2A80
void CVehicle::AddDamagedVehicleParticles()
{
    ((void(__thiscall*)(CVehicle*))0x6D2A80)(this);
}

// Converted from thiscall void CVehicle::MakeDirty(CColPoint &colPoint) 0x6D2BF0
void CVehicle::MakeDirty(CColPoint& colPoint)
{
    ((void(__thiscall*)(CVehicle*, CColPoint&))0x6D2BF0)(this, colPoint);
}

// Converted from thiscall bool CVehicle::AddWheelDirtAndWater(CColPoint &colPoint,uint,uchar,uchar) 0x6D2D50
bool CVehicle::AddWheelDirtAndWater(CColPoint& colPoint, unsigned int arg1, unsigned char arg2, unsigned char arg3)
{
    return ((bool(__thiscall*)(CVehicle*, CColPoint&, unsigned int, unsigned char, unsigned char))0x6D2D50)(this, colPoint, arg1, arg2, arg3);
}

// Converted from thiscall void CVehicle::SetGettingInFlags(uchar doorId) 0x6D3000
void CVehicle::SetGettingInFlags(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3000)(this, doorId);
}

// Converted from thiscall void CVehicle::SetGettingOutFlags(uchar doorId) 0x6D3020
void CVehicle::SetGettingOutFlags(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3020)(this, doorId);
}

// Converted from thiscall void CVehicle::ClearGettingInFlags(uchar doorId) 0x6D3040
void CVehicle::ClearGettingInFlags(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3040)(this, doorId);
}

// Converted from thiscall void CVehicle::ClearGettingOutFlags(uchar doorId) 0x6D3060
void CVehicle::ClearGettingOutFlags(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3060)(this, doorId);
}

// Converted from thiscall void CVehicle::SetWindowOpenFlag(uchar doorId) 0x6D3080
void CVehicle::SetWindowOpenFlag(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3080)(this, doorId);
}

// Converted from thiscall void CVehicle::ClearWindowOpenFlag(uchar doorId) 0x6D30B0
void CVehicle::ClearWindowOpenFlag(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D30B0)(this, doorId);
}

// Converted from thiscall bool CVehicle::SetVehicleUpgradeFlags(int upgradeModelIndex,int componentIndex,int &resultModelIndex) 0x6D30E0
bool CVehicle::SetVehicleUpgradeFlags(int upgradeModelIndex, int componentIndex, int& resultModelIndex)
{
    return ((bool(__thiscall*)(CVehicle*, int, int, int&))0x6D30E0)(this, upgradeModelIndex, componentIndex, resultModelIndex);
}

// Converted from thiscall bool CVehicle::ClearVehicleUpgradeFlags(int,int componentIndex) 0x6D3210
bool CVehicle::ClearVehicleUpgradeFlags(int arg0, int componentIndex)
{
    return ((bool(__thiscall*)(CVehicle*, int, int))0x6D3210)(this, arg0, componentIndex);
}

// Converted from stdcall RpAtomic* RemoveUpgradeCB(RpAtomic *atomic,void *data) 0x6D3300
RpAtomic* RemoveUpgradeCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D3300)(atomic, data);
}

// Converted from stdcall RpAtomic* FindUpgradeCB(RpAtomic *atomic,void *data) 0x6D3370
RpAtomic* FindUpgradeCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D3370)(atomic, data);
}

// Converted from stdcall RwObject* RemoveObjectsCB(RwObject *object,void *data) 0x6D33B0
RwObject* RemoveObjectsCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D33B0)(object, data);
}

// Converted from stdcall RwFrame* RemoveObjectsCB(RwFrame *component,void *data) 0x6D3420
RwFrame* RemoveObjectsCB(RwFrame* component, void* data)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x6D3420)(component, data);
}

// Converted from stdcall RwObject* CopyObjectsCB(RwObject *object,void *data) 0x6D3450
RwObject* CopyObjectsCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D3450)(object, data);
}

// Converted from stdcall RwObject* FindReplacementUpgradeCB(RwObject *object,void *data) 0x6D3490
RwObject* FindReplacementUpgradeCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D3490)(object, data);
}

// Converted from stdcall RpAtomic* RemoveAllUpgradesCB(RpAtomic *atomic,void *data) 0x6D34D0
RpAtomic* RemoveAllUpgradesCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D34D0)(atomic, data);
}

// Converted from thiscall RpAtomic* CVehicle::CreateUpgradeAtomic(CBaseModelInfo *model,UpgradePosnDesc const*upgradePosn,RwFrame *parentComponent,bool isDamaged) 0x6D3510
RpAtomic* CVehicle::CreateUpgradeAtomic(CBaseModelInfo* model, UpgradePosnDesc const* upgradePosn, RwFrame* parentComponent, bool isDamaged)
{
    return ((RpAtomic * (__thiscall*)(CVehicle*, CBaseModelInfo*, UpgradePosnDesc const*, RwFrame*, bool))0x6D3510)(this, model, upgradePosn, parentComponent, isDamaged);
}

// Converted from thiscall void CVehicle::RemoveUpgrade(int upgradeId) 0x6D3630
void CVehicle::RemoveUpgrade(int upgradeId)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D3630)(this, upgradeId);
}

// Converted from thiscall int CVehicle::GetUpgrade(int upgradeId) 0x6D3650
int CVehicle::GetUpgrade(int upgradeId)
{
    return ((int(__thiscall*)(CVehicle*, int))0x6D3650)(this, upgradeId);
}

// Converted from thiscall RpAtomic* CVehicle::CreateReplacementAtomic(CBaseModelInfo *model,RwFrame *component,int,bool bDamaged,bool bIsWheel) 0x6D3700
RpAtomic* CVehicle::CreateReplacementAtomic(CBaseModelInfo* model, RwFrame* component, int arg2, bool bDamaged, bool bIsWheel)
{
    return ((RpAtomic * (__thiscall*)(CVehicle*, CBaseModelInfo*, RwFrame*, int, bool, bool))0x6D3700)(this, model, component, arg2, bDamaged, bIsWheel);
}

// Converted from thiscall void CVehicle::AddReplacementUpgrade(int modelIndex,int nodeId) 0x6D3830
void CVehicle::AddReplacementUpgrade(int modelIndex, int nodeId)
{
    ((void(__thiscall*)(CVehicle*, int, int))0x6D3830)(this, modelIndex, nodeId);
}

// Converted from thiscall void CVehicle::RemoveReplacementUpgrade(int nodeId) 0x6D39E0
void CVehicle::RemoveReplacementUpgrade(int nodeId)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D39E0)(this, nodeId);
}

// Converted from thiscall void CVehicle::GetReplacementUpgrade(int nodeId) 0x6D3A50
void CVehicle::GetReplacementUpgrade(int nodeId)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D3A50)(this, nodeId);
}

// Converted from thiscall void CVehicle::RemoveAllUpgrades(void) 0x6D3AB0
void CVehicle::RemoveAllUpgrades()
{
    ((void(__thiscall*)(CVehicle*))0x6D3AB0)(this);
}

// Converted from thiscall int CVehicle::GetSpareHasslePosId(void) 0x6D3AE0
int CVehicle::GetSpareHasslePosId()
{
    return ((int(__thiscall*)(CVehicle*))0x6D3AE0)(this);
}

// Converted from thiscall void CVehicle::SetHasslePosId(int hasslePos,bool enable) 0x6D3B30
void CVehicle::SetHasslePosId(int hasslePos, bool enable)
{
    ((void(__thiscall*)(CVehicle*, int, bool))0x6D3B30)(this, hasslePos, enable);
}

// Converted from thiscall void CVehicle::InitWinch(int) 0x6D3B60
void CVehicle::InitWinch(int arg0)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D3B60)(this, arg0);
}

// Converted from thiscall void CVehicle::UpdateWinch(void) 0x6D3B80
void CVehicle::UpdateWinch()
{
    ((void(__thiscall*)(CVehicle*))0x6D3B80)(this);
}

// Converted from thiscall void CVehicle::RemoveWinch(void) 0x6D3C70
void CVehicle::RemoveWinch()
{
    ((void(__thiscall*)(CVehicle*))0x6D3C70)(this);
}

// Converted from thiscall void CVehicle::ReleasePickedUpEntityWithWinch(void) 0x6D3CB0
void CVehicle::ReleasePickedUpEntityWithWinch()
{
    ((void(__thiscall*)(CVehicle*))0x6D3CB0)(this);
}

// Converted from thiscall void CVehicle::PickUpEntityWithWinch(CEntity *) 0x6D3CD0
void CVehicle::PickUpEntityWithWinch(CEntity* arg0)
{
    ((void(__thiscall*)(CVehicle*, CEntity*))0x6D3CD0)(this, arg0);
}

// Converted from thiscall CEntity* CVehicle::QueryPickedUpEntityWithWinch(void) 0x6D3CF0
CEntity* CVehicle::QueryPickedUpEntityWithWinch()
{
    return ((CEntity * (__thiscall*)(CVehicle*))0x6D3CF0)(this);
}

// Converted from thiscall float CVehicle::GetRopeHeightForHeli(void) 0x6D3D10
float CVehicle::GetRopeHeightForHeli()
{
    return ((float(__thiscall*)(CVehicle*))0x6D3D10)(this);
}

// Converted from thiscall void CVehicle::SetRopeHeightForHeli(float height) 0x6D3D30
void CVehicle::SetRopeHeightForHeli(float height)
{
    ((void(__thiscall*)(CVehicle*, float))0x6D3D30)(this, height);
}

// Converted from thiscall void CVehicle::RenderDriverAndPassengers(void) 0x6D3D60
void CVehicle::RenderDriverAndPassengers()
{
    ((void(__thiscall*)(CVehicle*))0x6D3D60)(this);
}

// Converted from thiscall void CVehicle::PreRenderDriverAndPassengers(void) 0x6D3DB0
void CVehicle::PreRenderDriverAndPassengers()
{
    ((void(__thiscall*)(CVehicle*))0x6D3DB0)(this);
}

// Converted from thiscall float CVehicle::GetPlaneGunsAutoAimAngle(void) 0x6D3E00
float CVehicle::GetPlaneGunsAutoAimAngle()
{
    return ((float(__thiscall*)(CVehicle*))0x6D3E00)(this);
}

// Converted from thiscall int CVehicle::GetPlaneNumGuns(void) 0x6D3F30
int CVehicle::GetPlaneNumGuns()
{
    return ((int(__thiscall*)(CVehicle*))0x6D3F30)(this);
}

// Converted from thiscall void CVehicle::SetFiringRateMultiplier(float multiplier) 0x6D4010
void CVehicle::SetFiringRateMultiplier(float multiplier)
{
    ((void(__thiscall*)(CVehicle*, float))0x6D4010)(this, multiplier);
}

// Converted from thiscall float CVehicle::GetFiringRateMultiplier(void) 0x6D4090
float CVehicle::GetFiringRateMultiplier()
{
    return ((float(__thiscall*)(CVehicle*))0x6D4090)(this);
}

// Converted from thiscall unsigned int CVehicle::GetPlaneGunsRateOfFire(void) 0x6D40E0
unsigned int CVehicle::GetPlaneGunsRateOfFire()
{
    return ((unsigned int(__thiscall*)(CVehicle*))0x6D40E0)(this);
}

// Converted from thiscall CVector CVehicle::GetPlaneGunsPosition(int gunId) 0x6D4290
CVector CVehicle::GetPlaneGunsPosition(int gunId)
{
    CVector result;
    ((void(__thiscall*)(CVehicle*, CVector*, int))0x6D4290)(this, &result, gunId);
    return result;
}

// Converted from thiscall unsigned int CVehicle::GetPlaneOrdnanceRateOfFire(eOrdnanceType ordnanceType) 0x6D4590
unsigned int CVehicle::GetPlaneOrdnanceRateOfFire(eOrdnanceType ordnanceType)
{
    return ((unsigned int(__thiscall*)(CVehicle*, eOrdnanceType))0x6D4590)(this, ordnanceType);
}

// Converted from thiscall CVector CVehicle::GetPlaneOrdnancePosition(eOrdnanceType ordnanceType) 0x6D46E0
CVector CVehicle::GetPlaneOrdnancePosition(eOrdnanceType ordnanceType)
{
    CVector result;
    ((void(__thiscall*)(CVehicle*, CVector*, eOrdnanceType))0x6D46E0)(this, &result, ordnanceType);
    return result;
}

// Converted from thiscall void CVehicle::SelectPlaneWeapon(bool bChange,eOrdnanceType ordnanceType) 0x6D4900
void CVehicle::SelectPlaneWeapon(bool bChange, eOrdnanceType ordnanceType)
{
    ((void(__thiscall*)(CVehicle*, bool, eOrdnanceType))0x6D4900)(this, bChange, ordnanceType);
}

// Converted from thiscall void CVehicle::DoPlaneGunFireFX(CWeapon *weapon,CVector &particlePos,CVector &gunshellPos,int particleIndex) 0x6D4AD0
void CVehicle::DoPlaneGunFireFX(CWeapon* weapon, CVector& particlePos, CVector& gunshellPos, int particleIndex)
{
    ((void(__thiscall*)(CVehicle*, CWeapon*, CVector&, CVector&, int))0x6D4AD0)(this, weapon, particlePos, gunshellPos, particleIndex);
}

// Converted from thiscall void CVehicle::FirePlaneGuns(void) 0x6D4D30
void CVehicle::FirePlaneGuns()
{
    ((void(__thiscall*)(CVehicle*))0x6D4D30)(this);
}

// Converted from thiscall void CVehicle::FireUnguidedMissile(eOrdnanceType ordnanceType,bool bCheckTime) 0x6D5110
void CVehicle::FireUnguidedMissile(eOrdnanceType ordnanceType, bool bCheckTime)
{
    ((void(__thiscall*)(CVehicle*, eOrdnanceType, bool))0x6D5110)(this, ordnanceType, bCheckTime);
}

// Converted from thiscall bool CVehicle::CanBeDriven(void) 0x6D5400
bool CVehicle::CanBeDriven()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D5400)(this);
}

// Converted from thiscall void CVehicle::ReactToVehicleDamage(CPed *ped) 0x6D5490
void CVehicle::ReactToVehicleDamage(CPed* ped)
{
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D5490)(this, ped);
}

// Converted from thiscall bool CVehicle::GetVehicleLightsStatus(void) 0x6D55C0
bool CVehicle::GetVehicleLightsStatus()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D55C0)(this);
}

// Converted from thiscall bool CVehicle::CanPedLeanOut(CPed *ped) 0x6D5CF0
bool CVehicle::CanPedLeanOut(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D5CF0)(this, ped);
}

// Converted from thiscall void CVehicle::SetVehicleCreatedBy(int createdBy) 0x6D5D70
void CVehicle::SetVehicleCreatedBy(int createdBy)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D5D70)(this, createdBy);
}

// Converted from thiscall void CVehicle::SetupRender(void) 0x6D64F0
void CVehicle::SetupRender()
{
    ((void(__thiscall*)(CVehicle*))0x6D64F0)(this);
}

// Converted from thiscall void CVehicle::ProcessWheel(CVector &,CVector &,CVector &,CVector &,int,float,float,float,char,float *,tWheelState *,ushort) 0x6D6C00
void CVehicle::ProcessWheel(CVector& arg0, CVector& arg1, CVector& arg2, CVector& arg3, int arg4, float arg5, float arg6, float arg7, char arg8, float* arg9, tWheelState* arg10, unsigned short arg11)
{
    ((void(__thiscall*)(CVehicle*, CVector&, CVector&, CVector&, CVector&, int, float, float, float, char, float*, tWheelState*, unsigned short))0x6D6C00)(this, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
}

// Converted from thiscall void CVehicle::ProcessBikeWheel(CVector &,CVector &,CVector &,CVector &,int,float,float,float,float,char,float *,tWheelState *,eBikeWheelSpecial,ushort) 0x6D73B0
void CVehicle::ProcessBikeWheel(CVector& arg0, CVector& arg1, CVector& arg2, CVector& arg3, int arg4, float arg5, float arg6, float arg7, float arg8, char arg9, float* arg10, tWheelState* arg11, eBikeWheelSpecial arg12, unsigned short arg13)
{
    ((void(__thiscall*)(CVehicle*, CVector&, CVector&, CVector&, CVector&, int, float, float, float, float, char, float*, tWheelState*, eBikeWheelSpecial, unsigned short))0x6D73B0)(this, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
}

// Converted from thiscall int CVehicle::FindTyreNearestPoint(float x,float y) 0x6D7BC0
int CVehicle::FindTyreNearestPoint(float x, float y)
{
    return ((int(__thiscall*)(CVehicle*, float, float))0x6D7BC0)(this, x, y);
}

// Converted from thiscall void CVehicle::InflictDamage(CEntity *damager,eWeaponType weapon,float intensity,CVector coords) 0x6D7C90
void CVehicle::InflictDamage(CEntity* damager, eWeaponType weapon, float intensity, CVector coords)
{
    ((void(__thiscall*)(CVehicle*, CEntity*, eWeaponType, float, CVector))0x6D7C90)(this, damager, weapon, intensity, coords);
}

// Converted from thiscall void CVehicle::KillPedsGettingInVehicle(void) 0x6D82F0
void CVehicle::KillPedsGettingInVehicle()
{
    ((void(__thiscall*)(CVehicle*))0x6D82F0)(this);
}

// Converted from thiscall bool CVehicle::UsesSiren(void) 0x6D8470
bool CVehicle::UsesSiren()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D8470)(this);
}

// Converted from thiscall bool CVehicle::IsSphereTouchingVehicle(float x,float y,float z,float radius) 0x6D84D0
bool CVehicle::IsSphereTouchingVehicle(float x, float y, float z, float radius)
{
    return ((bool(__thiscall*)(CVehicle*, float, float, float, float))0x6D84D0)(this, x, y, z, radius);
}

// Converted from thiscall void CVehicle::FlyingControl(eFlightModel flightModel,float,float,float,float) 0x6D85F0
void CVehicle::FlyingControl(eFlightModel flightModel, float arg1, float arg2, float arg3, float arg4)
{
    ((void(__thiscall*)(CVehicle*, eFlightModel, float, float, float, float))0x6D85F0)(this, flightModel, arg1, arg2, arg3, arg4);
}

// Converted from thiscall void CVehicle::BladeColSectorList(CPtrList &ptrList,CColModel &colModel,CMatrix &matrix,short,float) 0x6DAF00
void CVehicle::BladeColSectorList(CPtrList& ptrList, CColModel& colModel, CMatrix& matrix, short arg3, float arg4)
{
    ((void(__thiscall*)(CVehicle*, CPtrList&, CColModel&, CMatrix&, short, float))0x6DAF00)(this, ptrList, colModel, matrix, arg3, arg4);
}

// Converted from thiscall void CVehicle::SetComponentRotation(RwFrame *component,int axis,float angle,bool bResetPosition) 0x6DBA30
void CVehicle::SetComponentRotation(RwFrame* component, int axis, float angle, bool bResetPosition)
{
    ((void(__thiscall*)(CVehicle*, RwFrame*, int, float, bool))0x6DBA30)(this, component, axis, angle, bResetPosition);
}

// Converted from thiscall void CVehicle::SetTransmissionRotation(RwFrame *component,float,float,CVector posn,bool isFront) 0x6DBBB0
void CVehicle::SetTransmissionRotation(RwFrame* component, float arg1, float arg2, CVector posn, bool isFront)
{
    ((void(__thiscall*)(CVehicle*, RwFrame*, float, float, CVector, bool))0x6DBBB0)(this, component, arg1, arg2, posn, isFront);
}

// Converted from thiscall void CVehicle::ProcessBoatControl(tBoatHandlingData *boatHandling,float &,bool,bool) 0x6DBCE0
void CVehicle::ProcessBoatControl(tBoatHandlingData* boatHandling, float& arg1, bool arg2, bool arg3)
{
    ((void(__thiscall*)(CVehicle*, tBoatHandlingData*, float&, bool, bool))0x6DBCE0)(this, boatHandling, arg1, arg2, arg3);
}

// Converted from thiscall void CVehicle::DoBoatSplashes(float) 0x6DD130
void CVehicle::DoBoatSplashes(float arg0)
{
    ((void(__thiscall*)(CVehicle*, float))0x6DD130)(this, arg0);
}

// Converted from thiscall void CVehicle::DoSunGlare(void) 0x6DD6F0
void CVehicle::DoSunGlare()
{
    ((void(__thiscall*)(CVehicle*))0x6DD6F0)(this);
}

// Converted from thiscall void CVehicle::AddWaterSplashParticles(void) 0x6DDF60
void CVehicle::AddWaterSplashParticles()
{
    ((void(__thiscall*)(CVehicle*))0x6DDF60)(this);
}

// Converted from thiscall void CVehicle::AddExhaustParticles(void) 0x6DE240
void CVehicle::AddExhaustParticles()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CVehicle*))0x6DE240)(this);
#else
    if (m_bOffscreen)
        return;
    float fSquaredMagnitude = (TheCamera.GetPosition() - GetPosition()).SquaredMagnitude();
    if (fSquaredMagnitude > 256.0f || fSquaredMagnitude > 64.0f
        && !((CTimer::m_FrameCounter + static_cast<std::uint8_t>(m_nModelIndex)) & 1))
    {
        return;
    }
    auto pVehicleModelInfo = static_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[m_nModelIndex]);
    CVector firstExhaustPos = pVehicleModelInfo->m_pVehicleStruct->m_avDummyPos[DUMMY_EXHAUST];
    CVector secondExhaustPos = firstExhaustPos;
    secondExhaustPos.x *= -1.0f;
    CMatrix entityMatrix (*m_matrix);
    bool bHasDoubleExhaust = m_pHandlingData->m_bDoubleExhaust;
    if (m_nVehicleSubClass == VEHICLE_BIKE) {
        CBike* pBike = static_cast<CBike*>(this);
        pBike->CalculateLeanMatrix();
        entityMatrix = pBike->m_mLeanMatrix;
        switch (m_nModelIndex)
        {
        case MODEL_FCR900:
            if (m_anExtras[0] == 1 || m_anExtras[0] == 2)
                bHasDoubleExhaust = true;
            break;
        case MODEL_NRG500:
            if (!m_anExtras[0] || m_anExtras[0] == 1)  
                secondExhaustPos = pVehicleModelInfo->m_pVehicleStruct->m_avDummyPos[DUMMY_EXHAUST_SECONDARY];
            break;
        case MODEL_BF400:
            if (m_anExtras[0] == 2)
                bHasDoubleExhaust = true;
            break;
        }
    }
    if (firstExhaustPos != 0.0f) {
        CVector vecParticleVelocity;
        if (DotProduct(m_matrix->up, m_vecMoveSpeed) >= 0.05f) {
            vecParticleVelocity = m_vecMoveSpeed * 30.0f;
        }
        else  {
            static float randomFactor = CGeneral::GetRandomNumberInRange(-1.8f, -0.9f);
            vecParticleVelocity = randomFactor * m_matrix->up;
        }
        firstExhaustPos = entityMatrix * firstExhaustPos;
        bool bFirstExhaustSubmergedInWater = false;
        bool bSecondExhaustSubmergedInWater = false;
        float pLevel = 0.0f;
        if (physicalFlags.bTouchingWater
            && CWaterLevel::GetWaterLevel(firstExhaustPos.x, firstExhaustPos.y, firstExhaustPos.z, &pLevel, true, nullptr)
            && pLevel >= firstExhaustPos.z)
        {
            bFirstExhaustSubmergedInWater = true;
        }
        if (bHasDoubleExhaust) {
            secondExhaustPos = entityMatrix * secondExhaustPos;
            if (physicalFlags.bTouchingWater
                && CWaterLevel::GetWaterLevel(secondExhaustPos.x, secondExhaustPos.y, secondExhaustPos.z, &pLevel, true, nullptr)
                && pLevel >= secondExhaustPos.z)
            {
                bSecondExhaustSubmergedInWater = true;
            }
        }
        if (CGeneral::GetRandomNumberInRange(1.0f, 3.0f) * (m_fGasPedal + 1.1f) > 2.5f) {
            float fMoveSpeed = m_vecMoveSpeed.Magnitude() * 0.5f;
            float particleAlpha = 0.0f;
            if (0.25f - fMoveSpeed >= 0.0f)
                particleAlpha = 0.25f - fMoveSpeed;
            float fLife = std::max(0.2f - fMoveSpeed, 0.0f);
            FxPrtMult_c fxPrt(0.9f, 0.9f, 1.0f, particleAlpha, 0.2f, 1.0f, fLife);
            std::int32_t numExhausts = 2;
            for (std::int32_t i = 0; i < 2; i++) {
                FxSystem_c* pFirstExhaustFxSystem = g_fx.m_pPrtSmokeII3expand;
                if (bFirstExhaustSubmergedInWater) {
                    fxPrt.m_color.alpha = particleAlpha * 0.5f;
                    fxPrt.m_fSize = 0.6f;
                    pFirstExhaustFxSystem = g_fx.m_pPrtBubble;
                }
                pFirstExhaustFxSystem->AddParticle(&firstExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
                if (bHasDoubleExhaust) {
                    FxSystem_c* pSecondExhaustFxSystem = g_fx.m_pPrtSmokeII3expand;
                    if (bSecondExhaustSubmergedInWater)
                    {
                        fxPrt.m_color.alpha = particleAlpha * 0.5f;
                        fxPrt.m_fSize = 0.6f;
                        pSecondExhaustFxSystem = g_fx.m_pPrtBubble;
                    }
                    pSecondExhaustFxSystem->AddParticle(&secondExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
                }
                if (m_fGasPedal > 0.5f && m_nCurrentGear < 3) {
                    if (rand() & 1) {
                        FxSystem_c* pSecondaryExhaustFxSystem = g_fx.m_pPrtSmokeII3expand;
                        if (bFirstExhaustSubmergedInWater)
                        {
                            fxPrt.m_color.alpha = particleAlpha * 0.5f;
                            fxPrt.m_fSize = 0.6f;
                            pSecondaryExhaustFxSystem = g_fx.m_pPrtBubble;
                        }
                        pSecondaryExhaustFxSystem->AddParticle(&firstExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
                    }
                    else if (bHasDoubleExhaust)
                    {
                        FxSystem_c* pSecondaryExhaustFxSystem = g_fx.m_pPrtSmokeII3expand;
                        if (bSecondExhaustSubmergedInWater)
                        {
                            fxPrt.m_color.alpha = particleAlpha * 0.5f;
                            fxPrt.m_fSize = 0.6f;
                            pSecondaryExhaustFxSystem = g_fx.m_pPrtBubble;
                        }
                        pSecondaryExhaustFxSystem->AddParticle(&secondExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
                    }
                }
            }
        }
    }
#endif
}

// Converted from thiscall bool CVehicle::AddSingleWheelParticles(tWheelState,uint,float,float,CColPoint *,CVector *,float,int,uint surfaceType,bool *bloodState,uint) 0x6DE880
bool CVehicle::AddSingleWheelParticles(tWheelState arg0, unsigned int arg1, float arg2, float arg3, CColPoint* arg4, CVector* arg5, float arg6, int arg7, unsigned int surfaceType, bool* bloodState, unsigned int arg10)
{
    return ((bool(__thiscall*)(CVehicle*, tWheelState, unsigned int, float, float, CColPoint*, CVector*, float, int, unsigned int, bool*, unsigned int))0x6DE880)(this, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, surfaceType, bloodState, arg10);
}

// Converted from thiscall bool CVehicle::GetSpecialColModel(void) 0x6DF3D0
bool CVehicle::GetSpecialColModel()
{
    return ((bool(__thiscall*)(CVehicle*))0x6DF3D0)(this);
}

// Converted from thiscall void CVehicle::RemoveVehicleUpgrade(int upgradeModelIndex) 0x6DF930
void CVehicle::RemoveVehicleUpgrade(int upgradeModelIndex)
{
    ((void(__thiscall*)(CVehicle*, int))0x6DF930)(this, upgradeModelIndex);
}

// Converted from thiscall void CVehicle::AddUpgrade(int modelIndex,int upgradeIndex) 0x6DFA20
void CVehicle::AddUpgrade(int modelIndex, int upgradeIndex)
{
    ((void(__thiscall*)(CVehicle*, int, int))0x6DFA20)(this, modelIndex, upgradeIndex);
}

// Converted from thiscall void CVehicle::UpdateTrailerLink(bool,bool) 0x6DFC50
void CVehicle::UpdateTrailerLink(bool arg0, bool arg1)
{
    ((void(__thiscall*)(CVehicle*, bool, bool))0x6DFC50)(this, arg0, arg1);
}

// Converted from thiscall void CVehicle::UpdateTractorLink(bool,bool) 0x6E0050
void CVehicle::UpdateTractorLink(bool arg0, bool arg1)
{
    ((void(__thiscall*)(CVehicle*, bool, bool))0x6E0050)(this, arg0, arg1);
}

// Converted from thiscall CEntity* CVehicle::ScanAndMarkTargetForHeatSeekingMissile(CEntity *entity) 0x6E0400
CEntity* CVehicle::ScanAndMarkTargetForHeatSeekingMissile(CEntity* entity)
{
    return ((CEntity * (__thiscall*)(CVehicle*, CEntity*))0x6E0400)(this, entity);
}

// Converted from thiscall void CVehicle::FireHeatSeakingMissile(CEntity *targetEntity,eOrdnanceType ordnanceType,bool) 0x6E05C0
void CVehicle::FireHeatSeakingMissile(CEntity* targetEntity, eOrdnanceType ordnanceType, bool arg2)
{
    ((void(__thiscall*)(CVehicle*, CEntity*, eOrdnanceType, bool))0x6E05C0)(this, targetEntity, ordnanceType, arg2);
}

// Converted from thiscall void CVehicle::PossiblyDropFreeFallBombForPlayer(eOrdnanceType ordnanceType,bool) 0x6E07E0
void CVehicle::PossiblyDropFreeFallBombForPlayer(eOrdnanceType ordnanceType, bool arg1)
{
    ((void(__thiscall*)(CVehicle*, eOrdnanceType, bool))0x6E07E0)(this, ordnanceType, arg1);
}

// Converted from thiscall void CVehicle::ProcessSirenAndHorn(bool) 0x6E0950
void CVehicle::ProcessSirenAndHorn(bool arg0)
{
    ((void(__thiscall*)(CVehicle*, bool))0x6E0950)(this, arg0);
}

// Converted from thiscall bool CVehicle::DoHeadLightEffect(int dummyId,CMatrix &vehicleMatrix,uchar lightId,uchar lightState) 0x6E0A50
bool CVehicle::DoHeadLightEffect(int dummyId, CMatrix& vehicleMatrix, unsigned char lightId, unsigned char lightState)
{
    return ((bool(__thiscall*)(CVehicle*, int, CMatrix&, unsigned char, unsigned char))0x6E0A50)(this, dummyId, vehicleMatrix, lightId, lightState);
}

// Converted from thiscall void CVehicle::DoHeadLightBeam(int,CMatrix &matrix,uchar) 0x6E0E20
void CVehicle::DoHeadLightBeam(int arg0, CMatrix& matrix, unsigned char arg2)
{
    ((void(__thiscall*)(CVehicle*, int, CMatrix&, unsigned char))0x6E0E20)(this, arg0, matrix, arg2);
}

// Converted from thiscall void CVehicle::DoHeadLightReflectionSingle(CMatrix &matrix,uchar lightId) 0x6E1440
void CVehicle::DoHeadLightReflectionSingle(CMatrix& matrix, unsigned char lightId)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&, unsigned char))0x6E1440)(this, matrix, lightId);
}

// Converted from thiscall void CVehicle::DoHeadLightReflectionTwin(CMatrix &matrix) 0x6E1600
void CVehicle::DoHeadLightReflectionTwin(CMatrix& matrix)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&))0x6E1600)(this, matrix);
}

// Converted from thiscall void CVehicle::DoHeadLightReflection(CMatrix &,uint,uchar,uchar) 0x6E1720
void CVehicle::DoHeadLightReflection(CMatrix& arg0, unsigned int flags, unsigned char left, unsigned char right)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&, unsigned int, unsigned char, unsigned char))0x6E1720)(this, arg0, flags, left, right);
}

// Converted from thiscall bool CVehicle::DoTailLightEffect(int lightId,CMatrix &matrix,uchar,uchar,uint,uchar) 0x6E1780
bool CVehicle::DoTailLightEffect(int lightId, CMatrix& matrix, unsigned char arg2, unsigned char arg3, unsigned int arg4, unsigned char arg5)
{
    return ((bool(__thiscall*)(CVehicle*, int, CMatrix&, unsigned char, unsigned char, unsigned int, unsigned char))0x6E1780)(this, lightId, matrix, arg2, arg3, arg4, arg5);
}

// Converted from thiscall void CVehicle::DoVehicleLights(CMatrix &matrix,uint flags) 0x6E1A60
void CVehicle::DoVehicleLights(CMatrix& matrix, unsigned int flags)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&, unsigned int))0x6E1A60)(this, matrix, flags);
}

// Converted from thiscall void CVehicle::FillVehicleWithPeds(bool bSetClothesToAfro) 0x6E2900
void CVehicle::FillVehicleWithPeds(bool bSetClothesToAfro)
{
    ((void(__thiscall*)(CVehicle*, bool))0x6E2900)(this, bSetClothesToAfro);
}

// Converted from thiscall void CVehicle::DoBladeCollision(CVector,CMatrix &matrix,short,float,float) 0x6E2E50
void CVehicle::DoBladeCollision(CVector arg0, CMatrix& matrix, short arg2, float arg3, float arg4)
{
    ((void(__thiscall*)(CVehicle*, CVector, CMatrix&, short, float, float))0x6E2E50)(this, arg0, matrix, arg2, arg3, arg4);
}

// Converted from thiscall void CVehicle::AddVehicleUpgrade(int modelId) 0x6E3290
void CVehicle::AddVehicleUpgrade(int modelId)
{
    ((void(__thiscall*)(CVehicle*, int))0x6E3290)(this, modelId);
}

// Converted from thiscall void CVehicle::SetupUpgradesAfterLoad(void) 0x6E3400
void CVehicle::SetupUpgradesAfterLoad()
{
    ((void(__thiscall*)(CVehicle*))0x6E3400)(this);
}

// Converted from thiscall void CVehicle::GetPlaneWeaponFiringStatus(bool &status,eOrdnanceType &ordnanceType) 0x6E3440 0x6E38A0
void CVehicle::GetPlaneWeaponFiringStatus(bool& status, eOrdnanceType& ordnanceType)
{
    ((void(__thiscall*)(CVehicle*, bool&, eOrdnanceType&))0x6E3440)(this, status, ordnanceType);
}

// Converted from stdcall bool IsVehiclePointerValid(CVehicle *vehicle) 0x6E38F0
bool IsVehiclePointerValid(CVehicle* vehicle)
{
    return ((bool(__cdecl*)(CVehicle*))0x6E38F0)(vehicle);
}

// Converted from thiscall void CVehicle::ProcessWeapons(void) 0x6E3950
void CVehicle::ProcessWeapons()
{
    ((void(__thiscall*)(CVehicle*))0x6E3950)(this);
}
