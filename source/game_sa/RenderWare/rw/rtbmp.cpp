#include "rtbmp.h"

RwImage* RtBMPImageWrite(RwImage* image, const RwChar* imageName) {
    return ((RwImage*(__cdecl *)(RwImage*, const RwChar*))0x7CE990)(image, imageName);
}

RwImage* RtBMPImageRead(const RwChar* imageName) {
    return ((RwImage*(__cdecl *)(const RwChar*))0x7CDF60)(imageName);
}
