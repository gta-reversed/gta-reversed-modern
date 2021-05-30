#include "StdInc.h"

int CSpecialPlateHandler::Find(int carGenId, char* outText)
{
    return plugin::CallMethodAndReturn<int, 0x6F2D30, CSpecialPlateHandler*, int, char*>(this, carGenId, outText);
}
