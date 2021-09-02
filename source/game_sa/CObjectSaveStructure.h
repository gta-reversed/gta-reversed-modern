#pragma once
#include "CCompressedMatrixNotAligned.h"

class CObjectSaveStructure
{
public:
    CCompressedMatrixNotAligned m_matrix;
    uint8   pad0x14[4];
    uint8   m_nBonusValue;
    int8_t    pad0x19;
    uint16  m_nCostValue;
    int32_t   m_nRemovalTime;
    uint32  m_nEntityFlags;
    int8_t    m_nUnused;
    uint8   pad0x25[3];
    uint32  m_nObjectFlags;
    int8_t    m_nObjectType;
    uint8   m_nColDamageEffect;
    uint8   m_nSpecialColResponseCase;
    union
    {
        uint8   m_nPhysicalFlags;
        struct
        {
            uint8 m_bDisableCollisionForce : 1;
            uint8 m_bDontApplySpeed        : 1;
            uint8 m_bBulletProof           : 1;
            uint8 m_bFireProof             : 1;
            uint8 m_bCollisionProof        : 1;
            uint8 m_bMeeleProof            : 1;
            uint8 m_bExplosionProof        : 1;
            uint8                        : 1;
        };
    };

public:
    static void InjectHooks();

    void Construct(CObject* pObject);
    void Extract(CObject* pObject);
};
VALIDATE_SIZE(CObjectSaveStructure, 0x30);
