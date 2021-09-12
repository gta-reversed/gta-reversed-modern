#include "StdInc.h"

int32 (&CAudioZones::m_aActiveBoxes)[10] = *(int32(*)[10])0xB6DC6C;
int32 (&CAudioZones::m_aActiveSpheres)[10] = *(int32(*)[10])0xB6DC94;

uint32& CAudioZones::m_NumActiveBoxes = *(uint32*)0xB6DCBC;
uint32& CAudioZones::m_NumActiveSpheres = *(uint32*)0xB6DCC0;
uint32& CAudioZones::m_NumBoxes = *(uint32*)0xB6DCC4;
uint32& CAudioZones::m_NumSpheres = *(uint32*)0xB6DCC8;

tAudioZoneBox (&CAudioZones::m_aBoxes)[NUM_AUDIO_BOXES] = *(tAudioZoneBox(*)[NUM_AUDIO_BOXES])0xB6DCD0;
tAudioZoneSphere (&CAudioZones::m_aSpheres)[NUM_AUDIO_SPHERES] = *(tAudioZoneSphere(*)[NUM_AUDIO_SPHERES])0xB6EBA8;

void CAudioZones::InjectHooks() {}

void CAudioZones::Init() {
    plugin::Call<0x5081A0>();
}

// 0x508240
int32 CAudioZones::RegisterAudioBox(char* name, int32 id, bool b, float x1, float y1, float z1, float x2, float y2, float z2) {
    return plugin::CallAndReturn<int32, 0x508240, char*, int32, bool, float, float, float, float, float, float>(name, id, b, x1, y1, z1, x2, y2, z2);
}

// 0x5081C0
int32 CAudioZones::RegisterAudioSphere(char* name, int32 id, bool b, float x1, float y1, float z1, float radius) {
    return plugin::CallAndReturn<int32, 0x5081C0, char*, int32, bool, float, float, float, float>(name, id, b, x1, y1, z1, radius);
}
