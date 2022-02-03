#pragma once

#include "renderware.h"

#include "Vector.h"
#include "Matrix.h"

class CEscalator {
public:
    CVector  m_vStart;
    CVector  m_vBottom;
    CVector  m_vTop;
    CVector  m_vEnd;
    CMatrix  m_mRotation;
    bool     m_bExist;
    char     m_bObjectsCreated;
    char     m_bMoveDown;
    char     __pad;
    int32    m_dwNumIntermediatePlanes;
    uint32   m_dwNumBottomPlanes;
    uint32   m_dwNumTopPlanes;
    char     __unused[8];
    RwSphere m_Bounding;
    float    m_dwCurrentPosition;
    void*    m_pEntity;
    void*    m_pObjects[42];

public:
    static void InjectHooks();

public:
    void SwitchOff();
    void AddThisOne(const CVector& vecStart, const CVector& vecBottom,const  CVector& vecEnd,const  CVector& vecTop, bool bMoveDown, CEntity* entity);
    void Update();
};

VALIDATE_SIZE(CEscalator, 0x150);
