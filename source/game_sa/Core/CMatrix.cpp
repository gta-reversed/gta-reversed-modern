/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

uint8_t* CMatrix::EulerIndices1 = (uint8_t*)0x866D9C;
uint8_t* CMatrix::EulerIndices2 = (uint8_t*)0x866D94;
int32_t& numMatrices = *(int32_t*)0xB74238;
CMatrix& gDummyMatrix = *(CMatrix*)0xB74240;


void CMatrix::InjectHooks()
{
    ReversibleHooks::Install("CMatrix", "Attach", 0x59BD10, &CMatrix::Attach);
    ReversibleHooks::Install("CMatrix", "Detach", 0x59ACF0, &CMatrix::Detach);
    ReversibleHooks::Install("CMatrix", "CopyOnlyMatrix", 0x59ADD0, &CMatrix::CopyOnlyMatrix);
    ReversibleHooks::Install("CMatrix", "Update", 0x59BB60, &CMatrix::Update);
    ReversibleHooks::Install("CMatrix", "UpdateMatrix", 0x59AD20, &CMatrix::UpdateMatrix);
    ReversibleHooks::Install("CMatrix", "UpdateRW", 0x59BBB0, &CMatrix::UpdateRW);
    ReversibleHooks::Install("CMatrix", "UpdateRwMatrix", 0x59AD70, &CMatrix::UpdateRwMatrix);
    ReversibleHooks::Install("CMatrix", "SetUnity", 0x59AE70, &CMatrix::SetUnity);
    ReversibleHooks::Install("CMatrix", "ResetOrientation", 0x59AEA0, &CMatrix::ResetOrientation);
    ReversibleHooks::Install("CMatrix", "SetScale_f", 0x59AED0, (void(CMatrix::*)(float))(&CMatrix::SetScale));
    ReversibleHooks::Install("CMatrix", "SetScale_fff", 0x59AF00, (void(CMatrix::*)(float, float, float))(&CMatrix::SetScale));
    ReversibleHooks::Install("CMatrix", "SetTranslateOnly", 0x59AF80, &CMatrix::SetTranslateOnly);
    ReversibleHooks::Install("CMatrix", "SetTranslate", 0x59AF40, &CMatrix::SetTranslate);
    ReversibleHooks::Install("CMatrix", "SetRotateXOnly", 0x59AFA0, &CMatrix::SetRotateXOnly);
    ReversibleHooks::Install("CMatrix", "SetRotateYOnly", 0x59AFE0, &CMatrix::SetRotateYOnly);
    ReversibleHooks::Install("CMatrix", "SetRotateZOnly", 0x59B020, &CMatrix::SetRotateZOnly);
    ReversibleHooks::Install("CMatrix", "SetRotateX", 0x59B060, &CMatrix::SetRotateX);
    ReversibleHooks::Install("CMatrix", "SetRotateY", 0x59B0A0, &CMatrix::SetRotateY);
    ReversibleHooks::Install("CMatrix", "SetRotateZ", 0x59B0E0, &CMatrix::SetRotateZ);
    ReversibleHooks::Install("CMatrix", "SetRotate_xyz", 0x59B120, (void(CMatrix::*)(float, float, float))(&CMatrix::SetRotate));
    ReversibleHooks::Install("CMatrix", "RotateX", 0x59B1E0, &CMatrix::RotateX);
    ReversibleHooks::Install("CMatrix", "RotateY", 0x59B2C0, &CMatrix::RotateY);
    ReversibleHooks::Install("CMatrix", "RotateZ", 0x59B390, &CMatrix::RotateZ);
    ReversibleHooks::Install("CMatrix", "Rotate", 0x59B460, &CMatrix::Rotate);
    ReversibleHooks::Install("CMatrix", "Reorthogonalise", 0x59B6A0, &CMatrix::Reorthogonalise);
    ReversibleHooks::Install("CMatrix", "CopyToRwMatrix", 0x59B8B0, &CMatrix::CopyToRwMatrix);
    ReversibleHooks::Install("CMatrix", "SetRotate_quat", 0x59BBF0, (void(CMatrix::*)(CQuaternion&))(&CMatrix::SetRotate));
    ReversibleHooks::Install("CMatrix", "Scale", 0x459350, &CMatrix::Scale);
    ReversibleHooks::Install("CMatrix", "ForceUpVector", 0x59B7E0, &CMatrix::ForceUpVector);
    ReversibleHooks::Install("CMatrix", "ConvertToEulerAngles", 0x59A840, &CMatrix::ConvertToEulerAngles);
    ReversibleHooks::Install("CMatrix", "ConvertFromEulerAngles", 0x59AA40, &CMatrix::ConvertFromEulerAngles);
    ReversibleHooks::Install("CMatrix", "operator=", 0x59BBC0, &CMatrix::operator=);
    ReversibleHooks::Install("CMatrix", "operator+=", 0x59ADF0, &CMatrix::operator+=);
    ReversibleHooks::Install("CMatrix", "operator*=", 0x411A80, &CMatrix::operator*=);
    ReversibleHooks::Install("CMatrix", "operator*_Mat", 0x59BE30, (CMatrix(*)(CMatrix const&, CMatrix const&))(&::operator*));
    ReversibleHooks::Install("CMatrix", "operator*_Vec", 0x59C890, (CVector(*)(CMatrix const&, CVector const&))(&::operator*));
    ReversibleHooks::Install("CMatrix", "operator+", 0x59BFA0, (CMatrix(*)(CMatrix const&, CMatrix const&))(&::operator+));
    ReversibleHooks::Install("CMatrix", "Invert_1", 0x59B920, (CMatrix&(*)(CMatrix&, CMatrix&)) &Invert);
    ReversibleHooks::Install("CMatrix", "Invert_2", 0x59BDD0, (CMatrix(*)(CMatrix&)) &Invert);
}

