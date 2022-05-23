#pragma once

class CNodeRoute {
    uint32       m_nNumAddresses;
    CNodeAddress m_aAddresses[8];

public:
    static void InjectHooks();

    static void* operator new(uint32 size);
    static void operator delete(void* ptr, size_t sz);
};

VALIDATE_SIZE(CNodeRoute, 0x24);
