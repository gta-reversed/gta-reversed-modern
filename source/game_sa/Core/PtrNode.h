/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CPtrNode {
public:
    void*     m_item;
    CPtrNode* m_next;

    CPtrNode(void* item) : m_item(item) {}
    CPtrNode* GetNext() const { return m_next; }
};

VALIDATE_SIZE(CPtrNode, 8);