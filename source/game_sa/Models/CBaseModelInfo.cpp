/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

CBaseModelInfo* CBaseModelInfo::DeletingDestructor(uint8_t deletingFlags)
{
    return((CBaseModelInfo * (__thiscall*)(CBaseModelInfo*, uint8_t))plugin::GetVMT(this, 0))(this, deletingFlags);
}

CAtomicModelInfo* CBaseModelInfo::AsAtomicModelInfoPtr()
{
    return ((CAtomicModelInfo * (__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 1))(this);
}

CDamagableModelInfo* CBaseModelInfo::AsDamageAtomicModelInfoPtr()
{
    return ((CDamagableModelInfo *(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 2))(this);
}

CBaseModelInfo *CBaseModelInfo::AsLodAtomicModelInfoPtr()
{
    return ((CBaseModelInfo *(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 3))(this);
}

ModelInfoType CBaseModelInfo::GetModelType()
{
    return ((ModelInfoType(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 4))(this);
}

struct tTimeInfo *CBaseModelInfo::GetTimeInfo()
{
    return ((struct tTimeInfo *(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 5))(this);
}

void CBaseModelInfo::Init()
{
    ((void(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 6))(this);
}

void CBaseModelInfo::Shutdown()
{
    ((void(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 7))(this);
}

void CBaseModelInfo::DeleteRwObject()
{
    ((void(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 8))(this);
}

unsigned int CBaseModelInfo::GetRwModelType()
{
    return ((unsigned int(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 9))(this);
}

RwObject *CBaseModelInfo::CreateInstance(RwMatrix *matrix)
{
    return ((RwObject *(__thiscall *)(CBaseModelInfo *, RwMatrix *))plugin::GetVMT(this, 10))(this, matrix);
}

RwObject *CBaseModelInfo::CreateInstance()
{
    return ((RwObject *(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 11))(this);
}

void CBaseModelInfo::SetAnimFile(char *filename)
{
    ((void(__thiscall *)(CBaseModelInfo *, char *))plugin::GetVMT(this, 12))(this, filename);
}

void CBaseModelInfo::ConvertAnimFileIndex()
{
    ((void(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 13))(this);
}

signed int CBaseModelInfo::GetAnimFileIndex()
{
    return ((signed int(__thiscall *)(CBaseModelInfo *))plugin::GetVMT(this, 14))(this);
}

void CBaseModelInfo::SetTexDictionary(const char *txdName)
{
    ((void(__thiscall *)(CBaseModelInfo *, const char*))0x4C4B40)(this, txdName);
}

void CBaseModelInfo::ClearTexDictionary()
{
    ((void(__thiscall *)(CBaseModelInfo *))0x4C4B70)(this);
}

void CBaseModelInfo::AddTexDictionaryRef()
{
    ((void(__thiscall *)(CBaseModelInfo *))0x4C4B80)(this);
}

void CBaseModelInfo::RemoveTexDictionaryRef()
{
    ((void(__thiscall *)(CBaseModelInfo *))0x4C4B90)(this);
}

void CBaseModelInfo::AddRef()
{
    ((void(__thiscall *)(CBaseModelInfo *))0x4C4BA0)(this);
}

void CBaseModelInfo::RemoveRef()
{
    ((void(__thiscall *)(CBaseModelInfo *))0x4C4BB0)(this);
}

void CBaseModelInfo::SetColModel(CColModel *colModel, bool initPairedModel)
{
    ((void(__thiscall *)(CBaseModelInfo *, CColModel *, bool))0x4C4BC0)(this, colModel, initPairedModel);
}

void CBaseModelInfo::Init2dEffects()
{
    ((void(__thiscall *)(CBaseModelInfo *))0x4C4C20)(this);
}

void CBaseModelInfo::DeleteCollisionModel()
{
    ((void(__thiscall *)(CBaseModelInfo *))0x4C4C40)(this);
}

C2dEffect *CBaseModelInfo::Get2dEffect(int index)
{
    return ((C2dEffect *(__thiscall *)(CBaseModelInfo *, int))0x4C4C70)(this, index);
}

void CBaseModelInfo::Add2dEffect(C2dEffect *effect)
{
    ((void(__thiscall *)(CBaseModelInfo *, C2dEffect *))0x4C4D20)(this, effect);
}

CBaseModelInfo::CBaseModelInfo()
{
    ((void(__thiscall *)(CBaseModelInfo *))0x4C4A60)(this);
}

// Converted from thiscall bool CBaseModelInfo::GetIsDrawLast(void) 0x5328C0
bool CBaseModelInfo::GetIsDrawLast() {
    return plugin::CallMethodAndReturn<bool, 0x5328C0, CBaseModelInfo *>(this);
}

// Converted from thiscall bool CBaseModelInfo::HasBeenPreRendered(void) 0x5328B0
bool CBaseModelInfo::HasBeenPreRendered() {
    return plugin::CallMethodAndReturn<bool, 0x5328B0, CBaseModelInfo *>(this);
}

// Converted from thiscall bool CBaseModelInfo::HasComplexHierarchy(void) 0x4C4E00
bool CBaseModelInfo::HasComplexHierarchy() {
    return plugin::CallMethodAndReturn<bool, 0x4C4E00, CBaseModelInfo *>(this);
}

// Converted from thiscall bool CBaseModelInfo::IsBackfaceCulled(void) 0x5328F0
bool CBaseModelInfo::IsBackfaceCulled() {
    return plugin::CallMethodAndReturn<bool, 0x5328F0, CBaseModelInfo *>(this);
}

// Converted from thiscall bool CBaseModelInfo::IsBreakableStatuePart(void) 0x59F090
bool CBaseModelInfo::IsBreakableStatuePart() {
    return plugin::CallMethodAndReturn<bool, 0x59F090, CBaseModelInfo *>(this);
}

// Converted from thiscall bool CBaseModelInfo::IsLod(void) 0x4C4A00
bool CBaseModelInfo::IsLod() {
    return plugin::CallMethodAndReturn<bool, 0x4C4A00, CBaseModelInfo *>(this);
}

// Converted from thiscall bool CBaseModelInfo::IsRoad(void) 0x4C4DF0
bool CBaseModelInfo::IsRoad() {
    return plugin::CallMethodAndReturn<bool, 0x4C4DF0, CBaseModelInfo *>(this);
}

// Converted from thiscall bool CBaseModelInfo::IsTagModel(void) 0x49CC20
bool CBaseModelInfo::IsTagModel() {
    return plugin::CallMethodAndReturn<bool, 0x49CC20, CBaseModelInfo *>(this);
}

// Converted from thiscall bool CBaseModelInfo::SwaysInWind(void) 0x4212C0	
bool CBaseModelInfo::SwaysInWind() {
    return plugin::CallMethodAndReturn<bool, 0x4212C0, CBaseModelInfo *>(this);
}

// Converted from thiscall void CBaseModelInfo::SetHasBeenPreRendered(int bHasBeenPreRendered) 0x4C42F0
void CBaseModelInfo::SetHasBeenPreRendered(int bHasBeenPreRendered) {
    plugin::CallMethod<0x4C42F0, CBaseModelInfo *, int>(this, bHasBeenPreRendered);
}

// Converted from thiscall void CBaseModelInfo::SetIsLod(int bIsLod) 0x4C4A10
void CBaseModelInfo::SetIsLod(int bIsLod) {
    plugin::CallMethod<0x4C4A10, CBaseModelInfo *, int>(this, bIsLod);
}

// Converted from thiscall void CBaseModelInfo::SetOwnsColModel(int bOwns) 0x5328D0
void CBaseModelInfo::SetOwnsColModel(int bOwns) {
    plugin::CallMethod<0x5328D0, CBaseModelInfo *, int>(this, bOwns);
}

// Converted from thiscall void CBaseModelInfo::IncreaseAlpha(void) 0x532900
void CBaseModelInfo::IncreaseAlpha() {
    plugin::CallMethod<0x532900, CBaseModelInfo *>(this);
}
