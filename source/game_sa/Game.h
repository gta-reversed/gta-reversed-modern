/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"

class CColModel;
class CEntity;

class CGame {
public:
    //! Current number of area
    static char (&aDatFile)[32];
    static int32& currLevel;
    static uint8& bMissionPackGame;
    static int32& currArea;
    static RwMatrix*& m_pWorkingMatrix1;
    static RwMatrix*& m_pWorkingMatrix2;

public:
    static void InjectHooks();

    static bool CanSeeOutSideFromCurrArea();
    static bool CanSeeWaterFromCurrArea();

    static void GenerateTempPedAtStartOfNetworkGame();

    static bool Init1(const char* datFile);
    static bool Init2(const char* datFile);
    static bool Init3(const char* datFile);
    static void Initialise(char const *datFile);
    static bool InitialiseCoreDataAfterRW();
    static bool InitialiseEssentialsAfterRW();
    static void InitialiseOnceBeforeRW();
    static bool InitialiseRenderWare();
    static void InitialiseWhenRestarting();
    static void Process();
    static void ReInitGameObjectVariables();
    static void ReloadIPLs();

    static void ShutDownForRestart();
    static bool Shutdown();
    static void ShutdownRenderWare();
    static void DrasticTidyUpMemory(bool a1);
    static void FinalShutdown();
    static void TidyUpMemory(bool a1, bool clearD3Dmem);
};

extern int32 &gameTxdSlot;
extern bool& gbLARiots;
extern bool& gbLARiots_NoPoliceCars;

static inline std::array<CColModel, 2>& col1 = *reinterpret_cast<std::array<CColModel, 2>*>(0xC17824);

bool MoveMem(void **pMem);
bool MoveColModelMemory(CColModel &colModel, bool a2);
RpGeometry *MoveGeometryMemory(RpGeometry *geometry);
bool TidyUpModelInfo2(CEntity *entity, bool a2);
void ValidateVersion();
void D3DDeviceRestoreCallback();
bool DoHaspChecks();
