/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

unsigned short& CObject::nNoTempObjects = *(unsigned short*)(0xBB4A70);
float& CObject::fDistToNearestTree = *(float*)0x8D0A20;
bool& CObject::bAircraftCarrierSamSiteDisabled = *(bool*)0x8D0A24;
bool& CObject::bArea51SamSiteDisabled = *(bool*)0xBB4A72;

void CObject::InjectHooks()
{
// VIRTUAL
    ReversibleHooks::Install("CObject", "SetIsStatic", 0x5A0760, &CObject::SetIsStatic_Reversed);
    ReversibleHooks::Install("CObject", "CreateRwObject", 0x59F110, &CObject::CreateRwObject_Reversed);
    ReversibleHooks::Install("CObject", "ProcessControl", 0x5A2130, &CObject::ProcessControl_Reversed);
    ReversibleHooks::Install("CObject", "Teleport", 0x5A17B0, &CObject::Teleport_Reversed);
    ReversibleHooks::Install("CObject", "PreRender", 0x59FD50, &CObject::PreRender_Reversed);
    ReversibleHooks::Install("CObject", "Render", 0x59F180, &CObject::Render_Reversed);
    ReversibleHooks::Install("CObject", "SetupLighting", 0x554FA0, &CObject::SetupLighting_Reversed);
    ReversibleHooks::Install("CObject", "RemoveLighting", 0x553E10, &CObject::RemoveLighting_Reversed);
    ReversibleHooks::Install("CObject", "SpecialEntityPreCollisionStuff", 0x59FEE0, &CObject::SpecialEntityPreCollisionStuff_Reversed);
    ReversibleHooks::Install("CObject", "SpecialEntityCalcCollisionSteps", 0x5A02E0, &CObject::SpecialEntityCalcCollisionSteps_Reversed);

// CLASS
    ReversibleHooks::Install("CObject", "Init", 0x59F840, &CObject::Init);
    ReversibleHooks::Install("CObject", "ProcessGarageDoorBehaviour", 0x44A4D0, &CObject::ProcessGarageDoorBehaviour);
    ReversibleHooks::Install("CObject", "CanBeDeleted", 0x59F120, &CObject::CanBeDeleted);
    ReversibleHooks::Install("CObject", "SetRelatedDummy", 0x59F160, &CObject::SetRelatedDummy);
    ReversibleHooks::Install("CObject", "TryToExplode", 0x59F2D0, &CObject::TryToExplode);
    ReversibleHooks::Install("CObject", "SetObjectTargettable", 0x59F300, &CObject::SetObjectTargettable);
    ReversibleHooks::Install("CObject", "CanBeTargetted", 0x59F320, &CObject::CanBeTargetted);
    ReversibleHooks::Install("CObject", "RefModelInfo", 0x59F330, &CObject::RefModelInfo);
    ReversibleHooks::Install("CObject", "SetRemapTexture", 0x59F350, &CObject::SetRemapTexture);
    ReversibleHooks::Install("CObject", "GetRopeHeight", 0x59F380, &CObject::GetRopeHeight);
    ReversibleHooks::Install("CObject", "SetRopeHeight", 0x59F3A0, &CObject::SetRopeHeight);
    ReversibleHooks::Install("CObject", "GetObjectCarriedWithRope", 0x59F3C0, &CObject::GetObjectCarriedWithRope);
    ReversibleHooks::Install("CObject", "ReleaseObjectCarriedWithRope", 0x59F3E0, &CObject::ReleaseObjectCarriedWithRope);
    ReversibleHooks::Install("CObject", "AddToControlCodeList", 0x59F400, &CObject::AddToControlCodeList);
    ReversibleHooks::Install("CObject", "RemoveFromControlCodeList", 0x59F450, &CObject::RemoveFromControlCodeList);
    ReversibleHooks::Install("CObject", "ResetDoorAngle", 0x59F4B0, &CObject::ResetDoorAngle);
    ReversibleHooks::Install("CObject", "LockDoor", 0x59F5C0, &CObject::LockDoor);
    ReversibleHooks::Install("CObject", "DoBurnEffect", 0x59FB50, &CObject::DoBurnEffect);
    ReversibleHooks::Install("CObject", "GetLightingFromCollisionBelow", 0x59FD00, &CObject::GetLightingFromCollisionBelow);
    ReversibleHooks::Install("CObject", "ProcessSamSiteBehaviour", 0x5A07D0, &CObject::ProcessSamSiteBehaviour);
    ReversibleHooks::Install("CObject", "ProcessTrainCrossingBehaviour", 0x5A0B50, &CObject::ProcessTrainCrossingBehaviour);
    ReversibleHooks::Install("CObject", "ObjectDamage", 0x5A0D90, &CObject::ObjectDamage);
    ReversibleHooks::Install("CObject", "Explode", 0x5A1340, &CObject::Explode);
    ReversibleHooks::Install("CObject", "ObjectFireDamage", 0x5A1580, &CObject::ObjectFireDamage);
    ReversibleHooks::Install("CObject", "GrabObjectToCarryWithRope", 0x5A1AB0, &CObject::GrabObjectToCarryWithRope);
    ReversibleHooks::Install("CObject", "CanBeUsedToTakeCoverBehind", 0x5A1B60, &CObject::CanBeUsedToTakeCoverBehind);
    ReversibleHooks::Install("CObject", "ProcessControlLogic", 0x5A29A0, &CObject::ProcessControlLogic);

// STATIC
    ReversibleHooks::Install("CObject", "Create_intbool", 0x5A1F60, static_cast<CObject*(*)(int, bool)>(&CObject::Create));
    ReversibleHooks::Install("CObject", "Create_dummy", 0x5A2070, static_cast<CObject*(*)(CDummyObject*)>(&CObject::Create));
    ReversibleHooks::Install("CObject", "SetMatrixForTrainCrossing", 0x59F200, &CObject::SetMatrixForTrainCrossing);
    ReversibleHooks::Install("CObject", "TryToFreeUpTempObjects", 0x5A1840, &CObject::TryToFreeUpTempObjects);
    ReversibleHooks::Install("CObject", "DeleteAllTempObjects", 0x5A18B0, &CObject::DeleteAllTempObjects);
    ReversibleHooks::Install("CObject", "DeleteAllMissionObjects", 0x5A1910, &CObject::DeleteAllMissionObjects);
    ReversibleHooks::Install("CObject", "DeleteAllTempObjectsInArea", 0x5A1980, &CObject::DeleteAllTempObjectsInArea);
    ReversibleHooks::Install("CObject", "IsObjectPointerValid_NotInWorld", 0x5A2B90, &IsObjectPointerValid_NotInWorld);
    ReversibleHooks::Install("CObject", "IsObjectPointerValid", 0x5A2C20, &IsObjectPointerValid);
}

CObject::CObject() : CPhysical()
{
    m_pDummyObject = nullptr;
    CObject::Init();
    m_nObjectType = eObjectType::OBJECT_UNKNOWN;
}

CObject::CObject(int modelId, bool bCreate) : CPhysical()
{
    m_pDummyObject = nullptr;
    if (bCreate)
        CEntity::SetModelIndex(modelId);
    else
        CEntity::SetModelIndexNoCreate(modelId);

    CObject::Init();
}

CObject::CObject(CDummyObject* pDummyObj) : CPhysical()
{
    CEntity::SetModelIndexNoCreate(pDummyObj->m_nModelIndex);
    if (pDummyObj->m_pRwObject)
        CEntity::AttachToRwObject(pDummyObj->m_pRwObject, true);
    else
        CPlaceable::SetMatrix(*pDummyObj->GetMatrix());

    pDummyObj->DetachFromRwObject();
    CObject::Init();

    m_nIplIndex = pDummyObj->m_nIplIndex;
    m_nAreaCode = pDummyObj->m_nAreaCode;
    m_bRenderDamaged = pDummyObj->m_bRenderDamaged;

    
    if (m_pRwObject)
    {
        auto* pAtomic = m_pRwAtomic;
        if (RwObjectGetType(m_pRwObject) != rpATOMIC)
            pAtomic = GetFirstAtomic(m_pRwClump);

        if (!CCustomBuildingRenderer::IsCBPCPipelineAttached(pAtomic))
            m_bLightObject = true;
    }
}

