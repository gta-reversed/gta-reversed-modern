/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "ColModel.h"
#include "Entity.h"

class CGame {
public:
    //! Current number of area
    static char(&aDatFile)[32]; // static char aDatFile[32]
    static int32 &currLevel;
    static uint8 &bMissionPackGame;
    static int32 &currArea;
    static RwMatrix *&m_pWorkingMatrix1;
    static RwMatrix *&m_pWorkingMatrix2;

public:
    static void InjectHooks();

    static bool CanSeeOutSideFromCurrArea();
    static bool CanSeeWaterFromCurrArea();

    static void GenerateTempPedAtStartOfNetworkGame();

    static bool Init1(char const *datFile);
    static void Init2(char const *datFile);
    static void Init3(char const *datFile);
    static void Initialise(char const *datFile);
    static void InitialiseCoreDataAfterRW();
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

    static bool IsInNormalWorld() { return currArea == eAreaCodes::AREA_CODE_NORMAL_WORLD; }
};

extern int32 &gameTxdSlot;
extern bool& gbLARiots;
extern bool& gbLARiots_NoPoliceCars;

bool MoveMem(void **pMem);
bool MoveColModelMemory(CColModel &colModel, bool a2);
RpGeometry *MoveGeometryMemory(RpGeometry *geometry);
bool TidyUpModelInfo2(CEntity *entity, bool a2);
void ValidateVersion();
void D3DDeviceRestoreCallback();
bool DoHaspChecks();
