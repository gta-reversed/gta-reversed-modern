#include "StdInc.h"

CStoredCar(&CGarages::aCarsInSafeHouse)[MAX_NUM_SAFEHOUSES][MAX_CARS_IN_SAFEHOUSE] = *(CStoredCar(*)[MAX_NUM_SAFEHOUSES][MAX_CARS_IN_SAFEHOUSE])0x96ABD4;
CGarage(&CGarages::aGarages)[MAX_NUM_GARAGES] = *(CGarage(*)[MAX_NUM_GARAGES])0x96C048;

CGarage*& CGarages::LastGaragePlayerWasIn = *(CGarage**)0x96BFDC;
uint32& CGarages::LastTimeHelpMessage = *(uint32*)0x96BFE0;
bool& CGarages::bCamShouldBeOutside = *(bool*)0x96BFE4;
int32& CGarages::CrushedCarId = *(int32*)0x96BFE8; // Unused in SA
uint32(&CGarages::CarTypesCollected)[4] = *(uint32(*)[4])0x96BFEC;
uint32& CGarages::PoliceCarsCollected = *(uint32*)0x96BFFC;
uint32& CGarages::BankVansCollected = *(uint32*)0x96C000;
uint32& CGarages::CarsCollected = *(uint32*)0x96C004;
bool& CGarages::NoResprays = *(bool*)0x96C008;
bool& CGarages::RespraysAreFree = *(bool*)0x96C009;
bool& CGarages::BombsAreFree = *(bool*)0x96C00A;
bool& CGarages::PlayerInGarage = *(bool*)0x96C00B;
int32& CGarages::MessageNumberInString = *(int32*)0x96C00C;
int32& CGarages::MessageNumberInString2 = *(int32*)0x96C010;
char(&CGarages::MessageIDString)[8] = *(char(*)[8])0x96C014;
uint32& CGarages::MessageEndTime = *(uint32*)0x96C01C;
uint32& CGarages::MessageStartTime = *(uint32*)0x96C020;
int32& CGarages::NumGarages = *(int32*)0x96C024;

CGarage*& pOldToGarageWeAreIn = *(CGarage**)0x96BFD8;

void CGarages::InjectHooks()
{
    RH_ScopedClass(CGarages);
    RH_ScopedCategoryGlobal();

}

// 0x447120
void CGarages::Init()
{
    plugin::Call<0x447120>();
}

// 0x448B60
void CGarages::Init_AfterRestart()
{
    plugin::Call<0x448B60>();
}

// 0x447790
void CGarages::PrintMessages()
{
    plugin::Call<0x447790>();
}

// 0x5D3270
bool CGarages::Load() {
    return plugin::CallAndReturn<bool, 0x5D3270>();
}

// 0x5D3160
bool CGarages::Save() {
    return plugin::CallAndReturn<bool, 0x5D3160>();
}

// 0x447B80
void CGarages::TriggerMessage(Const char* cTagMsg, int16 wMsgMin, uint16 ucTime, int16 wMsgMax)
{
    plugin::Call<0x447B80, const char*, int16, uint16, int16>(cTagMsg, wMsgMin, ucTime, wMsgMax);
}

// 0x448AF0
bool CGarages::IsModelIndexADoor(int32 nModelIndex)
{
    return plugin::CallAndReturn<bool, 0x448AF0, int32>(nModelIndex);
}

// 0x44A240
int32 CGarages::FindGarageForObject(CObject* obj)
{
    return plugin::CallAndReturn<int32, 0x44A240, CObject*>(obj);
}

// Garage flags
// 0x1	door opens up and rotate
// 0x2	door goes in
// 0x4	camera follow players
//
// 0x4471E0
void CGarages::AddOne(float x1, float y1, float z1, float frontX, float frontY, float x2, float y2, float z2, eGarageType type, uint32 a10, char* name, uint32 door) {
    plugin::Call<0x4471E0, float, float, float, float, float, float, float, float, eGarageType, uint32, char*, uint32>(x1, y1, z1, frontX, frontY, x2, y2, z2, type, a10, name, door);
}

// 0x44A3C0
void CGarages::StoreCarInNearestImpoundingGarage(CVehicle* vehicle) {
    plugin::Call<0x44A3C0, CVehicle*>(vehicle);
}

// 0x448900
bool CGarages::IsPointWithinHideOutGarage(CVector& pos) {
    return plugin::CallAndReturn<bool, 0x448900, CVector&>(pos);
}
