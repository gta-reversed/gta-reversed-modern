/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CColTriangle {
public:
    CColTriangle() = default;
    CColTriangle(uint16 a, uint16 b, uint16 c, eSurfaceType material, tColLighting light) :
          m_nVertA(a),
          m_nVertB(b),
          m_nVertC(c),
          m_nMaterial(material),
          m_nLight(light)
    {
    }

    /*!
    * @addr notsa
    * @brief Render the triangle in the 3D world (Be sure to call from a place where 3D stuff is rendered, if called from elsewhere you won't see the lines!)
    *
    * @param color     Color of the lines used
    * @param vertices  Pointer to the array of vertices where this triangles vertices are (CColData::m_pVertices usually)
    * @param transform Transformation matrix to be used
    */
    void DrawWireFrame(CRGBA color, const CompressedVector* vertices, const CMatrix& transform) const;

public:
    union {
        struct {
            uint16 m_nVertA; // vertex index in vertices array
            uint16 m_nVertB; // vertex index in vertices array
            uint16 m_nVertC; // vertex index in vertices array
        };
        uint16 m_vertIndices[3];
    };
    eSurfaceType m_nMaterial;
    tColLighting m_nLight;
};
VALIDATE_SIZE(CColTriangle, 0x8);
