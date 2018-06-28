/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPed.h"
#include "eCopType.h"


class  CCopPed : public CPed {
public:
	char field_79C;
	char field_79D;
private:
	char padding[2];
public:
	eCopType       m_copType;
    int field_7A4;
	CCopPed *m_pCopPartner;
	CPed          *m_apCriminalsToKill[5];
	char field_7C0;

    // we can use modelIds as copType too!
    CCopPed(eCopType copType);

	void SetPartner(CCopPed* partner);
	void AddCriminalToKill(CPed* criminal);
	void RemoveCriminalToKill(CPed* likeUnused, int criminalIdx);
	void ClearCriminalsToKill();
};

VALIDATE_SIZE(CCopPed, 0x7C4);