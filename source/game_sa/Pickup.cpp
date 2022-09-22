#include "StdInc.h"

#include "Pickup.h"

void CPickup::InjectHooks() {
    RH_ScopedClass(CPickup);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(ExtractAmmoFromPickup, 0x454BE0, { .reversed = false });
    RH_ScopedInstall(FindStringForTextIndex, 0x455540);
    RH_ScopedInstall(FindTextIndexForString, 0x455500);
    RH_ScopedInstall(GetPosn, 0x4549A0);
    RH_ScopedInstall(GetRidOfObjects, 0x454CF0);
    RH_ScopedInstall(GiveUsAPickUpObject, 0x4567E0, { .reversed = false });
    RH_ScopedInstall(IsVisible, 0x454C70);
    RH_ScopedInstall(PickUpShouldBeInvisible, 0x454D20, { .reversed = false });
    RH_ScopedInstall(ProcessGunShot, 0x4588B0);
    RH_ScopedInstall(Remove, 0x4556C0, { .reversed = false });
    RH_ScopedInstall(SetPosn, 0x454960);
    RH_ScopedInstall(Update, 0x457410, { .reversed = false });
}

// Give player an ammo from weapon pickup
// 0x454BE0
void CPickup::ExtractAmmoFromPickup(CPlayerPed* player) {
    plugin::CallMethod<0x454BE0, CPickup*, CPlayerPed*>(this, player);
}

// 0x455540
const char* CPickup::FindStringForTextIndex(int32 index) {
    if (index == 1) return "PROP_3";
    if (index == 2) return "PROP_4";
    return "FESZ_CA";
}

// message = GXT key
// 0x455500
int32 CPickup::FindTextIndexForString(char* message) {
    if (!message) return 0;
    if (!_stricmp("PROP_3", message)) return 1;
    if (!_stricmp("PROP_4", message)) return 2;
    return 0;
}

// 0x4549A0
CVector CPickup::GetPosn() const {
    return UncompressLargeVector(m_vecPos);
}

// Delete pickup's object (CObject)
// 0x454CF0
void CPickup::GetRidOfObjects() {
    if (m_pObject) {
        CWorld::Remove(m_pObject);
        delete m_pObject;
        m_pObject = nullptr;
    }
}

// Creates an object (CObject) for pickup. slotIndex - object to replace; use -1 to create a new object
// 0x4567E0
void CPickup::GiveUsAPickUpObject(CObject** obj, int32 slotIndex) {
    plugin::CallMethod<0x4567E0, CPickup*, CObject**, int32>(this, obj, slotIndex);
}

// Is pickup visible (checks if distance between pickup and camera is shorter than 100 units)
// 0x454C70
bool CPickup::IsVisible() {
    return DistanceBetweenPoints2D({ GetXCoord(), GetYCoord() }, TheCamera.GetPosition()) < 100.0f;
}

// 0x454D20
bool CPickup::PickUpShouldBeInvisible() {
    return plugin::CallMethodAndReturn<bool, 0x454D20, CPickup*>(this);
}

// Checks if pickup collides with line (origin;target), removes pickup and creates an explosion. Used in previous GTA games for mine pickup
// 0x4588B0
void CPickup::ProcessGunShot(CVector* start, CVector* end) {
    if (!m_pObject)
        return;

    if (CCollision::TestLineSphere({ start, end }, { 4.0f, m_pObject->GetPosition() })) {
        const auto posn = m_pObject->GetPosition();
        CExplosion::AddExplosion(nullptr, nullptr, EXPLOSION_MINE, posn, 0, true, -1.0f, false);
        Remove();
    }
}

// 0x4556C0
void CPickup::Remove() {
    plugin::CallMethod<0x4556C0, CPickup*>(this);
    /*
    auto handle = (this - CPickups::aPickUps) | (CPickups::aPickUps[this - CPickups::aPickUps].m_nReferenceIndex << 16);
    CRadar::ClearBlipForEntity(static_cast<eBlipType>(BLIP_CONTACT_POINT | BLIP_CHAR), handle);
    GetRidOfObjects();
    m_nPickupType = PICKUP_NONE;
    m_nFlags.bDisabled = true;
    */
}

// 0x454960
void CPickup::SetPosn(float x, float y, float z) {
    m_vecPos = CompressLargeVector({x, y, z});
}

// Updates the pickup. Returns TRUE if pickup was removed/disabled
// 0x457410
void CPickup::Update(CPlayerPed* player, CVehicle* vehicle, int32 playerId) {
    plugin::CallMethod<0x457410, CPickup*, CPlayerPed*, CVehicle*, int32>(this, player, vehicle, playerId);
}
