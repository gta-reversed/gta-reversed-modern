#pragma once

class CVector;

class CBulletTraces {
public:

    static CBulletTrace(&aTraces)[16];

    static void InjectHooks();

private:
public:
    static void Init();
    static void AddTrace(const CVector& from, const CVector& to, float radius, uint32_t disappearTime, uint8_t alpha);
    static void Render();
    static void AddTrace(const CVector& from, const CVector& to, eWeaponType weaponType, class CEntity* pFromEntity);
    static void Update();

    static CBulletTrace* GetFree(); // Inlined function (Kinda NOTSA)
    static size_t GetTraceIndex(CBulletTrace* pTrace) { return std::distance(std::begin(aTraces), pTrace); } // NOTSA
};
