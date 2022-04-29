#pragma once

class CEntityScanner;

class CPedScanner : public CEntityScanner {
public:
    void ScanForPedsInRange(const CPed& ped);
    CPed* GetClosestPedInRange() const;
};
