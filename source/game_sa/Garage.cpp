#include "StdInc.h"

#include "Garage.h"
#include <extensions/Shapes/AngledRect.hpp>

void CGarage::InjectHooks() {
    RH_ScopedClass(CGarage);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(BuildRotatedDoorMatrix, 0x4479F0);
    RH_ScopedInstall(StoreAndRemoveCarsForThisHideOut, 0x449900);
    RH_ScopedInstall(OpenThisGarage, 0x447D50);
    RH_ScopedInstall(CloseThisGarage, 0x447D70);
    RH_ScopedInstall(TidyUpGarageClose, 0x449D10);
    RH_ScopedInstall(TidyUpGarage, 0x449C50);
    RH_ScopedInstall(EntityHasASphereWayOutsideGarage, 0x449050);
    RH_ScopedInstall(RemoveCarsBlockingDoorNotInside, 0x449690);
    RH_ScopedInstall(IsEntityTouching3D, 0x448EE0);
    RH_ScopedInstall(IsEntityEntirelyOutside, 0x448D30);
    RH_ScopedInstall(IsStaticPlayerCarEntirelyInside, 0x44A830);
    RH_ScopedInstall(IsEntityEntirelyInside3D, 0x448BE0);
    RH_ScopedInstall(PlayerArrestedOrDied, 0x4486C0, {.reversed = false});
    RH_ScopedInstall(InitDoorsAtStart, 0x447600, {.reversed = false});
    RH_ScopedOverloadedInstall(IsPointInsideGarage, "NoTolerance", 0x448740, bool(CGarage::*)(CVector));
    RH_ScopedOverloadedInstall(IsPointInsideGarage, "WithTolerance", 0x4487D0, bool(CGarage::*)(CVector, float));
    RH_ScopedInstall(Update, 0x44AA50, {.reversed = false});
}

// NOTSA [Based on 0x4471E0]
CGarage::CGarage(
    CVector base,
    CVector2D pA,
    CVector2D pB,
    float ceilingZ,
    eGarageType type,
    uint32,
    const char* name,
    uint32 flagsIPL
) :
    m_Base{ base },
    m_DirA{ (pA - base).Normalized(&m_LenA) },
    m_DirB{ (pB - base).Normalized(&m_LenB) },
    m_CeilingZ{ ceilingZ },
    m_Type{ type },
    m_bDoorGoesIn{ flagsIPL & IPL_FLAG_DOOR_GOES_IN },
    m_bCameraFollowsPlayer{ flagsIPL & IPL_FLAG_CAM_FOLLOW_PLAYER },
    m_bDoorOpensUp{ flagsIPL & IPL_FLAG_DOOR_UP_AND_ROTATE }
{
    assert(m_Base.z <= ceilingZ);

    strcpy_s(m_Name, name);

    const auto SetMinMaxAxis = [&](float& min, float& max, size_t axis) {
        std::tie(min, max) = std::minmax({ base[axis], pA[axis], pB[axis], (pA[axis] + pB[axis]) - base[axis] });
    };
    SetMinMaxAxis(m_MinX, m_MaxX, 0);
    SetMinMaxAxis(m_MinY, m_MaxY, 1);
}

// 0x4479F0
void CGarage::BuildRotatedDoorMatrix(CEntity* entity, float fDoorPosition) {
    const auto fAngle = fDoorPosition * -HALF_PI;
    const auto fSin = sin(fAngle);
    const auto fCos = cos(fAngle);
    CMatrix& matrix = entity->GetMatrix();

    const auto& vecForward = matrix.GetForward();
    matrix.GetUp() = CVector(-fSin * vecForward.y, fSin * vecForward.x, fCos);
    matrix.GetRight() = CrossProduct(vecForward, matrix.GetUp());
}

// 0x449D10
void CGarage::TidyUpGarageClose() {
    for (auto& veh : GetVehiclePool()->GetAllValid()) {
        if (!veh.IsAutomobile() && !veh.IsBike()) {
            continue;
        }
        if (veh.GetStatus() != STATUS_WRECKED) {
            continue;
        }
        if (!IsEntityTouching3D(&veh)) {
            continue;
        }
        if (!IsClosed()) {
            // TODO/NOTE/BUG:
            // I'm not sure what this check is supposed to do
            // The door is open, so why check if the vehicle is not wholly inside?
            // I think this check is meant to be done in case the door *IS* closed
            // and is meant to check if the vehicle *IS* wholly inside the garage.
            // This is kinda confirmed by looking at `TidyUpGarage` [where the veh. is only removed if inside the garage]
            if (!EntityHasASphereWayOutsideGarage(&veh)) {
                continue;
            }
        }
        CWorld::Remove(&veh);
        delete &veh;
    }
}

