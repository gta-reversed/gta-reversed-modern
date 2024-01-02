#include "StdInc.h"

#include "HeapFreeBlockDesc.h"

HeapFreeBlockDesc::HeapFreeBlockDesc() : HeapBlockDesc(), m_Next(nullptr), m_Prev(nullptr) {

}

HeapFreeBlockDesc* HeapFreeBlockDesc::FindSmallestFreeBlock(int32 size) {
    HeapFreeBlockDesc* block = this;
    do {
        block = block->m_Next;
        assert(block);
    } while (block->m_nSize < size);
    return block;
}

void HeapFreeBlockDesc::InsertOrderedHeapFreeBlock(HeapFreeBlockDesc* desc) {
    assert(desc);
    FindSmallestFreeBlock(desc->m_nSize)->m_Prev->InsertHeapFreeBlock(desc);
}

void HeapFreeBlockDesc::InsertHeapFreeBlock(HeapFreeBlockDesc* desc) {
    assert(desc);
    assert(m_Next && m_Prev);

    desc->m_Next = m_Next;
    desc->m_Prev = this;
    m_Next->m_Prev = desc;
    m_Next = desc;
}

void HeapFreeBlockDesc::ReplaceHeapFreeBlock(HeapFreeBlockDesc* desc) {
    assert(desc);
    assert(m_Next && m_Prev);

    desc->m_Next = m_Next;
    m_Next->m_Prev = desc;
    desc->m_Prev = m_Prev;
    m_Prev->m_Next = desc;
}

void HeapFreeBlockDesc::RemoveHeapFreeBlock() {
    assert(m_Next && m_Prev);

    m_Next->m_Prev = m_Prev;
    m_Prev->m_Next = m_Next;
}
