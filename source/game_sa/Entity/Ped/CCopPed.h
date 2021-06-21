/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPed.h"

enum eCopType : unsigned int {
    COP_TYPE_CITYCOP,
    COP_TYPE_LAPDM1,
    COP_TYPE_SWAT1,
    COP_TYPE_SWAT2,
    COP_TYPE_FBI,
    COP_TYPE_ARMY,
    COP_TYPE_CSHER = 7
};

class CCopPed : public CPed {
public:
    bool     m_bDontPursuit;
    char     field_79D;
    char     _pad[2];
    eCopType m_copType;
    int      field_7A4;
    CCopPed* m_pCopPartner;
    CPed*    m_apCriminalsToKill[5];
    char     field_7C0;

    // we can use modelIds as copType too!
    CCopPed(eCopType copType);

    void SetPartner(CCopPed* partner);
    void AddCriminalToKill(CPed* criminal);
    void RemoveCriminalToKill(CPed* likeUnused, int criminalIdx);
    void ClearCriminalsToKill();
};

VALIDATE_SIZE(CCopPed, 0x7C4);
