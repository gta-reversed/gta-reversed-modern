#include "StdInc.h"

#include "Garage.h"
#include "StoredCar.h"

void CGarage::InjectHooks() {
    RH_ScopedClass(CGarage);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(BuildRotatedDoorMatrix, 0x4479F0);                                                //
    // RH_ScopedInstall(TidyUpGarageClose, 0x449D10);                                                     //
    // RH_ScopedInstall(TidyUpGarage, 0x449C50);                                                          //
    RH_ScopedInstall(StoreAndRemoveCarsForThisHideOut, 0x449900);                                      //
    RH_ScopedInstall(EntityHasASphereWayOutsideGarage, 0x449050);                                      //
    RH_ScopedInstall(RemoveCarsBlockingDoorNotInside, 0x449690);                                       //
    RH_ScopedInstall(IsEntityTouching3D, 0x448EE0);                                                    //
    RH_ScopedInstall(IsEntityEntirelyOutside, 0x448D30);                                               //
    RH_ScopedInstall(IsEntityEntirelyInside3D, 0x448BE0);                                              //
    RH_ScopedInstall(IsStaticPlayerCarEntirelyInside, 0x44A830);                                       //
    RH_ScopedOverloadedInstall(IsPointInsideGarage, "p",  0x448740, bool(CGarage::*)(CVector));        //
    RH_ScopedOverloadedInstall(IsPointInsideGarage, "pr", 0x4487D0, bool(CGarage::*)(CVector, float)); //
    // RH_ScopedInstall(PlayerArrestedOrDied, 0x4486C0);                                                  //
    RH_ScopedInstall(OpenThisGarage, 0x447D50);                                                        //
    RH_ScopedInstall(CloseThisGarage, 0x447D70);                                                       //
    // RH_ScopedInstall(InitDoorsAtStart, 0x447600);                                                      //
    // RH_ScopedInstall(Update, 0x44AA50);                                                                //
    // RH_ScopedInstall(IsAnyOtherCarTouchingGarage, 0x449100);                                           //
    // RH_ScopedInstall(IsAnyOtherPedTouchingGarage, 0x4493E0);                                           //

    // RH_ScopedInstall(RightModTypeForThisGarage, 0x0);                                                  //
    // RH_ScopedInstall(CalcDistToGarageRectangleSquared, 0x0);                                           //
    // RH_ScopedInstall(NeatlyLineUpStoredCars, 0x0);                                                     //
    // RH_ScopedInstall(FindMaxNumStoredCarsForGarage, 0x0);                                              //
    // RH_ScopedInstall(IsPlayerOutsideGarage, 0x448E50);                                                 //
    // RH_ScopedInstall(IsPlayerEntirelyInsideGarage, 0x448EA0);                                          //
    // RH_ScopedInstall(ThrowCarsNearDoorOutOfGarage, 0x0);                                               //
    // RH_ScopedInstall(IsAnyCarBlockingDoor, 0x0);                                                       //
    // RH_ScopedInstall(CountCarsWithCenterPointWithinGarage, 0x0);                                       //
    // RH_ScopedInstall(StoreAndRemoveCarsForThisImpoundingGarage, 0x449A50);                             //
    // RH_ScopedInstall(FindDoorsWithGarage, 0x449FF0);                                                   //
    // RH_ScopedInstall(SlideDoorOpen, 0x44A660);                                                         //
    // RH_ScopedInstall(SlideDoorClosed, 0x44A750);                                                       //
}

// 0x4479F0
void CGarage::BuildRotatedDoorMatrix(CEntity* entity, float fDoorPosition) {
    const auto fAngle = fDoorPosition * -HALF_PI;
    const auto fSin = std::sin(fAngle);
    const auto fCos = std::cos(fAngle);
    CMatrix& matrix = entity->GetMatrix();

    const auto& vecForward = matrix.GetForward();
    matrix.GetUp() = CVector(-fSin * vecForward.y, fSin * vecForward.x, fCos);
    matrix.GetRight() = CrossProduct(vecForward, matrix.GetUp());
}

// 0x449D10
void CGarage::TidyUpGarageClose() {
    plugin::CallMethod<0x449D10, CGarage*>(this);
}

// 0x449C50
void CGarage::TidyUpGarage() {
    plugin::CallMethod<0x449C50, CGarage*>(this);
}

