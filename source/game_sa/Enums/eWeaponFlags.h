/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

enum eWeaponFlags : uint32 {
    WEAPON_CANAIM = 0x1,
    WEAPON_AIMWITHARM = 0x2,
    WEAPON_1STPERSON = 0x4,
    WEAPON_ONLYFREEAIM = 0x8,
    WEAPON_MOVEAIM = 0x10,
    WEAPON_MOVEFIRE = 0x20,
    WEAPON_THROW = 0x100,
    WEAPON_HEAVY = 0x200,
    WEAPON_CONTINUOUSFIRE = 0x400,
    WEAPON_TWIN_PISTOL = 0x800,
    WEAPON_RELOAD = 0x1000,
    WEAPON_CROUCHFIRE = 0x2000,
    WEAPON_RELOAD2START = 0x4000,
    WEAPON_LONG_RELOAD = 0x8000,
    WEAPON_SLOWSDWN = 0x10000,
    WEAPON_RANDSPEED = 0x20000,
    WEAPON_EXPANDS = 0x40000
};
