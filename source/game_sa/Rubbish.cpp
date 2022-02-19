#include "Rubbish.h"
#include "StdInc.h"

void CRubbish::InjectHooks() {
  RH_ScopedClass(CRubbish);
  RH_ScopedCategoryGlobal(); 

  RH_ScopedGlobalInstall(SetVisibility, 0x7204C0);
}

// 0x7204C0
void CRubbish::SetVisibility() { 
    // NOP
}
