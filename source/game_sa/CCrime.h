#pragma once

class CPed;
enum class eCrimeType;

class CCrime
{
public:
    static void ReportCrime(eCrimeType crimeType, CPed* ped1, CPed* ped2);
};
