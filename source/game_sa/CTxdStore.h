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

    static RwTexDictionary* ms_pStoredTxd;
    // variables list is not finished. Need to make CPools before.

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static void GameShutdown();

    static bool StartLoadTxd(int index, RwStream* stream);
    static bool FinishLoadTxd(int index, RwStream* stream);
    static bool LoadTxd(int index, RwStream* stream);
    static bool LoadTxd(int index, char const* filename);

    static void PushCurrentTxd();
    static void PopCurrentTxd();
    static void SetCurrentTxd(int index);

    static int FindTxdSlot(char const* name);
    static int FindTxdSlot(unsigned int hash);

    static size_t GetTxd(int index);
    static int GetParentTxdSlot(int index);

    static void Create(int index);

    static int AddTxdSlot(char const* name);
    static void RemoveTxdSlot(int index);
    static void RemoveTxd(int index);

    static TxdDef* AddRef(int index);
    static void RemoveRef(int index);
    static TxdDef* RemoveRefWithoutDelete(int index);
    static unsigned int GetNumRefs(int index);
};