CObject::~CObject()
{
    if (objectFlags.b0x200000 || objectFlags.b0x100000)
    {
        const auto iIndex = CTheScripts::ScriptsForBrains.m_aScriptForBrains[m_wScriptTriggerIndex].m_nIMGindex + RESOURCE_ID_SCM;
        CStreaming::SetMissionDoesntRequireModel(iIndex);
        objectFlags.b0x100000 = false;
        objectFlags.b0x200000 = false;
        CTheScripts::RemoveFromWaitingForScriptBrainArray(this, m_wScriptTriggerIndex);
        m_wScriptTriggerIndex = -1;
    }

    if (objectFlags.bHasNoModel)
    {
        auto* const colModel = CModelInfo::GetModelInfo((m_nModelIndex))->GetColModel();
        CColStore::RemoveRef(colModel->m_boundSphere.m_nMaterial); //This seems weird, maybe BUG or Union field?
    }

    CRadar::ClearBlipForEntity(eBlipType::BLIP_OBJECT, CPools::ms_pObjectPool->GetRef(this));

    if (m_nRefModelIndex != -1)
        CModelInfo::GetModelInfo(m_nRefModelIndex)->RemoveRef();

    if (m_wRemapTxd != -1)
        CTxdStore::RemoveRef(m_wRemapTxd);

    if (IsTemporary() && CObject::nNoTempObjects)
        --CObject::nNoTempObjects;

    CObject::RemoveFromControlCodeList();
    if (m_nModelIndex == ModelIndices::MI_TRAINCROSSING1)
    {
        const auto& pDummyPos = m_pDummyObject->GetPosition();
        ThePaths.SetLinksBridgeLights(pDummyPos.x - 12.0F, pDummyPos.x + 12.0F, pDummyPos.y - 12.0F, pDummyPos.y + 12.0F, false);
    }

    if (m_pFire)
        m_pFire->Extinguish();
}

void* CObject::operator new(unsigned int size)
{
    return CPools::ms_pObjectPool->New();
}

void* CObject::operator new(unsigned size, int iPoolRef)
{
    return CPools::ms_pObjectPool->New(iPoolRef);
}

void CObject::operator delete(void* pObj)
{
    CPools::ms_pObjectPool->Delete(static_cast<CObject*>(pObj));
}

void CObject::SetIsStatic(bool isStatic)
{
    return SetIsStatic_Reversed(isStatic);
}
void CObject::SetIsStatic_Reversed(bool isStatic)
{
    m_bIsStatic = isStatic;
    physicalFlags.b31 = false;
    if (!isStatic && (physicalFlags.bDisableMoveForce && m_fDoorStartAngle < -1000.0F))
        m_fDoorStartAngle = GetHeading();
}

void CObject::CreateRwObject()
{
    CObject::CreateRwObject_Reversed();
}
void CObject::CreateRwObject_Reversed()
{
    CEntity::CreateRwObject();
}

void CObject::ProcessControl()
{
    CObject::ProcessControl_Reversed();
}
void CObject::ProcessControl_Reversed()
{
    auto* pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    auto bIsAnimated = false;
    if (pModelInfo->GetRwModelType() == rpCLUMP && pModelInfo->bHasAnimBlend && m_pRwObject)
        bIsAnimated = true;

    if (m_fDamageIntensity > 0.0F
        && objectFlags.bDamaged
        && !m_pAttachedTo
        && !IsCraneMovingPart()
        && !physicalFlags.bInfiniteMass
        && !physicalFlags.bDisableMoveForce
        && m_pDamageEntity)
    {
        const auto bCanCarryItems = m_pDamageEntity->m_nModelIndex == eModelID::MODEL_DUMPER || m_pDamageEntity->m_nModelIndex == eModelID::MODEL_FORKLIFT;
        if (bCanCarryItems && static_cast<CAutomobile*>(m_pDamageEntity)->m_wMiscComponentAngle
            && !CRopes::IsCarriedByRope(this))
        {
            if (m_nColDamageEffect != eObjectColDamageEffect::COL_DAMAGE_EFFECT_NONE && m_fDamageIntensity > 5.0F)
                CObject::ObjectDamage(m_fDamageIntensity, &m_vecLastCollisionPosn, &m_vecLastCollisionImpactVelocity, m_pDamageEntity, eWeaponType::WEAPON_RAMMEDBYCAR);

            if (m_vecLastCollisionImpactVelocity.z > 0.3F)
            {
                m_nFakePhysics = 0;
                const auto vecColDir = GetPosition() - m_pDamageEntity->GetPosition();
                const auto vecEntSpeed = static_cast<CPhysical*>(m_pDamageEntity)->GetSpeed(vecColDir);
                auto vecSpeedDiff = vecEntSpeed - m_vecMoveSpeed;
                if (vecSpeedDiff.SquaredMagnitude() < 0.0001F && m_vecTurnSpeed.SquaredMagnitude() < 0.0001F)
                {
                    CPhysical::AttachEntityToEntity(static_cast<CPhysical*>(m_pDamageEntity), nullptr, nullptr);
                    m_fElasticity = 0.2F;
                }
            }
        }
    }

    objectFlags.bDamaged = false;
    if (!m_bIsStuck && !IsStatic())
    {
        if (!physicalFlags.bDisableZ && !physicalFlags.bInfiniteMass && !physicalFlags.bDisableMoveForce)
        {
            m_vecForce += m_vecMoveSpeed;
            m_vecForce /= 2.0F;
            m_vecTorque += m_vecTurnSpeed;
            m_vecTorque /= 2.0F;

            const auto fTimeStep = CTimer::ms_fTimeStep * 0.003F;
            if (pow(fTimeStep, 2.0F) <= m_vecForce.SquaredMagnitude()
                || pow(fTimeStep, 2.0F) <= m_vecTorque.SquaredMagnitude())
            {
                m_nFakePhysics = 0;
            }
            else
            {
                m_nFakePhysics++;
                if (m_nFakePhysics > 10 && !physicalFlags.bAttachedToEntity)
                {
                    m_nFakePhysics = 10;
                    if (!bIsAnimated)
                        this->SetIsStatic(true);

                    m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
                    m_vecTurnSpeed.Set(0.0F, 0.0F, 0.0F);
                    m_vecFrictionMoveSpeed.Set(0.0F, 0.0F, 0.0F);
                    m_vecFrictionTurnSpeed.Set(0.0F, 0.0F, 0.0F);
                    return;
                }
            }
        }
    }

    if (!IsStatic())
        CPhysical::ProcessControl();

    if (bIsAnimated)
        this->SetIsStatic(false);

    CVector vecBuoyancyTurnPoint, vecBuoyancyForce;
    if (mod_Buoyancy.ProcessBuoyancy(this, m_fBuoyancyConstant, &vecBuoyancyTurnPoint, &vecBuoyancyForce))
    {
        physicalFlags.bTouchingWater = true;
        physicalFlags.bSubmergedInWater = true;
        this->SetIsStatic(false);

        CPhysical::ApplyMoveForce(vecBuoyancyForce);
        CPhysical::ApplyTurnForce(vecBuoyancyForce, vecBuoyancyTurnPoint);
        const auto fTimeStep = pow(0.97F, CTimer::ms_fTimeStep);
        m_vecMoveSpeed *= fTimeStep;
        m_vecTurnSpeed *= fTimeStep;
    }
    else if (m_nModelIndex != ModelIndices::MI_BUOY)
        physicalFlags.bTouchingWater = false; // Not clearing bSubmergedInWater, BUG?

    if (m_pObjectInfo->m_bCausesExplosion
        && objectFlags.bIsExploded
        && m_bIsVisible
        && (rand() & 0x1F) == 10)
    {
        m_bUsesCollision = false;
        m_bIsVisible = false;
        physicalFlags.bExplosionProof = true;
        physicalFlags.bApplyGravity = false;
        m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
        this->DeleteRwObject();
    }

    if (m_nModelIndex == ModelIndices::MI_RCBOMB)
    {
        CPhysical::ApplyTurnForce(m_vecMoveSpeed * -0.05F, -GetForward());
        m_vecMoveSpeed *= pow(CTimer::ms_fTimeStep, 1.0F - m_vecMoveSpeed.SquaredMagnitude() * 0.2F);
    }

    if (m_bIsBIGBuilding)
        m_bIsInSafePosition = true;

    if (physicalFlags.bDisableMoveForce && m_fDoorStartAngle > -1000.0F)
    {
        auto fHeading = GetHeading();
        if (m_fDoorStartAngle + PI < fHeading)
            fHeading -= TWO_PI;
        else if (m_fDoorStartAngle - PI > fHeading)
            fHeading += TWO_PI;

        auto fDiff = m_fDoorStartAngle - fHeading;
        if (fabs(fDiff) > PI / 6.0F)
            objectFlags.bIsDoorOpen = true;

        static float fMaxDoorDiff = 0.3F;
        static float fDoorCutoffSpeed = 0.02F;
        static float fDoorSpeedMult = 0.002F;
        fDiff = clamp(fDiff, -fMaxDoorDiff, fMaxDoorDiff);
        if (fDiff > 0.0F && m_vecTurnSpeed.z < fDoorCutoffSpeed
            || fDiff < 0.0F && m_vecTurnSpeed.z > fDoorCutoffSpeed)
        {
            m_vecTurnSpeed.z += CTimer::ms_fTimeStep * fDoorSpeedMult * fDiff;
        }

        if (fDiff != 0.0F && objectFlags.bIsDoorMoving)
            AudioEngine.ReportDoorMovement(this);

        if (!m_bIsBIGBuilding
            && !IsStatic()
            && fabs(fDiff) < 0.01F
            && (objectFlags.bIsDoorMoving || fabs(m_vecTurnSpeed.z) < 0.01F))
        {
            this->SetIsStatic(true);
            m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
            m_vecTurnSpeed.Set(0.0F, 0.0F, 0.0F);
            m_vecFrictionMoveSpeed.Set(0.0F, 0.0F, 0.0F);
            m_vecFrictionTurnSpeed.Set(0.0F, 0.0F, 0.0F);

            if (objectFlags.bIsDoorMoving && objectFlags.bIsDoorOpen)
                CObject::LockDoor();
        }
    }
}

