#include "StdInc.h"

// depends on libjpeg

void JPegPlugin::InjectHooks() {

}

void JPegCompressScreenToFile(RwCamera* camera, const char* path) {
    plugin::Call<0x5D0820, RwCamera*, const char*>(camera, path);
}
