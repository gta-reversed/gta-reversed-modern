#include "StdInc.h"

#include "Range2D.h"

CRange2D::CRange2D(CVector2D min, CVector2D max) {
    m_Min = min;
    m_Max = max;
}

void CRange2D::DebugShowRange(int32) {

}

CVector2D CRange2D::GetRandomPointInRange() {
    return {
        CGeneral::GetRandomNumberInRange(m_Min.x, m_Max.x),
        CGeneral::GetRandomNumberInRange(m_Min.y, m_Max.y)
    };
}

bool CRange2D::IsInRange(const CVector2D& point) {
    return m_Min.x < point.x
        && m_Max.x > point.x
        && m_Min.y < point.y
        && m_Max.y > point.y;
}
