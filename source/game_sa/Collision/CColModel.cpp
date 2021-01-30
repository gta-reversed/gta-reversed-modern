#include "StdInc.h"

void CColModel::InjectHooks()
{
    ReversibleHooks::Install("CColModel", "operator new", 0x40FC30, &CColModel::operator new);
    ReversibleHooks::Install("CColModel", "operator delete", 0x40FC40, &CColModel::operator delete);
}

void CColModel::AllocateData(int numSpheres, int numBoxes, int numLines, int numVertices, int numTriangles, bool disks)
{
    plugin::CallMethod<0x40F870, CColModel*, int, int, int, int, int, bool>
        (this, numSpheres, numBoxes, numLines, numVertices, numTriangles, disks);
}

CColModel::CColModel() : m_boundBox()
{
    m_boundSphere.m_nMaterial = 0;
    m_pColData = nullptr;
    m_boundSphere.m_bFlag0x01 = false;
    m_boundSphere.m_bFlag0x02 = false;
    m_boundSphere.m_bFlag0x04 = true;
}

CColModel::~CColModel()
{
    if (!m_boundSphere.m_bFlag0x04)
        return;

    if (!m_pColData)
        return;

    if (m_boundSphere.m_bFlag0x02) {
        CCollision::RemoveTrianglePlanes(m_pColData);
        CMemoryMgr::Free(m_pColData);
    }
    else
    {
        m_pColData->RemoveCollisionVolumes();
        delete m_pColData;
    }
}

void* CColModel::operator new(unsigned int size)
{
	return CPools::ms_pColModelPool->New();
}

void CColModel::operator delete(void* data)
{
    CPools::ms_pColModelPool->Delete(reinterpret_cast<CColModel*>(data));
}

