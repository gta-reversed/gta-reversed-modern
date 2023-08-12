#include "StdInc.h"

#include "Crime.h"

void CCrime::ReportCrime(eCrimeType crimeType, CEntity* entity, CPed* ped2) {
    assert(!ped2 || ped2->IsPed());
    plugin::Call<0x532010, eCrimeType, CEntity*, CPed*>(crimeType, entity, ped2);
}