// 0x449900
void CGarage::StoreAndRemoveCarsForThisHideOut(CStoredCar* storedCars, int32 maxSlot) {
    maxSlot = std::min(maxSlot, NUM_GARAGE_STORED_CARS);

    for (auto i = 0; i < NUM_GARAGE_STORED_CARS; i++) {
        storedCars[i].Clear();
    }

    auto storedCarIdx{0u};
    for (auto i = 0; i < GetVehiclePool()->GetSize(); i++) {
        auto vehicle = GetVehiclePool()->GetAt(i);
        if (!vehicle)
            continue;

        if (IsPointInsideGarage(vehicle->GetPosition()) && !vehicle->IsCreatedBy(MISSION_VEHICLE)) {
            if (storedCarIdx < maxSlot && !EntityHasASphereWayOutsideGarage(vehicle, 1.0f)) {
                storedCars[storedCarIdx++].StoreCar(vehicle);
            }

            FindPlayerInfo().CancelPlayerEnteringCars(vehicle);
            CWorld::Remove(vehicle);
            delete vehicle;
        }
    }

    // Clear slots with no vehicles in it
    for (auto i = storedCarIdx; i < NUM_GARAGE_STORED_CARS; i++) {
        storedCars[i].Clear();
    }
}

// 0x448550
bool CGarage::RestoreCarsForThisHideOut(CStoredCar* car) {
    return 0;
}

// 0x4485C0
bool CGarage::RestoreCarsForThisImpoundingGarage(CStoredCar* car) {
    return 0;
}

// 0x449050
bool CGarage::EntityHasASphereWayOutsideGarage(CEntity* entity, float fRadius) {
    // return plugin::CallMethodAndReturn<bool, 0x449050, CGarage*, CEntity*, float>(this, entity, fRadius);

    for (auto& sphere : entity->GetColModel()->m_pColData->GetSpheres()) {
        auto mat = entity->GetMatrix(); // creates a matrix if it is missing
        auto point = MultiplyMatrixWithVector(mat, sphere.m_vecCenter);
        if (!IsPointInsideGarage(point, fRadius + sphere.m_fRadius)) {
            return true;
        }
    }
    return false;
}

// 0x449690
void CGarage::RemoveCarsBlockingDoorNotInside() {
    // return plugin::CallMethod<0x449690, CGarage*>(this);

    for (auto i = 0; i < GetVehiclePool()->GetSize(); i++) {
        auto vehicle = GetVehiclePool()->GetAt(i);
        if (!vehicle)
            continue;

        if (IsEntityTouching3D(vehicle) &&
            !IsPointInsideGarage(vehicle->GetPosition()) &&
            !vehicle->vehicleFlags.bIsLocked &&
            vehicle->CanBeDeleted()
        ) {
            CWorld::Remove(vehicle);
            delete vehicle;
            return;
        }
    }
}

// 0x448EE0
bool CGarage::IsEntityTouching3D(CEntity* entity) {
    // return plugin::CallMethodAndReturn<bool, 0x448EE0, CGarage*, CEntity*>(this, entity);

    const auto cm = entity->GetModelInfo()->GetColModel();
    const auto& radius = cm->GetBoundRadius();
    const auto& pos = entity->GetPosition();

    if (MinX - radius > pos.x || radius + MaxX < pos.x)
        return false;
    if (MinY - radius > pos.y || radius + MaxY < pos.y)
        return false;
    if (Base.z - radius > pos.z || radius + CeilingZ < pos.z)
        return false;

    for (auto& sphere : cm->m_pColData->GetSpheres()) {
        CVector point = MultiplyMatrixWithVector(entity->GetMatrix(), sphere.m_vecCenter);
        if (IsPointInsideGarage(point, sphere.m_fRadius)) {
            return true;
        }
    }
    return false;
}

// 0x44A830
bool CGarage::IsStaticPlayerCarEntirelyInside() {
    // return plugin::CallMethodAndReturn<bool, 0x44A830, CGarage*>(this);

    auto vehicle = FindPlayerVehicle();
    if (!vehicle)
        return false;
    if (!vehicle->IsAutomobile() && !vehicle->IsBike())
        return false;

    auto player = FindPlayerPed();
    if (player->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_LEAVE_CAR))
        return false;

    const auto& pos = vehicle->GetPosition();
    if (pos.x < MinX || pos.x > MaxX)
        return false;
    if (pos.y < MinY || pos.y > MaxY)
        return false;

    auto x = vehicle->m_vecMoveSpeed.x;
    if (x < 0.0f)
        x = -x;
    if (x > 0.01f)
        return false;

    auto y = vehicle->m_vecMoveSpeed.y;
    if (y < 0.0f)
        y = -y;
    if (y > 0.01f)
        return false;

    auto z = vehicle->m_vecMoveSpeed.z;
    if (z < 0.0f)
        z = -z;
    if (z > 0.01f)
        return false;

    if (CVector{ x, y, z }.SquaredMagnitude() > sq(0.01f))
        return false;

    return IsEntityEntirelyInside3D(vehicle, 0.0f);
}

