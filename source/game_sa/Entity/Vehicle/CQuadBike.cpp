#include "StdInc.h"

CQuadBike::CQuadBike(int modelIndex, unsigned char createdBy) :CAutomobile(plugin::dummy)
{
    plugin::CallMethod<0x6CE370, CQuadBike*, int, unsigned char>(this, modelIndex, createdBy);
}
