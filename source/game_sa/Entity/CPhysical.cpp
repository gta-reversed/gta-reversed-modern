/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

float& CPhysical::PHYSICAL_SHIFT_SPEED_DAMP = *(float*)0x8CD788;

CRect* CPhysical::GetBoundRect(CRect* pRect)
{
    return ((CRect*(__thiscall*)(CEntity*, CRect*))(*(void***)this)[9])(this, pRect);
}

void CPhysical::ProcessShift()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CPhysical*))(*(void***)this)[12])(this);
#else
    ProcessShift_Reversed();
#endif
}

void CPhysical::ProcessShift_Reversed()
{
    CRect boundingBox;
    CPhysical::GetBoundRect(&boundingBox);
    m_fMovingSpeed = 0.0f;

    bool bPhysicalFlagsSet = m_nPhysicalFlags & (PHYSICAL_DISABLE_MOVE_FORCE | PHYSICAL_INFINITE_MASS | PHYSICAL_DISABLE_Z);
    if (m_nStatus == STATUS_SIMPLE || bPhysicalFlagsSet)
    {
        if (bPhysicalFlagsSet)
        {
            m_vecTurnSpeed = CVector(0.0f, 0.0f, 0.0f);
        }
        m_bIsStuck = false;
        m_bIsInSafePosition = true;
        RemoveAndAdd();
    }
    else
    {
        if (m_bHasHitWall)
        {
            CPed* pPed = static_cast<CPed*>(this);
            bool bSomeSpecificFlagsSet = false;
            if (m_nType == ENTITY_TYPE_PED && pPed->somePedStruct)
            {
                if (!pPed->somePedStruct->flags.b03 || pPed->somePedStruct->flags.b04)
                {
                    bSomeSpecificFlagsSet = true;
                }
            }
            if ((m_nType == ENTITY_TYPE_PED && bSomeSpecificFlagsSet) || CWorld::bSecondShift)
            {
                float fMoveSpeedShift = pow(CPhysical::PHYSICAL_SHIFT_SPEED_DAMP, CTimer::ms_fTimeStep);
                m_vecMoveSpeed *= fMoveSpeedShift;
                float fTurnSpeedShift = pow(CPhysical::PHYSICAL_SHIFT_SPEED_DAMP, CTimer::ms_fTimeStep);
                m_vecTurnSpeed *= fTurnSpeedShift;
            }
        }

        CMatrix oldEntityMatrix(*m_matrix);
        ApplySpeed();
        m_matrix->Reorthogonalise();
        SetNextScanCode();

        bool bShifted = false;
        if (m_nType == ENTITY_TYPE_VEHICLE)
        {
            physicalFlags.b16 = true;
        }

        int startSectorX = static_cast<int>(floor(boundingBox.left * 0.02 + 60.0));
        int startSectorY = static_cast<int>(floor(boundingBox.top * 0.02 + 60.0));
        int endSectorX = static_cast<int>(floor(boundingBox.right * 0.02 + 60.0));
        int endSectorY = static_cast<int>(floor(boundingBox.bottom * 0.02 + 60.0));
        for (int sectorY = startSectorY; sectorY <= endSectorY; ++sectorY)
        {
            int sectorX = startSectorX;
            if (startSectorX <= endSectorX)
            {
                do
                {
                    if (ProcessShiftSectorList(sectorX, sectorY))
                    {
                        bShifted = true;
                    }
                    ++sectorX;
                } while (sectorX <= endSectorX);
            }
        }

        physicalFlags.b16 = false;

        if (bShifted || m_nType == ENTITY_TYPE_VEHICLE)
        {
            if (CWorld::ms_nCurrentScanCode >= 65535u)
            {
                CWorld::ClearScanCodes();
                CWorld::ms_nCurrentScanCode = 1;
            }
            else
            {
                CWorld::ms_nCurrentScanCode++;
            }
            bool bShifted2 = false;
            startSectorX = static_cast<int>(floor(boundingBox.left * 0.02 + 60.0));
            startSectorY = static_cast<int>(floor(boundingBox.top * 0.02 + 60.0));
            endSectorX = static_cast<int>(floor(boundingBox.right * 0.02 + 60.0));
            endSectorY = static_cast<int>(floor(boundingBox.bottom * 0.02 + 60.0));
            int sectorY = startSectorY;
            if (startSectorY <= endSectorY)
            {
                do
                {
                    int sectorX = startSectorX;
                    if (startSectorX <= endSectorX)
                    {
                        while (1)
                        {
                            if (ProcessCollisionSectorList(sectorX, sectorY))
                            {
                                if (!CWorld::bSecondShift)
                                {
                                    *(CMatrix*)m_matrix = oldEntityMatrix;
                                    return;
                                }
                                bShifted2 = true;
                            }
                            if (++sectorX > endSectorX)
                            {
                                break;
                            }
                        }
                    }
                    ++sectorY;
                } while (sectorY <= endSectorY);
                if (bShifted2)
                {
                    *(CMatrix*)m_matrix = oldEntityMatrix;
                    return;
                }
            }
        }

        m_bIsStuck = false;
        m_bIsInSafePosition = true;

        float fZ = m_matrix->pos.z - oldEntityMatrix.pos.z;
        float fY = m_matrix->pos.y - oldEntityMatrix.pos.y;
        float fX = m_matrix->pos.x - oldEntityMatrix.pos.x;
        m_fMovingSpeed = sqrt(fX * fX + fY * fY + fZ * fZ);
        RemoveAndAdd();
    }
}

