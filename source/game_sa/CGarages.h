/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CGarages
{
public:
	// static char MessageIDString[8];
	static char *MessageIDString;

    static void Init();
    static void PrintMessages();
    static void TriggerMessage(char* cTagMsg, short wMsgMin, unsigned short ucTime, short wMsgMax);
};
