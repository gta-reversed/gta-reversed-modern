#include "StdInc.h"

#include "Pickup.h"
#include "ModelIndices.h"

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
    return plugin::CallMethod<0x454BE0, CPickup*, CPlayerPed*>(this, player);
    const auto weapon = CPickups::WeaponForModel(m_pObject->m_nModelIndex);
    const auto slot = CWeaponInfo::GetWeaponInfo(weapon)->m_nSlot;

    if (m_nPickupType != PICKUP_IN_SHOP) {
        switch (slot) {
        case PICKUP_ONCE:
        case PICKUP_ONCE_TIMEOUT:
        case PICKUP_ONCE_TIMEOUT_SLOW:
            break;

        default:
            return;
        }

        const auto EmptyAmmo = [this] {
            m_nFlags.bEmpty = true;
            m_nAmmo = 0;
        };

        if (m_nAmmo) {
            player->GrantAmmo(weapon, m_nAmmo);
        } else {
            if (m_nFlags.bEmpty) {
                return EmptyAmmo();
            }

            player->GrantAmmo(weapon, AmmoForWeapon_OnStreet[weapon]);
        }

        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_PICKUP_WEAPON);
        EmptyAmmo();
    }
}

// 0x455540
const char* CPickup::FindStringForTextIndex(ePickupPropertyText index) {
    switch (index) {
    case PICKUP_PROPERTY_TEXT_CAN_BUY:
        return "PROP_3"; // Press ~k~~PED_ANSWER_PHONE~ to buy this property.

    case PICKUP_PROPERTY_TEXT_CANT_BUY:
        return "PROP_4"; // You cannot buy this property yet.

    case PICKUP_PROPERTY_TEXT_CANCEL:
    default:
        return "FESZ_CA"; // Cancel
    }
}

// 0x455500
ePickupPropertyText CPickup::FindTextIndexForString(const char* message) {
    if (!message)
        return PICKUP_PROPERTY_TEXT_CANCEL;

    if (!_stricmp("PROP_3", message)) {
        return PICKUP_PROPERTY_TEXT_CAN_BUY;
    } else if (!_stricmp("PROP_4", message)) {
        return PICKUP_PROPERTY_TEXT_CANT_BUY;
    }

    return PICKUP_PROPERTY_TEXT_CANCEL;
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
    return DistanceBetweenPoints2D(GetPosn2D(), TheCamera.GetPosition()) < 100.0f;
}

// 0x454D20
bool CPickup::PickUpShouldBeInvisible() {
    return plugin::CallMethodAndReturn<bool, 0x454D20, CPickup*>(this);

    const auto IsKillFrenzy = [this] {
        return CLocalisation::KillFrenzy() && m_nModelIndex == ModelIndices::MI_PICKUP_KILLFRENZY && CTheScripts::IsPlayerOnAMission() && CDarkel::FrenzyOnGoing();
    };

    if (CCutsceneMgr::ms_running || IsKillFrenzy() || (m_nPickupType == PICKUP_2P && FindPlayerPed(PED_TYPE_PLAYER2))) {
        return true;
    }

    const CVector2D somewhere{+1479.0f, -1658.0f};
    if (m_nModelIndex == ModelIndices::MI_PICKUP_2P_KILLFRENZY && CLocalisation::GermanGame()
      && (DistanceBetweenPoints2D(GetPosn2D(), somewhere) < 10.0f || DistanceBetweenPoints2D(GetPosn2D(), {}) < 10.0f)) {
        return true;
    }

    if (TheCamera.m_bWideScreenOn && m_nPickupType != PICKUP_ASSET_REVENUE && m_nModelIndex != MODEL_FIRE_EX) {
        return true;
    }

    if (!CGameLogic::IsCoopGameGoingOn() || CWeapon::CanBeUsedFor2Player(CPickups::WeaponForModel(m_nModelIndex))) {
        return false;
    }
}

// Checks if pickup collides with line (origin;target), removes pickup and creates an explosion. Used in previous GTA games for mine pickup
// 0x4588B0
void CPickup::ProcessGunShot(CVector* start, CVector* end) {
    if (!m_pObject)
        return;

    if (const auto posn = m_pObject->GetPosition(); CCollision::TestLineSphere({start, end}, {4.0f, posn})) {
        CExplosion::AddExplosion(nullptr, nullptr, EXPLOSION_MINE, posn, 0, true, -1.0f, false);
        Remove();
    }
}

// 0x4556C0
void CPickup::Remove() {
    CRadar::ClearBlipForEntity(BLIP_PICKUP, m_nReferenceIndex);
    GetRidOfObjects();
    m_nPickupType = PICKUP_NONE;
    m_nFlags.bDisabled = true;
}

// 0x454960
void CPickup::SetPosn(CVector posn) {
    m_vecPos = CompressLargeVector(posn);
}

// Updates the pickup. Returns TRUE if pickup was removed/disabled
// 0x457410
void CPickup::Update(CPlayerPed* player, CVehicle* vehicle, int32 playerId) {
    plugin::CallMethod<0x457410, CPickup*, CPlayerPed*, CVehicle*, int32>(this, player, vehicle, playerId);
}
