#include "StdInc.h"

float& CIniFile::PedNumberMultiplier = *(float*)0x8CDF14;
float& CIniFile::CarNumberMultiplier = *(float*)0x8CDF18;

void CIniFile::LoadIniFile() {
    ((void(__cdecl*)())0x56D070)();
}
