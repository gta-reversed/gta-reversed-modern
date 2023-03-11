#pragma once

#include <assert.h>
#include <Vector2D.h>
#include "AngledRect.hpp"

namespace notsa {
namespace shapes {
//! An angled box. Internally composed of an AngledRect + additional Z checks
//! Constructors use the same arguments as an AngledRect + Z coords
class AngledBox {
public:
    AngledBox(
        AngledRect rect,
        float bottomZ,
        float ceilingZ
    );

    AngledBox(
        CVector2D a,
        CVector2D dirAB, float lenAB,
        CVector2D dirAD, float lenAD,
        float bottomZ,
        float ceilingZ
    );


    //! Check if a point is inside this box
    bool IsPointWithin(CVector pt) const;

    //! Draw wireframe of this quad (Must set-up render states beforehands!)
    void DrawWireFrame(CRGBA color, float z, const CMatrix& transform = CMatrix::Unity()) const;
private:
    AngledRect m_rect;
    float      m_bottomZ, m_ceilingZ;
};
}; // namespace shapes
}; // namespace notsa
