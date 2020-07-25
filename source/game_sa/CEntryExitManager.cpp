#include "StdInc.h"

CEntryExit* (&CEntryExitManager::ms_entryExitStack)[4] = *reinterpret_cast<CEntryExit * (*)[4]>(0x96A720);
bool& CEntryExitManager::ms_bBurglaryHousesEnabled = *reinterpret_cast<bool*>(0x96A730);
int& CEntryExitManager::ms_oldAreaCode = *reinterpret_cast<int*>(0x96A734);
CEntity* (&CEntryExitManager::ms_visibleEntityList)[32] = *reinterpret_cast<CEntity * (*)[32]>(0x96A738);
int& CEntryExitManager::ms_entryExitStackPosn = *reinterpret_cast<int*>(0x96A7C4);
bool& CEntryExitManager::ms_bDisabled = *reinterpret_cast<bool*>(0x96A7C8);
int& CEntryExitManager::ms_exitEnterState = *reinterpret_cast<int*>(0x96A7CC);
CQuadTreeNode*& CEntryExitManager::mp_QuadTree = *reinterpret_cast<CQuadTreeNode**>(0x96A7D0);
CEntryExit*& CEntryExitManager::mp_Active = *reinterpret_cast<CEntryExit**>(0x96A7D4);
CPool<CEntryExit>*& CEntryExitManager::mp_poolEntryExits = *reinterpret_cast<CPool<CEntryExit>**>(0x96A7D8);
unsigned int& CEntryExitManager::ms_numVisibleEntities = *reinterpret_cast<unsigned int*>(0x96A7DC);