int CPhysical::ProcessEntityCollision(CEntity* entity, CColPoint* point)
{
    return ((int (__thiscall*)(CPhysical*, CEntity*, CColPoint*))(*(void***)this)[23])(this, entity, point);
}

// Converted from thiscall void CPhysical::RemoveAndAdd(void) 0x542560
void CPhysical::RemoveAndAdd()
{
    ((void(__thiscall*)(CPhysical*))0x542560)(this);
}

// Converted from thiscall void CPhysical::AddToMovingList(void) 0x542800
void CPhysical::AddToMovingList()
{
    ((void(__thiscall*)(CPhysical*))0x542800)(this);
}

// Converted from thiscall void CPhysical::RemoveFromMovingList(void) 0x542860
void CPhysical::RemoveFromMovingList()
{
    ((void(__thiscall*)(CPhysical*))0x542860)(this);
}

// Converted from thiscall void CPhysical::SetDamagedPieceRecord(float damageIntensity,CEntity *damagingEntity,CColPoint &colPoint,float distanceMult) 0x5428C0
void CPhysical::SetDamagedPieceRecord(float damageIntensity, CEntity* damagingEntity, CColPoint& colPoint, float distanceMult)
{
    ((void(__thiscall*)(CPhysical*, float, CEntity*, CColPoint&, float))0x5428C0)(this, damageIntensity, damagingEntity, colPoint, distanceMult);
}

// Converted from thiscall void CPhysical::ApplyMoveForce(CVector force) 0x5429F0
void CPhysical::ApplyMoveForce(CVector force)
{
    ((void(__thiscall*)(CPhysical*, CVector))0x5429F0)(this, force);
}

// Converted from thiscall void CPhysical::ApplyTurnForce(CVector dir,CVector velocity) 0x542A50
void CPhysical::ApplyTurnForce(CVector dir, CVector velocity)
{
    ((void(__thiscall*)(CPhysical*, CVector, CVector))0x542A50)(this, dir, velocity);
}

// Converted from thiscall void CPhysical::ApplyForce(CVector dir,CVector velocity,bool flag) 0x542B50
void CPhysical::ApplyForce(CVector dir, CVector velocity, bool flag)
{
    ((void(__thiscall*)(CPhysical*, CVector, CVector, bool))0x542B50)(this, dir, velocity, flag);
}

// Converted from thiscall CVector CPhysical::GetSpeed(CVector direction) 0x542CE0
CVector CPhysical::GetSpeed(CVector direction)
{
    CVector result;
    ((void(__thiscall*)(CPhysical*, CVector*, CVector))0x542CE0)(this, &result, direction);
    return result;
}

// Converted from thiscall void CPhysical::ApplyMoveSpeed(void) 0x542DD0
void CPhysical::ApplyMoveSpeed()
{
    ((void(__thiscall*)(CPhysical*))0x542DD0)(this);
}

