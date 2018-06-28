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
    unsigned short     m_nNumSpheres;
    unsigned short     m_nNumBoxes;
    unsigned short     m_nNumTriangles;
    unsigned char      m_nNumLines;
    struct {
        unsigned char   bUsesDisks : 1;
        unsigned char   bNotEmpty : 1;
        unsigned char b03 : 1;
        unsigned char   bHasFaceGroups : 1;
        unsigned char   bHasShadow : 1;
    }                  m_nFlags;
    CColSphere        *m_pSpheres;
    CColBox           *m_pBoxes;
    union {
        CColLine      *m_pLines;
        CColDisk      *m_pDisks;
    };
    CompressedVector  *m_pVertices;
    CColTriangle      *m_pTriangles;
    CColTrianglePlane *m_pTrianglePlanes;
    unsigned int       m_nNumShadowTriangles;
    unsigned int       m_nNumShadowVertices;
    CompressedVector  *m_pShadowVertices;
    CColTriangle      *m_pShadowTriangles;

    CCollisionData();
    void RemoveCollisionVolumes();
    void Copy(CCollisionData const& arg0);
    void CalculateTrianglePlanes();
    void GetTrianglePoint(CVector& outVec, int vertId);
    void GetShadTrianglePoint(CVector& outVec, int vertId);
    void RemoveTrianglePlanes();
    void SetLinkPtr(CLink<CCollisionData*> *link);
    CLink<CCollisionData*> *GetLinkPtr();
};

VALIDATE_SIZE(CCollisionData, 0x30);