// 0x449C50
void CGarage::TidyUpGarage() {
    for (auto& veh : GetVehiclePool()->GetAllValid()) {
        if (!veh.IsAutomobile() && !veh.IsBike()) {
            continue;
        }
        if (veh.GetStatus() != STATUS_WRECKED && veh.GetUp().z >= 0.5f) {
            continue;
        }
        if (!IsPointInsideGarage(veh.GetPosition())) {
            continue;
        }
        CWorld::Remove(&veh);
        delete &veh;
    }
}

// 0x449900
void CGarage::StoreAndRemoveCarsForThisHideOut(CStoredCar* storedCars, int32 maxSlot) {
    maxSlot = std::min<int32>(maxSlot, NUM_GARAGE_STORED_CARS);

    for (auto i = 0; i < NUM_GARAGE_STORED_CARS; i++)
storedCars[i].Clear();

auto pool = GetVehiclePool();
auto storedCarIdx{ 0u };
for (auto i = pool->GetSize(); i; i--) {
    if (auto vehicle = pool->GetAt(i - 1)) {
        if (IsPointInsideGarage(vehicle->GetPosition()) && vehicle->m_nCreatedBy != MISSION_VEHICLE) {
            if (storedCarIdx < static_cast<uint32>(maxSlot) && !EntityHasASphereWayOutsideGarage(vehicle, 1.0f)) {
                storedCars[storedCarIdx++].StoreCar(vehicle);
            }

            FindPlayerInfo().CancelPlayerEnteringCars(vehicle);
            CWorld::Remove(vehicle);
            delete vehicle;
        }
    }
}

// Clear slots with no vehicles in it
for (auto i = storedCarIdx; i < NUM_GARAGE_STORED_CARS; i++)
    storedCars[i].Clear();
}

// !any_of(outside) = all_of(inside)
// !any_of(inside) = all_of(outside)

bool CGarage::EntityHasASphereTest(CEntity* entity, bool inside, float tolerance) {
    return rng::any_of(
        entity->GetColData()->GetSpheres(),
        [&](CColSphere sp) {
            sp.m_fRadius += tolerance;
    const auto hasSphereInside = IsSphereInsideGarage(TransformObject(sp, entity->GetMatrix()));
    return inside
        ? hasSphereInside
        : !hasSphereInside;
        }
    );
}

// 0x449050
bool CGarage::EntityHasASphereWayOutsideGarage(CEntity* entity, float tolerance) {
    return EntityHasASphereTest(entity, false, tolerance);
}

// NOTSA
bool CGarage::EntityHasSphereInsideGarage(CEntity* entity, float tolerance) {
    return EntityHasASphereTest(entity, true, tolerance);
}

// 0x449690
void CGarage::RemoveCarsBlockingDoorNotInside() {
    for (auto& veh : GetVehiclePool()->GetAllValid()) {
        if (!IsEntityTouching3D(&veh)) {
            continue;
        }
        if (!IsPointInsideGarage(veh.GetPosition())) {
            continue;
        }
        if (veh.vehicleFlags.bIsLocked) {
            continue;
        }
        if (!veh.CanBeDeleted()) {
            continue;
        }
        CWorld::Remove(&veh);
        delete& veh;
        if (!notsa::IsFixBugs()) { // For some reason original code only deletes one vehicle
            break;
        }
    }
}

// 0x448EE0
bool CGarage::IsEntityTouching3D(CEntity* entity) {
    if (CCollision::TestSphereBox({ entity->GetPosition(), entity->GetColModel()->GetBoundRadius() }, GetAABB())) {
        return true;
    }
    return EntityHasSphereInsideGarage(entity);
}

// 0x448BE0
bool CGarage::IsEntityEntirelyInside3D(CEntity* entity, float tolerance) {
    if (!CCollision::TestSphereBox({ entity->GetPosition(), entity->GetColModel()->GetBoundRadius() }, GetAABB())) {
        return true;
    }
    return !EntityHasSphereInsideGarage(entity);
}

// 0x448D30
bool CGarage::IsEntityEntirelyOutside(CEntity* entity, float radius) {
    if (!CCollision::TestSphereBox({ entity->GetPosition(), entity->GetColModel()->GetBoundRadius() }, GetAABB())) {
        return true;
    }
    return !EntityHasSphereInsideGarage(entity);
}

// 0x448740 - Original function was __spoils<>, so we have to keep the registers intact!
bool CGarage::IsPointInsideGarage(CVector point) { // TODO: Remove this in favor of the overloaded version
    __asm pushad;
    const auto ret = GetBB().IsPointWithin(point);
    __asm popad;
    return ret;
}

