/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "ColSphere.h"
#include "ColBox.h"
#include "ColLine.h"
#include "CompressedVector.h"
#include "ColTriangle.h"
#include "ColTrianglePlane.h"
#include "ColDisk.h"
#include "Link.h"

class CCollisionData {
public:
    CCollisionData();

public:
    uint16 m_nNumSpheres;       // 0x00
    uint16 m_nNumBoxes;         // 0x02
    uint16 m_nNumTriangles;     // 0x04
    uint8  m_nNumLines;         // 0x06


    struct { // 0x07
        uint8 bUsesDisks : 1;
        uint8 bNotEmpty : 1;
        uint8 bHasShadowInfo : 1;
        uint8 bHasFaceGroups : 1;
        uint8 bHasShadow : 1;
    };

    CColSphere* m_pSpheres;    // 0x08
    CColBox*    m_pBoxes;      // 0x0C

    union { // 0x10
        CColLine* m_pLines;
        CColDisk* m_pDisks;
    };
        
    CompressedVector*  m_pVertices;             // 0x14
    CColTriangle*      m_pTriangles;            // 0x18
    CColTrianglePlane* m_pTrianglePlanes;       // 0x1C
    uint32             m_nNumShadowTriangles;   // 0x20
    uint32             m_nNumShadowVertices;    // 0x24
    CompressedVector*  m_pShadowVertices;       // 0x28
    CColTriangle*      m_pShadowTriangles;      // 0x2C

    // <size 0x30>

public:
    static void InjectHooks();

    void RemoveCollisionVolumes();
    void Copy(CCollisionData const& src);
    void CalculateTrianglePlanes();
    void RemoveTrianglePlanes();
    void GetTrianglePoint(CVector& outVec, int32 vertId);
    void GetShadTrianglePoint(CVector& outVec, int32 vertId);
    void SetLinkPtr(CLink<CCollisionData*>* link);
    CLink<CCollisionData*>* GetLinkPtr();

private:
    // HELPERS
    template <typename T> T* GetPointerToColArray(uint32 byteOffset) {
        return reinterpret_cast<T*>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    }

    friend class CColModel;
};

VALIDATE_SIZE(CCollisionData, 0x30);
