/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CWeaponInfo* aWeaponInfo = (CWeaponInfo*)0xC8AAB8;

CWeaponInfo::CWeaponInfo()
{
    ((void(__thiscall*)(CWeaponInfo*))0x743C30)(this);
}

CWeaponInfo::~CWeaponInfo()
{
    ((void(__thiscall*)(CWeaponInfo*))0x743C40)(this);
}

char** CWeaponInfo::ms_aWeaponNames = (char**)0x8D6150;

void CWeaponInfo::LoadWeaponData()
{
    ((void(__cdecl*)())0x5BE670)();
}

CWeaponInfo* CWeaponInfo::GetWeaponInfo(eWeaponType weaponType, unsigned char skill)
{
    return ((CWeaponInfo * (__cdecl*)(eWeaponType, unsigned char))0x743C60)(weaponType, skill);
}

eWeaponType CWeaponInfo::FindWeaponType(char* name)
{
    return ((eWeaponType(__cdecl*)(char*))0x743D10)(name);
}

eWeaponFire CWeaponInfo::FindWeaponFireType(char* name)
{
    return ((eWeaponFire(__cdecl*)(char*))0x5BCF30)(name);
}

void CWeaponInfo::Initialise()
{
    ((void(__cdecl*)())0x5BF750)();
}

void CWeaponInfo::Shutdown()
{
    ((void(__cdecl*)())0x743C50)();
}