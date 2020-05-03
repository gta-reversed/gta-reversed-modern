/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

enum eStreamingFlags {
    GAME_REQUIRED = 0x2,
    MISSION_REQUIRED = 0x4,
    KEEP_IN_MEMORY = 0x8,
    PRIORITY_REQUEST = 0x10
};

enum eStreamingLoadState {
    LOADSTATE_NOT_LOADED = 0,
    LOADSTATE_LOADED = 1,
    LOADSTATE_Requested = 2,
    LOADSTATE_Channeled = 3,
    LOADSTATE_Finishing = 4
};

class  CStreamingInfo {
public:
    short m_nNextIndex; // ms_pArrayBase array index
    short m_nPrevIndex; // ms_pArrayBase array index
    short m_nNextIndexOnCd;
    unsigned char m_nFlags; // see eStreamingFlags
    unsigned char m_nImgId;
    unsigned int m_nCdPosn;
    unsigned int m_nCdSize;
    unsigned char m_nLoadState; // see eStreamingLoadState
private:
    char  __pad[3];

public:
     static CStreamingInfo *&ms_pArrayBase;

     static void InjectHooks();
     int GetIndexFromBase(CStreamingInfo * pThis, CStreamingInfo * ArrayBase);
     int AddToList(CStreamingInfo *listStart);
     unsigned int GetCdPosn();
     bool GetCdPosnAndSize(unsigned int *CdPosn, unsigned int *CdSize);
    //! unused
     unsigned int GetCdSize();
     CStreamingInfo* GetNext() { return m_nNextIndex == -1 ? nullptr : &ms_pArrayBase[m_nNextIndex]; }
     CStreamingInfo *GetPrev() { return m_nPrevIndex == -1 ? nullptr : &ms_pArrayBase[m_nPrevIndex]; }
    //! unused
     bool InList();
     void Init();
     void RemoveFromList();
     void SetCdPosnAndSize(unsigned int CdPosn, unsigned int CdSize);
};

VALIDATE_SIZE(CStreamingInfo, 0x14);

//#include "meta/meta.CStreamingInfo.h"
