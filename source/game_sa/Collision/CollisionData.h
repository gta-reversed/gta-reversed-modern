/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CColSphere.h"
#include "CColBox.h"
#include "CColLine.h"
#include "CompressedVector.h"
#include "CColTriangle.h"
#include "CColTrianglePlane.h"
#include "CColDisk.h"
#include "CLink.h"

class CCollisionData {
public:
    CCollisionData();

public:
    uint16 m_nNumSpheres;
    uint16 m_nNumBoxes;
    uint16 m_nNumTriangles;
    uint8  m_nNumLines;
    struct {
        uint8 bUsesDisks : 1;
        uint8 bNotEmpty : 1;
        uint8 bHasShadowInfo : 1;
        uint8 bHasFaceGroups : 1;
        uint8 bHasShadow : 1;
    };
    CColSphere* m_pSpheres;
    CColBox*    m_pBoxes;
    union {
        CColLine* m_pLines;
        CColDisk* m_pDisks;
    };
    CompressedVector*  m_pVertices;
    CColTriangle*      m_pTriangles;
    CColTrianglePlane* m_pTrianglePlanes;
    uint32             m_nNumShadowTriangles;
    uint32             m_nNumShadowVertices;
    CompressedVector*  m_pShadowVertices;
    CColTriangle*      m_pShadowTriangles;

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
