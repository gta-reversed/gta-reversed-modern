/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

void CPlaceable::InjectHooks()
{
    ReversibleHooks::Install("CPlaceable", "SetPosn_xyz", 0x420B80, (void(CPlaceable::*)(float, float, float))(&CPlaceable::SetPosn));
    ReversibleHooks::Install("CPlaceable", "SetPosn_vector", 0x4241C0, (void(CPlaceable::*)(CVector const&))(&CPlaceable::SetPosn));
    ReversibleHooks::Install("CPlaceable", "SetOrientation", 0x439A80, &CPlaceable::SetOrientation);
    ReversibleHooks::Install("CPlaceable", "SetHeading", 0x43E0C0, &CPlaceable::SetHeading);
    ReversibleHooks::Install("CPlaceable", "GetHeading", 0x441DB0, &CPlaceable::GetHeading);
    ReversibleHooks::Install("CPlaceable", "IsWithinArea_xy", 0x54F200, (bool(CPlaceable::*)(float, float, float, float))(&CPlaceable::IsWithinArea));
    ReversibleHooks::Install("CPlaceable", "IsWithinArea_xyz", 0x54F2B0, (bool(CPlaceable::*)(float, float, float, float, float, float))(&CPlaceable::IsWithinArea));
    ReversibleHooks::Install("CPlaceable", "RemoveMatrix", 0x54F3B0, &CPlaceable::RemoveMatrix);
    ReversibleHooks::Install("CPlaceable", "AllocateStaticMatrix", 0x54F4C0, &CPlaceable::AllocateStaticMatrix);
    ReversibleHooks::Install("CPlaceable", "AllocateMatrix", 0x54F560, &CPlaceable::AllocateMatrix);
    ReversibleHooks::Install("CPlaceable", "SetMatrix", 0x54F610, &CPlaceable::SetMatrix);
    ReversibleHooks::Install("CPlaceable", "GetMatrix", 0x411990, &CPlaceable::GetMatrix);
    ReversibleHooks::Install("CPlaceable", "ShutdownMatrixArray", 0x54EFD0, &CPlaceable::ShutdownMatrixArray);
    ReversibleHooks::Install("CPlaceable", "InitMatrixArray", 0x54F3A0, &CPlaceable::InitMatrixArray);
    ReversibleHooks::Install("CPlaceable", "FreeStaticMatrix", 0x54F010, &CPlaceable::FreeStaticMatrix);
}

CPlaceable::CPlaceable() : m_placement()
{
    m_matrix = nullptr;
}

CPlaceable::~CPlaceable()
{
    if (m_matrix) {
        CPlaceable::RemoveMatrix();
        --numMatrices;
    }

    m_matrix = reinterpret_cast<CMatrixLink*>(&gDummyMatrix);
}

CVector CPlaceable::GetRightVector()
{
    if (m_matrix)
        m_matrix->GetRight();
    return CVector(cos(m_placement.m_fHeading), sin(m_placement.m_fHeading), 0.0f);
}

CVector CPlaceable::GetForwardVector()
{
    if (m_matrix)
        return m_matrix->GetForward();
    return CVector(-sin(m_placement.m_fHeading), cos(m_placement.m_fHeading), 0.0f);
}

CVector CPlaceable::GetUpVector()
{
    if (m_matrix)
        m_matrix->GetUp();
    return CVector(0.0f, 0.0f, 1.0f);
}

void CPlaceable::SetPosn(float x, float y, float z)
{
    auto& pPos = GetPosition();
    pPos.Set(x, y, z);
}

void CPlaceable::SetPosn(CVector const& posn)
{
    GetPosition() = posn;
}

void CPlaceable::SetOrientation(float x, float y, float z)
{
    if (!m_matrix) {
        m_placement.m_fHeading = z;
        return;
    }

    CVector vecPos = m_matrix->GetPosition();
    m_matrix->SetRotate(x, y, z);
    m_matrix->GetPosition() += vecPos;
}

