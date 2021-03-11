/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CSimpleTransform.h"
#include "CMatrixLink.h"

class  CPlaceable {
protected:
    CPlaceable(plugin::dummy_func_t) {}
    CPlaceable();
    virtual ~CPlaceable();

public:
    CSimpleTransform m_placement;
    CMatrixLink *m_matrix;

public:
    static void InjectHooks();
    
    CMatrixLink& GetMatrix();
    
    static void ShutdownMatrixArray();
    static void InitMatrixArray();

    CVector GetRightVector();
    CVector GetForwardVector();
    CVector GetUpVector();

    void FreeStaticMatrix();
    void SetPosn(float x, float y, float z);
    void SetPosn(CVector const& posn);
    void SetOrientation(float x, float y, float z);
    void GetOrientation(float& x, float& y, float& z);
    void SetHeading(float heading);
    float GetHeading();
    bool IsWithinArea(float x1, float y1, float x2, float y2);
    bool IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2);
    void RemoveMatrix();
    void AllocateStaticMatrix();
    void AllocateMatrix();
    void SetMatrix(CMatrix& matrix);

public:
    static constexpr uint32_t NUM_MATRICES_TO_CREATE = 900;
    
    inline CVector& GetRight() { return m_matrix->GetRight(); }
    inline CVector& GetForward() { return m_matrix->GetForward(); }
    inline CVector& GetUp() { return m_matrix->GetUp(); }
    inline CVector& GetPosition() { return m_matrix ? m_matrix->GetPosition() : m_placement.m_vPosn; }
};

VALIDATE_SIZE(CPlaceable, 0x18);