void CObject::Teleport(CVector destination, bool resetRotation)
{
    CObject::Teleport_Reversed(destination, resetRotation);
}
void CObject::Teleport_Reversed(CVector destination, bool resetRotation)
{
    CWorld::Remove(this);
    SetPosn(destination);
    CEntity::UpdateRW();
    CEntity::UpdateRwFrame();
    CWorld::Add(this);
}

void CObject::SpecialEntityPreCollisionStuff(CEntity* colEntity, bool bIgnoreStuckCheck, bool* bCollisionDisabled,
    bool* bCollidedEntityCollisionIgnored, bool* bCollidedEntityUnableToMove, bool* bThisOrCollidedEntityStuck)
{
    CObject::SpecialEntityPreCollisionStuff_Reversed(colEntity, bIgnoreStuckCheck, bCollisionDisabled,
        bCollidedEntityCollisionIgnored, bCollidedEntityUnableToMove, bThisOrCollidedEntityStuck);
}
void CObject::SpecialEntityPreCollisionStuff_Reversed(CEntity* colEntity, bool bIgnoreStuckCheck, bool* bCollisionDisabled,
    bool* bCollidedEntityCollisionIgnored, bool* bCollidedEntityUnableToMove, bool* bThisOrCollidedEntityStuck)
{
    auto* const pColPhysical = static_cast<CPhysical*>(colEntity);
    if(m_pEntityIgnoredCollision == colEntity || pColPhysical->m_pEntityIgnoredCollision == this)
    {
        *bCollidedEntityCollisionIgnored = true;
        return;
    }

    if (m_pAttachedTo == colEntity)
        *bCollisionDisabled = true;
    else if(pColPhysical->m_pAttachedTo == this || (m_pAttachedTo && m_pAttachedTo == pColPhysical->m_pAttachedTo))
        *bCollisionDisabled = true;
    else if(physicalFlags.bDisableZ && !physicalFlags.bApplyGravity && pColPhysical->physicalFlags.bDisableZ)
        *bCollisionDisabled = true;
    else
    {
        if (!physicalFlags.bDisableZ) {
            if (physicalFlags.bInfiniteMass || physicalFlags.bDisableMoveForce)
            {
                if (bIgnoreStuckCheck || m_bIsStuck)
                    *bCollisionDisabled = true;
                else if (!pColPhysical->m_bIsStuck) { /* Do nothing pretty much, and skip further calc */ }
                else if (!pColPhysical->m_bHasHitWall)
                    *bThisOrCollidedEntityStuck = true;
                else
                    *bCollidedEntityUnableToMove = true;
            }
            else if(objectFlags.bIsLampPost && (GetUp().z < 0.66F || m_bIsStuck))
            {
                if (colEntity->IsVehicle() || colEntity->IsPed()) {
                    *bCollidedEntityCollisionIgnored = true;
                    if (colEntity->IsVehicle())
                        return;

                    m_pEntityIgnoredCollision = colEntity;
                }
            }
            else if( colEntity->IsVehicle())
            {
                if (IsModelTempCollision())
                    *bCollisionDisabled = true;
                else if (m_nObjectType == eObjectType::OBJECT_TEMPORARY || (objectFlags.bIsExploded || !CEntity::IsStatic()))
                {
                    if (colEntity->m_nModelIndex == eModelID::MODEL_DUMPER
                        || colEntity->m_nModelIndex == eModelID::MODEL_DOZER
                        || colEntity->m_nModelIndex == eModelID::MODEL_FORKLIFT)
                    {

                        if (m_bIsStuck || colEntity->m_bIsStuck)
                            *bThisOrCollidedEntityStuck = true;
                    }
                    else if (m_nColDamageEffect < eObjectColDamageEffect::COL_DAMAGE_EFFECT_SMASH_COMPLETELY)
                    {
                        auto tempMat = CMatrix();
                        auto* pColModel = CEntity::GetColModel();
                        auto vecSize = pColModel->GetBoundingBox().m_vecMax - pColModel->GetBoundingBox().m_vecMin;
                        auto vecTransformed = *m_matrix * vecSize;

                        auto& vecCollidedPos = colEntity->GetPosition();
                        if (vecTransformed.z < vecCollidedPos.z)
                        {
                            *bCollidedEntityCollisionIgnored = true;
                            m_pEntityIgnoredCollision = colEntity;
                        }
                        else
                        {
                            Invert(colEntity->GetMatrix(), &tempMat);
                            if ((tempMat * vecTransformed).z < 0.0F)
                            {
                                *bCollidedEntityCollisionIgnored = true;
                                m_pEntityIgnoredCollision = colEntity;
                            }
                        }
                    }
                }
            }
            else if(m_nModelIndex != eModelID::MODEL_GRENADE
                || !colEntity->IsPed()
                || GetPosition().z > colEntity->GetPosition().z)
            {
                if (colEntity->IsObject() && static_cast<CObject*>(colEntity)->m_pObjectInfo->m_fUprootLimit > 0.0F && !pColPhysical->m_pAttachedTo)
                {
                    if ((!pColPhysical->physicalFlags.bDisableCollisionForce || pColPhysical->physicalFlags.bCollidable)
                        && pColPhysical->m_fMass * 10.0F > m_fMass)
                    {
                        *bCollidedEntityUnableToMove = true;
                    }
                }
            }
        }
        else
        {
            if (bIgnoreStuckCheck)
                *bCollisionDisabled = true;
            else if (m_bIsStuck || colEntity->m_bIsStuck)
                *bThisOrCollidedEntityStuck = true;
        }
    }


    if (!*bCollidedEntityCollisionIgnored && (bIgnoreStuckCheck || m_bIsStuck))
        *bThisOrCollidedEntityStuck = true;

}

unsigned char CObject::SpecialEntityCalcCollisionSteps(bool* bProcessCollisionBeforeSettingTimeStep, bool* unk2)
{
    return CObject::SpecialEntityCalcCollisionSteps_Reversed(bProcessCollisionBeforeSettingTimeStep, unk2);
}
unsigned char CObject::SpecialEntityCalcCollisionSteps_Reversed(bool* bProcessCollisionBeforeSettingTimeStep, bool* unk2)
{
    if (physicalFlags.bDisableZ
        || m_pObjectInfo->m_nSpecialColResponseCase == eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_GRENADE)
    {
        auto* pColModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();
        const auto fMove = m_vecMoveSpeed.SquaredMagnitude() * pow(CTimer::ms_fTimeStep, 2.0F);
        if (fMove >= pow(pColModel->GetBoundRadius(), 2.0F))
            return static_cast<uint8_t>(ceil(sqrt(fMove) / pColModel->GetBoundRadius()));

        return 1;
    }

    if (!physicalFlags.bDisableMoveForce)
    {
        if (physicalFlags.bInfiniteMass)
        {
            auto pColModel = CEntity::GetColModel();
            auto vecMin = Multiply3x3(m_matrix, &pColModel->GetBoundingBox().m_vecMin);
            auto vecSpeed = CPhysical::GetSpeed(vecMin);
            const auto fMove = vecSpeed.SquaredMagnitude() * pow(CTimer::ms_fTimeStep, 2.0F);
            if (fMove >= 0.0225F) // pow(0.15F, 2.0F)
                return static_cast<uint8_t>(ceil(sqrt(fMove) / 0.15F));

            return 1;
        }

        if (IsTemporary() && !objectFlags.bIsLiftable)
            return 1;

        if (m_pObjectInfo->m_nSpecialColResponseCase == eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_LAMPOST)
        {
            auto* pColModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();

            auto vecMin = CVector(0.0F, 0.0F, pColModel->GetBoundingBox().m_vecMin.z);
            vecMin = Multiply3x3(m_matrix, &vecMin);
            vecMin = CPhysical::GetSpeed(vecMin);

            auto vecMax = CVector(0.0F, 0.0F, pColModel->GetBoundingBox().m_vecMax.z);
            vecMax = Multiply3x3(m_matrix, &vecMax);
            vecMax = CPhysical::GetSpeed(vecMax);

            auto& vecUsed = vecMin.SquaredMagnitude() >= vecMax.SquaredMagnitude() ? vecMin : vecMax;
            const auto fMove = vecUsed.SquaredMagnitude() * pow(CTimer::ms_fTimeStep, 2.0F);
            if (fMove >= 0.09F)
                return static_cast<uint8_t>(ceil(sqrt(fMove) / 0.3F));

            return 1;
        }

        if (objectFlags.bIsLiftable
            || m_pObjectInfo->m_nSpecialColResponseCase == eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_SMALLBOX
            || m_pObjectInfo->m_nSpecialColResponseCase == eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_FENCEPART)
        {
            auto* pColModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();
            const auto vecSize = pColModel->GetBoundingBox().m_vecMax - pColModel->GetBoundingBox().m_vecMin;
            const auto fEdge = std::max({ vecSize.x, vecSize.y, vecSize.z }) / 2.0F;
            const auto fMove = m_vecMoveSpeed.SquaredMagnitude() * pow(CTimer::ms_fTimeStep, 2.0F);
            if (fMove >= pow(fEdge, 2.0F))
                return static_cast<uint8_t>(ceil(sqrt(fMove) / fEdge));

            return 1;
        }

        const auto fMove = m_vecMoveSpeed.SquaredMagnitude() * pow(CTimer::ms_fTimeStep, 2.0F);
        if (fMove >= 0.09F)
            return static_cast<uint8_t>(ceil(sqrt(fMove) / 0.3F));

        return 1;
    }

    auto& pBox = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox();
    auto fLongest = std::max({ pBox.m_vecMax.x, pBox.m_vecMax.y, -pBox.m_vecMin.x, -pBox.m_vecMin.y });
    const auto fMove = fabs(fLongest * m_vecTurnSpeed.z);
    if (fMove > 0.1F)
        return static_cast<uint8_t>(ceil(fMove * 10.0F));

    return 1;
}