// 0x4487D0 - Original function was __spoils<>, so we have to keep the registers intact!
bool CGarage::IsPointInsideGarage(CVector point, float tolerance) {
    __asm pushad;
    const auto ret = GetBB().IsPointWithin(point, tolerance);
    __asm popad;
    return ret;
}


// 0x44A830
bool CGarage::IsStaticPlayerCarEntirelyInside() {
    const auto plyrVeh = FindPlayerVehicle();
    if (!plyrVeh) {
        return false;
    }
    if (!plyrVeh->IsAutomobile() && !plyrVeh->IsBike()) {
        return false;
    }
    if (FindPlayerPed()->GetTaskManager().Find<TASK_COMPLEX_LEAVE_CAR>()) { // Ped is leaving teh car
        return false;
    }
    if (!GetAABB().IsPointWithin(plyrVeh->GetPosition())) {
        return false;
    }
    if (plyrVeh->GetMoveSpeed().SquaredMagnitude() >= sq(0.01f)) { // The originally compared each component: abs(x) > 0.01, but that's retarded
        return false;
    }
    if (!IsEntityEntirelyInside3D(plyrVeh)) {
        return false;
    }
    return true;
}

// 0x4486C0
eGarageDoorState CGarage::PlayerArrestedOrDied() {
    return plugin::CallMethodAndReturn<eGarageDoorState, 0x4486C0, CGarage*>(this);
}

// 0x447D50
void CGarage::OpenThisGarage() {
  if ( m_DoorState == GARAGE_DOOR_CLOSED
    || m_DoorState == GARAGE_DOOR_CLOSING
    || m_DoorState == GARAGE_DOOR_CLOSED_DROPPED_CAR)
  {
    m_DoorState = GARAGE_DOOR_OPENING;
  }
}

// 0x447D70
void CGarage::CloseThisGarage() {
    if (m_DoorState == GARAGE_DOOR_OPEN || m_DoorState == GARAGE_DOOR_OPENING)
        m_DoorState = GARAGE_DOOR_CLOSING;
}

// 0x447600
void CGarage::InitDoorsAtStart() {
    plugin::CallMethod<0x447600, CGarage*>(this);
}

// 0x44AA50
void CGarage::Update(int32 garageId) {
    plugin::CallMethod<0x44AA50, CGarage*>(this, garageId);
}

bool CGarage::IsHideOut() const {
    switch (m_Type) {
    case eGarageType::SAFEHOUSE_GANTON:
    case eGarageType::SAFEHOUSE_SANTAMARIA:
    case eGarageType::SAGEHOUSE_ROCKSHORE:
    case eGarageType::SAFEHOUSE_FORTCARSON:
    case eGarageType::SAFEHOUSE_VERDANTMEADOWS:
    case eGarageType::SAFEHOUSE_DILLIMORE:
    case eGarageType::SAFEHOUSE_PRICKLEPINE:
    case eGarageType::SAFEHOUSE_WHITEWOOD:
    case eGarageType::SAFEHOUSE_PALOMINOCREEK:
    case eGarageType::SAFEHOUSE_REDSANDSWEST:
    case eGarageType::SAFEHOUSE_ELCORONA:
    case eGarageType::SAFEHOUSE_MULHOLLAND:
    case eGarageType::SAFEHOUSE_CALTONHEIGHTS:
    case eGarageType::SAFEHOUSE_PARADISO:
    case eGarageType::SAFEHOUSE_DOHERTY:
    case eGarageType::SAFEHOUSE_HASHBURY:
    case eGarageType::HANGAR_ABANDONED_AIRPORT:
        return true;
    default:
        return false;
    }
}

bool CGarage::IsImpound() const {
    return notsa::contains({ IMPOUND_LS, IMPOUND_LV, IMPOUND_SF }, m_Type);
}

CVector2D CGarage::GetCenterOffset() const {
    return m_DirA * (m_DirA / 2.f)
         + m_DirB * (m_DirB / 2.f);
}

CBoundingBox CGarage::GetAABB() const {
    return {
        CVector{m_MinX, m_MinY, m_Base.z},
        CVector{m_MaxX, m_MaxY, m_CeilingZ}
    };
}

notsa::shapes::AngledRect CGarage::GetBaseAngledRect() const {
    return notsa::shapes::AngledRect{
        m_Base,
        -m_DirA, // AngledRect's AB goes left to right, but ours is vice versa, so flip it
        m_LenA,
        m_DirB,
        m_LenB
    };
}

notsa::shapes::AngledBox CGarage::GetBB() const {
    return {
        GetBaseAngledRect(),
        m_Base.z,
        m_CeilingZ
    };
}

