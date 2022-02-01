/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CEntity;

class CReference {
public:
    class CReference* m_pNext;
    class CEntity**   m_ppEntity;
};

VALIDATE_SIZE(CReference, 8);
