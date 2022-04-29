#pragma once

#include "HeapBlockDesc.h"

/**
 * Free heap block descriptor
 */
class HeapFreeBlockDesc : public HeapBlockDesc {
public:
    HeapFreeBlockDesc* m_Next;
    HeapFreeBlockDesc* m_Prev;

public:
    HeapFreeBlockDesc();

    HeapFreeBlockDesc* FindSmallestFreeBlock(int32 size);
    void InsertOrderedHeapFreeBlock(HeapFreeBlockDesc* desc);
    void InsertHeapFreeBlock(HeapFreeBlockDesc* desc);
    void ReplaceHeapFreeBlock(HeapFreeBlockDesc* desc);
    void RemoveHeapFreeBlock();
};
//VALIDATE_SIZE(HeapBlockDesc, 0x18);
