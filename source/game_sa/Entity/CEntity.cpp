/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

// vtable functions

void CEntity::Add(CRect &rect)
{
    ((void(__thiscall *)(CEntity *, CRect &))(unsigned int)(*(void ***)this)[1])(this, rect);
}

void CEntity::Add()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[2])(this);
}

void CEntity::Remove()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[3])(this);
}

void CEntity::SetIsStatic(bool isStatic)
{
    ((void(__thiscall *)(CEntity *, bool))(*(void ***)this)[4])(this, isStatic);
}

void CEntity::SetModelIndex(unsigned int index)
{
    ((void(__thiscall *)(CEntity *, unsigned int))(*(void ***)this)[5])(this, index);
}

void CEntity::SetModelIndexNoCreate(unsigned int index)
{
    ((void(__thiscall *)(CEntity *, unsigned int))(*(void ***)this)[6])(this, index);
}

void CEntity::CreateRwObject()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[7])(this);
}

void CEntity::DeleteRwObject()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[8])(this);
}

CRect CEntity::GetBoundRect()
{
    return ((CRect(__thiscall *)(CEntity *))(*(void ***)this)[9])(this);
}

void CEntity::ProcessControl()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[10])(this);
}

void CEntity::ProcessCollision()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[11])(this);
}

void CEntity::ProcessShift()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[12])(this);
}

bool CEntity::TestCollision()
{
    return ((bool(__thiscall *)(CEntity *))(*(void ***)this)[13])(this);
}

void CEntity::Teleport(CVector destination, bool resetRotation)
{
    ((void(__thiscall *)(CEntity *, CVector, bool))(*(void ***)this)[14])(this, destination, resetRotation);
}

void CEntity::SpecialEntityPreCollisionStuff(CEntity *colEntity, bool unk1, unsigned char *unk2, unsigned char *unk3, unsigned char *unk4, unsigned char *unk5)
{
    ((void(__thiscall *)(CEntity *, CEntity *, bool, unsigned char *, unsigned char *, unsigned char *, unsigned char *))(*(void ***)this)[15])(this, colEntity, unk1, unk2, unk3, unk4, unk5);
}

void CEntity::SpecialEntityCalcCollisionSteps(unsigned char *unk1, unsigned char *unk2)
{
    ((void(__thiscall *)(CEntity *, unsigned char *, unsigned char *))(*(void ***)this)[16])(this, unk1, unk2);
}

void CEntity::PreRender()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[17])(this);
}

void CEntity::Render()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[18])(this);
}

bool CEntity::SetupLighting()
{
    return ((bool(__thiscall *)(CEntity *))(*(void ***)this)[19])(this);
}

void CEntity::RemoveLighting()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[20])(this);
}

void CEntity::FlagToDestroyWhenNextProcessed()
{
    ((void(__thiscall *)(CEntity *))(*(void ***)this)[21])(this);
}

// Converted from thiscall void CEntity::UpdateRwFrame(void) 0x532B00
void CEntity::UpdateRwFrame()
{
    ((void(__thiscall *)(CEntity*))0x532B00)(this);
}

// Converted from thiscall void CEntity::UpdateRpHAnim(void) 0x532B20
void CEntity::UpdateRpHAnim()
{
    ((void(__thiscall *)(CEntity*))0x532B20)(this);
}

// Converted from thiscall bool CEntity::HasPreRenderEffects(void) 0x532B70
bool CEntity::HasPreRenderEffects()
{
    return ((bool(__thiscall *)(CEntity*))0x532B70)(this);
}

// Converted from thiscall bool CEntity::DoesNotCollideWithFlyers(void) 0x532D40
bool CEntity::DoesNotCollideWithFlyers()
{
    return ((bool(__thiscall *)(CEntity*))0x532D40)(this);
}

// Converted from stdcall RpMaterial* MaterialUpdateUVAnimCB(RpMaterial *material,void *data) 0x532D70
RpMaterial* MaterialUpdateUVAnimCB(RpMaterial* material, void* data)
{
    return ((RpMaterial* (__cdecl *)(RpMaterial*, void*))0x532D70)(material, data);
}

// Converted from thiscall void CEntity::ModifyMatrixForPoleInWind(void) 0x532DB0
void CEntity::ModifyMatrixForPoleInWind()
{
    ((void(__thiscall *)(CEntity*))0x532DB0)(this);
}

