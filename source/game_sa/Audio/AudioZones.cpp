#include "StdInc.h"

#include "AudioZones.h"

int32 (&CAudioZones::m_aActiveBoxes)[10] = *(int32(*)[10])0xB6DC6C;
int32 (&CAudioZones::m_aActiveSpheres)[10] = *(int32(*)[10])0xB6DC94;

uint32& CAudioZones::m_NumActiveBoxes = *(uint32*)0xB6DCBC;
uint32& CAudioZones::m_NumActiveSpheres = *(uint32*)0xB6DCC0;
uint32& CAudioZones::m_NumBoxes = *(uint32*)0xB6DCC4;
uint32& CAudioZones::m_NumSpheres = *(uint32*)0xB6DCC8;

tAudioZoneBox (&CAudioZones::m_aBoxes)[NUM_AUDIO_BOXES] = *(tAudioZoneBox(*)[NUM_AUDIO_BOXES])0xB6DCD0;
tAudioZoneSphere (&CAudioZones::m_aSpheres)[NUM_AUDIO_SPHERES] = *(tAudioZoneSphere(*)[NUM_AUDIO_SPHERES])0xB6EBA8;

void CAudioZones::InjectHooks() {
    RH_ScopedClass(CAudioZones);
    RH_ScopedCategory("Audio");

    RH_ScopedInstall(Init, 0x5081A0, { .reversed = false });
    RH_ScopedInstall(RegisterAudioSphere, 0x5081C0);
    RH_ScopedInstall(RegisterAudioBox, 0x508240);
    RH_ScopedInstall(SwitchAudioZone, 0x508320, { .reversed = false });
    RH_ScopedInstall(Update, 0x5083C0, { .reversed = false });
}

// 0x5081A0
void CAudioZones::Init() {
    ZoneScoped;

    m_NumSpheres = 0;
    m_NumBoxes = 0;
    m_NumActiveSpheres = 0;
    m_NumActiveBoxes = 0;
}

// 0x508240
void CAudioZones::RegisterAudioBox(char name[8], int32 id, bool isActive, CVector min, CVector max) {

    tAudioZoneBox audioZoneBox;
    strcpy_s(audioZoneBox.m_szName, name);
    audioZoneBox.m_bIsActive = isActive; // TODO: m_nFlags field has only 1 flag - Active or inactive and takes only 1 bit. Although gta uses 2 bytes for this, but how is the idea to define this single flag so as not to be confused in the future
    audioZoneBox.m_nAudioZone = id;
    audioZoneBox.m_Box = CompressedBox{
        .m_vecMin = CompressLargeVector(min),
        .m_vecMax = CompressLargeVector(max),
    };
    CAudioZones::m_aBoxes[m_NumBoxes++] = audioZoneBox;
}

// 0x5081C0
void CAudioZones::RegisterAudioSphere(char name[8], int32 id, bool isActive, CVector position, float radius) {
    tAudioZoneSphere audioZoneSphere;
    strcpy_s(audioZoneSphere.m_szName, name);
    audioZoneSphere.m_nAudioZone = id;
    audioZoneSphere.m_bIsActive = isActive; // TODO: m_nFlags field has only 1 flag - Active or inactive and takes only 1 bit. Although gta uses 2 bytes for this, but how is the idea to define this single flag so as not to be confused in the future
    audioZoneSphere.m_vPosn = position;
    audioZoneSphere.m_fRadius = radius;

    CAudioZones::m_aSpheres[m_NumSpheres++] = audioZoneSphere;
}

// 0x508320
void CAudioZones::SwitchAudioZone(char* zoneName, bool enable) {
    plugin::Call<0x508320, const char*, bool>(zoneName, enable);
}

// 0x5083C0
void CAudioZones::Update(bool a1, CVector posn) {
    ZoneScoped;

    plugin::Call<0x5083C0, bool, CVector>(a1, posn);
}