void CPlaceable::SetHeading(float heading)
{
    if (m_matrix)
        m_matrix->SetRotateZOnly(heading);
    else
        m_placement.m_fHeading = heading;
}

float CPlaceable::GetHeading()
{
    if (!m_matrix)
        return m_placement.m_fHeading;

    auto& vecForward = m_matrix->GetForward();
    return atan2(-vecForward.x, vecForward.y);
}

bool CPlaceable::IsWithinArea(float x1, float y1, float x2, float y2)
{
    auto& vecPos = GetPosition();
    if (x1 > x2)
        std::swap(x1, x2);

    if (y1 > y2)
        std::swap(y1, y2);

    return vecPos.x >= x1
        && vecPos.x <= x2
        && vecPos.y >= y1
        && vecPos.y <= y2;
}

bool CPlaceable::IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2)
{
    auto& vecPos = GetPosition();
    if (x1 > x2)
        std::swap(x1, x2);

    if (y1 > y2)
        std::swap(y1, y2);

    if (z1 > z2)
        std::swap(z1, z2);

    return vecPos.x >= x1
        && vecPos.x <= x2
        && vecPos.y >= y1
        && vecPos.y <= y2
        && vecPos.z >= z1
        && vecPos.z <= z2;
}

void CPlaceable::RemoveMatrix()
{
    auto& vecForward = m_matrix->GetForward();
    auto fHeading = atan2(-vecForward.x, vecForward.y);

    m_placement.m_vPosn = m_matrix->GetPosition();
    m_placement.m_fHeading = fHeading;

    m_matrix->m_pOwner = nullptr;
    gMatrixList.MoveToFreeList(m_matrix);
    m_matrix = nullptr;
}

void CPlaceable::AllocateStaticMatrix()
{
    if (m_matrix)
        return gMatrixList.MoveToList2(m_matrix);

    if (gMatrixList.IsFull())
        gMatrixList.GetOldestLink()->m_pOwner->RemoveMatrix();

    m_matrix = gMatrixList.AddToList2();
    m_matrix->m_pOwner = this;
}

void CPlaceable::AllocateMatrix()
{
    if (m_matrix)
        return;

    if (gMatrixList.IsFull())
        gMatrixList.GetOldestLink()->m_pOwner->RemoveMatrix();

    m_matrix = gMatrixList.AddToList1();
    m_matrix->m_pOwner = this;
}

void CPlaceable::SetMatrix(CMatrix& matrix)
{
    if (!m_matrix) {
        if (matrix.GetUp().z == 1.0F) {
            auto& vecForward = matrix.GetForward();
            auto fHeading = atan2(-vecForward.x, vecForward.y);

            m_placement.m_vPosn = matrix.GetPosition();
            m_placement.m_fHeading = fHeading;
            return;
        }
        CPlaceable::AllocateMatrix();
    }

    *static_cast<CMatrix*>(m_matrix) = matrix;
}

CMatrixLink& CPlaceable::GetMatrix() {
    if (!m_matrix) {
        CPlaceable::AllocateMatrix();
        m_placement.UpdateMatrix(m_matrix);
    }

    return *m_matrix;
}

void CPlaceable::ShutdownMatrixArray() {
    gMatrixList.Shutdown();
}

void CPlaceable::InitMatrixArray() {
    gMatrixList.Init(CPlaceable::NUM_MATRICES_TO_CREATE);
}

void CPlaceable::FreeStaticMatrix() {
    gMatrixList.MoveToList1(m_matrix);
}

void CPlaceable::GetOrientation(float& x, float& y, float& z)
{
    if (!m_matrix) {
        z = m_placement.m_fHeading;
        return;
    }

    x = asinf(GetForward().z);

    float cosx = cosf(x);
    float cosy = GetUp().z / cosx;
    y = acosf(cosy);

    float cosz = GetForward().y / cosx;
    z = acosf(cosz);
}
