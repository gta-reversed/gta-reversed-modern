/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "RenderWare.h"
#include "CQuaternion.h"

class CMatrix {
private:
    // RwV3d-like:
    CVector      m_right;
    unsigned int flags;
    CVector      m_forward;
    unsigned int pad1;
    CVector      m_up;
    unsigned int pad2;
    CVector      m_pos;
    unsigned int pad3;
public:
	RwMatrix *m_pAttachMatrix;
	bool m_bOwnsAttachedMatrix; // do we need to delete attaching matrix at detaching

    inline CMatrix() {
        m_pAttachMatrix = nullptr;
        m_bOwnsAttachedMatrix = false;
    }

    CMatrix(plugin::dummy_func_t) {}
	CMatrix(CMatrix const& matrix);
	CMatrix(RwMatrix *matrix, bool temporary); // like previous + attach
	~CMatrix(); // destructor detaches matrix if attached

    inline CVector& GetRight() { return m_right; }
    inline CVector& GetForward() { return m_forward; }
    inline CVector& GetUp() { return m_up; }
    inline CVector& GetPosition() { return m_pos; }
	void Attach(RwMatrix *matrix, bool temporary);
	void Detach();
	void CopyOnlyMatrix(CMatrix const& matrix); // copy base RwMatrix to another matrix
	void Update(); // update RwMatrix with attaching matrix. This doesn't check if attaching matrix is present, so use it only if you know it is present.
	               // Using UpdateRW() is more safe since it perform this check.
	void UpdateRW(); // update RwMatrix with attaching matrix.
	void UpdateRwMatrix(RwMatrix *matrix); // update RwMatrix with this matrix
	void UpdateMatrix(RwMatrixTag* rwMatrix);
	void SetUnity();
	void ResetOrientation();
	void SetScale(float scale); // set (scaled)
	void SetScale(float x, float y, float z); // set (scaled)
	void SetTranslateOnly(CVector translation);
	void SetTranslate(CVector translation); // like previous + reset orientation
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
	void CopyToRwMatrix(RwMatrix *matrix); // similar to UpdateRW(RwMatrixTag *)
	void SetRotate(CQuaternion  const& quat);
    void Scale(float scale);
    void Scale(float x, float y, float z);
	void ForceUpVector(float x, float y, float z);
	void operator=(CMatrix const& right);
	void operator+=(CMatrix const& right);
	void operator*=(CMatrix const& right);
};

VALIDATE_SIZE(CMatrix, 0x48);

CMatrix operator*(CMatrix const&a, CMatrix const&b);
CVector operator*(CMatrix const&a, CVector const&b);
CMatrix operator+(CMatrix const&a, CMatrix const&b);

CMatrix* Invert(CMatrix* a1, CMatrix* out);

// It's also called Invert, but renamed it as we cannot have 2 functions with same names and prototype
CMatrix* InvertMatrix(CMatrix* out, CMatrix* a2); 
