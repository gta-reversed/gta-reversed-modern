#include "StdInc.h"

char (&CGridRef::GridRefList)[3200] = *reinterpret_cast<char (*)[3200]>(0xC72FB0);

void CGridRef::InjectHooks() {
//    RH_ScopedInstall(Init, 0x71D4E0);
}

// 0x71D4E0
void CGridRef::Init() {
    plugin::Call<0x71D4E0>();
}

// unused
// 0x71D670
void CGridRef::GetAreaName(uint8 a1, uint8 a2) {

}

// unused
void CGridRef::GetArtistBugstarID(uint8 a1, uint8 a2) {

}

// unused
// 0x71D5A0
void CGridRef::GetGridRefPositions(CVector a1, uint8* a2, uint8* a3) {

}

// unused
// 0x71D5E0
void CGridRef::GetGridRefPositions(uint8* a1, uint8* a2) {

}
