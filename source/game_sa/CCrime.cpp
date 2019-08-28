#include "StdInc.h"

void CCrime::ReportCrime(int crimeType, CPed* ped1, CPed* ped2)
{
    plugin::Call<0x532010, int, CPed*, CPed*>(crimeType, ped1, ped2);
}