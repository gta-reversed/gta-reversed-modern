#include "StdInc.h"
#include "Furniture_c.h"

void Furniture_c::InjectHooks() {
    RH_ScopedClass(Furniture_c);
    RH_ScopedCategory("Interior");

    // Constructors (1x)
    // RH_ScopedInstall(Constructor, 0x590EC0);

    // Destructors (1x)
    // RH_ScopedInstall(Destructor, 0x590ED0);
}

// 0x590EC0
Furniture_c::Furniture_c() {}

// 0x590EC0
Furniture_c* Furniture_c::Constructor() {
    this->Furniture_c::Furniture_c();
    return this;
}

// 0x590ED0
Furniture_c::~Furniture_c() {}

// 0x590ED0
Furniture_c* Furniture_c::Destructor() {
    this->Furniture_c::~Furniture_c();
    return this;
}
