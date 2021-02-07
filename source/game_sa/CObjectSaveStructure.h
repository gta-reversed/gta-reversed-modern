#pragma once
#include "CCompressedMatrixNotAligned.h"

class CObjectSaveStructure
{
public:
    CCompressedMatrixNotAligned m_matrix;
    uint8_t   pad0x14[4];
    uint8_t   m_nBonusValue;
    int8_t    pad0x19;
    uint16_t  m_nCostValue;
    int32_t   m_nRemovalTime;
    uint32_t  m_nEntityFlags;
    int8_t    m_nUnused;
    uint8_t   pad0x25[3];
    uint32_t  m_nObjectFlags;
    int8_t    m_nObjectType;
    uint8_t   m_nColDamageEffect;
    uint8_t   m_nSpecialColResponseCase;
    union
    {
        uint8_t   m_nPhysicalFlags;
        struct
        {
            uint8_t m_bDisableCollisionForce : 1;
            uint8_t m_bDontApplySpeed        : 1;
            uint8_t m_bBulletProof           : 1;
            uint8_t m_bFireProof             : 1;
            uint8_t m_bCollisionProof        : 1;
            uint8_t m_bMeeleProof            : 1;
            uint8_t m_bExplosionProof        : 1;
            uint8_t                        : 1;
        };
    };

public:
    static void InjectHooks();

    void Construct(CObject* pObject);
    void Extract(CObject* pObject);
};
VALIDATE_SIZE(CObjectSaveStructure, 0x30);
