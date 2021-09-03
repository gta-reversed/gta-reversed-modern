#pragma once

class CVector;
class CEntity;
class CPed;
class CEntity;
class CColSphere;
class CPhysical;

class CPointRoute {
public:
    int32 field_0;
    int32 field_4;
    int32 field_8;
    int32 field_C;
    int32 field_10;
    int32 field_14;
    int32 field_18;
    int32 field_1C;
    int32 field_20;
    int32 field_24;
    int32 field_28;
    int32 field_2C;
    int32 field_30;
    int32 field_34;
    int32 field_38;
    int32 field_3C;
    int32 field_40;
    int32 field_44;
    int32 field_48;
    int32 field_4C;
    int32 field_50;
    int32 field_54;
    int32 field_58;
    int32 field_5C;
    int32 field_60;
};

VALIDATE_SIZE(CPointRoute, 0x64);

class CPedGeometryAnalyser {
public:
    static void InjectHooks();
    
    static void CanPedJumpObstacle(const CPed& ped, const CEntity& entity);
    static void CanPedJumpObstacle(const CPed& ped, const CEntity& entity, const CVector&, const CVector&);
    static void CanPedTargetPed(CPed& ped, CPed& targetPed, bool a3);
    static void CanPedTargetPoint(const CPed& ped, const CVector& a2, bool a3);

    static int32 ComputeBuildingHitPoints(const CVector& a1, const CVector& a2);
    static void ComputeClearTarget(const CPed& ped, const CVector&, CVector&);
    static bool ComputeClosestSurfacePoint(const CPed& ped, CEntity& entity, CVector& point);
    static bool ComputeClosestSurfacePoint(const CVector& posn, CEntity& entity, CVector& point);
    static bool ComputeClosestSurfacePoint(const CVector& posn, const CVector* corners, CVector& point);

    static void ComputeEntityBoundingBoxCentre(float zPos, CEntity& entity, CVector& center);
    static void ComputeEntityBoundingBoxCentreUncached(float zPos, const CVector* corners, CVector& center);
    static void ComputeEntityBoundingBoxCentreUncachedAll(float zPos, CEntity& entity, CVector& center);
    static void ComputeEntityBoundingBoxCorners(float zPos, CEntity& entity, CVector* corners);
    static void ComputeEntityBoundingBoxCornersUncached(float zPos, CEntity& entity, CVector* corners);
    static void ComputeEntityBoundingBoxPlanes(float zPos, CEntity& entity, CVector* planes, float* planes_D);
    static void ComputeEntityBoundingBoxPlanesUncached(float zPos, const CVector* corners, CVector* planes, float* planes_D);
    static void ComputeEntityBoundingBoxPlanesUncachedAll(float zPos, CEntity& entity, CVector* posn, float* a4);
    static void ComputeEntityBoundingBoxSegmentPlanes(float zPos, CEntity& entity, CVector*, float*);
    static CVector* ComputeEntityBoundingBoxSegmentPlanesUncached(const CVector* corners, CVector& center, CVector* a3, float* a4);
    static CVector* ComputeEntityBoundingBoxSegmentPlanesUncachedAll(float zPos, CEntity& entity, CVector* a3, float* a4);
    static void ComputeEntityBoundingSphere(const CPed& ped, CEntity& entity, CColSphere&);

    static int32 ComputeMoveDirToAvoidEntity(const CPed& ped, CEntity& entity, CVector& posn);

    static CVector* ComputeEntityDirs(const CEntity& entity, CVector* posn);
    static int32 ComputeEntityHitSide(const CPed& ped, CEntity& entity);
    static int32 ComputeEntityHitSide(const CVector& point1, const CVector* point2, const float* x);
    static int32 ComputeEntityHitSide(const CVector& point, CEntity& entity);
    static int32 ComputePedHitSide(const CPed& ped, const CPhysical& physical);
    static int32 ComputePedHitSide(const CPed& ped, const CVector& posn);
    static int32 ComputePedShotSide(const CPed& ped, const CVector& posn);

    static int32 ComputeRouteRoundEntityBoundingBox(const CPed& ped, CEntity& entity, const CVector& posn, CPointRoute& pointRoute, int32 a5);
    static int32 ComputeRouteRoundEntityBoundingBox(const CPed& ped, const CVector& a2, CEntity& entity, const CVector& a4, CPointRoute& pointRoute, int32 a6);

    static bool ComputeRouteRoundSphere(const CPed& ped, const CColSphere& sphere, const CVector& a3, const CVector& a4, CVector& a5, CVector& a6);

    static bool GetIsLineOfSightClear(const CPed& ped, const CVector& a2, CEntity& entity, float& a4);
    static bool GetIsLineOfSightClear(const CVector& a1, const CVector& a2, CEntity& a3);
    static CPed* GetNearestPed(const CVector& point);

    static bool IsEntityBlockingTarget(CEntity* entity, const CVector& point, float distance);
    static bool IsInAir(const CPed& ped);
    static bool IsWanderPathClear(const CVector& a1, const CVector& a2, float a3, int32 a4);

    static bool LiesInsideBoundingBox(const CPed& ped, const CVector& posn, CEntity& entity);
};
