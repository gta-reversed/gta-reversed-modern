/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "TxdDef.h"
#include "Pool.h"

class CTxdStore {
public:
    // class variables

    static CPool<TxdDef>*& ms_pTxdPool;
    static RwTexDictionary*& ms_pStoredTxd;
    static int32& ms_lastSlotFound;
    // variables list is not finished. Need to make CPools before.

    static int16 (&defaultTxds)[4];

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static void GameShutdown();

    static bool StartLoadTxd(int32 index, RwStream* stream);
    static bool FinishLoadTxd(int32 index, RwStream* stream);
    static bool LoadTxd(int32 index, RwStream* stream);
    static bool LoadTxd(int32 index, const char* filename);

    static void PushCurrentTxd();
    static void PopCurrentTxd();
    static void SetCurrentTxd(int32 index);

    static int32 FindTxdSlot(const char* name);
    static int32 FindTxdSlot(uint32 hash);

    static RwTexDictionary* GetTxd(int32 index);
    static int32 GetParentTxdSlot(int32 index);

    static void Create(int32 index);

    static int32 AddTxdSlot(const char* name);
    static void RemoveTxdSlot(int32 index);
    static void RemoveTxd(int32 index);

    static void AddRef(int32 index);
    static void RemoveRef(int32 index);
    static void RemoveRefWithoutDelete(int32 index);
    static int32 GetNumRefs(int32 index);

    static RwTexDictionary* GetTxdParent(RwTexDictionary* txd);
    static void SetTxdParent(RwTexDictionary* txd, RwTexDictionary* parent);
    static void SetupTxdParent(int32 index);

    static RwTexture* TxdStoreFindCB(const char* name);
    static RwTexture* TxdStoreLoadCB(const char* name, const char* mask);
};

RwTexture* RemoveIfRefCountIsGreaterThanOne(RwTexture* texture, void* data);
