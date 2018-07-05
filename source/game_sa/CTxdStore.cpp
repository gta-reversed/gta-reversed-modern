#include "StdInc.h"

int CTxdStore::GetParentTxdSlot(int index)
{
    typedef int(__cdecl* hGetParentTxdSlot)( int index );
    hGetParentTxdSlot _GetParentTxdSlot = (hGetParentTxdSlot)0x00408370;
    return _GetParentTxdSlot(index);
}