CMatrix::CMatrix(CMatrix const& matrix)
{
    m_pAttachMatrix = nullptr;
    m_bOwnsAttachedMatrix = false;
    CMatrix::CopyOnlyMatrix(matrix);
}

// like previous + attach
CMatrix::CMatrix(RwMatrix* matrix, bool temporary)
{
    m_pAttachMatrix = nullptr;
    CMatrix::Attach(matrix, temporary);
}

// destructor detaches matrix if attached 
CMatrix::~CMatrix()
{
    CMatrix::Detach();
}

void CMatrix::Attach(RwMatrix* matrix, bool bOwnsMatrix)
{
    CMatrix::Detach();

    m_pAttachMatrix = matrix;
    m_bOwnsAttachedMatrix = bOwnsMatrix;
    CMatrix::Update();
}

void CMatrix::Detach()
{
    if (m_bOwnsAttachedMatrix && m_pAttachMatrix)
        RwMatrixDestroy(m_pAttachMatrix);

    m_pAttachMatrix = nullptr;
}

// copy base RwMatrix to another matrix
void CMatrix::CopyOnlyMatrix(CMatrix const& matrix)
{
    memcpy(this, &matrix, sizeof(RwMatrix));
}

// update RwMatrix with attaching matrix. This doesn't check if attaching matrix is present, so use it only if you know it is present.
// Using UpdateRW() is more safe since it perform this check.
void CMatrix::Update()
{
    CMatrix::UpdateMatrix(m_pAttachMatrix);
}

// update RwMatrix with attaching matrix.
void CMatrix::UpdateRW()
{
    if (!m_pAttachMatrix)
        return;

    CMatrix::UpdateRwMatrix(m_pAttachMatrix);
}

// update RwMatrix with this matrix
void CMatrix::UpdateRwMatrix(RwMatrix* matrix)
{
    *RwMatrixGetRight(matrix) = m_right;
    *RwMatrixGetUp(matrix) = m_forward;
    *RwMatrixGetAt(matrix) = m_up;
    *RwMatrixGetPos(matrix) = m_pos;

    RwMatrixUpdate(matrix);
}

void CMatrix::UpdateMatrix(RwMatrixTag* rwMatrix)
{
    m_right = *RwMatrixGetRight(rwMatrix);
    m_forward = *RwMatrixGetUp(rwMatrix);
    m_up = *RwMatrixGetAt(rwMatrix);
    m_pos = *RwMatrixGetPos(rwMatrix);
}

void CMatrix::SetUnity()
{
    CMatrix::ResetOrientation();
    m_pos.Set(0.0F, 0.0F, 0.0F);
}

