/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

enum eStreamingFlags {
    STREAMING_UNKNOWN_1 = 0x1,
    STREAMING_GAME_REQUIRED = 0x2,
    STREAMING_MISSION_REQUIRED = 0x4,
    STREAMING_KEEP_IN_MEMORY = 0x8,
    STREAMING_PRIORITY_REQUEST = 0x10,
    STREAMING_LOADING_SCENE = 0x20,
    STREAMING_DONTREMOVE_IN_LOADSCENE = STREAMING_LOADING_SCENE | STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY | STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED,
};

enum eStreamingLoadState {
    LOADSTATE_NOT_LOADED = 0,
    LOADSTATE_LOADED = 1,
    LOADSTATE_REQUESTED = 2,
    LOADSTATE_CHANNELED = 3,
    LOADSTATE_FINISHING = 4
};

const std::uint32_t STREAMING_SECTOR_SIZE = 2048;

class CStreamingInfo {
public:
    short m_nNextIndex; // ms_pArrayBase array index
    short m_nPrevIndex; // ms_pArrayBase array index
    short m_nNextIndexOnCd;
    unsigned char m_nFlags; // see eStreamingFlags
    unsigned char m_nImgId;
    unsigned int m_nCdPosn;
    unsigned int m_nCdSize; // number of blocks/sectors; m_nCdSize * STREAMING_BLOCK_SIZE = actual size in bytes
    unsigned char m_nLoadState; // see eStreamingLoadState
private:
    char  __pad[3];

public:
     static CStreamingInfo *&ms_pArrayBase;

     static void InjectHooks();
     void Init();
     void AddToList(CStreamingInfo* listStart);
     unsigned int GetCdPosn();
     bool GetCdPosnAndSize(unsigned int *CdPosn, unsigned int *CdSize);
    //! unused
     unsigned int GetCdSize();
     CStreamingInfo* GetNext() { return m_nNextIndex == -1 ? nullptr : &ms_pArrayBase[m_nNextIndex]; }
     CStreamingInfo *GetPrev() { return m_nPrevIndex == -1 ? nullptr : &ms_pArrayBase[m_nPrevIndex]; }
    //! unused
     bool InList();
     void RemoveFromList();
     void SetCdPosnAndSize(unsigned int CdPosn, unsigned int CdSize);
};

VALIDATE_SIZE(CStreamingInfo, 0x14);

//#include "meta/meta.CStreamingInfo.h"