// 0x44A9C0
bool CGarage::IsGarageEmpty() {
    return plugin::CallMethodAndReturn<bool, 0x44A9C0, CGarage*>(this);

    CVector cornerA = { m_MinX, m_MinY, m_Base.z };
    CVector cornerB = { m_MaxX, m_MaxY, m_CeilingZ   };

    int16 outCount[2];
    CEntity* outEntities[16];
    CWorld::FindObjectsIntersectingCube(&cornerA, &cornerB, outCount, static_cast<int16>(std::size(outEntities)), outEntities, false, true, true, false, false);
    if (outCount[0] <= 0)
        return true;

    int16 entityIndex = 0;

    while (!IsEntityTouching3D(outEntities[entityIndex])) {
        if (++entityIndex >= outCount[0])
            return true;
    }
    return false;
}

// Based on 0x4476D0
void CGarage::ChangeType(eGarageType newType) {
    m_Type = newType;
    switch (newType) {
    case BOMBSHOP_TIMED:
    case BOMBSHOP_ENGINE:
    case BOMBSHOP_REMOTE:
    case PAYNSPRAY: {
        if (IsClosed()) {
            SetOpened();
            m_DoorOpenness = 1.0f;
        }
        break;
    }
    case BURGLARY:
        break;
    default: {
        SetClosed();
        ResetDoorPosition();
        break;
    }
    }
}

// Based on 0x447CD0
void CGarage::Activate() {
    m_bInactive = false;
    if (m_Type == eGarageType::UNKN_CLOSESONTOUCH && IsClosed()) {
        SetOpened();
    }
}

void CGarage::DeActivate() {
    m_bInactive = true;
}

/*
void CGarage::CenterCarInGarage(CEntity* entity) {
    auto vehicle = FindPlayerVehicle();
    if (IsAnyOtherCarTouchingGarage(vehicle))
        return;

    auto player = FindPlayerPed();
    if (IsAnyOtherPedTouchingGarage(player))
        return;

    auto pos = entity->GetPosition();

    const auto halfX = (m_fRightCoord + m_fLeftCoord) * 0.5f;
    const auto halfY = (m_fBackCoord + m_fFrontCoord) * 0.5f;
    CVector p1{
        halfX - pos.x,
        halfY - pos.y,
        pos.z - pos.z
    };

    auto dist = p1.Magnitude();
    if (dist >= 0.4f) {
        auto x = halfX - pos.x * 0.4f / dist + pos.x;
        auto y = 0.4f / dist * halfY - pos.y + pos.y;
    } else {
        auto x = halfX;
        auto y = halfY;
    }

    if (!IsEntityEntirelyInside3D(entity, 0.3f))
        entity->SetPosn(entity->GetPosition());
}
*/

// 0x5D3020
void CSaveGarage::CopyGarageIntoSaveGarage(Const CGarage& g) {
    m_nType         = g.m_Type;
    m_nDoorState    = g.m_DoorState;
    m_nFlags        = g.m_nFlags;
    m_vPosn         = g.m_Base;
    m_vDirectionA   = g.m_DirA;
    m_vDirectionB   = g.m_DirB;
    m_fTopZ         = g.m_CeilingZ;
    m_fWidth        = g.m_LenA;
    m_fHeight       = g.m_LenB;
    m_fLeftCoord    = g.m_MinX;
    m_fRightCoord   = g.m_MaxX;
    m_fFrontCoord   = g.m_MinY;
    m_fBackCoord    = g.m_MaxY;
    m_fDoorPosition = g.m_DoorOpenness;
    m_nTimeToOpen   = g.m_TimeToOpen;
    m_nOriginalType = g.m_OriginalType;
    strcpy_s(m_anName, g.m_Name);
}

// 0x5D30C0
void CSaveGarage::CopyGarageOutOfSaveGarage(CGarage& g) const {
    g.m_Type         = m_nType;
    g.m_DoorState    = m_nDoorState;
    g.m_nFlags        = m_nFlags;
    g.m_Base         = m_vPosn;
    g.m_DirA   = m_vDirectionA;
    g.m_DirB   = m_vDirectionB;
    g.m_CeilingZ         = m_fTopZ;
    g.m_LenA        = m_fWidth;
    g.m_LenB       = m_fHeight;
    g.m_MinX    = m_fLeftCoord;
    g.m_MaxX   = m_fRightCoord;
    g.m_MinY   = m_fFrontCoord;
    g.m_MaxY    = m_fBackCoord;
    g.m_DoorOpenness = m_fDoorPosition;
    g.m_TimeToOpen   = m_nTimeToOpen;
    g.m_OriginalType = m_nOriginalType;
    g.m_TargetCar    = nullptr;
    strcpy_s(g.m_Name, m_anName);
}
