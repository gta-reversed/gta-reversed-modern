/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include "TxdDef.h"
#include "CPool.h"

class  CTxdStore
{
public:
	// class variables

	static CPool<TxdDef> *&ms_pTxdPool;

	static RwTexDictionary *ms_pStoredTxd;
	// variables list is not finished. Need to make CPools before.

	// class functions

	// store current txd
	static void PushCurrentTxd();
	// restore txd
	static void PopCurrentTxd();
	// find txd by name. Returning value is txd index
	static int FindTxdSlot(char  const* name);
	// find txd by name hash. Returning value is txd index
	static int FindTxdSlot(unsigned int hash);
	static bool StartLoadTxd(int index, RwStream *stream);
	// create rw tex dictionary for txd slot
	static void Create(int index);
	// set the txd to work with
	static void SetCurrentTxd(int index);
	// add reference for txd
	static TxdDef *AddRef(int index);
	// remove reference, if references count is 0, then delete txd
	static void RemoveRef(int index);
	// remove reference without deleting
	static TxdDef *RemoveRefWithoutDelete(int index);
	// get references count
	static unsigned int GetNumRefs(int index);
	// allocate new slot for this txd
	static int AddTxdSlot(char  const* name);
	// remove txd slot
	static void RemoveTxdSlot(int index);
	// load txd from stream
	static bool LoadTxd(int index, RwStream *stream);
	static bool FinishLoadTxd(int index, RwStream *stream);
	// remove txd
	static void RemoveTxd(int index);
	// initialise txd store
	static void Initialise();
	// shutdown txd store
	static void Shutdown();
	static void GameShutdown();
	// load txd from file
	static bool LoadTxd(int index, char  const* filename);
    // plugin-sdk has named it to getTXDEntryParentIndex
    static int GetParentTxdSlot(int index);
};