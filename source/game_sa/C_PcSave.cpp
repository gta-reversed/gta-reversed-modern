#include "StdInc.h"
#include "GenericGameStorage.h"
#include "Messages.h"
#include <stdio.h>
#include "C_PcSave.h"
#include <SimpleVariablesSaveStructure.h>
#include <GxtChar.h>
#include <filesystem>
namespace fs = std::filesystem;

void C_PcSave::InjectHooks() {
    using namespace ReversibleHooks;
    Install("C_PcSave", "SetSaveDirectory", 0x619040, &C_PcSave::SetSaveDirectory);
    Install("C_PcSave", "DeleteSlot", 0x6190D0, &C_PcSave::DeleteSlot);
    Install("C_PcSave", "GenerateGameFilename", 0x6190A0, &C_PcSave::GenerateGameFilename<MAX_PATH>);
    Install("C_PcSave", "PopulateSlotInfo", 0x619140, &C_PcSave::PopulateSlotInfo);
    Install("C_PcSave", "SaveSlot", 0x619060, &C_PcSave::SaveSlot);
}

void C_PcSave::SetSaveDirectory(const char* path) {
    sprintf_s(SaveFilePathWithName, "%s\\%s", path, "GTASAsf");
}

void C_PcSave::PopulateSlotInfo(void) {
	s_PcSaveHelper.error = eErrorCode::NONE;

	for (auto i = 0u; i < std::size(CGenericGameStorage::ms_Slots); ++i) {
		CGenericGameStorage::ms_Slots[i] = CGenericGameStorage::eSlotState::EMPTY;
		CGenericGameStorage::ms_SlotFileName[i][0] = 0;
		CGenericGameStorage::ms_SlotSaveDate[i][0] = 0;
	}

	for (auto i = 0u; i < std::size(CGenericGameStorage::ms_Slots); ++i) {
        char path[MAX_PATH]{};
        CSimpleVariablesSaveStructure vars{};

		GenerateGameFilename(i, path);
		auto file = CFileMgr::OpenFile(path, "rb");
		if (file) {
			CFileMgr::Seek(file, strlen(CGenericGameStorage::ms_BlockTagName), SEEK_SET);
			CFileMgr::Read(file, &vars, sizeof(CSimpleVariablesSaveStructure));

			if (strncmp(vars.m_szSaveName, TopLineEmptyFile, strlen(TopLineEmptyFile))) {
				memcpy(CGenericGameStorage::ms_SlotFileName[i], vars.m_szSaveName, 48); // TODO: why 48?
				CGenericGameStorage::ms_Slots[i] = CGenericGameStorage::eSlotState::IN_USE;
				CGenericGameStorage::ms_SlotFileName[i][24] = 0;                        // TODO: Why 24?
			}
			CFileMgr::CloseFile(file);
		}

		if (CGenericGameStorage::ms_Slots[i] != CGenericGameStorage::eSlotState::IN_USE) {
			continue;
		}

		if (CGenericGameStorage::CheckDataNotCorrupt(i, path)) {
            const auto& time = vars.m_systemTime;

            char monthGXTKey[64]{};
            sprintf_s(monthGXTKey, "MONTH%d", (uint32)time.wMonth); 
            assert(time.wMonth - 1 < 12); // NOTSA

            char date[128];
            sprintf_s(date,
                "%02d %s %04d %02d:%02d:%02d",
                time.wDay,
                GxtCharToAscii(TheText.Get(monthGXTKey), 0),
                time.wYear,
                time.wHour,
                time.wMinute,
                time.wSecond
			);
			AsciiToGxtChar(date, CGenericGameStorage::ms_SlotSaveDate[i]);
		} else {
			CMessages::InsertNumberInString(TheText.Get("FEC_SLC"), i, -1, -1, -1, -1, -1, CGenericGameStorage::ms_SlotFileName[i]);
		}
	}
}

bool C_PcSave::DeleteSlot(int32 slot) {
    char path[MAX_PATH]{};
	GenerateGameFilename(slot, path);
    std::error_code ec{}; // Dont want to be using throwing overload
    return fs::remove(path, ec);

    /* Original code:
	<delete file function>(path);
	auto file = CFileMgr::OpenFile(_szPath, "rb");
	if (file) {
		CFileMgr::CloseFile(file);
		return false;
	}
	return true;
    */
}

void C_PcSave::SaveSlot(int32 slot) {
	CGenericGameStorage::MakeValidSaveName(slot);
    s_PcSaveHelper.error = eErrorCode::NONE;
	CFileMgr::SetDirMyDocuments();
	CGenericGameStorage::DoGameSpecificStuffBeforeSave();
    CGenericGameStorage::GenericSave();
}
