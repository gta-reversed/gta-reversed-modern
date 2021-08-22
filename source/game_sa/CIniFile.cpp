#include "StdInc.h"

float& CIniFile::PedNumberMultiplier = *(float*)0x8CDF14;
float& CIniFile::CarNumberMultiplier = *(float*)0x8CDF18;

void CIniFile::InjectHooks() {
    ReversibleHooks::Install("CIniFile", "LoadIniFile", 0x56D070, &CIniFile::LoadIniFile);
}

// 0x56D070
void CIniFile::LoadIniFile() {
    CFileMgr::SetDir(gta_empty_string);
    FILE *file = CFileMgr::OpenFile("gta3.ini", "r");
    if (file) {
        CFileMgr::ReadLine(file, gString, 200);
        sscanf(gString, "%f", &CIniFile::PedNumberMultiplier);
        if (CIniFile::PedNumberMultiplier >= 0.5f) {
            if (CIniFile::PedNumberMultiplier > 3.0f)
                CIniFile::PedNumberMultiplier = 3.0f;
        } else {
            CIniFile::PedNumberMultiplier = 0.5f;
        }

        CFileMgr::ReadLine(file, gString, 200);
        sscanf(gString, "%f", &CIniFile::CarNumberMultiplier);
        if (CIniFile::CarNumberMultiplier >= 0.5f) {
            if (CIniFile::CarNumberMultiplier > 3.0f)
                CIniFile::CarNumberMultiplier = 3.0f;
        } else {
            CIniFile::CarNumberMultiplier = 0.5f;
        }
        CFileMgr::CloseFile(file);
    }
    CPopulation::MaxNumberOfPedsInUse = 25;
    CCarCtrl::MaxNumberOfCarsInUse = 12;
}
