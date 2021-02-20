/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CBoundingBox.h"
#include "CColSphere.h"
#include "CCollisionData.h"

class CColModel {
public:
    CColModel();
    ~CColModel();
    static void* operator new(unsigned int size);
    static void operator delete(void* data);
    CColModel& operator=(CColModel const& colModel);

public:
    CBoundingBox m_boundBox;
    CColSphere m_boundSphere;
    CCollisionData *m_pColData;

public:
    static void InjectHooks();

private:
    void AllocateData(int size);
public:
    void AllocateData();
    void AllocateData(int numSpheres, int numBoxes, int numLines, int numVertices, int numTriangles, bool bUsesDisks);
    void MakeMultipleAlloc();
    void RemoveCollisionVolumes();
    void CalculateTrianglePlanes();
    void RemoveTrianglePlanes();

// HELPERS
    inline float GetBoundRadius() const { return m_boundSphere.m_fRadius; }
    inline CVector& GetBoundCenter() { return m_boundSphere.m_vecCenter; }
    inline CBoundingBox& GetBoundingBox() { return m_boundBox; }
};

VALIDATE_SIZE(CColModel, 0x30);
