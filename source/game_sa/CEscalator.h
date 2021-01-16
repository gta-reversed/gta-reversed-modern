#pragma once
#include "PluginBase.h"

class CEscalator {
public:
    CVector m_vStart;
    CVector m_vBottom;
    CVector m_vTop;
    CVector m_vEnd;
    CMatrix m_mRotation;
    bool m_bExist;
    char m_bObjectsCreated;
    char m_bMoveDown;
private:
    char __pad;
public:
    int m_dwNumIntermediatePlanes;
    unsigned int m_dwNumBottomPlanes;
    unsigned int m_dwNumTopPlanes;
private:
    char __unused[8];
public:
    RwSphere m_Bounding;
    float m_dwCurrentPosition;
    void* m_pEntity;
    void* m_pObjects[42];

public:
    static void InjectHooks();

public:
    void SwitchOff();
    void AddThisOne(CVector const& vecStart, CVector const& vecBottom, CVector const& vecEnd, CVector const& vecTop, bool bMoveDown, CEntity* pEntity);
    void Update();
};

VALIDATE_SIZE(CEscalator, 0x150);