void CMatrix::ResetOrientation()
{
    m_right.Set  (1.0F, 0.0F, 0.0F);
    m_forward.Set(0.0F, 1.0F, 0.0F);
    m_up.Set     (0.0F, 0.0F, 1.0F);
}

void CMatrix::SetScale(float scale)
{
    m_right.Set  (scale, 0.0F,  0.0F);
    m_forward.Set(0.0F,  scale, 0.0F);
    m_up.Set     (0.0F,  0.0F,  scale);
    m_pos.Set    (0.0F,  0.0F,  0.0F);
}

// scale on three axes
void CMatrix::SetScale(float x, float y, float z)
{
    m_right.Set  (x,     0.0F,  0.0F);
    m_forward.Set(0.0F,  y,     0.0F);
    m_up.Set     (0.0F,  0.0F,  z   );
    m_pos.Set    (0.0F,  0.0F,  0.0F);
}

void CMatrix::SetTranslateOnly(CVector translation)
{
    m_pos = translation;
}

// like previous + reset orientation
void CMatrix::SetTranslate(CVector translation)
{
    CMatrix::ResetOrientation();
    CMatrix::SetTranslateOnly(translation);
}

void CMatrix::SetRotateXOnly(float angle)
{
    auto fSin = sin(angle);
    auto fCos = cos(angle);

    m_right.Set  (1.0F,  0.0F,  0.0F);
    m_forward.Set(0.0F,  fCos,  fSin);
    m_up.Set     (0.0F, -fSin,  fCos);
}

void CMatrix::SetRotateYOnly(float angle)
{
    auto fSin = sin(angle);
    auto fCos = cos(angle);

    m_right.Set  (fCos,  0.0F, -fSin);
    m_forward.Set(0.0F,  1.0F,  0.0F);
    m_up.Set     (fSin,  0.0F,  fCos);
}

void CMatrix::SetRotateZOnly(float angle)
{
    auto fSin = sin(angle);
    auto fCos = cos(angle);

    m_right.Set  ( fCos, fSin, 0.0F);
    m_forward.Set(-fSin, fCos, 0.0F);
    m_up.Set     ( 0.0F, 0.0F, 1.0F);
}

void CMatrix::SetRotateX(float angle)
{
    CMatrix::SetRotateXOnly(angle);
    m_pos.Set(0.0F, 0.0F, 0.0F);
}

void CMatrix::SetRotateY(float angle)
{
    CMatrix::SetRotateYOnly(angle);
    m_pos.Set(0.0F, 0.0F, 0.0F);
}

void CMatrix::SetRotateZ(float angle)
{
    CMatrix::SetRotateZOnly(angle);
    m_pos.Set(0.0F, 0.0F, 0.0F);
}

// set rotate on 3 axes
void CMatrix::SetRotate(float x, float y, float z)
{
    auto fSinX = sin(x);
    auto fCosX = cos(x);
    auto fSinY = sin(y);
    auto fCosY = cos(y);
    auto fSinZ = sin(z);
    auto fCosZ = cos(z);

    m_right.Set  ( fCosZ*fCosY-(fSinZ*fSinX)*fSinY,  fCosZ*fSinX*fSinY+fSinZ*fCosY,  -(fSinY*fCosX));
    m_forward.Set(-(fSinZ*fCosX),                    fCosZ*fCosX,                     fSinX);
    m_up.Set     ( fCosZ*fSinY+fSinZ*fSinX*fCosY,    fSinZ*fSinY-fCosZ*fSinX*fCosY,   fCosY*fCosX);
    m_pos.Set(0.0F, 0.0F, 0.0F);
}

void CMatrix::RotateX(float angle)
{
    auto rotMat = CMatrix();
    rotMat.SetRotateX(angle);
    m_right =   rotMat * m_right;
    m_forward = rotMat * m_forward;
    m_up =      rotMat * m_up;
    m_pos =     rotMat * m_pos;
}

void CMatrix::RotateY(float angle)
{
    auto rotMat = CMatrix();
    rotMat.SetRotateY(angle);
    m_right =   rotMat * m_right;
    m_forward = rotMat * m_forward;
    m_up =      rotMat * m_up;
    m_pos =     rotMat * m_pos;
}

void CMatrix::RotateZ(float angle)
{
    auto rotMat = CMatrix();
    rotMat.SetRotateZ(angle);
    m_right =   rotMat * m_right;
    m_forward = rotMat * m_forward;
    m_up =      rotMat * m_up;
    m_pos =     rotMat * m_pos;
}

