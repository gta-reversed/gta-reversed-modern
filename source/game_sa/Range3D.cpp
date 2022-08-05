#include "StdInc.h"

#include "Range3D.h"

CRange3D::CRange3D(CVector min, CVector max) {
    m_Min = min;
    m_Max = max;
}

void CRange3D::DebugShowRange(int32) {

}

CVector CRange3D::GetRandomPointInRange() {
    return CVector(
        CGeneral::GetRandomNumberInRange(m_Min.x, m_Max.x),
        CGeneral::GetRandomNumberInRange(m_Min.y, m_Max.y),
        CGeneral::GetRandomNumberInRange(m_Min.z, m_Max.z)
    );
}

bool CRange3D::IsInRange(CVector point) {
    return m_Min.x < point.x
        && m_Max.x > point.x
        && m_Min.y < point.y
        && m_Max.y > point.y
        && m_Min.z < point.z
        && m_Max.z > point.z;
}
