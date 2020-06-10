#include "StdInc.h"

void CEventDamage::InjectHooks() {
    HookInstall(0x4B33B0, (CEventDamage*(CEventDamage::*)(CEventDamage*)) & CEventDamage::Constructor, 7);
    HookInstall(0x4AD830, (CEventDamage * (CEventDamage::*)(CEntity*, unsigned int, eWeaponType, ePedPieceTypes, unsigned char, bool, bool)) & CEventDamage::Constructor, 7);
    HookInstall(0x4AD910, &CEventDamage::GetEventType_Reversed, 7);
    HookInstall(0x4AD950, &CEventDamage::GetEventPriority_Reversed, 7);
    HookInstall(0x4AD920, &CEventDamage::GetLifeTime_Reversed, 7);
    HookInstall(0x4B35A0, &CEventDamage::AffectsPed_Reversed, 7);
    HookInstall(0x4B38D0, &CEventDamage::AffectsPedGroup_Reversed, 7);
    HookInstall(0x4ADA90, &CEventDamage::IsCriminalEvent_Reversed, 7);
    HookInstall(0x4B3440, &CEventDamage::ReportCriminalEvent_Reversed, 7);
    HookInstall(0x4ADA70, &CEventDamage::GetSourceEntity_Reversed, 7);
    HookInstall(0x4ADB00, &CEventDamage::TakesPriorityOver_Reversed, 7);
    HookInstall(0x4AD930, &CEventDamage::GetLocalSoundLevel_Reversed, 7);
    HookInstall(0x4ADAE0, &CEventDamage::DoInformVehicleOccupants_Reversed, 7);
    HookInstall(0x4AD940, &CEventDamage::CanBeInterruptedBySameEvent_Reversed, 7);
    HookInstall(0x4B5D40, &CEventDamage::CloneEditable_Reversed, 7);
    HookInstall(0x4AD9C0, &CEventDamage::From, 7);
    HookInstall(0x4B3A20, &CEventDamage::ProcessDamage, 7);
    HookInstall(0x4ADC10, &CEventDamage::ComputeBodyPartToRemove, 7);
    HookInstall(0x4B3A60, &CEventDamage::ComputeDeathAnim, 7);
    HookInstall(0x4B3FC0, &CEventDamage::ComputeDamageAnim, 7);
}

CEventDamage::CEventDamage(CEventDamage* pCopyFrom) {
    m_damageResponse.m_fDamageHealth = 0.0f;
    m_damageResponse.m_fDamageArmor = 0.0f;
    m_damageResponse.m_bHealthZero = false;
    m_damageResponse.m_bForceDeath = false;
    m_damageResponse.m_bDamageCalculated = false;
    m_damageResponse.m_bCheckIfAffectsPed = false;
    From(pCopyFrom);
}

CEventDamage::CEventDamage(CEntity* source, unsigned int startTime, eWeaponType weaponType, ePedPieceTypes pieceHit, unsigned char direction, bool a7, bool bPedInVehicle) {
    m_pSourceEntity = source;
    m_nStartTime = startTime;
    m_weaponType = weaponType;
    m_pedPieceType = pieceHit;
    m_ucDirection = direction;
    m_ucFlags = 0;
    m_bPedInVehicle = bPedInVehicle;
    m_b01 = a7;
    m_nAnimGroup = 0;
    m_nAnimID = ANIM_ID_NO_ANIMATION_SET;
    m_fAnimBlend = 8.0f;
    m_fAnimSpeed = 1.0f;
    m_damageResponse.m_fDamageHealth = 0.0f;
    m_damageResponse.m_fDamageArmor = 0.0f;
    m_damageResponse.m_bHealthZero = false;
    m_damageResponse.m_bForceDeath = false;
    m_damageResponse.m_bDamageCalculated = false;
    m_damageResponse.m_bCheckIfAffectsPed = false;
    if (m_pSourceEntity)
        m_pSourceEntity->RegisterReference(&m_pSourceEntity);
    m_bPedInVehicle = true; // if we're setting this to true, then why do we have bPedInVehicle paramter in this constructor? bug?
}

CEventDamage::~CEventDamage() {
    if (m_pSourceEntity)
        m_pSourceEntity->CleanUpOldReference(&m_pSourceEntity);
}

CEventDamage* CEventDamage::Constructor(CEventDamage* pCopyFrom) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventDamage*, 0x4B33B0, CEventDamage*, CEventDamage*>(this, pCopyFrom);
#else
    this->CEventDamage::CEventDamage(pCopyFrom);
    return this;
#endif
}

CEventDamage* CEventDamage::Constructor(CEntity* source, unsigned int startTime, eWeaponType weaponType, ePedPieceTypes pieceHit, unsigned char direction, bool a7, bool bPedInVehicle) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventDamage*, 0x4AD830, CEventDamage*, CEntity *, unsigned int, eWeaponType, ePedPieceTypes, unsigned char, bool, bool>(this, source, startTime, weaponType, pieceHit, direction, a7, bPedInVehicle);
#else
    this->CEventDamage::CEventDamage(source, startTime, weaponType, pieceHit, direction, a7, bPedInVehicle);
    return this;
#endif
}

eEventType CEventDamage::GetEventType() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((eEventType(__thiscall*)(CEvent*))0x4AD910)(this);
#else
    return CEventDamage::GetEventType_Reversed();
#endif
}

int CEventDamage::GetEventPriority() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(__thiscall*)(CEvent*))0x4AD950)(this);
#else
    return CEventDamage::GetEventPriority_Reversed();
#endif
}

int CEventDamage::GetLifeTime() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(__thiscall*)(CEvent*))0x4AD920)(this);
#else
    return CEventDamage::GetLifeTime_Reversed();
#endif
}

bool CEventDamage::AffectsPed(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*, CPed*))0x4B35A0)(this, ped);
#else
    return CEventDamage::AffectsPed_Reversed(ped);