// rotate on 3 axes
void CMatrix::Rotate(CVector rotation)
{
    auto rotMat = CMatrix();
    rotMat.SetRotate(rotation.x, rotation.y, rotation.z);
    m_right =   rotMat * m_right;
    m_forward = rotMat * m_forward;
    m_up =      rotMat * m_up;
    m_pos =     rotMat * m_pos;
}

void CMatrix::Reorthogonalise()
{
    auto vecCross = CrossProduct(m_right, m_forward);
    vecCross.Normalise();

    auto vecCross2 = CrossProduct(m_forward, vecCross);
    vecCross2.Normalise();

    auto vecCross3 = CrossProduct(vecCross, vecCross2);

    m_right = vecCross2;
    m_forward = vecCross3;
    m_up = vecCross;
}

// similar to UpdateRW(RwMatrixTag *)
void CMatrix::CopyToRwMatrix(RwMatrix* matrix)
{
    CMatrix::UpdateRwMatrix(matrix);
    RwMatrixUpdate(matrix);
}

void CMatrix::SetRotate(CQuaternion& quat)
{
    auto vecImag2 = quat.imag + quat.imag;
    auto x2x = vecImag2.x * quat.imag.x;
    auto y2x = vecImag2.y * quat.imag.x;
    auto z2x = vecImag2.z * quat.imag.x;

    auto y2y = vecImag2.y * quat.imag.y;
    auto z2y = vecImag2.z * quat.imag.y;
    auto z2z = vecImag2.z * quat.imag.z;

    auto x2r = vecImag2.x * quat.real;
    auto y2r = vecImag2.y * quat.real;
    auto z2r = vecImag2.z * quat.real;

    m_right.Set  (1.0F-(z2z+y2y),   z2r+y2x,        z2x-y2r);
    m_forward.Set(y2x-z2r,          1.0F-(z2z+x2x), x2r+z2y);
    m_up.Set     (y2r+z2x,          z2y-x2r,        1.0F-(y2y+x2x));
}

void CMatrix::Scale(float scale) {
    m_right *= scale;
    m_forward *= scale;
    m_up *= scale;
}

void CMatrix::ForceUpVector(CVector vecUp) {
    auto vecCross = CrossProduct(m_forward, vecUp);
    auto vecCross2 = CrossProduct(vecUp, vecCross);

    m_right = vecCross;
    m_forward = vecCross2;
    m_up = vecUp;
}

void CMatrix::ConvertToEulerAngles(float* pX, float* pY, float* pZ, unsigned int uiFlags)
{
    float fArr[3][3];

    fArr[0][0] = m_right.x;
    fArr[0][1] = m_right.y;
    fArr[0][2] = m_right.z;

    fArr[1][0] = m_forward.x;
    fArr[1][1] = m_forward.y;
    fArr[1][2] = m_forward.z;

    fArr[2][0] = m_up.x;
    fArr[2][1] = m_up.y;
    fArr[2][2] = m_up.z;

    /* Original indices deciding logic, i replaced it with clearer one
    auto iInd1 = CMatrix::EulerIndices1[(uiFlags >> 3) & 0x3];
    auto iInd2 = CMatrix::EulerIndices2[iInd1 + ((uiFlags & 0x4) != 0)];
    auto iInd3 = CMatrix::EulerIndices2[iInd1 - ((uiFlags & 0x4) != 0) + 1]; */
    int8_t iInd1 = 0, iInd2 = 1, iInd3 = 2;
    switch (uiFlags & eMatrixEulerFlags::_ORDER_MASK) {
    case ORDER_XYZ:
        iInd1 = 0, iInd2 = 1, iInd3 = 2;
        break;
    case ORDER_XZY:
        iInd1 = 0, iInd2 = 2, iInd3 = 1;
        break;
    case ORDER_YZX:
        iInd1 = 1, iInd2 = 2, iInd3 = 0;
        break;
    case ORDER_YXZ:
        iInd1 = 1, iInd2 = 0, iInd3 = 2;
        break;
    case ORDER_ZXY:
        iInd1 = 2, iInd2 = 0, iInd3 = 1;
        break;
    case ORDER_ZYX:
        iInd1 = 2, iInd2 = 1, iInd3 = 0;
        break;
    }

    if (uiFlags & eMatrixEulerFlags::EULER_ANGLES) {
        auto r13 = fArr[iInd1][iInd3];
        auto r12 = fArr[iInd1][iInd2];
        auto cy = sqrt(r12 * r12 + r13 * r13);
        if (cy > 0.0000019073486) { // Some epsilon?
            *pX = atan2(r12, r13);
            *pY = atan2(cy, fArr[iInd1][iInd1]);
            *pZ = atan2(fArr[iInd2][iInd3], -fArr[iInd3][iInd1]);
        }
        else {
            *pX = atan2(-fArr[iInd2][iInd3], fArr[iInd2][iInd2]);
            *pY = atan2(cy, fArr[iInd1][iInd1]);
            *pZ = 0.0F;
        }
    }
    else {
        auto r21 = fArr[iInd2][iInd1];
        auto r11 = fArr[iInd1][iInd1];
        auto cy = sqrt(r11 * r11 + r21 * r21);
        if (cy > 0.0000019073486) { // Some epsilon?
            *pX = atan2(fArr[iInd3][iInd2], fArr[iInd3][iInd3]);
            *pY = atan2(-fArr[iInd3][iInd1], cy);
            *pZ = atan2(r21, r11);
        }
        else {
            *pX = atan2(-fArr[iInd2][iInd3], fArr[iInd2][iInd2]);
            *pY = atan2(-fArr[iInd3][iInd1], cy);
            *pZ = 0.0F;
        }
    }

    if (uiFlags & eMatrixEulerFlags::SWAP_XZ)
        std::swap(*pX, *pZ);

    if (uiFlags & eMatrixEulerFlags::_ORDER_NEEDS_SWAP) {
        *pX = -*pX;
        *pY = -*pY;
        *pZ = -*pZ;
    }
}

