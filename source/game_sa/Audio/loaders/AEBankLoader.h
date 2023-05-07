#pragma once

class CAESoundRequest {
public:
    void* m_pBankSlotInfo;
    uint32 m_nBankOffset;
    uint32 m_nBankSize;
    void* m_pStreamOffset;
    void* m_pStreamBuffer;
    uint32 m_nStatus;
    uint16 m_nBankId;
    uint16 m_nBankSlotId;
    uint16 m_nNumSounds;
    uint8 m_nPakFileNumber;
};
VALIDATE_SIZE(CAESoundRequest, 0x20);

struct CAEBankLookupItem {
    uint8 m_nPakFileNumber;
    uint32 m_nOffset;
    uint32 m_nSize;
};
VALIDATE_SIZE(CAEBankLookupItem, 0xC);

struct CAEBankSlotItem {
    uint32 m_nOffset;
    uint32 m_nLoopOffset;
    uint16 m_usSampleRate;
    uint16 m_usSoundHeadroom;
};
VALIDATE_SIZE(CAEBankSlotItem, 0xC);

struct CAEBankSlot {
    uint32 m_nOffset;
    uint32 m_nSize;
    uint32 field_8;
    uint32 field_C;
    uint16 m_nBankId;
    uint16 m_nSoundCount;
    CAEBankSlotItem m_aSlotItems[400];
};
VALIDATE_SIZE(CAEBankSlot, 0x12D4);

struct tPakLookup {
    char m_szName[12];
    uint32 field_0C[10];
};
VALIDATE_SIZE(tPakLookup, 0x34);

class CAEBankLoader {
public:
    CAEBankSlot* m_paBankSlots;
    CAEBankLookupItem* m_paBankLookups;
    tPakLookup* m_paPakLookups;
    uint16 m_nBankSlotCount;
    uint16 m_nBankLookupCount;
    int16 m_nPakLookupCount;
    bool m_bInitialised;
    uint32 m_nBufferSize;
    void* m_pBuffer;
    int32* m_paStreamHandles;
    CAESoundRequest m_aRequests[50];
    uint16 field_664;
    uint16 m_iRequestCount;
    uint16 m_iNextRequest;
    uint16 m_iStreamingChannel;
    uint16 m_aBankSlotSound[60];
    uint32 pad; // not sure

public:
    static void InjectHooks();

    CAEBankLoader() = default;
    ~CAEBankLoader();

    CAEBankLookupItem* GetBankLookup(uint16 bankId);
    bool LoadBankLookupFile();
    bool LoadBankSlotFile();
    bool LoadSFXPakLookupFile();

    void CalculateBankSlotsInfosOffsets();

private:
    // NOTSA
    void Deconstructor() { this->~CAEBankLoader(); }
};
VALIDATE_SIZE(CAEBankLoader, 0x6E4);