#endif
}

bool CEventDamage::AffectsPedGroup(CPedGroup* pedGroup) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*, CPedGroup*))0x4B38D0)(this, pedGroup);
#else
    return CEventDamage::AffectsPedGroup_Reversed(pedGroup);
#endif
}

bool CEventDamage::IsCriminalEvent() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*))0x4ADA90)(this);
#else
    return CEventDamage::IsCriminalEvent_Reversed();
#endif
}

void CEventDamage::ReportCriminalEvent(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((void(__thiscall*)(CEvent*, CPed*))0x4B3440)(this, ped);
#else
    return CEventDamage::ReportCriminalEvent_Reversed(ped);
#endif
}

CEntity* CEventDamage::GetSourceEntity() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CEntity * (__thiscall*)(CEvent*))0x4ADA70)(this);
#else
    return CEventDamage::GetSourceEntity_Reversed();
#endif
}

bool CEventDamage::TakesPriorityOver(CEvent* refEvent) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*, CEvent*))0x4ADB00)(this, refEvent);
#else
    return CEventDamage::TakesPriorityOver_Reversed(refEvent);
#endif
}

float CEventDamage::GetLocalSoundLevel() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*))0x4AD930)(this);
#else
    return CEventDamage::GetLocalSoundLevel_Reversed();
#endif
}


bool CEventDamage::DoInformVehicleOccupants(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*, CPed*))0x4ADAE0)(this, ped);
#else
    return CEventDamage::DoInformVehicleOccupants_Reversed(ped);
#endif
}

bool CEventDamage::CanBeInterruptedBySameEvent() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*))0x4AD940)(this);
#else
    return CEventDamage::CanBeInterruptedBySameEvent_Reversed();
#endif
}

CEventEditableResponse* CEventDamage::CloneEditable() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CEventEditableResponse * (__thiscall*)(CEvent*))0x4B5D40)(this);
#else
    return CEventDamage::CloneEditable_Reversed();
#endif
}

bool CEventDamage::AffectsPed_Reversed(CPed* ped) {
    CPed* pPedSourceEntity = static_cast<CPed*>(GetSourceEntity());
    if (m_damageResponse.m_bDamageCalculated && !m_damageResponse.m_bCheckIfAffectsPed)
        return true;
    if (!ped->IsAlive() || ped == FindPlayerPed(-1) && !FindPlayerPed(-1)->m_pPlayerData->m_bCanBeDamaged)
        return false;
    if (m_weaponType == WEAPON_DROWNING && !ped->bDrownsInWater)
        return false;
    if (ped == FindPlayerPed(-1)) {
        if (m_pSourceEntity) {
            if (m_pSourceEntity->m_nType == ENTITY_TYPE_PED && pPedSourceEntity->m_nPedType == PED_TYPE_GANG2 && m_weaponType >= WEAPON_GRENADE) {
                CTaskManager* pTaskManager = &pPedSourceEntity->m_pIntelligence->m_TaskMgr;
                auto pTask = static_cast<CTaskComplexKillPedOnFoot*>(pTaskManager->FindActiveTaskByType(TASK_COMPLEX_KILL_PED_ON_FOOT));
                if (!pTask || pTask->m_pTarget != ped)
                    return false;
            }
        }
    }
    if (ped == FindPlayerPed(-1)) {
        if (CWorld::Players[CWorld::PlayerInFocus].m_bFireProof) {
            if (m_weaponType == WEAPON_MOLOTOV || m_weaponType == WEAPON_FLAMETHROWER)
                return false;
        }
    }
    if (ped->physicalFlags.bInvulnerable) {
        if (pPedSourceEntity != FindPlayerPed(-1)) {
            if (m_weaponType != WEAPON_DROWNING && m_weaponType != WEAPON_EXPLOSION && ped->m_fHealth > 0.0f)
                return false;
        }
    }
    if (ped->bHasBulletProofVest) {
        if (CWeaponInfo::GetWeaponInfo(m_weaponType, 1)->m_nWeaponFire == WEAPON_FIRE_INSTANT_HIT) {
            if (m_pedPieceType == PED_PIECE_TORSO || m_pedPieceType == PED_PIECE_ASS)
                return false;
        }
    }
    if (!m_bAddToEventGroup)
    {
        if (m_weaponType == WEAPON_PISTOL_SILENCED) {
            if (!m_pSourceEntity)
                return false;
            if (m_pSourceEntity->m_nType != ENTITY_TYPE_PED)
                return false;
            if (!m_bPedInVehicle)
                return false;
            if (!ped->bInVehicle)
                return false;
        }
        if (m_pSourceEntity) {
            if (m_pSourceEntity->m_nType == ENTITY_TYPE_PED) {
                CTask* pActiveTask = pPedSourceEntity->m_pIntelligence->m_TaskMgr.GetActiveTask();
                if (pActiveTask && pActiveTask->GetId() == TASK_SIMPLE_STEALTH_KILL) {
                    CVector vecDirection = m_pSourceEntity->GetPosition() - ped->GetPosition();
                    vecDirection.Normalise();
                    if (ped->m_pIntelligence->CanSeeEntityWithLights(m_pSourceEntity, 0) <= 0.0f
                        || DotProduct(&vecDirection, &ped->GetForward()) < CPedAcquaintanceScanner::ms_fThresholdDotProduct) 
                    {
                        return false;
                    }
                }
            }
        }
    }
    if (m_pSourceEntity) {
        if (m_pSourceEntity->m_nType == ENTITY_TYPE_PED && !pPedSourceEntity->IsPlayer() 
            && CPedGroups::AreInSameGroup(ped, pPedSourceEntity) && m_weaponType != WEAPON_EXPLOSION) {
            return false;
        }
    }
    bool bAffectsPed = ped->CanPhysicalBeDamaged(m_weaponType, 0);
    if (m_weaponType == WEAPON_FALL
        && (ped->physicalFlags.bCollisionProof || ped->m_pAttachedTo || ped->m_fHealth > 0.0 && ped->m_pIntelligence->GetTaskJetPack())) {
        bAffectsPed = false;
    }
    return bAffectsPed;

}

