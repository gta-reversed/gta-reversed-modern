/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

CPool<TxdDef>*& CTxdStore::ms_pTxdPool = *(CPool<TxdDef>**)0xC8800C;

RwTexDictionary* CTxdStore::ms_pStoredTxd;
// variables list is not finished. Need to make CPools before.

void CTxdStore::InjectHooks() {
    // ReversibleHooks::Install("CTxdStore", "PushCurrentTxd", 0x7316A0, &CTxdStore::PushCurrentTxd);
    // ReversibleHooks::Install("CTxdStore", "PopCurrentTxd", 0x7316B0, &CTxdStore::PopCurrentTxd);
    // ReversibleHooks::Install("CTxdStore", "FindTxdSlot_name", 0x731850, static_cast<int (*)(char const*)>(&CTxdStore::FindTxdSlot));
    // ReversibleHooks::Install("CTxdStore", "FindTxdSlot_hash", 0x7318E0, static_cast<int (*)(unsigned int)>(&CTxdStore::FindTxdSlot));
    // ReversibleHooks::Install("CTxdStore", "StartLoadTxd", 0x731930, &CTxdStore::StartLoadTxd);
    // ReversibleHooks::Install("CTxdStore", "Create", 0x731990, &CTxdStore::Create);
    // ReversibleHooks::Install("CTxdStore", "SetCurrentTxd", 0x7319C0, &CTxdStore::SetCurrentTxd);
    // ReversibleHooks::Install("CTxdStore", "AddRef", 0x731A00, &CTxdStore::AddRef);
    // ReversibleHooks::Install("CTxdStore", "RemoveRef", 0x731A30, &CTxdStore::RemoveRef);
    // ReversibleHooks::Install("CTxdStore", "RemoveRefWithoutDelete", 0x731A70, &CTxdStore::RemoveRefWithoutDelete);
    // ReversibleHooks::Install("CTxdStore", "GetNumRefs", 0x731AA0, &CTxdStore::GetNumRefs);
    // ReversibleHooks::Install("CTxdStore", "AddTxdSlot", 0x731C80, &CTxdStore::AddTxdSlot);
    // ReversibleHooks::Install("CTxdStore", "RemoveTxdSlot", 0x731CD0, &CTxdStore::RemoveTxdSlot);
    // ReversibleHooks::Install("CTxdStore", "LoadTxd_stream", 0x731DD0, static_cast<bool (*)(int, RwStream*)>(&CTxdStore::LoadTxd));
    ReversibleHooks::Install("CTxdStore", "LoadTxd_filename", 0x7320B0, static_cast<bool (*)(int, char const*)>(&CTxdStore::LoadTxd));
    // ReversibleHooks::Install("CTxdStore", "FinishLoadTxd", 0x731E40, &CTxdStore::FinishLoadTxd);
    // ReversibleHooks::Install("CTxdStore", "RemoveTxd", 0x731E90, &CTxdStore::RemoveTxd);
    // ReversibleHooks::Install("CTxdStore", "Initialise", 0x731F20, &CTxdStore::Initialise);
    // ReversibleHooks::Install("CTxdStore", "Shutdown", 0x732000, &CTxdStore::Shutdown);
    // ReversibleHooks::Install("CTxdStore", "GameShutdown", 0x732060, &CTxdStore::GameShutdown);
    // ReversibleHooks::Install("CTxdStore", "GetParentTxdSlot", 0x0, &CTxdStore::GetParentTxdSlot);
    // ReversibleHooks::Install("CTxdStore", "GetTxd", 0x408340, &CTxdStore::GetTxd);
}

// initialise txd store
// 0x731F20
void CTxdStore::Initialise() {
    ((void(__cdecl*)())0x731F20)();
}

// shutdown txd store
// 0x732000
void CTxdStore::Shutdown() {
    ((void(__cdecl*)())0x732000)();
}

// 0x732060
void CTxdStore::GameShutdown() {
    ((void(__cdecl*)())0x732060)();
}

// 0x731930
bool CTxdStore::StartLoadTxd(int index, RwStream* stream) {
    return ((bool(__cdecl*)(int, RwStream*))0x731930)(index, stream);
}

// 0x731E40
bool CTxdStore::FinishLoadTxd(int index, RwStream* stream) {
    return ((bool(__cdecl*)(int, RwStream*))0x731E40)(index, stream);
}

// load txd from stream
// 0x731DD0
bool CTxdStore::LoadTxd(int index, RwStream* stream) {
    return ((bool(__cdecl*)(int, RwStream*))0x731DD0)(index, stream);
}

// load txd from file
// 0x7320B0
bool CTxdStore::LoadTxd(int index, char const* filename) {
    char      data[260];
    RwStream* stream{};
    sprintf(data, "%s", filename);
    do {
        stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, data);
    } while (!stream);
    bool loaded = CTxdStore::LoadTxd(index, stream);
    RwStreamClose(stream, nullptr);
    return loaded;
}

// store current txd
// 0x7316A0
void CTxdStore::PushCurrentTxd() {
    ((void(__cdecl*)())0x7316A0)();
}

// restore txd
// 0x7316B0
void CTxdStore::PopCurrentTxd() {
    ((void(__cdecl*)())0x7316B0)();
}

// set the txd to work with
// 0x7319C0
void CTxdStore::SetCurrentTxd(int index) {
    ((void(__cdecl*)(int))0x7319C0)(index);
}

// find txd by name. Returning value is txd index
// 0x731850
int CTxdStore::FindTxdSlot(char const* name) {
    return ((int(__cdecl*)(char const*))0x731850)(name);
}

// find txd by name hash. Returning value is txd index
// 0x7318E0
int CTxdStore::FindTxdSlot(unsigned int hash) {
    return ((signed int(__cdecl*)(unsigned int))0x7318E0)(hash);
}

// plugin-sdk has named it to getTexDictionary
size_t CTxdStore::GetTxd(int index) {
    return plugin::CallAndReturn<size_t, 0x408340, int>(index);
}

// plugin-sdk has named it to getTXDEntryParentIndex
// 0x408370
int CTxdStore::GetParentTxdSlot(int index) {
    return plugin::CallAndReturn<int, 0x408370, int>(index);
}

// create rw tex dictionary for txd slot
// 0x731990
void CTxdStore::Create(int index) {
    ((void(__cdecl*)(int))0x731990)(index);
}

// allocate new slot for this txd
// 0x731C80
int CTxdStore::AddTxdSlot(char const* name) {
    return ((int(__cdecl*)(char const*))0x731C80)(name);
}

// remove txd slot
// 0x731CD0
void CTxdStore::RemoveTxdSlot(int index) {
    ((void(__cdecl*)(int))0x731CD0)(index);
}

// remove txd
// 0x731E90
void CTxdStore::RemoveTxd(int index) {
    ((void(__cdecl*)(int))0x731E90)(index);
}

// add reference for txd
// 0x731A00
TxdDef* CTxdStore::AddRef(int index) {
    return ((TxdDef * (__cdecl*)(int))0x731A00)(index);
}

// remove reference, if references count is 0, then delete txd
// 0x731A30
void CTxdStore::RemoveRef(int index) {
    ((void(__cdecl*)(int))0x731A30)(index);
}

// remove reference without deleting
// 0x731A70
TxdDef* CTxdStore::RemoveRefWithoutDelete(int index) {
    return ((TxdDef * (__cdecl*)(int))0x731A70)(index);
}

// get references count
// 0x731AA0
unsigned int CTxdStore::GetNumRefs(int index) {
    return ((unsigned int(__cdecl*)(int))0x731AA0)(index);
}
