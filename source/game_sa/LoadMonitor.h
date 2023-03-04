#pragma once

/*
TODO: size of CLoadMonitor is unknown, and it's uncomplete.
*/
class CLoadMonitor {
public:
    uint32 m_bInFrame;
    uint32 m_bUseLoadMonitor;
    uint32 m_bForceProcLevel;
    char  field_C;
    char  field_D;
    char  field_E;
    char  field_F;
    char  field_10;
    char  field_11;
    char  field_12;
    char  field_13;
    char  field_14;
    char  field_15;
    char  field_16;
    char  field_17;
    char  field_18;
    char  field_19;
    char  field_1A;
    char  field_1B;
    char  field_1C;
    char  field_1D;
    char  field_1E;
    char  field_1F;
    char  field_20;
    char  field_21;
    char  field_22;
    char  field_23;
    char  field_24;
    char  field_25;
    char  field_26;
    char  field_27;
    char  field_28;
    char  field_29;
    char  field_2A;
    char  field_2B;
    char  field_2C;
    char  field_2D;
    char  field_2E;
    char  field_2F;
    char  field_30;
    char  field_31;
    char  field_32;
    char  field_33;
    char  field_34;
    char  field_35;
    char  field_36;
    char  field_37;
    char  field_38;
    char  field_39;
    char  field_3A;
    char  field_3B;
    int32 field_3C;
    int32 field_40;
    int32 m_numModelsRequest;
    char  field_48[88];

public:
    static void InjectHooks();

    CLoadMonitor();
    CLoadMonitor* Constructor();

    ~CLoadMonitor() = default; // 0x856430-
    CLoadMonitor*  Destructor();

    void BeginFrame();
    void EndFrame();
    void StartTimer(uint32 timerIndex);
    void EndTimer(uint32 timerIndex);
};

extern CLoadMonitor& g_LoadMonitor;
