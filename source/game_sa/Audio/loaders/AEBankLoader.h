#pragma once

enum class eSoundRequestStatus : uint32 {
    UNK_0,
    JUST_LOADED,
    ALREADY_LOADED,
    UNK_3
};

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

constexpr auto NUM_BANK_SLOT_ITEMS = 400u;

struct CAEBankSlot {
    uint32 m_nOffset;
    uint32 m_nSize;
    uint32 field_8;
    uint32 field_C;
    int16 m_nBankId;
    int16 m_nSoundCount; // -1: Single sound.
    CAEBankSlotItem m_aSlotItems[NUM_BANK_SLOT_ITEMS];

    bool IsSingleSound() const { return m_nSoundCount == -1; }
};
VALIDATE_SIZE(CAEBankSlot, 0x12D4);

struct tPakLookup {
    char m_szName[12];
    uint32 field_0C[10];
};
VALIDATE_SIZE(tPakLookup, 0x34);

// NOTSA
struct CdAudioStream {
    int16 m_nSoundCount;
    int16 __pad;
    CAEBankSlotItem m_aSlotItems[400];
    uint8 m_aBankData[]; // uint16 samples?
};
VALIDATE_SIZE(CdAudioStream, 0x12C4 /* + samples*/);

class CAESoundRequest {
public:
    CAEBankSlot* m_pBankSlotInfo;
    uint32 m_nBankOffset;
    uint32 m_nBankSize;
    CdAudioStream* m_pStreamOffset;
    CdAudioStream* m_pStreamBuffer;
    eSoundRequestStatus m_nStatus;
    uint16 m_nBankId;
    uint16 m_nBankSlotId;
    uint16 m_nNumSounds;
    uint8 m_nPakFileNumber;

    void Reset() {
        m_nBankId = m_nBankSlotId = m_nNumSounds = -1;
        m_pBankSlotInfo = nullptr;
        m_nStatus = eSoundRequestStatus::UNK_0;
    }

    bool IsSingleSound() const {
        return m_nNumSounds == (uint16)-1;
    }
};
VALIDATE_SIZE(CAESoundRequest, 0x20);

class CAEBankLoader {
public:
    CAEBankSlot* m_paBankSlots;
    CAEBankLookupItem* m_paBankLookups;
    tPakLookup* m_paPakLookups;
    uint16 m_nBankSlotCount;
    uint16 m_nBankLookupCount;
    int16 m_nPakLookupCount;
    uint16 __pad;
    bool m_bInitialised;
    uint32 m_nBufferSize;
    uint8* m_pBuffer;
    int32* m_paStreamHandles;
    CAESoundRequest m_aRequests[50];
    uint16 field_664;
    uint16 m_iRequestCount;
    uint16 m_iNextRequest;
    uint16 m_iStreamingChannel;
    uint16 m_aBankSlotSound[60];

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