bool CEventDamage::AffectsPedGroup_Reversed(CPedGroup* pedGroup) {
    if (m_weaponType == WEAPON_PISTOL_SILENCED)
        return false;
    if (!m_pSourceEntity)
        return true;
    if (m_pSourceEntity->m_nType != ENTITY_TYPE_PED)
        return true;
    CPed* pPed = static_cast<CPed*>(m_pSourceEntity);
    CTask* pActiveTask = pPed->m_pIntelligence->m_TaskMgr.GetActiveTask();
    if (!pActiveTask)
        return true;
    if (pActiveTask->GetId() != TASK_SIMPLE_STEALTH_KILL)
        return true;
    for (size_t memberId = 0; memberId < 8; memberId++) {
        CPed* pGroupMember = pedGroup->m_groupMembership.GetMember(memberId);
        if (pGroupMember) {
            CVector vecDirection = m_pSourceEntity->GetPosition() - pGroupMember->GetPosition();
            vecDirection.Normalise();
            if (pGroupMember->m_pIntelligence->CanSeeEntityWithLights(m_pSourceEntity, 0) > 0.0f) {
                if (DotProduct(&vecDirection, &pGroupMember->GetForward()) > CPedAcquaintanceScanner::ms_fThresholdDotProduct)
                    return true;
            }
        }
    }
    return false;
}

bool CEventDamage::IsCriminalEvent_Reversed() {
    if (m_pSourceEntity) {
        CVehicle* pVehicle = static_cast<CVehicle*>(m_pSourceEntity);
        CPed* pPed = static_cast<CPed*>(m_pSourceEntity);
        return (m_pSourceEntity->m_nType == ENTITY_TYPE_PED && pPed->IsPlayer()
                || m_pSourceEntity->m_nType == ENTITY_TYPE_VEHICLE && pVehicle->m_pDriver == FindPlayerPed(-1));
    }
    return false;
}

void CEventDamage::ReportCriminalEvent_Reversed(CPed* ped) {
    if (IsCriminalEvent() && m_pSourceEntity) {
        bool bPoliceCareAboutCrime = CPedType::PoliceDontCareAboutCrimesAgainstPedType(ped->m_nPedType);
        if (m_weaponType <= WEAPON_CHAINSAW) {
            enum eCrimeType crimeType = eCrimeType::CRIME_DAMAGED_PED;
            if (ped->m_nPedType == PED_TYPE_COP)
                crimeType = eCrimeType::CRIME_DAMAGED_COP;
            FindPlayerWanted(-1)->RegisterCrime(crimeType, m_pSourceEntity->GetPosition(), ped, bPoliceCareAboutCrime);
            return;
        }
        if (m_weaponType <= WEAPON_DETONATOR || m_weaponType == WEAPON_SPRAYCAN) {
            enum eCrimeType crimeType = eCrimeType::CRIME_DAMAGE_CAR;
            if (ped->m_nPedType == PED_TYPE_COP)
                crimeType = eCrimeType::CRIME_DAMAGE_COP_CAR;
            FindPlayerWanted(-1)->RegisterCrime(crimeType, m_pSourceEntity->GetPosition(), ped, bPoliceCareAboutCrime);
            return;
        }
        if (m_weaponType == WEAPON_RAMMEDBYCAR || m_weaponType == WEAPON_RUNOVERBYCAR) {
            enum eCrimeType crimeType = eCrimeType::CRIME_KILL_PED_WITH_CAR;
            if (ped->m_nPedType == PED_TYPE_COP)
                crimeType = eCrimeType::CRIME_KILL_COP_PED_WITH_CAR;
            FindPlayerWanted(-1)->RegisterCrime(crimeType, m_pSourceEntity->GetPosition(), ped, bPoliceCareAboutCrime);
            return;
        }
    }
}

CEntity* CEventDamage::GetSourceEntity_Reversed() {
    if (m_pSourceEntity && m_pSourceEntity->m_nType == ENTITY_TYPE_VEHICLE) {
        CVehicle* pVehicle = static_cast<CVehicle*>(m_pSourceEntity);
        if (pVehicle->m_pDriver)
            return pVehicle->m_pDriver;
    }
    return m_pSourceEntity;
}

bool CEventDamage::TakesPriorityOver_Reversed(CEvent* refEvent) {
    if (refEvent->GetEventType() == EVENT_IN_WATER && m_damageResponse.m_bHealthZero && m_bAddToEventGroup
        || refEvent->GetEventType() == EVENT_ON_FIRE && m_damageResponse.m_bHealthZero && m_bAddToEventGroup
        || refEvent->GetEventType() == EVENT_KNOCK_OFF_BIKE && m_damageResponse.m_bHealthZero && m_bAddToEventGroup) {
        return true;
    }
    CPed* pPed = static_cast<CPed*>(m_pSourceEntity);
    if (m_pSourceEntity && m_pSourceEntity->m_nType == ENTITY_TYPE_PED && pPed->IsPlayer() && refEvent->GetEventType() == EVENT_DAMAGE) {
        if (refEvent->GetSourceEntity() == m_pSourceEntity && (!m_damageResponse.m_bHealthZero || !m_bAddToEventGroup))
            return CEvent::TakesPriorityOver(refEvent);
        return true;
    }
    if (refEvent->GetEventType() == EVENT_DAMAGE) {
        if (GetSourceEntity() != refEvent->GetSourceEntity())
            return true;
    }
    return CEvent::TakesPriorityOver(refEvent);
}

bool CEventDamage::DoInformVehicleOccupants_Reversed(CPed* ped) {
    if (GetSourceEntity())
        return m_weaponType != WEAPON_DROWNING;
    return false;
}

