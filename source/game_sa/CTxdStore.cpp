/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CPool<TxdDef> *&CTxdStore::ms_pTxdPool = *(CPool<TxdDef> **)0xC8800C;

RwTexDictionary *CTxdStore::ms_pStoredTxd;
// variables list is not finished. Need to make CPools before.

// class functions

// store current txd
void CTxdStore::PushCurrentTxd()
{
    ((void(__cdecl *)())0x7316A0)();
}

// restore txd
void CTxdStore::PopCurrentTxd()
{
    ((void(__cdecl *)())0x7316B0)();
}

// find txd by name. Returning value is txd index
int CTxdStore::FindTxdSlot(char  const* name)
{
    return ((int(__cdecl *)(char  const*))0x731850)(name);
}

// find txd by name hash. Returning value is txd index
signed int CTxdStore::FindTxdSlot(unsigned int hash)
{
    return ((signed int(__cdecl *)(unsigned int))0x7318E0)(hash);
}

bool CTxdStore::StartLoadTxd(int index, RwStream *stream)
{
    return ((bool(__cdecl *)(int, RwStream *))0x731930)(index, stream);
}

// create rw tex dictionary for txd slot
void CTxdStore::Create(int index)
{
    ((void(__cdecl *)(int))0x731990)(index);
}

// set the txd to work with
void CTxdStore::SetCurrentTxd(int index)
{
    ((void(__cdecl *)(int))0x7319C0)(index);
}

// add reference for txd
TxdDef *CTxdStore::AddRef(int index)
{
    return ((TxdDef *(__cdecl *)(int))0x731A00)(index);
}

// remove reference, if references count is 0, then delete txd
void CTxdStore::RemoveRef(int index)
{
    ((void(__cdecl *)(int))0x731A30)(index);
}

// remove reference without deleting
TxdDef *CTxdStore::RemoveRefWithoutDelete(int index)
{
    return ((TxdDef *(__cdecl *)(int))0x731A70)(index);
}

// get references count
unsigned int CTxdStore::GetNumRefs(int index)
{
    return ((unsigned int(__cdecl *)(int))0x731AA0)(index);
}

// allocate new slot for this txd
int CTxdStore::AddTxdSlot(char  const* name)
{
    return ((int(__cdecl *)(char  const*))0x731C80)(name);
}

// remove txd slot
void CTxdStore::RemoveTxdSlot(int index)
{
    ((void(__cdecl *)(int))0x731CD0)(index);
}

// load txd from stream
bool CTxdStore::LoadTxd(int index, RwStream *stream)
{
    return ((bool(__cdecl *)(int, RwStream *))0x731DD0)(index, stream);
}

bool CTxdStore::FinishLoadTxd(int index, RwStream *stream)
{
    return ((bool(__cdecl *)(int, RwStream *))0x731E40)(index, stream);
}

// remove txd
void CTxdStore::RemoveTxd(int index)
{
    ((void(__cdecl *)(int))0x731E90)(index);
}

// initialise txd store
void CTxdStore::Initialise()
{
    ((void(__cdecl *)())0x731F20)();
}

// shutdown txd store
void CTxdStore::Shutdown()
{
    ((void(__cdecl *)())0x732000)();
}

void CTxdStore::GameShutdown()
{
    ((void(__cdecl *)())0x732060)();
}

// load txd from file
bool CTxdStore::LoadTxd(int index, char  const* filename)
{
    return ((bool(__cdecl *)(int, char  const*))0x7320B0)(index, filename);
}

int CTxdStore::GetParentTxdSlot(int index)
{
    typedef int(__cdecl* hGetParentTxdSlot)( int index );
    hGetParentTxdSlot _GetParentTxdSlot = (hGetParentTxdSlot)0x00408370;
    return _GetParentTxdSlot(index);
}