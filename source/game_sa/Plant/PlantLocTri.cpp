#include "StdInc.h"

#include "PlantLocTri.h"
#include "PlantMgr.h"
#include "PlantSurfPropMgr.h"
#include "ProcObjectMan.h"

// 0x5DC210
float GetPlantDensity(CPlantLocTri* plant) {
    CVector a = plant->posn1 - plant->posn;
    CVector b = plant->posn2 - plant->posn;

    CVector out;
    CrossProduct(&out, &a, &b);
    return out.Magnitude() / 2.0f;
}

// 0x5DC290
void CPlantLocTri::Add(const CVector& p1, const CVector& p2, const CVector& p3, uint8 material, uint8 light, bool bIsProcPlant, bool bIsProcObj) {
    return plugin::CallMethod<0x5DC290, CPlantLocTri*, const CVector&, const CVector&, const CVector&, uint8, uint8, bool, bool>(this, p1, p2, p3, material, light, bIsProcPlant, bIsProcObj);

    posn  = p1;
    posn1 = p2;
    posn2 = p3;

    m_nLight    = light;
    m_SurfaceId = material;

    // todo: m_nFlags = bIsProcPlant | LOBYTE(m_nFlags) & 0xF8 | (2 * bIsProcObj);

    posn3 = p1 + p2 + p3;
    posn3.x *= 0.33333334f;

    m_fDistance = posn3.Magnitude() * 1.75f;
    if ((m_nFlags & 2) != 0 && (m_nFlags & 1) == 0) {
        CPlantMgr::MoveLocTriToList(&CPlantMgr::m_UnusedLocTriListHead, &CPlantMgr::m_CloseLocTriListHead[3], this);
        return;
    }

    auto properties = CPlantSurfPropMgr::GetSurfProperties(material);
    auto densityMult = GetPlantDensity(this);
    auto density1 = (uint16)(densityMult * properties->m_Plants[0].density);
    auto density2 = (uint16)(densityMult * properties->m_Plants[1].density);
    auto density3 = (uint16)(densityMult * properties->m_Plants[2].density);
    if (density1 + density2 + density3 > 0) {
        m_RandVec  = CVector::Random(0.0f, 1.0f);
        m_Density1 = density1;
        m_Density2 = density2;
        m_Density3 = density3;
        CPlantMgr::MoveLocTriToList(&CPlantMgr::m_UnusedLocTriListHead, &CPlantMgr::m_CloseLocTriListHead[properties->m_SlotId], this);
        return;
    }

    if ((m_nFlags & 2) != 0) {
        m_nFlags = m_nFlags & 0xFE;
        CPlantMgr::MoveLocTriToList(&CPlantMgr::m_UnusedLocTriListHead, &CPlantMgr::m_CloseLocTriListHead[3], this);
    }
}

// 0x5DB6D0
void CPlantLocTri::Release() {
    return plugin::CallMethod<0x5DB6D0, CPlantLocTri*>(this);

    m_Density1 = 0;
    m_Density2 = 0;
    m_Density3 = 0;
    if ((m_nFlags & 4) != 0)
        g_procObjMan.ProcessTriangleRemoved(this);

    if ((m_nFlags & 2) == 0 || (m_nFlags & 1) != 0) {
        auto v9 = &CPlantMgr::m_CloseLocTriListHead[CPlantSurfPropMgr::GetSurfProperties(m_SurfaceId)->m_SlotId];
        if (m_NextPlant) {
            if (m_PrevPlant) {
                m_PrevPlant->m_NextPlant = m_NextPlant;
                m_NextPlant->m_PrevPlant = m_PrevPlant;
            } else {
                m_NextPlant->m_PrevPlant = nullptr;
            }
        } else {
            auto v10 = m_PrevPlant;
            *v9 = v10;
            if (v10)
                v10->m_NextPlant = nullptr;
        }
        m_PrevPlant = CPlantMgr::m_UnusedLocTriListHead;
        m_NextPlant = nullptr;
        CPlantMgr::m_UnusedLocTriListHead = this;
        if (m_PrevPlant)
            m_PrevPlant->m_NextPlant = this;
        m_SurfaceId = -1;
        m_nFlags = m_nFlags & 0xF8;
        ;
    } else {
        if (m_NextPlant) {
            if (m_PrevPlant) {
                m_PrevPlant->m_NextPlant = m_NextPlant;
                m_NextPlant->m_PrevPlant = m_PrevPlant;
            } else {
                m_NextPlant->m_PrevPlant = nullptr;
            }
        } else {
            CPlantMgr::m_CloseLocTriListHead[3] = m_PrevPlant;
            if (CPlantMgr::m_CloseLocTriListHead[3])
                CPlantMgr::m_CloseLocTriListHead[3]->m_NextPlant = nullptr;
        }
        m_PrevPlant = CPlantMgr::m_UnusedLocTriListHead;
        m_NextPlant = nullptr;
        CPlantMgr::m_UnusedLocTriListHead = this;
        if (m_PrevPlant)
            m_PrevPlant->m_NextPlant = this;
        m_SurfaceId = 254;
        m_nFlags = m_nFlags & 0xF8;
    }
}
