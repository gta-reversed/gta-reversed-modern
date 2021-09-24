/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "Quaternion.h"

enum eMatrixEulerFlags : uint32 {
    SWAP_XZ = 0x01,

    TAIT_BRYAN_ANGLES = 0x0,
    EULER_ANGLES = 0x2,

    ORDER_XYZ = 0x00,
    ORDER_XZY = 0x04,
    ORDER_YZX = 0x08,
    ORDER_YXZ = 0x0C,
    ORDER_ZXY = 0x10,
    ORDER_ZYX = 0x14,
    _ORDER_MASK = 0x1C,
    _ORDER_NEEDS_SWAP = 0x4
};

class CMatrix {
public:
    CMatrix(plugin::dummy_func_t) {}
    CMatrix(CMatrix const& matrix);
    CMatrix(RwMatrix* matrix, bool temporary); // like previous + attach
    ~CMatrix();                                // destructor detaches matrix if attached
    CMatrix() {
        m_pAttachMatrix = nullptr;
        m_bOwnsAttachedMatrix = false;
    }

private:
    // RwV3d-like:
    CVector m_right;
    uint32  flags;
    CVector m_forward;
    uint32  pad1;
    CVector m_up;
    uint32  pad2;
    CVector m_pos;
    uint32  pad3;

public:
    RwMatrix* m_pAttachMatrix;
    bool      m_bOwnsAttachedMatrix; // do we need to delete attaching matrix at detaching

public:
    static void InjectHooks();

    inline CVector& GetRight() { return m_right; }
    inline CVector& GetForward() { return m_forward; }
    inline CVector& GetUp() { return m_up; }
    inline CVector& GetPosition() { return m_pos; }

    void Attach(RwMatrix* matrix, bool bOwnsMatrix);
    void Detach();
    void CopyOnlyMatrix(CMatrix const& matrix); // copy base RwMatrix to another matrix
    void Update();                              // update RwMatrix with attaching matrix. This doesn't check if attaching matrix is present, so use it only if you know it is present.
                                                // Using UpdateRW() is more safe since it perform this check.
    void UpdateRW();                            // update RwMatrix with attaching matrix.
    void UpdateRwMatrix(RwMatrix* matrix);      // update RwMatrix with this matrix
    void UpdateMatrix(RwMatrixTag* rwMatrix);
    void SetUnity();
    void ResetOrientation();
    void SetScale(float scale);                 // set (scaled)
    void SetScale(float x, float y, float z);   // set (scaled)
    void SetTranslateOnly(CVector translation);
    void SetTranslate(CVector translation);     // like previous + reset orientation
    void SetRotateXOnly(float angle);
    void SetRotateYOnly(float angle);
    void SetRotateZOnly(float angle);
    void SetRotateX(float angle);
    void SetRotateY(float angle);
    void SetRotateZ(float angle);
    void SetRotate(float x, float y, float z); // set rotate on 3 axes
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
    void Rotate(CVector rotation); // rotate on 3 axes
    void Reorthogonalise();
    void CopyToRwMatrix(RwMatrix* matrix); // similar to UpdateRW(RwMatrixTag *)
    void SetRotate(CQuaternion& quat);
    void Scale(float scale);
    void ForceUpVector(CVector vecUp);
    void ConvertToEulerAngles(float* pX, float* pY, float* pZ, uint32 uiFlags);
    void ConvertFromEulerAngles(float x, float y, float z, uint32 uiFlags);

    void operator=(CMatrix const& right);
    void operator+=(CMatrix const& right);
    void operator*=(CMatrix const& right);

    static uint8* EulerIndices1;
    static uint8* EulerIndices2;

    // operators and classes that aren't defined as part of class, but it's much easier to get them working with access to class private fields
private:
    friend class CVector; // So Vector methods have access to private fields of matrix whitout accessor methods, for more readable code
    friend class CVector2D;
    friend CMatrix operator*(CMatrix const& a, CMatrix const& b);
    // static CMatrix* impl_operatorMul(CMatrix* pOut, CMatrix const& a, CMatrix const& b);

    friend CVector operator*(CMatrix const& a, CVector const& b);
    // static CVector* impl_operatorMul(CVector* pOut, CMatrix const& a, CVector const& b);

    friend CMatrix operator+(CMatrix const& a, CMatrix const& b);
    // static CMatrix* impl_operatorAdd(CMatrix* pOut, CMatrix const& a, CMatrix const& b);
};

CMatrix operator*(CMatrix const& a, CMatrix const& b);
CVector operator*(CMatrix const& a, CVector const& b);
CMatrix operator+(CMatrix const& a, CMatrix const& b);

CMatrix& Invert(CMatrix& in, CMatrix& out);
CMatrix  Invert(CMatrix& in);

VALIDATE_SIZE(CMatrix, 0x48);

extern int32& numMatrices;
extern CMatrix& gDummyMatrix;