void CMatrix::ConvertFromEulerAngles(float x, float y, float z, unsigned int uiFlags)
{
    /* Original indices deciding logic, i replaced it with clearer one
    auto iInd1 = CMatrix::EulerIndices1[(uiFlags >> 3) & 0x3];
    auto iInd2 = CMatrix::EulerIndices2[iInd1 + ((uiFlags & 0x4) != 0)];
    auto iInd3 = CMatrix::EulerIndices2[iInd1 - ((uiFlags & 0x4) != 0) + 1]; */
    int8_t iInd1 = 0, iInd2 = 1, iInd3 = 2;
    switch (uiFlags & eMatrixEulerFlags::_ORDER_MASK) {
    case ORDER_XYZ:
        iInd1 = 0, iInd2 = 1, iInd3 = 2;
        break;
    case ORDER_XZY:
        iInd1 = 0, iInd2 = 2, iInd3 = 1;
        break;
    case ORDER_YZX:
        iInd1 = 1, iInd2 = 2, iInd3 = 0;
        break;
    case ORDER_YXZ:
        iInd1 = 1, iInd2 = 0, iInd3 = 2;
        break;
    case ORDER_ZXY:
        iInd1 = 2, iInd2 = 0, iInd3 = 1;
        break;
    case ORDER_ZYX:
        iInd1 = 2, iInd2 = 1, iInd3 = 0;
        break;
    }

    float fArr[3][3];

    if (uiFlags & eMatrixEulerFlags::SWAP_XZ)
        std::swap(x, z);

    if (uiFlags & eMatrixEulerFlags::_ORDER_NEEDS_SWAP) {
        x = -x;
        y = -y;
        z = -z;
    }

    auto fSinX = sin(x);
    auto fCosX = cos(x);
    auto fSinY = sin(y);
    auto fCosY = cos(y);
    auto fSinZ = sin(z);
    auto fCosZ = cos(z);

    if (uiFlags & eMatrixEulerFlags::EULER_ANGLES) {
        fArr[iInd1][iInd1] = fCosY;
        fArr[iInd1][iInd2] = fSinX*fSinY;
        fArr[iInd1][iInd3] = fCosX*fSinY;

        fArr[iInd2][iInd1] =   fSinY*fSinZ;
        fArr[iInd2][iInd2] =   fCosX*fCosY  - fCosY*fSinX*fSinZ;
        fArr[iInd2][iInd3] = -(fSinX*fCosZ) -(fCosX*fCosY*fSinZ);

        fArr[iInd3][iInd1] = -(fCosZ*fSinY);
        fArr[iInd3][iInd2] =   fCosX*fSinZ  + fCosY*fCosZ*fSinX;
        fArr[iInd3][iInd3] = -(fSinX*fSinZ) + fCosX*fCosY*fCosZ;
    }
    else { // Use Tait-Bryan angles
        fArr[iInd1][iInd1] =   fCosY*fCosZ;
        fArr[iInd1][iInd2] = -(fCosX*fSinZ) + fCosZ*fSinX*fSinY;
        fArr[iInd1][iInd3] =   fSinX*fSinZ  + fCosX*fCosZ*fSinY;

        fArr[iInd2][iInd1] =   fCosY*fSinZ;
        fArr[iInd2][iInd2] =   fCosX*fCosZ  + fSinX*fSinY*fSinZ;
        fArr[iInd2][iInd3] = -(fCosZ*fSinX) + fCosX*fSinY*fSinZ;

        fArr[iInd3][iInd1] = -fSinY;
        fArr[iInd3][iInd2] =  fCosY*fSinX;
        fArr[iInd3][iInd3] =  fCosX*fCosY;
    }

    m_right.Set  (fArr[0][0], fArr[0][1], fArr[0][2]);
    m_forward.Set(fArr[1][0], fArr[1][1], fArr[1][2]);
    m_up.Set     (fArr[2][0], fArr[2][1], fArr[2][2]);
}