// Doesn't check the height against the IsEntityEntirelyInside3D.
// Also, can't use inverted IsEntityEntirelyInside3D due m_pColData check.
// 0x448D30
bool CGarage::IsEntityEntirelyOutside(CEntity* entity, float radius) {
    // return plugin::CallMethodAndReturn<bool, 0x448D30, CGarage*, CEntity*, float>(this, entity, radius);

    const auto& pos = entity->GetPosition();
    if (MinX - radius < pos.x || radius + MaxX > pos.x)
        return false;
    if (MinY - radius < pos.y || radius + MaxY > pos.y)
        return false;

    auto cd = entity->GetColModel()->m_pColData;
    if (!cd) return true;

    for (const auto& sphere : cd->GetSpheres()) {
        CVector out = MultiplyMatrixWithVector(entity->GetMatrix(), sphere.m_vecCenter);
        if (!IsPointInsideGarage(out, radius + sphere.m_fRadius)) {
            return true;
        }
    }
    return false;
}

// 0x448BE0
bool CGarage::IsEntityEntirelyInside3D(CEntity* entity, float radius) {
    // return plugin::CallMethodAndReturn<bool, 0x448BE0, CGarage*, CEntity*, float>(this, entity, radius);

    const auto& pos = entity->GetPosition();
    if (MinX - radius > pos.x || radius + MaxX < pos.x)
        return false;
    if (MinY - radius > pos.y || radius + MaxY < pos.y)
        return false;
    if (Base.z - radius > pos.z || radius + CeilingZ < pos.z)
        return false;

    auto cd = entity->GetColModel()->m_pColData;
    if (!cd) return true;

    for (const auto& sphere : cd->GetSpheres()) {
        CVector out = MultiplyMatrixWithVector(entity->GetMatrix(), sphere.m_vecCenter);
        if (IsPointInsideGarage(out, radius - sphere.m_fRadius)) {
            return true;
        }
    }
    return false;
}

// 0x4486C0
eGarageDoorState CGarage::PlayerArrestedOrDied() {
    return plugin::CallMethodAndReturn<eGarageDoorState, 0x4486C0, CGarage*>(this);
}

// 0x447D50
void CGarage::OpenThisGarage() {
    if (DoorState == GARAGE_DOOR_CLOSED || DoorState == GARAGE_DOOR_CLOSING || DoorState == GARAGE_DOOR_CLOSED_DROPPED_CAR
    ) {
        DoorState = GARAGE_DOOR_OPENING;
    }
}

// 0x447D70
void CGarage::CloseThisGarage() {
    if (DoorState == GARAGE_DOOR_OPEN || DoorState == GARAGE_DOOR_OPENING) {
        DoorState = GARAGE_DOOR_CLOSING;
    }
}

// 0x447600
void CGarage::InitDoorsAtStart() {
    plugin::CallMethod<0x447600, CGarage*>(this);
}

// 0x448740
bool CGarage::IsPointInsideGarage(CVector point) {
    // return plugin::CallMethodAndReturn<bool, 0x448740, CGarage*, CVector>(this, point);

    if (point.z < Base.z || point.z > CeilingZ)
        return false;

    const auto x0 = point.x - Base.x;
    const auto y0 = point.y - Base.y;

    auto sqMagA = x0 * m_Delta1.x + y0 * m_Delta1.y;
    if (sqMagA < 0.0f || sqMagA > Delta1Length)
        return false;

    auto sqMagB = x0 * m_Delta2.x + y0 * m_Delta2.y;
    if (sqMagB < 0.0f || sqMagB > Delta2Length)
        return false;

    return true;
}

// See CZoneDef::IsPointWithin
// 0x4487D0
bool CGarage::IsPointInsideGarage(CVector point, float radius) {
    // return plugin::CallMethodAndReturn<bool, 0x4487D0, CGarage*, CVector, float>(this, point, radius);

    if (Base.z - radius > point.z || radius + CeilingZ < point.z)
        return false;

    const auto x0 = point.x - Base.x;
    const auto y0 = point.y - Base.y;

    auto sqMagA = x0 * m_Delta1.x + y0 * m_Delta1.y;
    if (sqMagA < -radius || sqMagA > radius + Delta1Length)
        return false;

    auto sqMagB = x0 * m_Delta2.x + y0 * m_Delta2.y;
    if (sqMagB < -radius || sqMagB > radius + Delta2Length)
        return false;

    return true;
}

