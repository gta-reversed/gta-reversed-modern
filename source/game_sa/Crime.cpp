#include "StdInc.h"

#include "Crime.h"

void CCrime::ReportCrime(eCrimeType crimeType, CEntity* entity, CPed* ped2) {
    plugin::Call<0x532010, eCrimeType, CEntity*, CPed*>(crimeType, entity, ped2);
}
