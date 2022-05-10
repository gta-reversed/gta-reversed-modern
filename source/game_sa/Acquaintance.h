/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Base.h"

typedef int32 AcquaintanceId;
enum {
    ACQUAINTANCE_RESPECT = 0,
    ACQUAINTANCE_LIKE    = 1,
    ACQUAINTANCE_IGNORE  = 2,
    ACQUAINTANCE_DISLIKE = 3,
    ACQUAINTANCE_HATE    = 4,

    ACQUAINTANCE_NUM
};

// This structure stores information about how a ped of given pedtype (each entry in PedRelationship[32]
// is separate pedtype, starting from 0 (PLAYER1) to 31 (MISSION8)) behaves toward any ped of other type.
// Five dwords in this structure (only four of them are used) are the bitmasks,
// where a bit sets a flag of acquaintance type (respect, like, dislike, hate)
// to the pedtype of given index (=number of bit).
// Say, if the 4th bit (counting from zero) in PedRelationship[5].respect is set,
// it means that a ped of type CIVFEMALE (pedtype=5) respects a ped of type CIVMALE (pedtype=4).
//
// These structures are filled with data from the file ped.dat.
// The relationship flags could be changed using opcode 0746 and similar.
//
// https://gtamods.com/wiki/Saves_(GTA_SA)#Block_19:_Ped_Relationships
class CAcquaintance {
public:
    union {
        struct {
            uint32 m_nRespect;
            uint32 m_nLike;
            uint32 m_nIgnore;
            uint32 m_nDislike;
            uint32 m_nHate;
        };
        std::array<uint32, 5> m_acquaintances;
    };

public:
    static void InjectHooks();

    CAcquaintance();
    ~CAcquaintance() = default; // 0x608780

    uint32 GetAcquaintances(AcquaintanceId id);
    void   SetAcquaintances(AcquaintanceId id, uint32 value);
    void   ClearAcquaintances(AcquaintanceId id);

    void   SetAsAcquaintance(AcquaintanceId id, uint32 pedTypeBitNum);
    void   ClearAsAcquaintance(AcquaintanceId id, uint32 pedTypeBitNum);

    [[nodiscard]] auto GetRespect() const { return m_nRespect; }
    [[nodiscard]] auto GetLike()    const { return m_nLike;    }
    [[nodiscard]] auto GetIgnore()  const { return m_nIgnore;  }
    [[nodiscard]] auto GetDislike() const { return m_nDislike; }
    [[nodiscard]] auto GetHate()    const { return m_nHate;    }
};

VALIDATE_SIZE(CAcquaintance, 0x14);
