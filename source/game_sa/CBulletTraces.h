#pragma once

class CVector;
class CEntity;

class CBulletTraces {
public:
    static CBulletTrace(&aTraces)[16];

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void AddTrace(CVector* from, CVector* to, float radius, uint32_t disappearTime, uint8_t alpha);
    static void AddTrace(CVector* from, CVector* to, eWeaponType weaponType, CEntity* fromEntity);
    static void Render();

    static CBulletTrace* GetFree(); // Inlined function (Kinda NOTSA)
    static size_t GetTraceIndex(CBulletTrace* pTrace) { return std::distance(std::begin(aTraces), pTrace); } // NOTSA
};