void CObject::PreRender()
{
    CObject::PreRender_Reversed();
}
void CObject::PreRender_Reversed()
{
    if (objectFlags.bAffectedByColBrightness)
        CObject::GetLightingFromCollisionBelow();

    if (m_dwBurnTime > CTimer::m_snTimeInMilliseconds)
        CObject::DoBurnEffect();

    if (!m_pAttachedTo)
    {
        const auto fDay = static_cast<float>(m_nDayBrightness) / 30.0F;
        const auto fNight = static_cast<float>(m_nNightBrightness) / 30.0F;
        m_fContactSurfaceBrightness = lerp(fDay, fNight, CCustomBuildingDNPipeline::m_fDNBalanceParam);
    }

    if (m_pRwObject && RwObjectGetType(m_pRwObject) == rpCLUMP && objectFlags.bFadingIn)
    {
        auto iAlpha = CVisibilityPlugins::GetClumpAlpha(m_pRwClump) - 16;
        iAlpha = std::max(0, iAlpha);
        CVisibilityPlugins::SetClumpAlpha(m_pRwClump, iAlpha);
    }

    CEntity::PreRender();

    if (m_fScale != 1.0F || objectFlags.bIsScaled)
    {
        auto vecScale = CVector(m_fScale, m_fScale, m_fScale);
        CEntity::UpdateRW();
        RwMatrixScale(CEntity::GetModellingMatrix(), &vecScale, RwOpCombineType::rwCOMBINEPRECONCAT);
        CEntity::UpdateRwFrame();
        objectFlags.bIsScaled = true;
        if (objectFlags.bIsScaled)
            objectFlags.bIsScaled = false; //BUG? It's unsetting the flag straight after setting it
    }

    if (m_pRwObject && RwObjectGetType(m_pRwObject) == rpCLUMP)
        CEntity::UpdateRpHAnim();
}

void CObject::Render()
{
    CObject::Render_Reversed();
}
void CObject::Render_Reversed()
{
    if (objectFlags.bDoNotRender)
        return;

    const auto iRefModel = m_nRefModelIndex;
    if (iRefModel != -1 && IsTemporary() && objectFlags.bChangesVehColor)
    {
        auto* vehModelInfo = CModelInfo::GetModelInfo(iRefModel)->AsVehicleModelInfoPtr();
        CVehicleModelInfo::ms_pRemapTexture = m_pRemapTexture;
        vehModelInfo->SetVehicleColour(m_nCarColor[0], m_nCarColor[1], m_nCarColor[2], m_nCarColor[3]);
    }

    CEntity::Render();
}

bool CObject::SetupLighting()
{
    return CObject::SetupLighting_Reversed();
}
bool CObject::SetupLighting_Reversed()
{
    if (physicalFlags.bDestroyed)
    {
        WorldReplaceNormalLightsWithScorched(Scene.m_pRpWorld, 0.18F);
        return true;
    }

    if (m_bLightObject)
    {
        ActivateDirectional();
        return CRenderer::SetupLightingForEntity(this);
    }

    return false;
}

void CObject::RemoveLighting(bool bRemove)
{
    CObject::RemoveLighting_Reversed(bRemove);
}
void CObject::RemoveLighting_Reversed(bool bRemove)
{
    if (!bRemove)
        return;

    if (!physicalFlags.bDestroyed)
        CPointLights::RemoveLightsAffectingObject();

    SetAmbientColours();
    DeActivateDirectional();
}

//0x5D2870 - Deserializes object from save storage buffer
bool CObject::Load()
{
    int32_t iSaveStructSize; // unused
    CObjectSaveStructure saveStruct;
    CGenericGameStorage::LoadDataFromWorkBuffer(&iSaveStructSize, 4);
    CGenericGameStorage::LoadDataFromWorkBuffer(&saveStruct, sizeof(saveStruct));
    saveStruct.Extract(this);
    return true;
}

//0x5D2830 - Serializes object to save storage buffer
bool CObject::Save()
{
    CObjectSaveStructure saveStruct;
    saveStruct.Construct(this);

    auto iStructSize = sizeof(CObjectSaveStructure);
    CGenericGameStorage::SaveDataToWorkBuffer(&iStructSize, 4);
    CGenericGameStorage::SaveDataToWorkBuffer(&saveStruct, iStructSize);
    return true;
}

// Converted from thiscall void CObject::ProcessGarageDoorBehaviour(void) 0x44A4D0
void CObject::ProcessGarageDoorBehaviour() {
    if (m_nGarageDoorGarageIndex < 0)
        m_nGarageDoorGarageIndex = CGarages::FindGarageForObject(this);

    if (m_nGarageDoorGarageIndex < 0)
        return;

    auto& vecDummyPos = m_pDummyObject->GetPosition();
    auto* pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    const auto fHeight = pModelInfo->GetColModel()->GetBoundingBox().GetHeight();
    auto& pGarage = CGarages::GetGarage(m_nGarageDoorGarageIndex);
    if (pGarage.m_bDoorOpensUp)
    {
        m_matrix->GetPosition().z = vecDummyPos.z + fHeight * pGarage.m_fDoorPosition * 0.48F;
        float fDoorPos = pGarage.m_fDoorPosition;
        if (pGarage.m_bDoorGoesIn)
            fDoorPos = -fDoorPos;

        CGarage::BuildRotatedDoorMatrix(this, fDoorPos);
    }
    else
    {
        if (pGarage.m_nType == eGarageType::HANGAR_AT400)
            m_matrix->GetPosition().z = vecDummyPos.z - fHeight * pGarage.m_fDoorPosition;
        else if (pGarage.m_nType == eGarageType::HANGAR_ABANDONED_AIRPORT)
            m_matrix->GetPosition().x = vecDummyPos.x - pGarage.m_fDoorPosition * m_matrix->GetRight().x * 14.0F;
        else
            m_matrix->GetPosition().z = vecDummyPos.z + fHeight * pGarage.m_fDoorPosition / 1.1F;
    }

    m_bUsesCollision = pGarage.m_bDoorClosed;
    CEntity::UpdateRW();
    CEntity::UpdateRwFrame();
}

// Converted from thiscall bool CObject::CanBeDeleted(void) 0x59F120
bool CObject::CanBeDeleted() {
    switch (m_nObjectType)
    {
    case eObjectType::OBJECT_MISSION:
    case eObjectType::OBJECT_TYPE_CUTSCENE:
    case eObjectType::OBJECT_TYPE_DECORATION:
    case eObjectType::OBJECT_MISSION2:
        return false;

    default:
        return true;
    }
}

// Converted from thiscall void CObject::SetRelatedDummy(CDummyObject *relatedDummy) 0x59F160
void CObject::SetRelatedDummy(CDummyObject* relatedDummy) {
    m_pDummyObject = relatedDummy;
    relatedDummy->RegisterReference(reinterpret_cast<CEntity**>(&m_pDummyObject));
}

// Converted from thiscall bool CObject::TryToExplode(void) 0x59F2D0
bool CObject::TryToExplode() {
    if (!m_pObjectInfo->m_bCausesExplosion)
        return false;

    if (objectFlags.bIsExploded)
        return false;

    objectFlags.bIsExploded = true;
    CObject::Explode();
    return true;
}

