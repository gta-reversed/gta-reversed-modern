#include "StdInc.h"

#include "StencilShadowObject.h"

void CStencilShadowObject::InjectHooks() {
    RH_ScopedClass(CStencilShadowObject);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Constructor, 0x70F8D0, { .reversed = false });
    RH_ScopedInstall(Destructor, 0x70F8E0, { .reversed = false });
}
