#pragma once

#include "CompressedMatrixNotAligned.h"

class CObjectSaveStructure {
public:
    CCompressedMatrixNotAligned m_matrix;
    int8                        pad0x14[4];
    uint8                       m_nBonusValue;
    int8                        pad0x19;
    uint16                      m_nCostValue;
    int32                       m_nRemovalTime;
    uint32                      m_nEntityFlags;
    int8                        m_nUnused;
    int8                        pad0x25[3];
    uint32                      m_nObjectFlags;
    int8                        m_nObjectType;
    uint8                       m_nColDamageEffect;
    uint8                       m_nSpecialColResponseCase;
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
            uint8 m_bMeleeProof            : 1;
            uint8 m_bExplosionProof        : 1;
            uint8                          : 1;
        };
    };

public:
    static void InjectHooks();

    void Construct(CObject* obj);
    void Extract(CObject* obj);
};
VALIDATE_SIZE(CObjectSaveStructure, 0x30);