// Converted from thiscall void CObject::SetObjectTargettable(uchar targetable) 0x59F300
void CObject::SetObjectTargettable(unsigned char targetable) {
    objectFlags.bIsTargatable = targetable;
}

// Converted from thiscall bool CObject::CanBeTargetted(void) 0x59F320
bool CObject::CanBeTargetted() {
    return objectFlags.bIsTargatable;
}

// Converted from thiscall void CObject::RefModelInfo(int modelIndex) 0x59F330
void CObject::RefModelInfo(int modelIndex) {
    m_nRefModelIndex = modelIndex;
    CModelInfo::GetModelInfo(modelIndex)->AddRef();
}

// Converted from thiscall void CObject::SetRemapTexture(RwTexture *remapTexture, short txdIndex) 0x59F350
void CObject::SetRemapTexture(RwTexture* remapTexture, short txdIndex) {
    m_pRemapTexture = remapTexture;
    m_wRemapTxd = txdIndex;
    if (txdIndex != -1)
        CTxdStore::AddRef(txdIndex);
}

// Converted from thiscall float CObject::GetRopeHeight(void) 0x59F380
float CObject::GetRopeHeight() {
    const auto ropeIndex = CRopes::FindRope(reinterpret_cast<uint32_t>(this));
    return CRopes::GetRope(ropeIndex).m_fRopeSegmentLength;
}

// Converted from thiscall void CObject::SetRopeHeight(float height) 0x59F3A0
void CObject::SetRopeHeight(float height) {
    const auto ropeIndex = CRopes::FindRope(reinterpret_cast<uint32_t>(this));
    CRopes::GetRope(ropeIndex).m_fRopeSegmentLength = height;
}

// Converted from thiscall CEntity* CObject::GetObjectCarriedWithRope(void) 0x59F3C0
CEntity* CObject::GetObjectCarriedWithRope() {
    const auto ropeIndex = CRopes::FindRope(reinterpret_cast<uint32_t>(this));
    return CRopes::GetRope(ropeIndex).m_pAttachedEntity;
}

// Converted from thiscall void CObject::ReleaseObjectCarriedWithRope(void) 0x59F3E0
void CObject::ReleaseObjectCarriedWithRope() {
    const auto ropeIndex = CRopes::FindRope(reinterpret_cast<uint32_t>(this));
    CRopes::GetRope(ropeIndex).ReleasePickedUpObject();
}

// Converted from thiscall void CObject::AddToControlCodeList(void) 0x59F400
void CObject::AddToControlCodeList() {
   m_pControlCodeList = CWorld::ms_listObjectsWithControlCode.AddItem(this);
}

// Converted from thiscall void CObject::RemoveFromControlCodeList(void) 0x59F450
void CObject::RemoveFromControlCodeList() {
    if (!m_pControlCodeList)
        return;

    CWorld::ms_listObjectsWithControlCode.DeleteNode(m_pControlCodeList);
    m_pControlCodeList = nullptr;
}

// Converted from thiscall void CObject::ResetDoorAngle(void) 0x59F4B0
void CObject::ResetDoorAngle() {
    if (!physicalFlags.bDisableMoveForce || m_fDoorStartAngle <= -1000.0F)
        return;

    CPlaceable::SetHeading(m_fDoorStartAngle);
    this->SetIsStatic(true);
    m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
    m_vecTurnSpeed.Set(0.0F, 0.0F, 0.0F);
    m_vecFrictionMoveSpeed.Set(0.0F, 0.0F, 0.0F);
    m_vecFrictionTurnSpeed.Set(0.0F, 0.0F, 0.0F);
    CEntity::UpdateRW();
    CEntity::UpdateRwFrame();
}

// Converted from thiscall void CObject::LockDoor(void) 0x59F5C0
void CObject::LockDoor() {
    objectFlags.bIsDoorOpen = false;
    physicalFlags.bCollidable = true;
    physicalFlags.bDisableCollisionForce = true;
    CObject::ResetDoorAngle();
}

// Converted from thiscall void CObject::Init(void) 0x59F840
void CObject::Init() {
    m_nType = eEntityType::ENTITY_TYPE_OBJECT;
    m_pObjectInfo = &CObjectData::GetDefault();
    m_nColDamageEffect = eObjectColDamageEffect::COL_DAMAGE_EFFECT_NONE;
    m_nSpecialColResponseCase = eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_NONE;
    m_nObjectType = eObjectType::OBJECT_GAME;
    this->SetIsStatic(true);

    m_nObjectFlags &= 0x0FC040000;
    objectFlags.bCanBeAttachedToMagnet = true;

    if (m_nModelIndex == 0xFFFF)
    {
        objectFlags.bHasNoModel = false;
    }
    else
    {
        CObjectData::SetObjectData(m_nModelIndex, *this);
        auto *pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
        if (pModelInfo->GetColModel()->m_boundSphere.m_bFlag0x01)
        {
            CColStore::AddRef(pModelInfo->GetColModel()->m_boundSphere.m_nMaterial);
            objectFlags.bHasNoModel = true;

            auto *pAtomicInfo = pModelInfo->AsAtomicModelInfoPtr();
            if (pAtomicInfo && pAtomicInfo->SwaysInWind() && !physicalFlags.bDisableCollisionForce)
            {
                auto& pBndBox = pModelInfo->GetColModel()->GetBoundingBox();
                m_vecCentreOfMass.z = pBndBox.m_vecMin.z + (pBndBox.m_vecMax.z - pBndBox.m_vecMin.z) * 0.2F;
            }
        }
    }

    if (physicalFlags.bDisableMoveForce)
    {
        auto* pColData = CEntity::GetColModel()->m_pColData;
        if (pColData)
            pColData->m_nNumSpheres = 0;
    }

    m_fHealth = 1000.0F;
    m_fDoorStartAngle = -1001.0F;
    m_dwRemovalTime = 0;
    m_nBonusValue = 0;
    m_wCostValue = 0;
    for (auto& col : m_nCarColor)
        col = 0;

    m_nRefModelIndex = -1;
    m_nGarageDoorGarageIndex = -1;
    m_nLastWeaponDamage = -1;
    m_pFire = nullptr;

    if (m_nModelIndex == ModelIndices::MI_BUOY)
        physicalFlags.bTouchingWater = true;

    if (m_nModelIndex != 0xFFFF && CModelInfo::GetModelInfo(m_nModelIndex)->GetModelType() == ModelInfoType::MODEL_INFO_WEAPON)
        m_bLightObject = true;

    if (m_nModelIndex == ModelIndices::MI_MLAMPPOST
        || m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_MIAMI
        || m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_VEGAS
        || m_nModelIndex == ModelIndices::MI_TRAFFICLIGHTS_TWOVERTICAL
        || m_nModelIndex == ModelIndices::MI_SINGLESTREETLIGHTS1
        || m_nModelIndex == ModelIndices::MI_SINGLESTREETLIGHTS2
        || m_nModelIndex == ModelIndices::MI_SINGLESTREETLIGHTS3
        || m_nModelIndex == ModelIndices::MI_DOUBLESTREETLIGHTS
        || m_nModelIndex != 0xFFFF && CModelInfo::GetModelInfo(m_nModelIndex)->AsAtomicModelInfoPtr() && CModelInfo::GetModelInfo(m_nModelIndex)->SwaysInWind())
    {
        objectFlags.bIsLampPost = true;
    }
    else
    {
        objectFlags.bIsLampPost = false;
    }

    objectFlags.bIsTargatable = false;
    physicalFlags.bAttachedToEntity = false;

    m_nAreaCode = eAreaCodes::AREA_CODE_13;
    m_wRemapTxd = -1;
    m_pRemapTexture = nullptr;
    m_pControlCodeList = nullptr;

    if (m_nModelIndex == ModelIndices::MI_SAMSITE
        || m_nModelIndex == ModelIndices::MI_SAMSITE2
        || m_nModelIndex == ModelIndices::MI_TRAINCROSSING
        || m_nModelIndex == ModelIndices::MI_TRAINCROSSING1
        || m_nModelIndex == ModelIndices::MI_MAGNOCRANE
        || m_nModelIndex == ModelIndices::MI_CRANETROLLEY
        || m_nModelIndex == ModelIndices::MI_QUARRYCRANE_ARM
        || CGarages::IsModelIndexADoor(static_cast<int16_t>(m_nModelIndex)))
    {
        CObject::AddToControlCodeList();
    }

    m_dwBurnTime = 0;
    m_fScale = 1.0F;

    m_nDayBrightness = 0x8;
    m_nNightBrightness = 0x4;
    m_wScriptTriggerIndex = -1;
}