// Converted from thiscall bool CEntity::LivesInThisNonOverlapSector(int sectorX,int sectorY) 0x533050
bool CEntity::LivesInThisNonOverlapSector(int sectorX, int sectorY)
{
    return ((bool(__thiscall *)(CEntity*, int, int))0x533050)(this, sectorX, sectorY);
}

// Converted from thiscall void CEntity::SetupBigBuilding(void) 0x533150
void CEntity::SetupBigBuilding()
{
    ((void(__thiscall *)(CEntity*))0x533150)(this);
}

// Converted from thiscall void CEntity::ModifyMatrixForCrane(void) 0x533170
void CEntity::ModifyMatrixForCrane()
{
    ((void(__thiscall *)(CEntity*))0x533170)(this);
}

// Converted from thiscall void CEntity::PreRenderForGlassWindow(void) 0x533240
void CEntity::PreRenderForGlassWindow()
{
    ((void(__thiscall *)(CEntity*))0x533240)(this);
}

// Converted from thiscall void CEntity::SetRwObjectAlpha(int alpha) 0x5332C0
void CEntity::SetRwObjectAlpha(int alpha)
{
    ((void(__thiscall *)(CEntity*, int))0x5332C0)(this, alpha);
}

// Converted from stdcall bool IsEntityPointerValid(CEntity *entity) 0x533310
bool IsEntityPointerValid(CEntity* entity)
{
    return ((bool(__cdecl *)(CEntity*))0x533310)(entity);
}

// Converted from thiscall CVector CEntity::FindTriggerPointCoors(int triggerIndex) 0x533380
CVector CEntity::FindTriggerPointCoors(int triggerIndex)
{
    CVector result;
    ((void(__thiscall *)(CEntity*, CVector*, int))0x533380)(this, &result, triggerIndex);
    return result;
}

// Converted from thiscall C2dEffect* CEntity::GetRandom2dEffect(int effectType,uchar) 0x533410
C2dEffect* CEntity::GetRandom2dEffect(int effectType, unsigned char arg1)
{
    return ((C2dEffect* (__thiscall *)(CEntity*, int, unsigned char))0x533410)(this, effectType, arg1);
}

// Converted from thiscall CVector CEntity::TransformFromObjectSpace(CVector const &offset) 0x5334F0
CVector CEntity::TransformFromObjectSpace(CVector const& offset)
{
    CVector result;
    ((void(__thiscall *)(CEntity*, CVector*, CVector const&))0x5334F0)(this, &result, offset);
    return result;
}

// Converted from thiscall void CEntity::TransformFromObjectSpace(CVector &outPosn,CVector const &offset) 0x533560
void CEntity::TransformFromObjectSpace(CVector& outPosn, CVector const& offset)
{
    ((void(__thiscall *)(CEntity*, CVector&, CVector const&))0x533560)(this, outPosn, offset);
}

// Converted from thiscall void CEntity::CreateEffects(void) 0x533790
void CEntity::CreateEffects()
{
    ((void(__thiscall *)(CEntity*))0x533790)(this);
}

// Converted from thiscall void CEntity::DestroyEffects(void) 0x533BF0
void CEntity::DestroyEffects()
{
    ((void(__thiscall *)(CEntity*))0x533BF0)(this);
}

// Converted from thiscall void CEntity::AttachToRwObject(RwObject *object, bool updateEntityMatrix) 0x533ED0
void CEntity::AttachToRwObject(RwObject* object, bool updateEntityMatrix)
{
    ((void(__thiscall *)(CEntity*, RwObject*, bool))0x533ED0)(this, object, updateEntityMatrix);
}

// Converted from thiscall void CEntity::DetachFromRwObject(void) 0x533FB0
void CEntity::DetachFromRwObject()
{
    ((void(__thiscall *)(CEntity*))0x533FB0)(this);
}

// Converted from thiscall CVector CEntity::GetBoundCentre(void) 0x534250
CVector CEntity::GetBoundCentre()
{
    CVector result;
    ((void(__thiscall *)(CEntity*, CVector*))0x534250)(this, &result);
    return result;
}

// Converted from thiscall void CEntity::GetBoundCentre(CVector &outCentre) 0x534290
void CEntity::GetBoundCentre(CVector& outCentre)
{
    ((void(__thiscall *)(CEntity*, CVector&))0x534290)(this, outCentre);
}

// Converted from thiscall void CEntity::RenderEffects(void) 0x5342B0
void CEntity::RenderEffects()
{
    ((void(__thiscall *)(CEntity*))0x5342B0)(this);
}