CEventEditableResponse* CEventDamage::CloneEditable_Reversed() {
    CEventDamage* pClonedEvent = new CEventDamage(this);
    pClonedEvent->m_nAnimID = m_nAnimID;
    pClonedEvent->m_b05 = m_b05;
    return pClonedEvent;
}

void CEventDamage::From(CEventDamage* pCopyFrom) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4AD9C0, CEventDamage*, CEvent*>(this, pCopyFrom);
#else
    m_pSourceEntity = pCopyFrom->m_pSourceEntity;
    if (pCopyFrom->m_pSourceEntity)
        pCopyFrom->m_pSourceEntity->RegisterReference(&m_pSourceEntity);
    m_nStartTime = pCopyFrom->m_nStartTime;
    m_weaponType = pCopyFrom->m_weaponType;
    m_pedPieceType = pCopyFrom->m_pedPieceType;
    m_ucDirection = pCopyFrom->m_ucDirection;
    m_damageResponse = pCopyFrom->m_damageResponse;
    m_nAnimGroup = pCopyFrom->m_nAnimGroup;
    m_nAnimID = pCopyFrom->m_nAnimID;
    m_fAnimBlend = pCopyFrom->m_fAnimBlend;
    m_fAnimSpeed = pCopyFrom->m_fAnimSpeed;
    m_ucFlags = pCopyFrom->m_ucFlags;
#endif
}

void CEventDamage::ProcessDamage(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4B3A20, CEventDamage*, CPed*>(this, ped);
#else
    int boneFrameId = 0;
    CEventDamage::ComputeBodyPartToRemove(&boneFrameId);
    if (boneFrameId)
        ped->RemoveBodyPart(boneFrameId, m_ucDirection);
#endif
}

void CEventDamage::ComputeBodyPartToRemove(int* pBoneFrameId) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4ADC10, CEventDamage*, int*>(this, pBoneFrameId);
#else
    *pBoneFrameId = 0;
    switch (m_weaponType)
    {
    case WEAPON_UNARMED:
    case WEAPON_BRASSKNUCKLE:
    case WEAPON_GOLFCLUB:
    case WEAPON_NIGHTSTICK:
    case WEAPON_KNIFE:
    case WEAPON_BASEBALLBAT:
    case WEAPON_SHOVEL:
    case WEAPON_POOL_CUE:
    case WEAPON_KATANA:
    case WEAPON_CHAINSAW:
    case WEAPON_DILDO1:
    case WEAPON_DILDO2:
    case WEAPON_VIBE1:
    case WEAPON_VIBE2:
    case WEAPON_FLOWERS:
    case WEAPON_CANE:
    case WEAPON_PARACHUTE: {
        if (m_damageResponse.m_bForceDeath)
            *pBoneFrameId = 2;
        break;
    }
    case WEAPON_GRENADE:
    case WEAPON_RLAUNCHER:
    case WEAPON_RLAUNCHER_HS:
    case WEAPON_EXPLOSION: {
        if (m_damageResponse.m_bForceDeath) {
            int boneArray[5] = {3, 8, 2, 4, 7};
            *pBoneFrameId = boneArray[CGeneral::GetRandomNumberInRange(0, 5)];
        }
        break;
    }
    case WEAPON_TEARGAS:
    case WEAPON_MOLOTOV:
    case WEAPON_ROCKET:
    case WEAPON_ROCKET_HS:
    case WEAPON_FREEFALL_BOMB:
    case WEAPON_PISTOL:
    case WEAPON_PISTOL_SILENCED:
    case WEAPON_MICRO_UZI:
    case WEAPON_MP5:
    case WEAPON_TEC9:
    case WEAPON_FLAMETHROWER:
    case WEAPON_REMOTE_SATCHEL_CHARGE:
    case WEAPON_DETONATOR:
    case WEAPON_SPRAYCAN:
    case WEAPON_EXTINGUISHER:
    case WEAPON_CAMERA:
    case WEAPON_NIGHTVISION:
    case WEAPON_INFRARED:
    case WEAPON_LAST_WEAPON:
    case WEAPON_ARMOUR:
    case WEAPON_RAMMEDBYCAR:
    case WEAPON_RUNOVERBYCAR:
        return;
    case WEAPON_DESERT_EAGLE:
    case WEAPON_SHOTGUN:
    case WEAPON_SAWNOFF_SHOTGUN:
    case WEAPON_SPAS12_SHOTGUN:
    case WEAPON_AK47:
    case WEAPON_M4:
    case WEAPON_COUNTRYRIFLE:
    case WEAPON_SNIPERRIFLE:
    case WEAPON_MINIGUN:
        if (m_damageResponse.m_bForceDeath) {
            switch (m_pedPieceType)
            {
            case PED_PIECE_LEFT_ARM:
                *pBoneFrameId = 3;
                break;
            case PED_PIECE_RIGHT_ARM:
                *pBoneFrameId = 4;
                break;
            case PED_PIECE_LEFT_LEG:
                *pBoneFrameId = 7;
                break;
            case PED_PIECE_RIGHT_LEG:
                *pBoneFrameId = 8;
                break;
            case PED_PIECE_HEAD:
                *pBoneFrameId = 2;
                break;
            }
        }
        break;
    }
#endif
}