// Converted from thiscall void CPhysical::ApplyTurnSpeed(void) 0x542E20
void CPhysical::ApplyTurnSpeed()
{
    ((void(__thiscall*)(CPhysical*))0x542E20)(this);
}

// Converted from thiscall void CPhysical::ApplyGravity(void) 0x542FE0
void CPhysical::ApplyGravity()
{
    ((void(__thiscall*)(CPhysical*))0x542FE0)(this);
}

// Converted from thiscall void CPhysical::ApplyFrictionMoveForce(CVector moveForce) 0x5430A0
void CPhysical::ApplyFrictionMoveForce(CVector moveForce)
{
    ((void(__thiscall*)(CPhysical*, CVector))0x5430A0)(this, moveForce);
}

// Converted from thiscall void CPhysical::ApplyFrictionTurnForce(CVector posn,CVector velocity) 0x543100
void CPhysical::ApplyFrictionTurnForce(CVector posn, CVector velocity)
{
    ((void(__thiscall*)(CPhysical*, CVector, CVector))0x543100)(this, posn, velocity);
}

// Converted from thiscall void CPhysical::ApplyFrictionForce(CVector posn,CVector velocity) 0x543220
void CPhysical::ApplyFrictionForce(CVector posn, CVector velocity)
{
    ((void(__thiscall*)(CPhysical*, CVector, CVector))0x543220)(this, posn, velocity);
}

// Converted from thiscall void CPhysical::SkipPhysics(void) 0x5433B0
void CPhysical::SkipPhysics()
{
    ((void(__thiscall*)(CPhysical*))0x5433B0)(this);
}

// Converted from thiscall void CPhysical::AddCollisionRecord(CEntity *collidedEntity) 0x543490
void CPhysical::AddCollisionRecord(CEntity* collidedEntity)
{
    ((void(__thiscall*)(CPhysical*, CEntity*))0x543490)(this, collidedEntity);
}

// Converted from thiscall bool CPhysical::GetHasCollidedWith(CEntity *entity) 0x543540
bool CPhysical::GetHasCollidedWith(CEntity* entity)
{
    return ((bool(__thiscall*)(CPhysical*, CEntity*))0x543540)(this, entity);
}

// Converted from thiscall bool CPhysical::GetHasCollidedWithAnyObject(void) 0x543580
bool CPhysical::GetHasCollidedWithAnyObject()
{
    return ((bool(__thiscall*)(CPhysical*))0x543580)(this);
}

// Converted from thiscall bool CPhysical::ApplyCollision(CEntity *entity,CColPoint &colPoint,float &) 0x5435C0
bool CPhysical::ApplyCollision(CEntity* entity, CColPoint& colPoint, float& arg2)
{
    return ((bool(__thiscall*)(CPhysical*, CEntity*, CColPoint&, float&))0x5435C0)(this, entity, colPoint, arg2);
}

// Converted from thiscall bool CPhysical::ApplySoftCollision(CEntity *entity,CColPoint &colPoint,float &) 0x543890
bool CPhysical::ApplySoftCollision(CEntity* entity, CColPoint& colPoint, float& arg2)
{
    return ((bool(__thiscall*)(CPhysical*, CEntity*, CColPoint&, float&))0x543890)(this, entity, colPoint, arg2);
}

// Converted from thiscall bool CPhysical::ApplySpringCollision(float,CVector &,CVector &,float,float,float &) 0x543C90
bool CPhysical::ApplySpringCollision(float arg0, CVector& arg1, CVector& arg2, float arg3, float arg4, float& arg5)
{
    return ((bool(__thiscall*)(CPhysical*, float, CVector&, CVector&, float, float, float&))0x543C90)(this, arg0, arg1, arg2, arg3, arg4, arg5);
}

