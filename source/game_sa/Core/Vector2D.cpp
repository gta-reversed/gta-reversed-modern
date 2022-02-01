/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "Vector2D.h"

void CVector2D::InjectHooks()
{
    RH_ScopedClass(CVector2D);
    RH_ScopedCategory("Core");

    RH_ScopedInstall(Magnitude, 0x420860);
    RH_ScopedInstall(Normalise, 0x44E480);
    RH_ScopedInstall(operator=, 0x43E110);
}

CVector2D::CVector2D(const CVector& vec3d) {
    x = vec3d.x;
    y = vec3d.y;
}

float CVector2D::Magnitude()
{
    return sqrt(x * x + y * y);
}

void CVector2D::Normalise()
{
    auto fMag = Magnitude();
    if (fMag > 0.0)
    {
        auto fRecip = 1.0F / fMag;
        x *= fRecip;
        y *= fRecip;
    }
    else
    {
        x = 1.0;
    }
}

void CVector2D::operator=(CVector2D const& right)
{
    x = right.x;
    y = right.y;
}
