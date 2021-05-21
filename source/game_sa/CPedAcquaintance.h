/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CAcquaintance {
public:
    static void InjectHooks();

    unsigned int GetAcquaintances(unsigned int acquaintanceID);
    void SetAcquaintances(int acquaintanceId, unsigned int value);
    void ClearAcquaintances(unsigned int acquaintanceId);
    void SetAsAcquaintance(unsigned int acquaintanceId, unsigned int pedTypeBitNum);
    void ClearAsAcquaintance(unsigned int acquaintanceId, unsigned int pedTypeBitNum);
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
class CPedAcquaintance : public CAcquaintance {
public:
    unsigned int m_nRespect;
    unsigned int m_nLike;
    unsigned int m_nIgnore;
    unsigned int m_nDislike;
    unsigned int m_nHate;

public:
    static void InjectHooks();

    CPedAcquaintance();
    ~CPedAcquaintance();
};

VALIDATE_SIZE(CPedAcquaintance, 0x14);