// Converted from thiscall bool CPhysical::ApplySpringCollisionAlt(float,CVector &,CVector &,float,float,CVector &,float &) 0x543D60
bool CPhysical::ApplySpringCollisionAlt(float arg0, CVector& arg1, CVector& arg2, float arg3, float arg4, CVector& arg5, float& arg6)
{
    return ((bool(__thiscall*)(CPhysical*, float, CVector&, CVector&, float, float, CVector&, float&))0x543D60)(this, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

// Converted from thiscall bool CPhysical::ApplySpringDampening(float,float,CVector &,CVector &,CVector &) 0x543E90
bool CPhysical::ApplySpringDampening(float arg0, float arg1, CVector& arg2, CVector& arg3, CVector& arg4)
{
    return ((bool(__thiscall*)(CPhysical*, float, float, CVector&, CVector&, CVector&))0x543E90)(this, arg0, arg1, arg2, arg3, arg4);
}

// Converted from thiscall bool CPhysical::ApplySpringDampeningOld(float,float,CVector &,CVector &,CVector &) 0x544100
bool CPhysical::ApplySpringDampeningOld(float arg0, float arg1, CVector& arg2, CVector& arg3, CVector& arg4)
{
    return ((bool(__thiscall*)(CPhysical*, float, float, CVector&, CVector&, CVector&))0x544100)(this, arg0, arg1, arg2, arg3, arg4);
}

// Converted from thiscall void CPhysical::RemoveRefsToEntity(CEntity *entity) 0x544280
void CPhysical::RemoveRefsToEntity(CEntity* entity)
{
    ((void(__thiscall*)(CPhysical*, CEntity*))0x544280)(this, entity);
}

// Converted from thiscall void CPhysical::DettachEntityFromEntity(float x,float y,float z,bool useCollision) 0x5442F0
void CPhysical::DettachEntityFromEntity(float x, float y, float z, bool useCollision)
{
    ((void(__thiscall*)(CPhysical*, float, float, float, bool))0x5442F0)(this, x, y, z, useCollision);
}

// Converted from thiscall void CPhysical::DettachAutoAttachedEntity(void) 0x5446A0
void CPhysical::DettachAutoAttachedEntity()
{
    ((void(__thiscall*)(CPhysical*))0x5446A0)(this);
}

// Converted from thiscall float CPhysical::GetLightingFromCol(bool flag) 0x5447B0
float CPhysical::GetLightingFromCol(bool flag)
{
    return ((float(__thiscall*)(CPhysical*, bool))0x5447B0)(this, flag);
}

// Converted from thiscall float CPhysical::GetLightingTotal(void) 0x544850
float CPhysical::GetLightingTotal()
{
    return ((float(__thiscall*)(CPhysical*))0x544850)(this);
}

// Converted from thiscall bool CPhysical::CanPhysicalBeDamaged(eWeaponType weapon,uchar *) 0x5448B0
bool CPhysical::CanPhysicalBeDamaged(eWeaponType weapon, unsigned char* arg1)
{
    return ((bool(__thiscall*)(CPhysical*, eWeaponType, unsigned char*))0x5448B0)(this, weapon, arg1);
}

// Converted from thiscall void CPhysical::ApplyAirResistance(void) 0x544C40
void CPhysical::ApplyAirResistance()
{
    ((void(__thiscall*)(CPhysical*))0x544C40)(this);
}

// Converted from thiscall bool CPhysical::ApplyCollisionAlt(CEntity *entity,CColPoint &colPoint,float &,CVector &,CVector &) 0x544D50
bool CPhysical::ApplyCollisionAlt(CEntity* entity, CColPoint& colPoint, float& arg2, CVector& arg3, CVector& arg4)
{
    return ((bool(__thiscall*)(CPhysical*, CEntity*, CColPoint&, float&, CVector&, CVector&))0x544D50)(this, entity, colPoint, arg2, arg3, arg4);
}

// Converted from thiscall bool CPhysical::ApplyFriction(float,CColPoint &colPoint) 0x5454C0
bool CPhysical::ApplyFriction(float arg0, CColPoint& colPoint)
{
    return ((bool(__thiscall*)(CPhysical*, float, CColPoint&))0x5454C0)(this, arg0, colPoint);
}

// Converted from thiscall bool CPhysical::ApplyFriction(CPhysical* physical,float,CColPoint &colPoint) 0x545980
bool CPhysical::ApplyFriction(CPhysical* physical, float arg1, CColPoint& colPoint)
{
    return ((bool(__thiscall*)(CPhysical*, CPhysical*, float, CColPoint&))0x545980)(this, physical, arg1, colPoint);
}

// Converted from thiscall bool CPhysical::ProcessShiftSectorList(int sectorX,int sectorY) 0x546670
bool CPhysical::ProcessShiftSectorList(int sectorX, int sectorY)
{
    //return ((bool(__thiscall*)(CPhysical*, int, int))0x546670)(this, sectorX, sectorY);

    CBaseModelInfo* pModelInfo = CModelInfo::ms_modelInfoPtrs[m_nModelIndex];
    float fBoundingSphereRadius = pModelInfo->m_pColModel->m_boundSphere.m_fRadius;
    float fMaxColPointDepth = 0.0f;
    CVector vecShift;
    CColPoint colPoints[32];
    CVector vecBoundCentre;

    GetBoundCentre(&vecBoundCentre);

    CSector* pSector = GetSector(sectorX, sectorY);
    CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);

    int totalAcceptableColPoints = 0;
    int scanListIndex = 4;
    do
    {
        CPtrListDoubleLink* pDoubleLinkList = nullptr;
        switch (--scanListIndex)
        {
        case 0:
            pDoubleLinkList = &pSector->m_buildings;
            break;
        case 1:
            pDoubleLinkList = &pRepeatSector->m_lists[0];
            break;
        case 2:
            pDoubleLinkList = &pRepeatSector->m_lists[1];
            break;
        case 3:
            pDoubleLinkList = &pRepeatSector->m_lists[2];
            break;
        }
        CPtrNodeDoubleLink* pNode = pDoubleLinkList->GetNode();
        if (pDoubleLinkList->GetNode())
        {
            do
            {
                CPhysical* pEntity = reinterpret_cast<CPhysical*>(pNode->pItem);
                CPed* pPedEntity = static_cast<CPed*>(pEntity);
                CVehicle* pVehicleEntity = static_cast<CVehicle*>(pEntity);
                pNode = pNode->pNext;

                bool bCollisionDisabled = false;
                bool bProcessEntityCollision = true;
                if (pEntity->m_nType != ENTITY_TYPE_BUILDING
                    && (pEntity->m_nType != ENTITY_TYPE_OBJECT || !pEntity->physicalFlags.bDisableCollisionForce))
                {
                    if (m_nType != ENTITY_TYPE_PED || m_nType != ENTITY_TYPE_OBJECT
                        || (!pEntity->m_bIsStatic && !pEntity->m_bIsStaticWaitingForCollision)
                        || pPedEntity->m_pedAudio.m_tempSound.m_nBankSlotId & 0x40)
                    {
                        bProcessEntityCollision = false;
                    }
                }
                if (pEntity != this
                    && pEntity->m_nScanCode != CWorld::ms_nCurrentScanCode
                    && pEntity->m_bUsesCollision && (!m_bHasHitWall || bProcessEntityCollision))
                {
                    if (pEntity->GetIsTouching(&vecBoundCentre, fBoundingSphereRadius))
                    {

                        bool bUnknown1 = false, bUnknown2 = false, bUnknown3 = false;
                        if (pEntity->m_nType == ENTITY_TYPE_BUILDING)
                        {
                            if (physicalFlags.bDisableCollisionForce
                                && (m_nType != ENTITY_TYPE_VEHICLE || pVehicleEntity->m_nVehicleSubClass == VEHICLE_TRAIN))
                            {
                                bCollisionDisabled = true;
                            }
                            else
                            {
                                if (m_pAttachedTo)
                                {
                                    unsigned char attachedEntityType = m_pAttachedTo->m_nType;
                                    if (attachedEntityType > ENTITY_TYPE_BUILDING && attachedEntityType < ENTITY_TYPE_DUMMY
                                        && m_pAttachedTo->physicalFlags.bDisableCollisionForce)
                                    {
                                        bCollisionDisabled = true;
                                    }
                                }
                                else if (m_pEntityIgnoredCollision == pEntity)
                                {
                                    bCollisionDisabled = true;
                                }

                                else if (!physicalFlags.bDisableZ || physicalFlags.bApplyGravity)
                                {
                                    if (physicalFlags.b25)
                                    {
                                        if (m_nStatus)
                                        {
                                            if (m_nStatus != STATUS_HELI && pEntity->DoesNotCollideWithFlyers())
                                            {
                                                bCollisionDisabled = true;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    bCollisionDisabled = true;
                                }
                            }
                        }
                        else
                        {
                            SpecialEntityPreCollisionStuff(pEntity, true, &bCollisionDisabled, &bUnknown1, &bUnknown2, &bUnknown3);
                        }

                        if (m_nType == ENTITY_TYPE_PED)
                        {
                            physicalFlags.b13 = true;
                        }

                        if (!bUnknown1 && !bCollisionDisabled)
                        {

                            pEntity->m_nScanCode = CWorld::ms_nCurrentScanCode;
                            int totalColPointsToProcess = ProcessEntityCollision(pEntity, colPoints);
                            if (totalColPointsToProcess > 0)
                            {
                                for (int colpointIndex = totalColPointsToProcess; colpointIndex > 0; --colpointIndex)
                                {
                                    CColPoint* pColPoint = &colPoints[colpointIndex];
                                    if (pColPoint->m_fDepth > 0.0f)
                                    {
                                        unsigned char pieceTypeB = pColPoint->m_nPieceTypeB;
                                        if (pieceTypeB < 13 || pieceTypeB > 16)
                                        {
                                            totalAcceptableColPoints++;
                                            if (m_nType == ENTITY_TYPE_VEHICLE && pEntity->m_nType == ENTITY_TYPE_PED
                                                && pColPoint->m_vecNormal.z < 0.0f)
                                            {
                                                vecShift.x += pColPoint->m_vecNormal.x;
                                                vecShift.y += pColPoint->m_vecNormal.y;
                                                vecShift.z += pColPoint->m_vecNormal.z * 0.0f;
                                                fMaxColPointDepth = std::max(fMaxColPointDepth, pColPoint->m_fDepth);
                                            }
                                            else
                                            {
                                                if (m_nType != ENTITY_TYPE_PED || pEntity->m_nType != ENTITY_TYPE_OBJECT
                                                    || !pEntity->physicalFlags.bDisableMoveForce
                                                    || fabs(pColPoint->m_vecNormal.z) <= 0.1f)
                                                {
                                                    vecShift += pColPoint->m_vecNormal;
                                                    fMaxColPointDepth = std::max(fMaxColPointDepth, pColPoint->m_fDepth);
                                                }
                                            }
                                        }
                                    }

                                }
                            }
                        }
                    }
                }
            } while (pNode);
        }
    } while (scanListIndex);

    if (totalAcceptableColPoints == 0)
    {
        return false;
    }

    float shiftMagnitude = vecShift.Magnitude();
    if (shiftMagnitude > 1.0f)
    {   // normalize the shift boi
        float shiftMultiplier = 1.0f / shiftMagnitude;
        vecShift *= shiftMultiplier;
    }

    CVector& vecEntityPosition = GetPosition();
    if (vecShift.z >= -0.5f)
    {
        if (m_nType != ENTITY_TYPE_PED)
        {
            vecEntityPosition += vecShift * fMaxColPointDepth * 1.5f;
        }
        else
        {
            float fDepthMultiplied = 1.5f * fMaxColPointDepth;
            if (fDepthMultiplied >= 0.0049999999)
            {
                if (fDepthMultiplied > 0.30000001)
                {
                    vecEntityPosition += vecShift * fMaxColPointDepth * 0.3f;
                }
            }
            else
            {
                vecEntityPosition += vecShift * fMaxColPointDepth * 0.0049999999f;
            }

            vecEntityPosition += vecShift * fDepthMultiplied;
        }
    }
    else
    {
        vecEntityPosition += vecShift * fMaxColPointDepth * 0.75f;
    }

    if (m_nType != ENTITY_TYPE_VEHICLE || 1.5f <= 0.0f)
    {
        return true;
    }

    if (vecShift.z < 0.0)
    {
        vecShift.z = 0.0;
    }

    m_vecMoveSpeed += vecShift * 0.0080000004f * CTimer::ms_fTimeStep;
    return true;
}

// Converted from stdcall void CPhysical::PlacePhysicalRelativeToOtherPhysical(CPhysical* physical1,CPhysical* physical2,CVector offset) 0x546DB0
void CPhysical::PlacePhysicalRelativeToOtherPhysical(CPhysical* physical1, CPhysical* physical2, CVector offset)
{
    ((void(__cdecl*)(CPhysical*, CPhysical*, CVector))0x546DB0)(physical1, physical2, offset);
}

// Converted from thiscall float CPhysical::ApplyScriptCollision(CVector,float,float,CVector*) 0x546ED0
float CPhysical::ApplyScriptCollision(CVector arg0, float arg1, float arg2, CVector* arg3)
{
    return ((float(__thiscall*)(CPhysical*, CVector, float, float, CVector*))0x546ED0)(this, arg0, arg1, arg2, arg3);
}

// Converted from thiscall void CPhysical::PositionAttachedEntity(void) 0x546FF0
void CPhysical::PositionAttachedEntity()
{
    ((void(__thiscall*)(CPhysical*))0x546FF0)(this);
}

// Converted from thiscall void CPhysical::ApplySpeed(void) 0x547B80
void CPhysical::ApplySpeed()
{
    ((void(__thiscall*)(CPhysical*))0x547B80)(this);
}

// Converted from thiscall void CPhysical::UnsetIsInSafePosition(void) 0x548320
void CPhysical::UnsetIsInSafePosition()
{
    ((void(__thiscall*)(CPhysical*))0x548320)(this);
}

// Converted from thiscall void CPhysical::ApplyFriction(void) 0x5483D0
void CPhysical::ApplyFriction()
{
    ((void(__thiscall*)(CPhysical*))0x5483D0)(this);
}

// Converted from thiscall bool CPhysical::ApplyCollision(CPhysical* physical,CColPoint &colPoint,float &,float &) 0x548680
bool CPhysical::ApplyCollision(CPhysical* physical, CColPoint& colPoint, float& arg2, float& arg3)
{
    return ((bool(__thiscall*)(CPhysical*, CPhysical*, CColPoint&, float&, float&))0x548680)(this, physical, colPoint, arg2, arg3);
}

// Converted from thiscall bool CPhysical::ApplySoftCollision(CPhysical* physical,CColPoint &colPoint,float &,float &) 0x54A2C0
bool CPhysical::ApplySoftCollision(CPhysical* physical, CColPoint& colPoint, float& arg2, float& arg3)
{
    return ((bool(__thiscall*)(CPhysical*, CPhysical*, CColPoint&, float&, float&))0x54A2C0)(this, physical, colPoint, arg2, arg3);
}

// Converted from thiscall bool CPhysical::ProcessCollisionSectorList(int sectorX,int sectorY) 0x54BA60
bool CPhysical::ProcessCollisionSectorList(int sectorX, int sectorY)
{
    return ((bool(__thiscall*)(CPhysical*, int, int))0x54BA60)(this, sectorX, sectorY);
}

// Converted from thiscall bool CPhysical::ProcessCollisionSectorList_SimpleCar(CRepeatSector *sector) 0x54CFF0
bool CPhysical::ProcessCollisionSectorList_SimpleCar(CRepeatSector* sector)
{
    return ((bool(__thiscall*)(CPhysical*, CRepeatSector*))0x54CFF0)(this, sector);
}

// Converted from thiscall void CPhysical::AttachEntityToEntity(CEntity *entity,CVector offset,CVector rotation) 0x54D570
void CPhysical::AttachEntityToEntity(CEntity* entity, CVector offset, CVector rotation)
{
    ((void(__thiscall*)(CPhysical*, CEntity*, CVector, CVector))0x54D570)(this, entity, offset, rotation);
}

// Converted from thiscall void CPhysical::AttachEntityToEntity(CEntity *entity,CVector *offset,RtQuat *rotation) 0x54D690
void CPhysical::AttachEntityToEntity(CEntity* entity, CVector* offset, RtQuat* rotation)
{
    ((void(__thiscall*)(CPhysical*, CEntity*, CVector*, RtQuat*))0x54D690)(this, entity, offset, rotation);
}

// Converted from thiscall bool CPhysical::CheckCollision(void) 0x54D920
bool CPhysical::CheckCollision()
{
    return ((bool(__thiscall*)(CPhysical*))0x54D920)(this);
}

// Converted from thiscall bool CPhysical::CheckCollision_SimpleCar(void) 0x54DAB0
bool CPhysical::CheckCollision_SimpleCar()
{
    return ((bool(__thiscall*)(CPhysical*))0x54DAB0)(this);
}