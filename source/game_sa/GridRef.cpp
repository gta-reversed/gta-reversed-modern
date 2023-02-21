#include "StdInc.h"

#include "GridRef.h"

// todo: remove magic numbers
char (&GridRefList)[10][10][32] = *reinterpret_cast<char (*)[10][10][32]>(0xC72FB0);

void CGridRef::InjectHooks() {
    RH_ScopedClass(CGridRef);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x71D4E0);
    RH_ScopedInstall(GetAreaName, 0x71D670);
    RH_ScopedInstall(GetArtistBugstarID, 0x71D650);
    RH_ScopedOverloadedInstall(GetGridRefPositions, "vec", 0x71D5A0, void(*)(CVector, uint8*, uint8*));
    RH_ScopedOverloadedInstall(GetGridRefPositions, "", 0x71D5E0, void(*)(uint8*, uint8*));
}

// 0x71D4E0
void CGridRef::Init() {
    char str[32];
    CFileMgr::SetDir("");
    auto* file = CFileMgr::OpenFile("DATA\\GRIDREF.DAT", "rb");
    for (auto line = CFileLoader::LoadLine(file); line; line = CFileLoader::LoadLine(file)) {
        if (*line == '#' || !*line)
            continue;

        uint8 x = 0;
        int32 y = 0;
        VERIFY(sscanf(line, "%c%d %s", &x, &y, str) == 3);
        auto lowstr = _strlwr(str);
        x -= 65; // - 'A'
        y -= 1;
        assert(x >= 0 && y >= 0);
        strcpy(&GridRefList[x][y][0], lowstr);
    }
    CFileMgr::CloseFile(file);
}

// 0x71D670
int32 CGridRef::GetAreaName(uint8 x, uint8 y) {
    if (x >= 10 || y >= 10)
        return 0;
    else
        return atoi(GridRefList[x][y]);
}

// 0x71D650
char* CGridRef::GetArtistBugstarID(uint8 x, uint8 y) {
    if (x >= 10 || y >= 10)
        return nullptr;
    else
        return {};
}

// 0x71D5A0
void CGridRef::GetGridRefPositions(CVector pos, uint8* x, uint8* y) {
    *x =     (uint32)((pos.x + 3000.0) / 600.0f);
    *y = 9 - (uint32)((pos.y + 3000.0) / 600.0f);
}

// 0x71D5E0
void CGridRef::GetGridRefPositions(uint8* x, uint8* y) {
    const auto& coors = FindPlayerCoors();
    GetGridRefPositions(coors, x, y);
}
