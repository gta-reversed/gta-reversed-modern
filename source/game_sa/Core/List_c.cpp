#include "StdInc.h"


// US-1.00 @ 0x004A8DD0
// EU-1.00 @ 0x004A8DD0
List_c::List_c(void) {
    plugin::CallMethod<0x004A8DD0>(this);
}

// US-1.00 @ 0x004A8DE0
// EU-1.00 @ 0x004A8DE0
List_c::~List_c(void) {
    plugin::CallMethod<0x004A8DE0>(this);
}

// US-1.00 @ 0x004A8DF0
// EU-1.00 @ 0x004A8DF0
void List_c::AddItem(ListItem_c * pItem) {
    assert(pItem);
    return plugin::CallMethod<0x004A8DF0, List_c *, ListItem_c *>(this, pItem);
}

// US-1.00 @ 0x004A8E30
// EU-1.00 @ 0x004A8E30
void List_c::RemoveItem(ListItem_c * pItem) {
    assert(pItem);
    return plugin::CallMethod<0x004A8E30, List_c *, ListItem_c *>(this, pItem);
}

ListItem_c * List_c::GetHead(void) {
    return first;
}

// EU-1.00 @ 0x004A8E70
ListItem_c * List_c::RemoveHead(void) {
    return plugin::CallMethodAndReturn<ListItem_c *, 0x004A8E70, List_c *>(this);
}

ListItem_c * List_c::GetNext(ListItem_c * pItem) {
    assert(pItem);
    return pItem->next;
}

// US-1.00 @ 0x004A9000
// EU-1.00 @ 0x004A9000
ListItem_c * List_c::GetPrev(ListItem_c * pItem) {
    assert(pItem);
    return plugin::CallMethodAndReturn<ListItem_c *, 0x004A9000, List_c *, ListItem_c *>(this, pItem);
}

// US-1.00 @ 0x004A9010
// EU-1.00 @ 0x004A9010
ListItem_c * List_c::GetItemOffset(bool bFromHead, int iOffset) {
    return plugin::CallMethodAndReturn<ListItem_c *, 0x004A9010, List_c *, bool, int>(this, bFromHead, iOffset);
}
