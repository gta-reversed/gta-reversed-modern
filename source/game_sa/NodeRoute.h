#pragma once

class CNodeRoute {
public:
    static void InjectHooks();

    static void* operator new(uint32 size);
    static void operator delete(void* ptr, size_t sz);

    auto GetAddresses() const { return m_Addresses | rng::views::take(m_NumAddresses); }
private:
    uint32       m_NumAddresses{};
    CNodeAddress m_Addresses[8]{};
};
VALIDATE_SIZE(CNodeRoute, 0x24);