void CEventDamage::ComputeDeathAnim(CPed* ped, bool bMakeActiveTaskAbortable) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4B3A60, CEventDamage*, CPed*, bool>(this, ped, bMakeActiveTaskAbortable);
#else
    m_nAnimGroup = ANIM_GROUP_DEFAULT;
    m_nAnimID = ANIM_ID_KO_SHOT_FRONT_0;
    m_fAnimBlend = 4.0f;
    m_fAnimSpeed = 1.0f;
    float fForceFactor = 0.0f;
    CTask* pActiveTask = ped->m_pIntelligence->m_TaskMgr.GetActiveTask();
    if (ped->bInVehicle || bMakeActiveTaskAbortable && pActiveTask && !pActiveTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, this))
    {
        m_nAnimID = ANIM_ID_NO_ANIMATION_SET;
    }
    else if (m_weaponType == WEAPON_DROWNING || ped->physicalFlags.bSubmergedInWater && !ped->bIsStanding)
    {
        m_nAnimID = ANIM_ID_DROWN;
    }
    else
    {
        CPed* pPedSourceEntity = static_cast<CPed*>(m_pSourceEntity);
        CTaskSimpleFight* pTaskFight = nullptr;
        if (m_pSourceEntity && m_pSourceEntity->m_nType == ENTITY_TYPE_PED)
            pTaskFight = pPedSourceEntity->m_pIntelligence->GetTaskFighting();
        CVector bonePosition;
        ped->GetBonePosition(*(RwV3d*)&bonePosition, BONE_HEAD, false);
        CTask* pSimplestActiveTask = ped->m_pIntelligence->m_TaskMgr.GetSimplestActiveTask();
        if (ped->GetPosition().z - 0.2f > bonePosition.z
            && pSimplestActiveTask && (pSimplestActiveTask->GetId() == TASK_SIMPLE_FALL || pSimplestActiveTask->GetId() == TASK_SIMPLE_GET_UP))
        {
            m_bKnockOffPed = true;
            m_nAnimID = RpAnimBlendClumpGetFirstAssociation(ped->m_pRwClump, ANIMATION_UNUSED_3) ? ANIM_ID_FLOOR_HIT_F : ANIM_ID_FLOOR_HIT;
        }
        else
        {
            if (!m_ucDirection
                && pTaskFight && pTaskFight->IsComboSet() && pTaskFight->m_nComboSet >= 4 && pTaskFight->m_nCurrentMove <= FIGHT_ATTACK_HIT_3)
            {
                m_nAnimGroup = pTaskFight->GetComboAnimGroupID();
                m_nAnimID = pTaskFight->m_nCurrentMove + ANIM_ID_FIGHT_HIT_1;
                m_fAnimBlend = 16.0f;
                fForceFactor = 1.0f;
            }
            else
            {
                bool bKnockOutAnim = false;
                bool bKnockOutShotFront = false;
                bool bKnockOutShotFrontExtraForce = false;
                switch (m_weaponType)
                {
                case WEAPON_UNARMED:
                case WEAPON_BRASSKNUCKLE:
                case WEAPON_NIGHTSTICK:
                case WEAPON_CHAINSAW:
                case WEAPON_PARACHUTE:
                    fForceFactor = 0.5f;
                    bKnockOutShotFrontExtraForce = true;
                    break;
                case WEAPON_GOLFCLUB:
                case WEAPON_BASEBALLBAT:
                case WEAPON_SHOVEL:
                case WEAPON_POOL_CUE:
                case WEAPON_KATANA:
                case WEAPON_DILDO1:
                    fForceFactor = 1.5f;
                    bKnockOutShotFrontExtraForce = true;
                    break;
                case WEAPON_KNIFE:
                case WEAPON_DILDO2:
                case WEAPON_VIBE1:
                case WEAPON_VIBE2:
                case WEAPON_FLOWERS:
                case WEAPON_CANE:
                    bKnockOutShotFrontExtraForce = true;
                    break;
                case WEAPON_GRENADE:
                case WEAPON_RLAUNCHER:
                case WEAPON_RLAUNCHER_HS:
                case WEAPON_REMOTE_SATCHEL_CHARGE:
                case WEAPON_EXPLOSION:
                    bKnockOutAnim = true;
                    break;
                case WEAPON_TEARGAS:
                case WEAPON_MOLOTOV:
                case WEAPON_FLAMETHROWER:
                case WEAPON_SPRAYCAN:
                case WEAPON_EXTINGUISHER:
                    m_nAnimID = ANIM_ID_KO_SHOT_FRONT_0;
                    break;
                case WEAPON_ROCKET:
                case WEAPON_ROCKET_HS:
                case WEAPON_FREEFALL_BOMB:
                case WEAPON_DETONATOR:
                case WEAPON_CAMERA:
                case WEAPON_NIGHTVISION:
                case WEAPON_INFRARED:
                case WEAPON_LAST_WEAPON:
                case WEAPON_ARMOUR:
                    break;
                case WEAPON_PISTOL:
                case WEAPON_PISTOL_SILENCED:
                case WEAPON_MICRO_UZI:
                case WEAPON_MP5:
                case WEAPON_TEC9:
                case WEAPON_COUNTRYRIFLE:
                case WEAPON_SNIPERRIFLE:
                case WEAPON_UZI_DRIVEBY:
                    bKnockOutShotFront = true;
                    break;
                case WEAPON_DESERT_EAGLE:
                    fForceFactor = 1.0f;
                    bKnockOutShotFront = true;
                    break;
                case WEAPON_SHOTGUN:
                case WEAPON_SAWNOFF_SHOTGUN:
                case WEAPON_SPAS12_SHOTGUN:
                case WEAPON_MINIGUN:
                    fForceFactor = 2.0f;
                    bKnockOutShotFront = true;
                    break;
                case WEAPON_AK47:
                case WEAPON_M4:
                    fForceFactor = 0.5f;
                    bKnockOutShotFront = true;
                    break;
                case WEAPON_RAMMEDBYCAR:
                case WEAPON_RUNOVERBYCAR:
                    switch (m_ucDirection)
                    {
                    case 0:
                        if (m_pedPieceType == PED_PIECE_LEFT_ARM)
                            m_nAnimID = ANIM_ID_KD_LEFT;
                        else
                            m_nAnimID = m_pedPieceType ? ANIM_ID_KO_SKID_BACK : ANIM_ID_KD_RIGHT;
                        break;
                    case 1:
                        m_nAnimID = ANIM_ID_KO_SPIN_R;
                        break;
                    case 2:
                        if (m_pedPieceType == PED_PIECE_LEFT_ARM)
                            m_nAnimID = ANIM_ID_KD_LEFT;
                        else
                            m_nAnimID = (m_pedPieceType != PED_PIECE_RIGHT_ARM) + ANIM_ID_KD_RIGHT;
                        break;
                    case 3:
                        m_nAnimID = ANIM_ID_KO_SPIN_L;
                        break;
                    }
                    break;
                case WEAPON_DROWNING:
                    m_nAnimID = ANIM_ID_DROWN;
                    break;
                case WEAPON_FALL:
                    m_nAnimID = ANIM_ID_KO_SHOT_FRONT_2;
                    break;
                }

                if (bKnockOutShotFrontExtraForce) {
                    if (m_damageResponse.m_bForceDeath) {
                        m_nAnimID = ANIM_ID_KO_SHOT_FACE;
                        fForceFactor = 0.0f;
                    }
                    else {
                        bKnockOutAnim = true;
                    }
                    if (m_pSourceEntity) {
                        if (m_pSourceEntity->m_nType == ENTITY_TYPE_PED && pPedSourceEntity->m_pPlayerData) {
                            if (pPedSourceEntity->m_pPlayerData->m_bAdrenaline)
                                fForceFactor = fForceFactor * 5.0f;
                            else
                                fForceFactor = CStats::GetFatAndMuscleModifier(STAT_MOD_4) * fForceFactor;
                        }
                    }
                }
                if (bKnockOutShotFront) {
                    if (m_damageResponse.m_bForceDeath) {
                        m_nAnimID = ANIM_ID_KO_SHOT_FRONT_0;
                        fForceFactor = 0.0f;
                    }
                    else if (fForceFactor <= 0.0f) {
                        m_nAnimID = ANIM_ID_KO_SHOT_FRONT_0;
                    }
                    else {
                        bKnockOutAnim = true;
                    }
                }
                if (bKnockOutAnim) {
                    switch (m_ucDirection)
                    {
                    case 0:
                        m_nAnimID = ANIM_ID_KO_SKID_FRONT;
                        break;
                    case 1:
                        m_nAnimID = ANIM_ID_KO_SPIN_R;
                        break;
                    case 2:
                        m_nAnimID = ANIM_ID_KO_SKID_BACK;
                        break;
                    case 3:
                    default:
                        m_nAnimID = ANIM_ID_KO_SPIN_L;
                        break;
                    }
                }
            }
            if (CCheat::m_aCheatsActive[CHEAT_MEGA_PUNCH]) {
                if (!m_weaponType || m_weaponType == WEAPON_BRASSKNUCKLE || m_weaponType == WEAPON_PARACHUTE)
                    fForceFactor = fForceFactor * 20.0f;
            }
            if (fForceFactor > 0.0f && m_pSourceEntity) {
                fForceFactor *= -5.0f;
                ped->bWasStanding = false;
                ped->bIsStanding = false;
                CVector vecForce = m_pSourceEntity->GetPosition() - ped->GetPosition();
                vecForce.Normalise();
                vecForce *= fForceFactor;
                vecForce.z = 5.0f;
                ped->ApplyMoveForce(vecForce);
            }
        }
    }
