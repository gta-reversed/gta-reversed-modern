#pragma once

class CSetPiece;

static constexpr auto MAX_SET_PIECES = 210;

class CSetPieces {
public:
    static inline std::array<CSetPiece, MAX_SET_PIECES>& aSetPieces = *reinterpret_cast<std::array<CSetPiece, MAX_SET_PIECES>*>(0xA95818);
    static inline uint32& NumSetPieces = *reinterpret_cast<uint32*>(0xA957FC);
    static inline bool& bDebug = *reinterpret_cast<bool*>(0xA957F8);

public:
    static void InjectHooks();

    static void AddOne(uint8 type, CVector2D cornerA, CVector2D cornerB, CVector2D spawnCoord1, CVector2D targetCoord1, CVector2D spawnCoord2, CVector2D targetCoord2);
    static void Init();
    static bool Load();
    static bool Save();
    static void Update();

    // NOTSA
    auto GetActiveSetPieces() {
        return std::span<CSetPiece>{ aSetPieces.data(), (size_t)NumSetPieces };
    }
};
