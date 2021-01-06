#include "StdInc.h"

void CGarages::PrintMessages()
{
    ((void(__cdecl*)())0x447790)();
}

void CGarages::TriggerMessage(char* cTagMsg, short wMsgMin, unsigned short ucTime, short wMsgMax)
{
    plugin::Call<0x447B80, char*, short, unsigned short, short>(cTagMsg, wMsgMin, ucTime, wMsgMax);
}