#endif
}

void CEventDamage::ComputeDamageAnim(CPed* ped, bool bMakeActiveTaskAbortable) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4B3FC0, CEventDamage*, CPed*, bool>(this, ped, bMakeActiveTaskAbortable);
#else
    if (ped->bInVehicle && ped->m_pVehicle) {
        CWeaponInfo* pWeaponInfo = CWeaponInfo::GetWeaponInfo((eWeaponType)this->m_weaponType, 1);
        if (!pWeaponInfo->m_nWeaponFire
            && m_weaponType
            && m_weaponType != WEAPON_BRASSKNUCKLE
            && m_weaponType != WEAPON_PARACHUTE
            || pWeaponInfo->m_nDamage > 50)
        {
            m_bKnockOffPed = true;
        }
        m_nAnimID = ANIM_ID_NO_ANIMATION_SET;
        return;
    }

    bool bHeavyHit = false;
    if (m_weaponType == WEAPON_SPAS12_SHOTGUN || m_weaponType == WEAPON_SHOTGUN || m_weaponType == WEAPON_SAWNOFF_SHOTGUN
        || m_weaponType == WEAPON_DESERT_EAGLE || m_weaponType == WEAPON_COUNTRYRIFLE) {
        bHeavyHit = true;
    }
    if (ped->bUpperBodyDamageAnimsOnly)
        bHeavyHit = false;

    float fPedStrength = 1.0f;
    float fHealthThreshold = 15.0f;
    float fForceFactor = 0.0f;
    CTaskSimpleFight* pSourceEntityTaskFight = nullptr;
    CTaskSimpleUseGun* pSourceEntityTaskUseGun = nullptr;
    if (m_pSourceEntity && m_pSourceEntity->m_nType == ENTITY_TYPE_PED) {
        CPed* pPedSourceEntity = static_cast<CPed*>(m_pSourceEntity);
        pSourceEntityTaskFight = pPedSourceEntity->m_pIntelligence->GetTaskFighting();
        if (!pSourceEntityTaskFight)
            pSourceEntityTaskUseGun = pPedSourceEntity->m_pIntelligence->GetTaskUseGun();
        if (pPedSourceEntity->m_pPlayerData) {
            if (pPedSourceEntity->m_pPlayerData->m_bAdrenaline) {
                fPedStrength = 2.0f;
            }
            else {
                fPedStrength = (CStats::GetFatAndMuscleModifier(STAT_MOD_4) + 1.0f) * 0.5f;
                fHealthThreshold = 10.0f * 0.5f + 10.0f;
            }
        }
    }
    
    CTask* pSimplestActiveTask = ped->m_pIntelligence->m_TaskMgr.GetSimplestActiveTask();
    CVector bonePosition;
    ped->GetBonePosition(*(RwV3d*)&bonePosition, BONE_HEAD, false);
    if (bonePosition.z < ped->GetPosition().z && !ped->IsPlayer()
        && pSimplestActiveTask
        && (pSimplestActiveTask->GetId() == TASK_SIMPLE_FALL|| pSimplestActiveTask->GetId() == TASK_SIMPLE_GET_UP))
    {
        m_bKnockOffPed = true;
        m_nAnimID = RpAnimBlendClumpGetFirstAssociation(ped->m_pRwClump, ANIMATION_UNUSED_3) ? ANIM_ID_FLOOR_HIT_F : ANIM_ID_FLOOR_HIT;
    }
    else if(m_pedPieceType == PED_PIECE_TORSO) {
        bool bMultiplyForceWithPedStrength = false;
        if (pSourceEntityTaskUseGun && pSourceEntityTaskUseGun->m_nLastCommand == 5) {
            if (m_ucDirection)
                bMultiplyForceWithPedStrength = true;
            if (ped->IsPlayer())
                bMultiplyForceWithPedStrength = false;
        }
        else {
            if (bHeavyHit && !ped->IsPlayer())
                bMultiplyForceWithPedStrength = true;
        }
        if (ped->bUpperBodyDamageAnimsOnly || ped->bIsDucking || ped->m_pAttachedTo || !bMultiplyForceWithPedStrength || !m_pSourceEntity) {
            if (m_weaponType >= WEAPON_CHAINSAW || ped->m_fHealth >= fHealthThreshold) {
                if (m_weaponType != WEAPON_FALL ||  !m_pSourceEntity  || m_pSourceEntity->m_nType != ENTITY_TYPE_OBJECT) {
                    if (pSourceEntityTaskFight && pSourceEntityTaskFight->m_nCurrentMove == FIGHT_ATTACK_FIGHTIDLE && !ped->IsPlayer() && ped->m_nMoveState > PEDMOVE_WALK)
                        m_bKnockOffPed = true;
                }
                else {
                    m_bKnockOffPed = true;
                }
            }
            else {
                m_bKnockOffPed = true;
                fForceFactor = fPedStrength * 5.0f;
            }
        }
        else {
            m_bKnockOffPed = true;
            fForceFactor = 5.0f;
        }
    }

    bool bPlayHitAnim = true;
    bool bNoComboHit = false;
    if (m_bKnockOffPed && (m_ucDirection || !pSourceEntityTaskFight || !pSourceEntityTaskFight->IsComboSet() && !pSourceEntityTaskFight->IsHitComboSet())) {
        bNoComboHit = true;
        bPlayHitAnim = false;
    }
    else {
        m_bKnockOffPed = false;
        if (!m_ucDirection) {
            if (pSourceEntityTaskFight && pSourceEntityTaskFight->m_nComboSet >= 4 && pSourceEntityTaskFight->m_nCurrentMove <= FIGHT_ATTACK_HIT_3) {
                m_nAnimGroup = pSourceEntityTaskFight->GetComboAnimGroupID();
                m_nAnimID = pSourceEntityTaskFight->m_nCurrentMove + ANIM_ID_FIGHT_HIT_1;
                m_fAnimBlend = 16.0f;
                if (pSourceEntityTaskFight->IsComboSet())
                    m_bKnockOffPed = true; 
                bPlayHitAnim = false;
            }
            else if (pSourceEntityTaskUseGun && pSourceEntityTaskUseGun->m_nLastCommand == 5) {
                m_nAnimGroup = CTaskSimpleFight::m_aComboData[0].m_dwAnimGroup;
                m_nAnimID = ANIM_ID_FIGHT_HIT_2;
                m_fAnimBlend = 16.0f;
                bPlayHitAnim = false;
            }
        }
    }
    if (bPlayHitAnim) {
        if (m_weaponType < WEAPON_PISTOL || m_weaponType > WEAPON_COUNTRYRIFLE || bHeavyHit && !ped->IsPlayer()
            || (!ped->IsPlayer() || bHeavyHit)
            && ped->m_nMoveState <= PEDMOVE_STILL && !ped->bIsDucking && !ped->bUpperBodyDamageAnimsOnly)
        {
            bool bPlayBodyPartHitAnim = true;
            if (ped->IsPlayer() && m_weaponType >= WEAPON_PISTOL) {
                CPlayerData* pPlayerData = ped->m_pPlayerData;
                if (CTimer::m_snTimeInMilliseconds <= pPlayerData->m_nHitAnimDelayTimer || ped->m_nPedState == PEDSTATE_DRIVING) {
                    m_nAnimID = ANIM_ID_NO_ANIMATION_SET;
                    bPlayBodyPartHitAnim = false;
                }
                else {
                    pPlayerData->m_nHitAnimDelayTimer = static_cast<unsigned int>(CTimer::m_snTimeInMilliseconds + 2500.0f);
                }
            }
            if (bPlayBodyPartHitAnim) {
                if (m_weaponType < WEAPON_PISTOL || m_weaponType > WEAPON_LAST_WEAPON) {
                    m_nAnimID = m_ucDirection + ANIM_ID_HIT_FRONT;
                    if (m_ucDirection || m_damageResponse.m_fDamageArmor + m_damageResponse.m_fDamageHealth <= 20.0f) {
                        if (m_ucDirection == 2 && m_weaponType <= WEAPON_CANE)
                            m_nAnimID = ANIM_ID_HIT_BEHIND;
                    }
                    else {
                        m_nAnimID = ANIM_ID_HIT_WALK;
                    }
                }
                else {
                    int currentEventAnimId = -1;
                    CEvent* pCurrentEvent = ped->m_pIntelligence->m_eventHandler.m_history.GetCurrentEvent();
                    if (pCurrentEvent && pCurrentEvent->GetEventType() == EVENT_DAMAGE)
                        currentEventAnimId = static_cast<CEventDamage*>(pCurrentEvent)->m_nAnimID;
                    switch (m_pedPieceType)
                    {
                    case PED_PIECE_LEFT_ARM:
                        if (m_ucDirection == 2)
                            m_nAnimID = ANIM_ID_DAM_ARML_FRMBK;
                        else if (m_ucDirection == 1)
                            m_nAnimID = ANIM_ID_DAM_ARML_FRMLT;
                        else
                            m_nAnimID = ANIM_ID_DAM_ARML_FRMFT;
                        if (m_nAnimID == currentEventAnimId) {
                            do {
                                m_nAnimID = ANIM_ID_DAM_ARML_FRMBK - static_cast<unsigned int>((rand() * 0.000030517578f * -3.0f));
                            } while (m_nAnimID == currentEventAnimId);
                        }
                        break;
                    case PED_PIECE_RIGHT_ARM:
                        if (m_ucDirection == 2)
                            m_nAnimID = ANIM_ID_DAM_ARMR_FRMBK;
                        else if (m_ucDirection == 3)
                            m_nAnimID = ANIM_ID_DAM_ARMR_FRMRT;
                        else
                            m_nAnimID = ANIM_ID_DAM_ARMR_FRMFT;
                        if (m_nAnimID == currentEventAnimId) {
                            do {
                                m_nAnimID = CGeneral::GetRandomNumberInRange(0, 3) + ANIM_ID_DAM_ARMR_FRMBK;
                            } while (m_nAnimID == currentEventAnimId);
                        }
                        break;
                    case PED_PIECE_LEFT_LEG:
                        if (m_ucDirection == 2)
                            m_nAnimID = ANIM_ID_DAM_LEGL_FRMBK;
                        else if (m_ucDirection == 1)
                            m_nAnimID = ANIM_ID_DAM_LEGL_FRMLT;
                        else
                            m_nAnimID = ANIM_ID_DAM_LEGL_FRMFT;
                        if (m_nAnimID == currentEventAnimId) {
                            do {
                                m_nAnimID = CGeneral::GetRandomNumberInRange(0, 3) + ANIM_ID_DAM_LEGL_FRMBK;
                            } while (m_nAnimID == currentEventAnimId);
                        }
                        break;
                    case PED_PIECE_RIGHT_LEG:
                        if (m_ucDirection == 2)
                            m_nAnimID = ANIM_ID_DAM_LEGR_FRMBK;
                        else if (m_ucDirection == 3)
                            m_nAnimID = ANIM_ID_DAM_LEGR_FRMRT;
                        else
                            m_nAnimID = ANIM_ID_DAM_LEGR_FRMFT;
                        if (m_nAnimID == currentEventAnimId) {
                            do {
                                m_nAnimID = CGeneral::GetRandomNumberInRange(0, 3) + ANIM_ID_DAM_LEGR_FRMBK;
                            } while (m_nAnimID == currentEventAnimId);
                        }
                        break;
                    case PED_PIECE_TORSO:
                    case PED_PIECE_ASS:
                        if (m_ucDirection) {
                            switch (m_ucDirection)
                            {
                            case 1:
                                m_nAnimID = ANIM_ID_DAM_STOMACH_FRMLT;
                                break;
                            case 2:
                                m_nAnimID = ANIM_ID_DAM_STOMACH_FRMBK;
                                break;
                            case 3:
                                m_nAnimID = ANIM_ID_DAM_STOMACH_FRMRT;
                                break;
                            }
                        }
                        else {
                            m_nAnimID = ANIM_ID_DAM_STOMACH_FRMFT;
                        }
                        if (m_nAnimID == currentEventAnimId) {
                            do {
                                m_nAnimID = CGeneral::GetRandomNumberInRange(0, 4) + ANIM_ID_DAM_STOMACH_FRMBK;
                            } while (m_nAnimID == currentEventAnimId);
                        }
                        break;
                    default:
                        m_nAnimID = m_ucDirection + ANIM_ID_HIT_FRONT;
                        break;
                    }
                }
            }
        }
        else
        {
            m_nAnimGroup = ANIM_GROUP_DEFAULT;
            m_fAnimBlend = 8.0f;
            m_nAnimID = m_ucDirection + ANIM_ID_SHOT_PARTIAL;
            if (ped->IsPlayer()) {
                CPlayerData* pPedPlayerData = ped->m_pPlayerData;
                if (CTimer::m_snTimeInMilliseconds > pPedPlayerData->m_nHitAnimDelayTimer && ped->m_nPedState != PEDSTATE_DRIVING) {
                    if (m_weaponType == WEAPON_M4)
                        pPedPlayerData->m_nHitAnimDelayTimer = static_cast<unsigned int>(CTimer::m_snTimeInMilliseconds + 2500.0f);
                    else
                        pPedPlayerData->m_nHitAnimDelayTimer = static_cast<unsigned int>(CTimer::m_snTimeInMilliseconds + 1500.0f);
                }
                else {
                    m_nAnimID = ANIM_ID_NO_ANIMATION_SET;
                }
            }
        }
    }
    if (bMakeActiveTaskAbortable) {
        CTask* pActiveTask = ped->m_pIntelligence->m_TaskMgr.GetActiveTask();
        if (pActiveTask && !pActiveTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, this)) {
            m_nAnimGroup = ANIM_GROUP_DEFAULT;
            m_nAnimID = 192;
            m_bKnockOffPed = false;
        }
    }

    if (m_bKnockOffPed && bNoComboHit) {
        m_nAnimID = m_ucDirection + ANIM_ID_KO_SKID_FRONT;
        if (fForceFactor > 0.0f) {
            ped->bWasStanding = false;
            ped->bIsStanding = false;
            CVector force = m_pSourceEntity->GetPosition() - ped->GetPosition();
            force.Normalise();
            force *= -fForceFactor;
            force.z = 5.0f;
            ped->ApplyMoveForce(force);
        }
    }
#endif
}