#include "StdInc.h"

#include "EntryExitManager.h"

CEntryExit* (&CEntryExitManager::ms_entryExitStack)[4] = *reinterpret_cast<CEntryExit * (*)[4]>(0x96A720);
bool& CEntryExitManager::ms_bBurglaryHousesEnabled = *reinterpret_cast<bool*>(0x96A730);
int32& CEntryExitManager::ms_oldAreaCode = *reinterpret_cast<int32*>(0x96A734);
CEntity* (&CEntryExitManager::ms_visibleEntityList)[32] = *reinterpret_cast<CEntity * (*)[32]>(0x96A738);
int32& CEntryExitManager::ms_entryExitStackPosn = *reinterpret_cast<int32*>(0x96A7C4);
bool& CEntryExitManager::ms_bDisabled = *reinterpret_cast<bool*>(0x96A7C8);
ExitEnterState& CEntryExitManager::ms_exitEnterState = *reinterpret_cast<ExitEnterState*>(0x96A7CC);
CQuadTreeNode*& CEntryExitManager::mp_QuadTree = *reinterpret_cast<CQuadTreeNode**>(0x96A7D0);
CEntryExit*& CEntryExitManager::mp_Active = *reinterpret_cast<CEntryExit**>(0x96A7D4);
CEntryExitsPool*& CEntryExitManager::mp_poolEntryExits = *reinterpret_cast<CEntryExitsPool**>(0x96A7D8);
uint32& CEntryExitManager::ms_numVisibleEntities = *reinterpret_cast<uint32*>(0x96A7DC);
// ms_entryExitStack? 0x96A718 = a * 10.0f; float a = 1.0f / (50.0f * 50.0f);

void CEntryExitManager::InjectHooks() {
    RH_ScopedClass(CEntryExitManager);
    RH_ScopedCategoryGlobal();

RH_ScopedInstall(Init, 0x43F880, { .reversed = false });
RH_ScopedInstall(Load, 0x5D55C0, { .reversed = false });
RH_ScopedInstall(Save, 0x5D5970, { .reversed = false });
RH_ScopedInstall(Update, 0x440D10, { .reversed = false });
RH_ScopedInstall(Shutdown, 0x440B90, { .reversed = false });
RH_ScopedInstall(ShutdownForRestart, 0x440C40, { .reversed = false });
}

// 0x43F880
void CEntryExitManager::Init() {
    plugin::Call<0x43F880>();
}

// 0x5D55C0
void CEntryExitManager::Load() {
    plugin::Call<0x5D55C0>();
}

// 0x5D5970
void CEntryExitManager::Save() {
    plugin::Call<0x5D5970>();
}

// 0x440D10
void CEntryExitManager::Update() {
    plugin::Call<0x440D10>();
}

// 0x440B90
void CEntryExitManager::Shutdown() {
    plugin::Call<0x440D10>();
}

// 0x440C40
void CEntryExitManager::ShutdownForRestart() {
    plugin::Call<0x440C40>();
}

// 0x43E410
void CEntryExitManager::AddEntryExitToStack(CEntryExit* entryExit) {
    plugin::Call<0x43E410, CEntryExit*>(entryExit);
}

int32 CEntryExitManager::AddOne(float entranceX, float entranceY, float entranceZ, float entranceAngle, float entranceRangeX, float entranceRangeY, float fUnused, float exitX, float exitY, float exitZ, float exitAngle, int32 area, int32 flags, int32 skyColor, int32 timeOn, int32 timeOff, int32 numberOfPeds, const char* name)
{
    return plugin::CallAndReturn<int32, 0x43FA00, float, float, float, float, float, float, float, float, float, float, float, int32, int32, int32, int32, int32, int32, const char*>
        (entranceX, entranceY, entranceZ, entranceAngle, entranceRangeX, entranceRangeY, fUnused, exitX, exitY, exitZ, exitAngle, area, flags, skyColor, timeOn, timeOff, numberOfPeds, name);
}

void CEntryExitManager::DeleteOne(int32 index)
{
    plugin::Call<0x43FD50, int32>(index);
}

int32 CEntryExitManager::FindNearestEntryExit(const CVector2D& position, float range, int32 ignoreArea)
{
    return plugin::CallAndReturn<int32, 0x43F4B0, const CVector2D&, float, int32>(position, range, ignoreArea);
}

// 0x43F0A0
void CEntryExitManager::PostEntryExitsCreation() {
    plugin::Call<0x43F0A0>();
}

// 0x43ED80
void CEntryExitManager::ResetAreaCodeForVisibleObjects() {
    plugin::Call<0x43ED80>();
}

// 0x43ECF0
void CEntryExitManager::SetAreaCodeForVisibleObjects() {
    plugin::Call<0x43ECF0>();
}

// 0x43EFD0
int32 CEntryExitManager::GetEntryExitIndex(const char* name, uint16 enabledFlags, uint16 disabledFlags) {
    return plugin::CallAndReturn<int32, 0x43EFD0, const char*, uint16, uint16>(name, enabledFlags, disabledFlags);
}

// 0x43F150
void CEntryExitManager::GetPositionRelativeToOutsideWorld(CVector& positionInOut) {
    plugin::Call<0x43F150, CVector&>(positionInOut);
}

// 0x43F180
void CEntryExitManager::EnableBurglaryHouses(bool a1) {
    plugin::Call<0x43F180, bool>(a1);
}

// 0x43FDB0
void CEntryExitManager::GotoEntryExit(CEntryExit* entryExit) {
    plugin::Call<0x43FDB0, CEntryExit*>(entryExit);
}

// 0x43FEA0
void CEntryExitManager::GotoEntryExitVC(const char* name) {
    plugin::Call<0x43FEA0, const char*>(name);
}

// 0x43F050
void CEntryExitManager::LinkEntryExit(CEntryExit* entryExit) {
    plugin::Call<0x43F050, CEntryExit*>(entryExit);
}
