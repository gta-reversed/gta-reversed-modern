#include "StdInc.h"

void CCarEnterExit::RemoveCarSitAnim(CPed* ped)
{
    return plugin::Call<0x64F680, CPed*>(ped);
}
