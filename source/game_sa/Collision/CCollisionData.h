/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
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
    uint16_t     m_nNumSpheres;
    uint16_t     m_nNumBoxes;
    uint16_t     m_nNumTriangles;
    uint8_t      m_nNumLines;
    struct {
        uint8_t   bUsesDisks : 1;
        uint8_t   bNotEmpty : 1;
        uint8_t   bHasShadowInfo : 1;
        uint8_t   bHasFaceGroups : 1;
        uint8_t   bHasShadow : 1;
    };
    CColSphere* m_pSpheres;
    CColBox* m_pBoxes;
    union {
        CColLine* m_pLines;
        CColDisk* m_pDisks;
    };
    CompressedVector* m_pVertices;
    CColTriangle* m_pTriangles;
    CColTrianglePlane* m_pTrianglePlanes;
    unsigned int       m_nNumShadowTriangles;
    unsigned int       m_nNumShadowVertices;
    CompressedVector* m_pShadowVertices;
    CColTriangle* m_pShadowTriangles;

public:
    static void InjectHooks();
    
    void RemoveCollisionVolumes();
    void Copy(CCollisionData const& src);
    void CalculateTrianglePlanes();
    void RemoveTrianglePlanes();
    void GetTrianglePoint(CVector& outVec, int vertId);
    void GetShadTrianglePoint(CVector& outVec, int vertId);
    void SetLinkPtr(CLink<CCollisionData*> *link);
    CLink<CCollisionData*> *GetLinkPtr();

private:
    //HELPERS
    template <typename T>
    T* GetPointerToColArray(uint32_t byteOffset)
    {
        return reinterpret_cast<T*>(&reinterpret_cast<uint8_t*>(this)[byteOffset]);
    }

    friend class CColModel;
};

VALIDATE_SIZE(CCollisionData, 0x30);
