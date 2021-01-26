/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include "CColModel.h"
#include "CEntity.h"

class CGame {
public:
    //! Current number of area
     static char(&aDatFile)[32]; // static char aDatFile[32]
     static int &currLevel;
     static unsigned char &bMissionPackGame;
     static int &currArea;
     static RwMatrix *&m_pWorkingMatrix1;
     static RwMatrix *&m_pWorkingMatrix2;

     static void InjectHooks();
     static bool CanSeeOutSideFromCurrArea();
     static bool CanSeeWaterFromCurrArea();
     static void DrasticTidyUpMemory(bool a1);
     static void FinalShutdown();
    //! dummy function
     static void GenerateTempPedAtStartOfNetworkGame();
     static bool Init1(char const *datFile);
     static bool Init2(char const *datFile);
     static bool Init3(char const *datFile);
     static void InitAfterLostFocus();
     static bool Initialise(char const *datFile);
     static bool InitialiseCoreDataAfterRW();
     static bool InitialiseEssentialsAfterRW();
     static bool InitialiseOnceBeforeRW();
     static bool InitialiseRenderWare();
     static void InitialiseWhenRestarting();
     static void Process();
     static void ReInitGameObjectVariables();
    //! dummy function
     static void ReloadIPLs();
     static void ShutDownForRestart();
     static bool Shutdown();
     static void ShutdownRenderWare();
     static void TidyUpMemory(bool a1, bool clearD3Dmem);
};

 extern int &gameTxdSlot;

 bool MoveMem(void **pMem);
 bool MoveColModelMemory(CColModel &colModel, bool a2);
 RpGeometry *MoveGeometryMemory(RpGeometry *geometry);
 bool TidyUpModelInfo2(CEntity *entity, bool a2);
 void ValidateVersion();
 void D3DDeviceRestoreCallback();
 bool DoHaspChecks();

//#include "meta/meta.CGame.h"
