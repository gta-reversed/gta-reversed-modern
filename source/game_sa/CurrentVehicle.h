#pragma once

class CVehicle;

class CCurrentVehicle {
public:
    CVehicle* m_pVehicle;

public:
    static void InjectHooks();

    CCurrentVehicle();

    void Init();
    void Display() const;
    void Process();
};
