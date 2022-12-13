/*
    Plugin-SDK file
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
    CMatrix() = default;

    CMatrix(const CVector& pos, const CVector& right, const CVector& fwd, const CVector& up) :
        m_right{right},
        m_forward{fwd},
        m_up{up},
        m_pos{pos}
    {
        // TODO: Add some kind of `assert` to check validity
    }
    CMatrix(const CMatrix& matrix);
    CMatrix(RwMatrix* matrix, bool temporary = false); // like previous + attach

    ~CMatrix();                                        // destructor detaches matrix if attached

    //! Returns an identity matrix
    static auto Unity() {
        CMatrix mat{};
        mat.SetUnity();
        return mat;
    }

    static CMatrix WithUp(const CVector& up, const CVector& pos = {}) {
        const auto zaxis = CVector::ZAxisVector();

        if (up == zaxis) {
            return Unity();
        }

        const auto right = zaxis.Cross(up);
        return {
            pos,
            right,
            up.Cross(right),
            up
        };
    }

private:
    // RwV3d-like:
    CVector m_right;        // 0x0
    uint32  flags;          // 0xC
    CVector m_forward;      // 0x10
    uint32  pad1;           // 0x1C
    CVector m_up;           // 0x20
    uint32  pad2;           // 0x2C
    CVector m_pos;          // 0x30
    uint32  pad3;           // 0x3C

public:
    RwMatrix* m_pAttachMatrix{};       // 0x40
    bool      m_bOwnsAttachedMatrix{}; // 0x44 - Do we need to delete attached matrix at detaching

public:
    static void InjectHooks();

    CVector& GetRight() { return m_right; }
    const CVector& GetRight() const { return m_right; }

    CVector& GetForward() { return m_forward; }
    const CVector& GetForward() const { return m_forward; }

    CVector& GetUp() { return m_up; }
    const CVector& GetUp() const { return m_up; }

    CVector& GetPosition() { return m_pos; }
    const CVector& GetPosition() const { return m_pos; }

    void Attach(RwMatrix* matrix, bool bOwnsMatrix);
    void Detach();
    void CopyOnlyMatrix(const CMatrix& matrix); // copy base RwMatrix to another matrix
    void Update();                              // update RwMatrix with attaching matrix. This doesn't check if attaching matrix is present, so use it only if you know it is present.
                                                // Using UpdateRW() is more safe since it perform this check.
    void UpdateRW();                            // update RwMatrix with attaching matrix.
    void UpdateRwMatrix(RwMatrix* matrix);      // update RwMatrix with this matrix
    void UpdateMatrix(RwMatrix* rwMatrix);
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
    void ScaleXYZ(float x, float y, float z); // notsa
    void ForceUpVector(CVector vecUp);
    void ConvertToEulerAngles(float* pX, float* pY, float* pZ, uint32 uiFlags);
    void ConvertFromEulerAngles(float x, float y, float z, uint32 uiFlags);

    void operator=(const CMatrix& right);
    void operator+=(const CMatrix& right);
    void operator*=(const CMatrix& right);

    static uint8* EulerIndices1;
    static uint8* EulerIndices2;

    void SetRotate(const CVector& rot) {
        SetRotate(rot.x, rot.y, rot.z);
    }

    void SetRotateKeepPos(const CVector& rot) {
        auto pos{ m_pos };
        SetRotate(rot.x, rot.y, rot.z);
        m_pos = pos;
    }

    // Similar to ::Scale but this also scales the position vector.
    // 0x45AF40
    void ScaleAll(float mult) {
        Scale(mult);
        GetPosition() *= mult;
    }

    // operators and classes that aren't defined as part of class, but it's much easier to get them working with access to class private fields
private:
    friend class CVector; // So Vector methods have access to private fields of matrix whitout accessor methods, for more readable code
    friend class CVector2D;
    friend CMatrix operator*(const CMatrix& a, const CMatrix& b);
    // static CMatrix* impl_operatorMul(CMatrix* out, const CMatrix& a, const CMatrix& b);

    friend CVector operator*(const CMatrix& a, const CVector& b);
    // static CVector* impl_operatorMul(CVector* out, const CMatrix& a, const CVector& b);

    friend CMatrix operator+(const CMatrix& a, const CMatrix& b);
    // static CMatrix* impl_operatorAdd(CMatrix* out, const CMatrix& a, const CMatrix& b);
};
VALIDATE_SIZE(CMatrix, 0x48);

CMatrix operator*(const CMatrix& a, const CMatrix& b);
CVector operator*(const CMatrix& a, const CVector& b);
CMatrix operator+(const CMatrix& a, const CMatrix& b);

CMatrix& Invert(CMatrix& in, CMatrix& out);
CMatrix  Invert(const CMatrix& in);

extern int32& numMatrices;
extern CMatrix& gDummyMatrix;
