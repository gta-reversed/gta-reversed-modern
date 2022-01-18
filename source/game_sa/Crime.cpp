#include "StdInc.h"

void CCrime::ReportCrime(eCrimeType crimeType, CPed* ped1, CPed* ped2)
{
    plugin::Call<0x532010, eCrimeType, CPed*, CPed*>(crimeType, ped1, ped2);
}
