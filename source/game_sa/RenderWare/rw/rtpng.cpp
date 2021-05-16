#include "StdInc.h"

#include "rtpng.h"

RwImage *RtPNGImageWrite(RwImage *image, const RwChar *imageName) {
    return ((RwImage *(__cdecl *)(RwImage *, const RwChar *)) 0x7CF600)(image, imageName);
}

RwImage *RtPNGImageRead(const RwChar *imageName) {
    return ((RwImage *(__cdecl *)(const RwChar *)) 0x7CF9B0)(imageName);
}
