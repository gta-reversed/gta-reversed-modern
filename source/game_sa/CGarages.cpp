#include "StdInc.h"

CStoredCar(&CGarages::aCarsInSafeHouse)[MAX_NUM_SAFEHOUSES][MAX_CARS_IN_SAFEHOUSE] = *(CStoredCar(*)[MAX_NUM_SAFEHOUSES][MAX_CARS_IN_SAFEHOUSE])0x96ABD4;
CGarage(&CGarages::aGarages)[MAX_NUM_GARAGES] = *(CGarage(*)[MAX_NUM_GARAGES])0x96C048;;

CGarage*& CGarages::LastGaragePlayerWasIn = *(CGarage**)0x96BFDC;
uint32_t& CGarages::LastTimeHelpMessage = *(uint32_t*)0x96BFE0;
bool& CGarages::bCamShouldBeOutside = *(bool*)0x96BFE4;
int32_t& CGarages::CrushedCarId = *(int32_t*)0x96BFE8; // Unused in SA
uint32_t(&CGarages::CarTypesCollected)[4] = *(uint32_t(*)[4])0x96BFEC;
uint32_t& CGarages::PoliceCarsCollected = *(uint32_t*)0x96BFFC;
uint32_t& CGarages::BankVansCollected = *(uint32_t*)0x96C000;
uint32_t& CGarages::CarsCollected = *(uint32_t*)0x96C004;
bool& CGarages::NoResprays = *(bool*)0x96C008;
bool& CGarages::RespraysAreFree = *(bool*)0x96C009;
bool& CGarages::BombsAreFree = *(bool*)0x96C00A;
bool& CGarages::PlayerInGarage = *(bool*)0x96C00B;
int32_t& CGarages::MessageNumberInString = *(int32_t*)0x96C00C;
int32_t& CGarages::MessageNumberInString2 = *(int32_t*)0x96C010;
char(&CGarages::MessageIDString)[8] = *(char(*)[8])0x96C014;
uint32_t& CGarages::MessageEndTime = *(uint32_t*)0x96C01C;
uint32_t& CGarages::MessageStartTime = *(uint32_t*)0x96C020;
int32_t& CGarages::NumGarages = *(int32_t*)0x96C024;

CGarage*& pOldToGarageWeAreIn = *(CGarage**)0x96BFD8;

void CGarages::InjectHooks()
{
}

void CGarages::Init()
{
    plugin::Call<0x447120>();
}

void CGarages::PrintMessages()
{
    plugin::Call<0x447790>();
}

void CGarages::TriggerMessage(char* cTagMsg, short wMsgMin, unsigned short ucTime, short wMsgMax)
{
    plugin::Call<0x447B80, char*, short, unsigned short, short>(cTagMsg, wMsgMin, ucTime, wMsgMax);
}

bool CGarages::IsModelIndexADoor(int nModelIndex)
{
    return plugin::CallAndReturn<bool, 0x448AF0, int>(nModelIndex);
}

int CGarages::FindGarageForObject(CObject* pObject)
{
    return plugin::CallAndReturn<int, 0x44A240, CObject*>(pObject);
}
