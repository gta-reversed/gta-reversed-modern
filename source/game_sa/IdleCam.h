#pragma once

class CIdleCam {
public:

public:
    static void InjectHooks();

    CIdleCam();

    void Init();
    void Reset(bool a1);
    void ProcessIdleCamTicker();
    bool IsItTimeForIdleCam();
    void IdleCamGeneralProcess();
    void GetLookAtPositionOnTarget(CEntity* target, CVector* posn);
    void ProcessFOVZoom(float a1);
    bool IsTargetValid(CEntity* target);
    void SetTarget(CEntity* target);
    void SetTargetPlayer();
    void ProcessTargetSelection();
    void VectorToAnglesRotXRotZ(CVector* posn, float* outA1, float* outA2);
    void ProcessSlerp(float* outA1, float* outA2);
    void FinaliseIdleCamera(float a1, float a2, float a3);
    void Run();
    void Process();
};

extern CIdleCam& gIdleCam;
extern uint32& gbCineyCamProcessedOnFrame;