// Converted from thiscall void CObject::DoBurnEffect(void) 0x59FB50
void CObject::DoBurnEffect() {
    const auto& pBox = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox();
    const auto& vecSize = pBox.GetSize();
    const auto nUsedSize = static_cast<int>(vecSize.x * vecSize.y * vecSize.z * m_fBurnDamage / 20.0F);
    if (nUsedSize <= 0)
        return;

    for (auto i = 0; i < nUsedSize; ++i)
    {
        const auto fRandX = CGeneral::GetRandomNumberInRange(pBox.m_vecMin.x, pBox.m_vecMax.x);
        const auto fRandY = CGeneral::GetRandomNumberInRange(pBox.m_vecMin.y, pBox.m_vecMax.y);
        const auto fRandZ = CGeneral::GetRandomNumberInRange(pBox.m_vecMin.z, pBox.m_vecMax.z);
        auto vecParticlePos = *m_matrix * CVector(fRandX, fRandY, fRandZ);

        //auto smokePart = FxPrtMult_c() Originally overwriten right after
        auto smokePart = FxPrtMult_c(0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F, 0.4F);
        auto vecVelocity = CVector(0.0F, 0.0F, 0.02F);
        g_fx.m_pPrtSmokeII3expand->AddParticle(&vecParticlePos,
                                               &vecVelocity,
                                               0.0F,
                                               &smokePart,
                                               -1.0F,
                                               1.2F,
                                               0.6F,
                                               false);
    }
}

// Converted from thiscall uchar CObject::GetLightingFromCollisionBelow(void) 0x59FD00
void CObject::GetLightingFromCollisionBelow() {
    CColPoint colPoint;
    CEntity* pEntity;
    if (CWorld::ProcessVerticalLine(GetPosition(), -1000.0F, colPoint, pEntity, true, false, false, false, true, false, nullptr))
    {
        m_nDayBrightness = colPoint.m_nLightingB.day;
        m_nNightBrightness = colPoint.m_nLightingB.night;
    }
}

// Converted from thiscall void CObject::ProcessSamSiteBehaviour(void) 0x5A07D0
void CObject::ProcessSamSiteBehaviour() {
    if (objectFlags.bIsBroken)
        return;

    auto& vecPos = GetPosition();
    bool bDisabled = CObject::bAircraftCarrierSamSiteDisabled;
    if (vecPos.x >= -1000)
        bDisabled = CObject::bArea51SamSiteDisabled;

    if (bDisabled)
        return;

    CEntity* pTargetEntity = nullptr;
    auto fHeading = CGeneral::GetATanOfXY(m_matrix->GetForward().x, m_matrix->GetForward().y);
    auto* pPlayerVeh = FindPlayerVehicle(-1, false);
    if (!pPlayerVeh
        || pPlayerVeh->GetVehicleAppearance() == eVehicleApperance::VEHICLE_APPEARANCE_BIKE
        || pPlayerVeh->GetVehicleAppearance() == eVehicleApperance::VEHICLE_APPEARANCE_AUTOMOBILE)
    {
        auto* pPlayer = FindPlayerPed(-1);
        if (pPlayer->GetIntelligence()->GetTaskJetPack())
            pTargetEntity = pPlayer;
    }
    else
    {
        pTargetEntity = pPlayerVeh;
    }

    if (pTargetEntity)
    {
        auto& vecTargetPos = pTargetEntity->GetPosition();
        if (vecPos.z <= vecTargetPos.z + 2.0F
            && vecTargetPos.y <= 2100.0F)
        {
            const auto vecDir = vecTargetPos - vecPos;
            const auto fAngle = CGeneral::GetATanOfXY(vecDir.x, vecDir.y);
            const auto fAngleDiff = CGeneral::LimitRadianAngle(fAngle - fHeading);

            float fNewAngle;
            const auto fTimeStep = CTimer::ms_fTimeStep / 20.0F;
            if (abs(fAngleDiff) <= fTimeStep)
                fNewAngle = fAngle;
            else if (fAngleDiff < 0.0F)
                fNewAngle = fHeading - fTimeStep;
            else
                fNewAngle = fHeading + fTimeStep;

            CPlaceable::SetHeading(fNewAngle - HALF_PI);
            CEntity::UpdateRW();
            CEntity::UpdateRwFrame();

            auto vecShootDir = vecPos - vecTargetPos;
            if (vecShootDir.Magnitude2D() >= 120.0F)
                return;

            if (fabs(fAngleDiff) >= 0.1F || CTimer::m_snTimeInMilliseconds / 4000 == CTimer::m_snPreviousTimeInMilliseconds / 4000)
                return;

            auto vecRocketDir = m_matrix->GetForward() + m_matrix->GetUp();
            const auto vecSrcPos = *m_matrix * CVector(0.0F, 2.0F, 4.0F);
            CProjectileInfo::AddProjectile(this, eWeaponType::WEAPON_ROCKET_HS, vecSrcPos, 0.0F, &vecRocketDir, pTargetEntity);
            return;
        }
    }

    fHeading += CTimer::ms_fTimeStep / 200.0F;
    CPlaceable::SetHeading(fHeading - HALF_PI);
    CEntity::UpdateRW();
    CEntity::UpdateRwFrame();
}

// Converted from thiscall void CObject::ProcessTrainCrossingBehaviour(void) 0x5A0B50
void CObject::ProcessTrainCrossingBehaviour() {
    if (!(static_cast<uint8_t>(CTimer::m_FrameCounter + m_nRandomSeedUpperByte) & 0x10))
    {
        const auto& vecPos = GetPosition();
        const auto bWasEnabled = objectFlags.bTrainCrossEnabled;
        objectFlags.bTrainCrossEnabled = false;
        auto* pTrain = CTrain::FindNearestTrain(vecPos, true);
        if (pTrain)
        {
            auto vecDist = pTrain->GetPosition() - vecPos;
            if (vecDist.Magnitude2D() < 120.0F)
                objectFlags.bTrainCrossEnabled = true;
        }

        if (m_nModelIndex == ModelIndices::MI_TRAINCROSSING1 && objectFlags.bTrainCrossEnabled != bWasEnabled)
        {
            const auto& pDummyPos = m_pDummyObject->GetPosition();
            ThePaths.SetLinksBridgeLights(pDummyPos.x - 12.0F, pDummyPos.x + 12.0F, pDummyPos.y - 12.0F, pDummyPos.y + 12.0F, !bWasEnabled);
        }
    }

    if (m_nModelIndex == ModelIndices::MI_TRAINCROSSING1)
        return;

    const auto fAngle = acos(m_matrix->GetUp().z);
    const auto fTimeStep = CTimer::ms_fTimeStep / 200.0F;
    if (objectFlags.bTrainCrossEnabled)
        CObject::SetMatrixForTrainCrossing(m_matrix, std::max(0.0F, fAngle - fTimeStep));
    else
        CObject::SetMatrixForTrainCrossing(m_matrix, std::min(PI * 0.43F, fAngle + fTimeStep));

    CEntity::UpdateRW();
    CEntity::UpdateRwFrame();
}

