/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "Vector.h"
#include "Vector2D.h"

void CVector::InjectHooks()
{
    RH_ScopedClass(CVector);
    RH_ScopedCategory("Core");

    RH_ScopedInstall(Magnitude, 0x4082C0);
    RH_ScopedInstall(Magnitude2D, 0x406D50);
    RH_ScopedInstall(Normalise, 0x59C910);
    RH_ScopedInstall(NormaliseAndMag, 0x59C970);
    RH_ScopedInstall(Cross_OG, 0x70F890);
    RH_ScopedInstall(Sum, 0x40FDD0);
    RH_ScopedInstall(Difference, 0x40FE00);
    RH_ScopedInstall(FromMultiply, 0x59C670);
    RH_ScopedInstall(FromMultiply3x3, 0x59C6D0);
    RH_ScopedGlobalOverloadedInstall(CrossProduct, "out", 0x59C730, CVector*(*)(CVector*, CVector*, CVector*));
    RH_ScopedGlobalOverloadedInstall(DotProduct, "v3d*v3d*", 0x59C6D0, float(*)(CVector*, CVector*));
}

/*!
* @brief From a 2D vector and Z position
*/
CVector::CVector(const CVector2D& v2d, float Z) :
    RwV3d{ v2d.x, v2d.y, Z }
{
}

/*!
* @returns A vector with each of its components set to a number in the given range [min, max)
*/
CVector CVector::Random(CVector min, CVector max) {
    const auto Get = [=](float fmin, float fmax) { return CGeneral::GetRandomNumberInRange(fmin, fmax); };
    return { Get(min.x, max.x), Get(min.y, max.y), Get(min.z, max.z) };
}

CVector CVector::Random(float min, float max) {
    const auto Get = [=] { return CGeneral::GetRandomNumberInRange(min, max); };
    return { Get(), Get(), Get() };
}

// Returns length of vector
float CVector::Magnitude() const
{
    return sqrt(x * x + y * y + z * z);
}

float CVector::Magnitude2D() const
{
    return sqrt(x * x + y * y);
}

// Normalises a vector
void CVector::Normalise()
{
    NormaliseAndMag();
}

// Normalises a vector and returns length
float CVector::NormaliseAndMag()
{
    const auto fDot = x * x + y * y + z * z;
    if (fDot <= 0.0F)
    {
        x = 1.0F;
        return 1.0F;
    }

    const auto fRecip = 1.0F / sqrt(fDot);
    x *= fRecip;
    y *= fRecip;
    z *= fRecip;

    return 1.0F / fRecip;
}

auto CVector::Dot(const CVector& o) const -> float{
    return DotProduct(*this, o);
}

// notsa
CVector CVector::Cross(const CVector& o) const {
    return {
        y * o.z - z * o.y,
        z * o.x - x * o.z,
        x * o.y - y * o.x
    };
}

// 0x70F890
void CVector::Cross_OG(const CVector& a, const CVector& b) {
    *this = a.Cross(b);
}

// Adds left + right and stores result
void CVector::Sum(const CVector& left, const CVector &right)
{
    x = left.x + right.x;
    y = left.y + right.y;
    z = left.z + right.z;
}

// Subtracts left - right and stores result
void CVector::Difference(const CVector& left, const CVector &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    z = left.z - right.z;
}

// Adds value from the second vector.
void CVector::operator+=(const CVector& right)
{
    x += right.x;
    y += right.y;
    z += right.z;
}

void CVector::operator-=(const CVector& right)
{
    x -= right.x;
    y -= right.y;
    z -= right.z;
}

void CVector::operator*=(const CVector& right)
{
    x *= right.x;
    y *= right.y;
    z *= right.z;
}

// Multiplies vector by a floating point value
void CVector::operator *= (float multiplier)
{
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
}

// Divides vector by a floating point value
void CVector::operator /= (float divisor)
{
    x /= divisor;
    y /= divisor;
    z /= divisor;
}

void CVector::FromMultiply(const CMatrix& matrix, const CVector& vector)
{
    x = matrix.m_pos.x + matrix.m_right.x * vector.x + matrix.m_forward.x * vector.y + matrix.m_up.x * vector.z;
    y = matrix.m_pos.y + matrix.m_right.y * vector.x + matrix.m_forward.y * vector.y + matrix.m_up.y * vector.z;
    z = matrix.m_pos.z + matrix.m_right.z * vector.x + matrix.m_forward.z * vector.y + matrix.m_up.z * vector.z;
}

void CVector::FromMultiply3x3(const CMatrix& matrix, const CVector& vector)
{
    x = matrix.m_right.x * vector.x + matrix.m_forward.x * vector.y + matrix.m_up.x * vector.z;
    y = matrix.m_right.y * vector.x + matrix.m_forward.y * vector.y + matrix.m_up.y * vector.z;
    z = matrix.m_right.z * vector.x + matrix.m_forward.z * vector.y + matrix.m_up.z * vector.z;
}

CVector CVector::Average(const CVector* begin, const CVector* end) {
    return std::accumulate(begin, end, CVector{}) / (float)std::distance(begin, end);
}

float CVector::Heading(bool limitAngle) const {
    const auto radians = std::atan2(-x, y);
    if (limitAngle) {
        return CGeneral::LimitRadianAngle(radians);
    }
    return radians;
}

CVector* CrossProduct(CVector* out, CVector* a, CVector* b)
{
    *out = a->Cross(b);
    return out;
}

CVector CrossProduct(const CVector& a, const CVector& b)
{
    return a.Cross(b);
}

float DotProduct(CVector* v1, CVector* v2)
{
    return v1->z * v2->z + v1->y * v2->y + v1->x * v2->x;
}

float DotProduct(const CVector& v1, const CVector& v2)
{
    return v1.z * v2.z + v1.y * v2.y + v1.x * v2.x;
}

float DotProduct2D(const CVector& v1, const CVector& v2)
{
    return v1.y * v2.y + v1.x * v2.x;
}

// NOTE: This function doesn't add m.GetPosition() like
//       MultiplyMatrixWithVector @ 0x59C890 does.
CVector Multiply3x3(const CMatrix& constm, const CVector& v) {
    auto& m = const_cast<CMatrix&>(constm);
    return {
        m.GetRight().x * v.x + m.GetForward().x * v.y + m.GetUp().x * v.z,
        m.GetRight().y * v.x + m.GetForward().y * v.y + m.GetUp().y * v.z,
        m.GetRight().z * v.x + m.GetForward().z * v.y + m.GetUp().z * v.z,
    };
}

// vector by matrix mult, resulting in a vector where each component is the dot product of the in vector and a matrix direction
CVector Multiply3x3(const CVector& v, const CMatrix& constm) {
    auto& m = const_cast<CMatrix&>(constm);
    return {
        DotProduct(m.GetRight(), v),
        DotProduct(m.GetForward(), v),
        DotProduct(m.GetUp(), v)
    };
}

CVector MultiplyMatrixWithVector(const CMatrix& mat, const CVector& vec) {
    return const_cast<CMatrix&>(mat).GetPosition() + Multiply3x3(const_cast<CMatrix&>(mat), vec);
}

CVector MultiplyMatrixWithVector(CMatrix& m, const CVector& v) {
    return m.GetPosition() + Multiply3x3(m, v);
}
