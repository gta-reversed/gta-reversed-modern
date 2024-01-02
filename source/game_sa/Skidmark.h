#pragma once

enum class eSkidmarkType : uint32 {
    DEFAULT = 0,
    SANDY,
    MUDDY,
    BLOODY,
};

enum class eSkidmarkState : uint8 {
    INACTIVE,
    JUST_UPDATED,
    DISAPPEARING // Set after `JUST_UPDATED`. See `CSkidmark::Update`.
};

constexpr auto SKIDMARK_NUM_PARTS{ 16u };
/*
 * Doesn't exist in Android IDB
 */
struct CSkidmark {
    CVector        m_vPosn[SKIDMARK_NUM_PARTS];
    float          m_partDirX[SKIDMARK_NUM_PARTS];
    float          m_partDirY[SKIDMARK_NUM_PARTS];
    uint32         m_nId;                       // Unique ID, usually the vehicle pointer
    uint32         m_lastDisappearTimeUpdateMs; // Last time it got updated
    uint32         m_fadeBeginMs;               // Begins fading at this tick
    uint32         m_disappearAtMs;             // Should disappear by this tick
    eSkidmarkType  m_nType;
    uint16         m_nNumParts;                 // Number of parts. The 0th 'part' isn't actually considered a part, so this number never exeeds SKIDMARK_NUM_PARTS - 1
    eSkidmarkState m_nState;
    bool           m_bActive;

    CVector GetPartPosn(unsigned i) const { return m_vPosn[i]; }
    CVector GetLastPartPosn() const { return GetPartPosn(m_nNumParts); }
    CVector GetFirstPartPosn() const { return GetPartPosn(0); }
    CSphere GetBoundingSphere() const;

    void Init(uint32 id, CVector posn, eSkidmarkType type, const bool* bloodState);
    void Update();
    void Render() const;
    void RegisterNewPart(CVector posn, CVector2D dir, float length, bool* bloodState);

    CRGBA GetColor() const;
};
VALIDATE_SIZE(CSkidmark, 0x158);