// Converted from thiscall bool CEntity::GetIsTouching(CEntity *entity) 0x5343F0
bool CEntity::GetIsTouching(CEntity* entity)
{
    return ((bool(__thiscall *)(CEntity*, CEntity*))0x5343F0)(this, entity);
}

// Converted from thiscall bool CEntity::GetIsTouching(CVector const &centre,float radius) 0x5344B0
bool CEntity::GetIsTouching(CVector const& centre, float radius)
{
    return ((bool(__thiscall *)(CEntity*, CVector const&, float))0x5344B0)(this, centre, radius);
}

// Converted from thiscall bool CEntity::GetIsOnScreen(void) 0x534540
bool CEntity::GetIsOnScreen()
{
    return ((bool(__thiscall *)(CEntity*))0x534540)(this);
}

// Converted from thiscall bool CEntity::GetIsBoundingBoxOnScreen(void) 0x5345D0
bool CEntity::GetIsBoundingBoxOnScreen()
{
    return ((bool(__thiscall *)(CEntity*))0x5345D0)(this);
}

// Converted from thiscall void CEntity::ModifyMatrixForTreeInWind(void) 0x534E90
void CEntity::ModifyMatrixForTreeInWind()
{
    ((void(__thiscall *)(CEntity*))0x534E90)(this);
}

// Converted from thiscall void CEntity::ModifyMatrixForBannerInWind(void) 0x535040
void CEntity::ModifyMatrixForBannerInWind()
{
    ((void(__thiscall *)(CEntity*))0x535040)(this);
}

// Converted from thiscall CColModel* CEntity::GetColModel(void) 0x535300
CColModel* CEntity::GetColModel()
{
    return ((CColModel* (__thiscall *)(CEntity*))0x535300)(this);
}

// Converted from thiscall void CEntity::CalculateBBProjection(CVector *,CVector *,CVector *,CVector *) 0x535340
void CEntity::CalculateBBProjection(CVector* arg0, CVector* arg1, CVector* arg2, CVector* arg3)
{
    ((void(__thiscall *)(CEntity*, CVector*, CVector*, CVector*, CVector*))0x535340)(this, arg0, arg1, arg2, arg3);
}

// Converted from thiscall void CEntity::UpdateAnim(void) 0x535F00
void CEntity::UpdateAnim()
{
    ((void(__thiscall *)(CEntity*))0x535F00)(this);
}

// Converted from thiscall bool CEntity::IsVisible(void) 0x536BC0
bool CEntity::IsVisible()
{
    return ((bool(__thiscall *)(CEntity*))0x536BC0)(this);
}

// Converted from thiscall float CEntity::GetDistanceFromCentreOfMassToBaseOfModel(void) 0x536BE0
float CEntity::GetDistanceFromCentreOfMassToBaseOfModel()
{
    return ((float(__thiscall *)(CEntity*))0x536BE0)(this);
}

// Converted from thiscall void CEntity::CleanUpOldReference(CEntity** entity) 0x571A00
void CEntity::CleanUpOldReference(CEntity** entity)
{
    ((void(__thiscall *)(CEntity*, CEntity**))0x571A00)(this, entity);
}

// Converted from thiscall void CEntity::ResolveReferences(void) 0x571A40
void CEntity::ResolveReferences()
{
    ((void(__thiscall *)(CEntity*))0x571A40)(this);
}

// Converted from thiscall void CEntity::PruneReferences(void) 0x571A90
void CEntity::PruneReferences()
{
    ((void(__thiscall *)(CEntity*))0x571A90)(this);
}

// Converted from thiscall void CEntity::RegisterReference(CEntity** entity) 0x571B70
void CEntity::RegisterReference(CEntity** entity)
{
    ((void(__thiscall *)(CEntity*, CEntity**))0x571B70)(this, entity);
}

// Converted from thiscall void CEntity::ProcessLightsForEntity(void) 0x6FC7A0
void CEntity::ProcessLightsForEntity()
{
    ((void(__thiscall *)(CEntity*))0x6FC7A0)(this);
}

// Converted from thiscall void CEntity::RemoveEscalatorsForEntity(void) 0x717900
void CEntity::RemoveEscalatorsForEntity()
{
    ((void(__thiscall *)(CEntity*))0x717900)(this);
}

// Converted from thiscall bool CEntity::IsEntityOccluded(void) 0x71FAE0
bool CEntity::IsEntityOccluded()
{
    return ((bool(__thiscall *)(CEntity*))0x71FAE0)(this);
}