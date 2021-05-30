#include "StdInc.h"

CTrailer::CTrailer(int modelIndex, unsigned char createdBy) :CAutomobile(plugin::dummy)
{
    plugin::CallMethod<0x6D03A0, CTrailer*, int, unsigned char>(this, modelIndex, createdBy);
}
