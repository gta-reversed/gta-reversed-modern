/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "TxdDef.h"
#include "CPool.h"

class CTxdStore {
public:
    // class variables

    static CPool<TxdDef>*& ms_pTxdPool;
    static RwTexDictionary*& ms_pStoredTxd;
    static int32_t& ms_lastSlotFound;
    // variables list is not finished. Need to make CPools before.

    static int16_t (&defaultTxds)[4];

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static void GameShutdown();

    static bool StartLoadTxd(int32_t index, RwStream* stream);
    static bool FinishLoadTxd(int32_t index, RwStream* stream);
    static bool LoadTxd(int32_t index, RwStream* stream);
    static bool LoadTxd(int32_t index, const char* filename);

    static void PushCurrentTxd();
    static void PopCurrentTxd();
    static void SetCurrentTxd(int32_t index);

    static int32_t FindTxdSlot(const char* name);
    static int32_t FindTxdSlot(uint32_t hash);

    static RwTexDictionary* GetTxd(int32_t index);
    static int32_t GetParentTxdSlot(int32_t index);

    static void Create(int32_t index);

    static int32_t AddTxdSlot(const char* name);
    static void RemoveTxdSlot(int32_t index);
    static void RemoveTxd(int32_t index);

    static void AddRef(int32_t index);
    static void RemoveRef(int32_t index);
    static void RemoveRefWithoutDelete(int32_t index);
    static int32_t GetNumRefs(int32_t index);

    static RwTexDictionary* GetTxdParent(RwTexDictionary* txd);
    static void SetTxdParent(RwTexDictionary* txd, RwTexDictionary* parent);
    static void SetupTxdParent(int32_t index);

    static RwTexture* TxdStoreFindCB(const char* name);
    static RwTexture* TxdStoreLoadCB(const char* name, const char* mask);
};

RwTexture* RemoveIfRefCountIsGreaterThanOne(RwTexture* texture, void* data);