// 0x44AA50
void CGarage::Update(int32 garageId) {
    plugin::CallMethod<0x44AA50, CGarage*>(this, garageId);
}

bool CGarage::IsHideOut() const {
    switch (Type) {
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

// 0x44A9C0
bool CGarage::IsGarageEmpty() {
    // return plugin::CallMethodAndReturn<bool, 0x44A9C0, CGarage*>(this);

    CVector cornerA = { MinX, MinY, Base.z   };
    CVector cornerB = { MaxX, MaxY, CeilingZ };

    int16 outCount[2];
    CEntity* outEntities[16];
    CWorld::FindObjectsIntersectingCube(&cornerA, &cornerB, outCount, std::size(outEntities), outEntities, false, true, true, false, false);
    if (outCount[0] <= 0)
        return true;

    int16 entityIndex = 0;

    while (!IsEntityTouching3D(outEntities[entityIndex])) {
        if (++entityIndex >= outCount[0])
            return true;
    }
    return false;
}

// 0x449100
bool CGarage::IsAnyOtherCarTouchingGarage(CVehicle* vehicle) {
    return plugin::CallMethodAndReturn<bool, 0x449100, CGarage*, CVehicle*>(this, vehicle);
}

// 0x4493E0
bool CGarage::IsAnyOtherPedTouchingGarage(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x4493E0, CGarage*, CPed*>(this, ped);
}

// WIP?
// 0x449E90
void CGarage::CenterCarInGarage(CVehicle* vehicle) {
    if (IsAnyOtherCarTouchingGarage(FindPlayerVehicle()) || IsAnyOtherPedTouchingGarage(FindPlayerPed()))
        return;

    const auto& pos = vehicle->GetPosition();
    const auto halfX = (MaxX + MinX) / 2.0f;
    const auto halfY = (MaxY + MinY) / 2.0f;
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

    if (!IsEntityEntirelyInside3D(vehicle, 0.3f)) {
        vehicle->SetPosn(pos);
    }
}

bool CGarage::RightModTypeForThisGarage(CVehicle* vehicle) {
    return 0;
}

// untested
float CGarage::CalcDistToGarageRectangleSquared(float x, float y) {
    float dx{}, dy{};

    if (MinX > x || x > MaxX) {
        dx = x - MinX * x - MinX;
    }

    if (MinY > y || y > MaxY) {
        dy = y - MinY * y - MinY;
    }

    return dx + dy;
}

void CGarage::NeatlyLineUpStoredCars(CStoredCar* car) {

}

int32 CGarage::FindMaxNumStoredCarsForGarage() {
    return 0;
}

// 0x448E50
bool CGarage::IsPlayerOutsideGarage(float fRadius) {
    CEntity* entity;
    auto vehicle = FindPlayerVehicle();
    if (vehicle)
        entity = vehicle;
    else
        entity = FindPlayerPed();
    return IsEntityEntirelyOutside(entity, fRadius);
}

// 0x448EA0
bool CGarage::IsPlayerEntirelyInsideGarage() {
    CEntity* entity;
    auto vehicle = FindPlayerVehicle();
    if (vehicle)
        entity = vehicle;
    else
        entity = FindPlayerPed();
    return IsEntityEntirelyInside3D(entity, 0.0f);
}

void CGarage::ThrowCarsNearDoorOutOfGarage(CVehicle* ignoredVehicle) {

}

bool CGarage::IsAnyCarBlockingDoor() {
    return 0;
}

int32 CGarage::CountCarsWithCenterPointWithinGarage(CVehicle* ignoredVehicle) {
    return 0;
}

// 0x449A50
void CGarage::StoreAndRemoveCarsForThisImpoundingGarage(CStoredCar* storedCars, int32 iMaxSlot) {

}

// 0x449FF0
void CGarage::FindDoorsWithGarage(CObject** ppFirstDoor, CObject** ppSecondDoor) {

}

// 0x44A660
bool CGarage::SlideDoorOpen() {
    return 0;
}

// 0x44A750
bool CGarage::SlideDoorClosed() {
    return 0;
}
