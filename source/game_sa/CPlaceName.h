#pragma once

class CZone;

class CPlaceName {
public:
    CZone* m_pZone;
    uint16 m_nAdditionalTimer;

public:
    static void InjectHooks();

    CPlaceName();

    void Init();
    static const char* GetForMap(float x, float y);
    void Process();
    inline void Display() const;
    void ProcessAfterFrontEndShutDown();

    static CVector CalcPosition() {
        CVector posn;
        auto player = FindPlayerPed();
        if (player->bInVehicle) {
            posn = player->m_pVehicle->GetPosition();
        } else {
            posn = player->GetPosition();
            CEntryExitManager::GetPositionRelativeToOutsideWorld(posn);
        }
        return posn;
    }
};

VALIDATE_SIZE(CPlaceName, 0x8);
