#pragma once
class CVector;
#include <stdint.h>

class CBulletTraces {
public:

    static CBulletTrace(&aTraces)[16];

    static void InjectHooks();

private:
public:
    static void Init();
    static void AddTrace(const CVector& from, const CVector& to, float radius, uint32_t dissapearTime, uint8_t alpha);
    static void Render();
    static void AddTrace(const CVector& from, const CVector& to, int32_t unused, class CEntity* a4);
    void Update();
};
