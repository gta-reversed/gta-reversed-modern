#pragma once

class CZone;

class CPlaceName {
public:
    CZone* m_pZone;
    uint16 m_nAdditionalTimer;
    char   _pad[2];

public:
    static void InjectHooks();

    void Init();
    void Clear();
    const char* GetForMap(float x, float y);
    void Process();
    inline void Display() const;
};

VALIDATE_SIZE(CPlaceName, 0x8);
