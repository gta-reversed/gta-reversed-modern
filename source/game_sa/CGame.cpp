#include "StdInc.h"

char(&CGame::aDatFile)[32] = *reinterpret_cast<char(*)[32]>(0xB728EC);
int &CGame::currLevel = *reinterpret_cast<int *>(0xB7290C);
unsigned char &CGame::bMissionPackGame = *reinterpret_cast<unsigned char *>(0xB72910);
int &CGame::currArea = *reinterpret_cast<int *>(0xB72914);
RwMatrix *&CGame::m_pWorkingMatrix1 = *reinterpret_cast<RwMatrix **>(0xB72920);
RwMatrix *&CGame::m_pWorkingMatrix2 = *reinterpret_cast<RwMatrix **>(0xB72924);
int &gameTxdSlot = *reinterpret_cast<int *>(0xB728E8);