void CMatrix::operator=(CMatrix const& rvalue)
{
    CMatrix::CopyOnlyMatrix(rvalue);
    CMatrix::UpdateRW();
}

void CMatrix::operator+=(CMatrix const& rvalue)
{
    m_right += rvalue.m_right;
    m_forward += rvalue.m_forward;
    m_up += rvalue.m_up;
    m_pos += rvalue.m_pos;
}

void CMatrix::operator*=(CMatrix const& rvalue)
{
    *this = (*this * rvalue);
}

CMatrix operator*(CMatrix const& a, CMatrix const& b)
{
    auto result = CMatrix();
    result.m_right =   a.m_right * b.m_right.x   + a.m_forward * b.m_right.y   + a.m_up * b.m_right.z;
    result.m_forward = a.m_right * b.m_forward.x + a.m_forward * b.m_forward.y + a.m_up * b.m_forward.z;
    result.m_up =      a.m_right * b.m_up.x      + a.m_forward * b.m_up.y      + a.m_up * b.m_up.z;
    result.m_pos =     a.m_right * b.m_pos.x     + a.m_forward * b.m_pos.y     + a.m_up * b.m_pos.z + a.m_pos;
    return result;
}

CVector operator*(CMatrix const& a, CVector const& b)
{
    CVector result;
    result.x = a.m_pos.x + a.m_right.x * b.x + a.m_forward.x * b.y + a.m_up.x * b.z;
    result.y = a.m_pos.y + a.m_right.y * b.x + a.m_forward.y * b.y + a.m_up.y * b.z;
    result.z = a.m_pos.z + a.m_right.z * b.x + a.m_forward.z * b.y + a.m_up.z * b.z;
    return result;
}
CMatrix operator+(CMatrix const& a, CMatrix const& b)
{
    CMatrix result;
    result.m_right =   a.m_right + b.m_right;
    result.m_forward = a.m_forward + b.m_forward;
    result.m_up =      a.m_up + b.m_up;
    result.m_pos =     a.m_pos + b.m_pos;
    return result;
}

CMatrix& Invert(CMatrix& in, CMatrix& out)
{
    out.GetPosition().Set(0.0F, 0.0F, 0.0F);

    out.GetRight().Set(in.GetRight().x, in.GetForward().x, in.GetUp().x);
    out.GetForward().Set(in.GetRight().y, in.GetForward().y, in.GetUp().y);
    out.GetUp().Set(in.GetRight().z, in.GetForward().z, in.GetUp().z);

    out.GetPosition() += in.GetPosition().x * out.GetRight();
    out.GetPosition() += in.GetPosition().y * out.GetForward();
    out.GetPosition() += in.GetPosition().z * out.GetUp();
    out.GetPosition() *= -1.0F;

    return out;
}

CMatrix Invert(CMatrix& in)
{
    CMatrix result;
    Invert(in, result);
    return result;
}
