#include "StdInc.h"

unsigned char(&CClock::daysInMonth)[12] = *reinterpret_cast<unsigned char(*)[12]>(0x8CCF24);
bool &CClock::bClockHasBeenStored = *reinterpret_cast<bool *>(0xB70144);
unsigned short &CClock::ms_Stored_nGameClockSeconds = *reinterpret_cast<unsigned short *>(0xB70148);
unsigned char &CClock::ms_Stored_nGameClockMinutes = *reinterpret_cast<unsigned char *>(0xB7014A);
unsigned char &CClock::ms_Stored_nGameClockHours = *reinterpret_cast<unsigned char *>(0xB7014B);
unsigned char &CClock::ms_Stored_nGameClockDays = *reinterpret_cast<unsigned char *>(0xB7014C);
unsigned char &CClock::ms_Stored_nGameClockMonths = *reinterpret_cast<unsigned char *>(0xB7014D);
unsigned char &CClock::CurrentDay = *reinterpret_cast<unsigned char *>(0xB7014E);
unsigned short &CClock::ms_nGameClockSeconds = *reinterpret_cast<unsigned short *>(0xB70150);
unsigned char &CClock::ms_nGameClockMinutes = *reinterpret_cast<unsigned char *>(0xB70152);
unsigned char &CClock::ms_nGameClockHours = *reinterpret_cast<unsigned char *>(0xB70153);
unsigned char &CClock::ms_nGameClockDays = *reinterpret_cast<unsigned char *>(0xB70154);
unsigned char &CClock::ms_nGameClockMonth = *reinterpret_cast<unsigned char *>(0xB70155);
unsigned int &CClock::ms_nLastClockTick = *reinterpret_cast<unsigned int *>(0xB70158);
unsigned int &CClock::ms_nMillisecondsPerGameMinute = *reinterpret_cast<unsigned int *>(0xB7015C);

bool CClock::GetIsTimeInRange(unsigned char hourA, unsigned char hourB) 
{
    return plugin::CallAndReturnDynGlobal<bool, unsigned char, unsigned char>(0x52CEE0, hourA, hourB);
}