// Converted from thiscall void CObject::ObjectDamage(float damage,CVector *fxOrigin,CVector *fxDirection,CEntity *damager,eWeaponType weaponType) 0x5A0D90
void CObject::ObjectDamage(float damage, CVector* fxOrigin, CVector* fxDirection, CEntity* damager, eWeaponType weaponType) {
    if (!m_bUsesCollision)
        return;

    if (weaponType == eWeaponType::WEAPON_UNIDENTIFIED && damager && damager->IsVehicle())
        weaponType = eWeaponType::WEAPON_RUNOVERBYCAR;

    if (!CPhysical::CanPhysicalBeDamaged(weaponType, nullptr))
        return;

    m_fHealth -= damage * m_pObjectInfo->m_fColDamageMultiplier;
    m_fHealth = std::max(0.0F, m_fHealth);

    if (!m_nColDamageEffect || physicalFlags.bInvulnerable && damager != FindPlayerPed(-1) && damager != FindPlayerVehicle(-1, false))
        return;

    // Big Smoke crack palace wall break checks
    if (m_nModelIndex == ModelIndices::MI_IMY_SHASH_WALL)
    {
        if (!damager)
            return;

        if (damager->IsPed())
        {
            auto* pPed = static_cast<CPed*>(damager);
            if (!pPed->bInVehicle || !pPed->m_pVehicle || pPed->m_pVehicle->m_nModelIndex != eModelID::MODEL_SWATVAN)
                return;
        }
        else if (damager->IsVehicle())
        {
            if (damager->m_nModelIndex != eModelID::MODEL_SWATVAN)
                return;
        }
        else
            return;
    }

    if (damager && damager->m_nModelIndex == eModelID::MODEL_FORKLIFT)
        return;

    m_nLastWeaponDamage = weaponType;
    bool bWasDestroyed = false;

    if (damage * m_pObjectInfo->m_fColDamageMultiplier > 150.0F || m_fHealth == 0.0F)
    {
        switch (m_nColDamageEffect)
        {
        case COL_DAMAGE_EFFECT_CHANGE_MODEL:
            if (!m_bRenderDamaged)
            {
                bWasDestroyed = true;
                this->DeleteRwObject();
            }
            m_bRenderDamaged = true;
            break;

        case COL_DAMAGE_EFFECT_SMASH_COMPLETELY:
            m_bUsesCollision = false;
            m_bIsVisible = false;
            if (!CEntity::IsStatic())
                CPhysical::RemoveFromMovingList();

            m_bIsStatic = true;
            physicalFlags.bExplosionProof = true;
            m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
            m_vecTurnSpeed.Set(0.0F, 0.0F, 0.0F);
            this->DeleteRwObject();
            bWasDestroyed = true;
            break;

        case COL_DAMAGE_EFFECT_CHANGE_THEN_SMASH:
            if (m_bRenderDamaged)
            {
                m_bUsesCollision = false;
                m_bIsVisible = false;
                if (!CEntity::IsStatic())
                    CPhysical::RemoveFromMovingList();

                m_bIsStatic = true;
                physicalFlags.bExplosionProof = true;
                m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
                m_vecTurnSpeed.Set(0.0F, 0.0F, 0.0F);
                this->DeleteRwObject();
                bWasDestroyed = true;
            }
            else
            {
                this->DeleteRwObject();
                m_bRenderDamaged = true;
            }
            break;

        case COL_DAMAGE_EFFECT_BREAKABLE:
        case COL_DAMAGE_EFFECT_BREAKABLE_REMOVED:
            {
                const auto bJustFaces = damage * m_pObjectInfo->m_fColDamageMultiplier > m_pObjectInfo->m_fSmashMultiplier * 150.0F;
                g_breakMan.Add(this, &m_pObjectInfo->m_vecBreakVelocity, m_pObjectInfo->m_fBreakVelocityRand, bJustFaces);

                m_bUsesCollision = false;
                m_bIsVisible = false;
                if (!CEntity::IsStatic())
                    CPhysical::RemoveFromMovingList();

                m_bIsStatic = true;
                physicalFlags.bExplosionProof = true;
                m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
                m_vecTurnSpeed.Set(0.0F, 0.0F, 0.0F);
                objectFlags.bIsBroken = true;
                this->DeleteRwObject();
                bWasDestroyed = true;
                break;
            }
        }

        if (!m_bUsesCollision && !m_bIsVisible)
            m_fHealth = 0.0F;
    }

    bool bExploded = false;
    if (bWasDestroyed)
    {
        if (CObject::TryToExplode())
            bExploded = true;

        AudioEngine.ReportObjectDestruction(this);
    }

    // Particle creation
    if (!bWasDestroyed || !bExploded)
    {
        if (m_pObjectInfo->m_nFxType == eObjectFxType::NO_FX)
            return;

        bool bCreateParticle = false;
        if (m_pObjectInfo->m_nFxType == eObjectFxType::PLAY_ON_HIT_DESTROYED)
            bCreateParticle = true;
        else if (m_pObjectInfo->m_nFxType == eObjectFxType::PLAY_ON_DESTROYED)
            bCreateParticle = bWasDestroyed;
        else if (m_pObjectInfo->m_nFxType == eObjectFxType::PLAY_ON_HIT)
            bCreateParticle = damage > 30.0F;

        if (!bCreateParticle)
            return;

        if (m_pObjectInfo->m_vFxOffset.x < -500.0F)
        {
            if (!fxOrigin)
                return;

            RwMatrix particleMat;
            g_fx.CreateMatFromVec(&particleMat, fxOrigin, fxDirection);
            auto* pFxSystem = g_fxMan.CreateFxSystem(m_pObjectInfo->m_pFxSystemBP, &particleMat, nullptr, false);
            if (pFxSystem)
                pFxSystem->PlayAndKill();

            return;
        }

        auto particleMat = CMatrix(*m_matrix);
        auto vecPoint = Multiply3x3(&particleMat, &m_pObjectInfo->m_vFxOffset);
        vecPoint += GetPosition();
        auto* pFxSystem = g_fxMan.CreateFxSystem(m_pObjectInfo->m_pFxSystemBP, &vecPoint, nullptr, false);
        if (pFxSystem)
            pFxSystem->PlayAndKill();
    }
}

// Converted from thiscall void CObject::Explode(void) 0x5A1340
void CObject::Explode() {
    CVector vecPos = GetPosition();
    vecPos.z += 0.5F;
    auto* pPlayer = FindPlayerPed(-1);
    CExplosion::AddExplosion(this, pPlayer, eExplosionType::EXPLOSION_OBJECT, vecPos, 100, true, -1.0F, false);
    if (m_nColDamageEffect == eObjectColDamageEffect::COL_DAMAGE_EFFECT_BREAKABLE
        || m_nColDamageEffect == eObjectColDamageEffect::COL_DAMAGE_EFFECT_BREAKABLE_REMOVED)
    {
        vecPos.z -= 1.0F;
        auto vecDir = CVector(0.0F, 0.0F, 1.0F);
        CObject::ObjectDamage(10000.0F, &vecPos, &vecDir, this, eWeaponType::WEAPON_EXPLOSION);
    }
    else if(!physicalFlags.bDisableCollisionForce)
    {
        m_vecMoveSpeed.x += CGeneral::GetRandomNumberInRange(-0.0256F, 0.0256F);
        m_vecMoveSpeed.y += CGeneral::GetRandomNumberInRange(-0.0256F, 0.0256F);
        m_vecMoveSpeed.z += 0.5F;

        if (IsStatic())
        {
            this->SetIsStatic(false);
            CPhysical::AddToMovingList();
        }
    }

    if (m_pObjectInfo->m_nFxType == eObjectFxType::PLAY_ON_DESTROYED)
    {
        auto particleMat = CMatrix(*m_matrix);
        auto vecPoint = Multiply3x3(&particleMat, &m_pObjectInfo->m_vFxOffset);
        vecPoint += GetPosition();
        auto* pFxSystem = g_fxMan.CreateFxSystem(m_pObjectInfo->m_pFxSystemBP, &vecPoint, nullptr, false);
        if (pFxSystem)
            pFxSystem->PlayAndKill();
    }
}

// Converted from thiscall void CObject::ObjectFireDamage(float damage,CEntity *damager) 0x5A1580
void CObject::ObjectFireDamage(float damage, CEntity* damager) {
    if (m_nModelIndex != ModelIndices::MI_GRASSPLANT && m_nModelIndex != ModelIndices::MI_GRASSHOUSE)
        return;

    m_fHealth -= damage;
    m_fHealth = std::max(0.0F, m_fHealth);

    if (!m_nColDamageEffect || physicalFlags.bInvulnerable && damager != FindPlayerPed(-1) && damager != FindPlayerVehicle(-1, false))
        return;

    if (m_nModelIndex == ModelIndices::MI_GRASSPLANT)
    {
        m_fBurnDamage = 1.0F - (m_fHealth / 2000.0F);
        m_dwBurnTime = CTimer::m_snTimeInMilliseconds + 3000;
    }

    if (m_fHealth != 0.0F)
        return;

    if (m_nColDamageEffect == eObjectColDamageEffect::COL_DAMAGE_EFFECT_SMASH_COMPLETELY
        || m_nColDamageEffect == eObjectColDamageEffect::COL_DAMAGE_EFFECT_CHANGE_THEN_SMASH)
    {
        if (!m_bRenderDamaged)
        {
            m_bRenderDamaged = true;
            this->DeleteRwObject();
            CShadows::AddPermanentShadow(eShadowType::SHADOW_DEFAULT,
                                         gpShadowHeliTex,
                                         &GetPosition(),
                                         3.0F,
                                         0.0F,
                                         0.0F,
                                         -3.0F,
                                         200,
                                         0,
                                         0,
                                         0,
                                         10.0F,
                                         30000,
                                         1.0F);
        }
    }
    else if (m_nColDamageEffect == eObjectColDamageEffect::COL_DAMAGE_EFFECT_BREAKABLE
        || m_nColDamageEffect == eObjectColDamageEffect::COL_DAMAGE_EFFECT_BREAKABLE_REMOVED)
    {
        if (!objectFlags.bIsBroken)
            AudioEngine.ReportObjectDestruction(this);

        g_breakMan.Add(this, &m_pObjectInfo->m_vecBreakVelocity, m_pObjectInfo->m_fBreakVelocityRand, true);

        m_bUsesCollision = false;
        m_bIsVisible = false;
        if (!CEntity::IsStatic())
            CPhysical::RemoveFromMovingList();

        m_bIsStatic = true;
        physicalFlags.bExplosionProof = true;
        m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
        m_vecTurnSpeed.Set(0.0F, 0.0F, 0.0F);
        objectFlags.bIsBroken = true;
        this->DeleteRwObject();
    }
}

