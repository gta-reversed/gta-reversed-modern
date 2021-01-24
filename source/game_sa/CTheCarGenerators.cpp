#include "StdInc.h"

unsigned char& CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter = *reinterpret_cast<unsigned char*>(0xC279D0);
unsigned char& CTheCarGenerators::ProcessCounter = *reinterpret_cast<unsigned char*>(0xC279D1);
unsigned int& CTheCarGenerators::NumOfCarGenerators = *reinterpret_cast<unsigned int*>(0xC279D4);
CSpecialPlateHandler& CTheCarGenerators::m_SpecialPlateHandler = *reinterpret_cast<CSpecialPlateHandler*>(0xC279D8);
CCarGenerator* CTheCarGenerators::CarGeneratorArray = reinterpret_cast<CCarGenerator*>(0xC27AD0);

signed int CTheCarGenerators::CreateCarGenerator(float x, float y, float z, float angle, int modelId, short color1, short color2, unsigned char forceSpawn, unsigned char alarm_chances, unsigned char doorLock_chances, unsigned short minDelay, unsigned short maxDelay, unsigned char iplId, unsigned char bOwnedbyplayer) {
    return plugin::CallAndReturnDynGlobal<signed int, float, float, float, float, int, short, short, unsigned char, unsigned char, unsigned char, unsigned short, unsigned short, unsigned char, unsigned char>(0x6F31A0, x, y, z, angle, modelId, color1, color2, forceSpawn, alarm_chances, doorLock_chances, minDelay, maxDelay, iplId, bOwnedbyplayer);
}

void CTheCarGenerators::Init() {
    plugin::CallDynGlobal(0x6F3270);
}

void CTheCarGenerators::Load() {
    plugin::CallDynGlobal(0x5D39B0);
}

void CTheCarGenerators::Process() {
    plugin::CallDynGlobal(0x6F3F40);
}

void CTheCarGenerators::RemoveCarGenerators(unsigned char IplID) {
    plugin::CallDynGlobal<unsigned char>(0x6F3240, IplID);
}

void CTheCarGenerators::Save() {
    plugin::CallDynGlobal(0x5D38C0);
}