// Converted from cdecl void CObject::TryToFreeUpTempObjects(int numObjects) 0x5A1840
void CObject::TryToFreeUpTempObjects(int numObjects) {
    const auto iPoolSize = CPools::ms_pObjectPool->GetSize();
    if (!iPoolSize)
        return;

    for (auto i = iPoolSize - 1; i >= 0; --i)
    {
        if (numObjects <= 0)
            return;

        auto* pObj = CPools::ms_pObjectPool->GetAt(i);
        if (pObj && pObj->IsTemporary() && !pObj->IsVisible()) {
            CWorld::Remove(pObj);
            delete pObj;
            --numObjects;
        }
    }
}

// Converted from cdecl void CObject::DeleteAllTempObjects(void) 0x5A18B0
void CObject::DeleteAllTempObjects() {
    const auto iPoolSize = CPools::ms_pObjectPool->GetSize();
    if (!iPoolSize)
        return;

    for (auto i = 0; i < iPoolSize; ++i)
    {
        auto* pObj = CPools::ms_pObjectPool->GetAt(i);
        if (pObj && pObj->IsTemporary()) {
            CWorld::Remove(pObj);
            delete pObj;
        }
    }
}

// Converted from cdecl void CObject::DeleteAllMissionObjects(void) 0x5A1910
void CObject::DeleteAllMissionObjects() {
    const auto iPoolSize = CPools::ms_pObjectPool->GetSize();
    if (!iPoolSize)
        return;

    for (auto i = 0; i < iPoolSize; ++i)
    {
        auto* pObj = CPools::ms_pObjectPool->GetAt(i);
        if (pObj && pObj->IsMissionObject()) {
            CWorld::Remove(pObj);
            delete pObj;
        }
    }
}

// Converted from cdecl void CObject::DeleteAllTempObjectsInArea(CVector point,float radius) 0x5A1980
void CObject::DeleteAllTempObjectsInArea(CVector point, float radius) {
    const auto iPoolSize = CPools::ms_pObjectPool->GetSize();
    if (!iPoolSize)
        return;

    for (auto i = 0; i < iPoolSize; ++i)
    {
        auto* pObj = CPools::ms_pObjectPool->GetAt(i);
        if (pObj && pObj->IsTemporary()) {
            if (DistanceBetweenPointsSquared(pObj->GetPosition(), point) < pow(radius, 2.0F)) {
                CWorld::Remove(pObj);
                delete pObj;
            }
        }
    }
}

// Converted from thiscall void CObject::GrabObjectToCarryWithRope(CPhysical *attachTo) 0x5A1AB0
void CObject::GrabObjectToCarryWithRope(CPhysical* attachTo) {
    const auto iRopeInd = CRopes::FindRope(reinterpret_cast<uint32_t>(this));
    auto& pRope = CRopes::GetRope(iRopeInd);
    pRope.ReleasePickedUpObject();
    pRope.m_pAttachedEntity = attachTo;
    attachTo->RegisterReference(&pRope.m_pAttachedEntity);

    auto vecRopePoint = CVector();
    vecRopePoint.z = CRopes::FindPickupHeight(attachTo);
    vecRopePoint *= *attachTo->m_matrix * vecRopePoint;

    pRope.m_pRopeAttachObject->SetPosn(vecRopePoint);
    pRope.m_pRopeAttachObject->m_bUsesCollision = false;
}

// Converted from thiscall bool CObject::CanBeUsedToTakeCoverBehind(void) 0x5A1B60
bool CObject::CanBeUsedToTakeCoverBehind() {
    if (m_nObjectType == eObjectType::OBJECT_MISSION)
        return false;

    if (m_nModelIndex == ModelIndices::MI_FIRE_HYDRANT)
        return true;

    auto* pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    if (pModelInfo->AsAtomicModelInfoPtr() && pModelInfo->AsAtomicModelInfoPtr()->IsBreakableStatuePart())
        return false;

    const auto fHeight = pModelInfo->GetColModel()->GetBoundingBox().GetHeight();
    if (fHeight <= 0.75F || fHeight >= 1.25F || GetUp().z <= 0.9F)
        return false;

    return true;
}

CObject* CObject::Create(int modelIndex, bool bUnused) {
    CPools::ms_pObjectPool->m_bIsLocked = true;
    auto* pObj = new CObject(modelIndex, false); //BUG? most likely the unused parameter was supposed to be passed to the constructor
    CPools::ms_pObjectPool->m_bIsLocked = false;

    if (pObj)
        return pObj;

    CObject::TryToFreeUpTempObjects(5);
    g_waterCreatureMan.TryToFreeUpWaterCreatures(5);

    return new CObject(modelIndex, false);

}

CObject* CObject::Create(CDummyObject* dummyObject) {
    CPools::ms_pObjectPool->m_bIsLocked = true;
    auto* pObj = new CObject(dummyObject);
    CPools::ms_pObjectPool->m_bIsLocked = false;

    if (pObj)
        return pObj;

    CObject::TryToFreeUpTempObjects(5);
    g_waterCreatureMan.TryToFreeUpWaterCreatures(5);

    return new CObject(dummyObject);
}

// Converted from cdecl void CObject::SetMatrixForTrainCrossing(CMatrix *matrix,float) 0x59F200
void CObject::SetMatrixForTrainCrossing(CMatrix* matrix, float fAngle) {
    auto vecForward = CrossProduct(CVector(0.0F, 0.0F, 1.0F), matrix->GetRight());
    const auto fCos = cos(fAngle);
    const auto fSin = sin(fAngle);
    vecForward *= fCos;
    vecForward.z += fSin;

    matrix->GetUp() = CrossProduct(matrix->GetRight(), vecForward);
    matrix->GetForward() = vecForward;
}

// Converted from thiscall void CObject::ProcessControlLogic(void) 0x5A29A0
void CObject::ProcessControlLogic() {
    if (m_nModelIndex == ModelIndices::MI_SAMSITE || m_nModelIndex == ModelIndices::MI_SAMSITE2)
        CObject::ProcessSamSiteBehaviour();

    if (m_nModelIndex == ModelIndices::MI_TRAINCROSSING || m_nModelIndex == ModelIndices::MI_TRAINCROSSING1)
        CObject::ProcessTrainCrossingBehaviour();

    if (m_nModelIndex == ModelIndices::MI_MAGNOCRANE
        || m_nModelIndex == ModelIndices::MI_CRANETROLLEY
        || m_nModelIndex == ModelIndices::MI_QUARRYCRANE_ARM)
    {
        const auto iRopeInd = CRopes::FindRope(reinterpret_cast<uint32_t>(this));
        uint8_t nSegments = 0;
        auto fRopeLengthChange = 0.0F;
        if (iRopeInd >= 0)
        {
            auto& pRope = CRopes::GetRope(iRopeInd);
            nSegments = static_cast<uint8_t>(pRope.m_fRopeSegmentLength * 32.0F);
            fRopeLengthChange = pRope.m_fMass * pRope.m_fRopeSegmentLength - static_cast<float>(nSegments) * pRope.m_fRopeTotalLength;
        }

        if (m_nModelIndex == ModelIndices::MI_MAGNOCRANE)
        {
            auto vecRopePoint = *m_matrix * CVector(0.0F, 36.64F, -1.69F);
            vecRopePoint.z += fRopeLengthChange;
            CRopes::RegisterRope(this, 4, vecRopePoint, false, nSegments, 1u, this, 20000u);
        }
        else if (m_nModelIndex == ModelIndices::MI_CRANETROLLEY)
        {
            const auto nRopeType = GetPosition().x >= 0 ? 7 : 5;
            auto vecRopePoint = *m_matrix * CVector(0.0F, 0.0F, 0.0F);
            vecRopePoint.z += fRopeLengthChange;
            CRopes::RegisterRope(this, nRopeType, vecRopePoint, false, nSegments, 1u, this, 20000u);
        }
        else
        {
            auto vecRopePoint = *m_matrix * CVector(0.0F, 0.0F, 59.0F);
            vecRopePoint.z += fRopeLengthChange;
            CRopes::RegisterRope(this, 6, vecRopePoint, false, nSegments, 1u, this, 20000u);
        }
    }

    if (CGarages::IsModelIndexADoor(m_nModelIndex))
        CObject::ProcessGarageDoorBehaviour();
}

// Converted from cdecl bool IsObjectPointerValid_NotInWorld(CObject *object) 0x5A2B90
bool IsObjectPointerValid_NotInWorld(CObject* object) {
    return CPools::ms_pObjectPool->IsObjectValid(object);
}

// Converted from cdecl bool IsObjectPointerValid(CObject *object) 0x5A2C20
bool IsObjectPointerValid(CObject* object) {
    if (!CPools::ms_pObjectPool->IsObjectValid(object))
        return false;

    if (object->m_bIsBIGBuilding)
        return true;

    return object->m_pCollisionList.m_pNode != nullptr;
}
