/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "RenderWare.h"
#include "CColModel.h"
#include "C2dEffect.h"
#include "eModelID.h"

enum RwModelInfoType
{
    RWMODEL_INFO_ATOMIC = 1,
    RWMODEL_INFO_CLUMP = 2
};

enum ModelInfoType : unsigned char
{
	MODEL_INFO_ATOMIC = 1,
	MODEL_INFO_TIME = 3,
	MODEL_INFO_WEAPON = 4,
	MODEL_INFO_CLUMP = 5,
	MODEL_INFO_VEHICLE = 6,
	MODEL_INFO_PED = 7,
	MODEL_INFO_LOD = 8
};

struct tTimeInfo
{
	unsigned char m_nTimeOn;
	unsigned char m_nTimeOff;
	signed short  m_wOtherTimeModel;
};

VALIDATE_SIZE(tTimeInfo, 4);

class CVehicleModelInfo;

// originally an abstract class
class  CBaseModelInfo {
public:
	unsigned int   m_nKey;
	unsigned short m_nRefCount;
	short          m_nTxdIndex;
	unsigned char  m_nAlpha; 
	unsigned char  m_n2dfxCount;
    short          m_n2dEffectIndex;
    short          m_nObjectInfoIndex;
	union{
        unsigned short m_nFlags;
        struct {
            unsigned char m_nFlagsUpperByte;
            unsigned char m_nFlagsLowerByte;
        };
		struct{
			/* https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CModelInfoSA.h */
			unsigned char bHasBeenPreRendered : 1; // we use this because we need to apply changes only once
			unsigned char bDrawLast: 1;
			unsigned char bAdditiveRender: 1;
			unsigned char bDontWriteZBuffer: 1;
			unsigned char bDontCastShadowsOn : 1;
			unsigned char bDoWeOwnTheColModel : 1;
			unsigned char bIsBackfaceCulled : 1;
			unsigned char bIsLod : 1;

			union{
				struct{
					unsigned char bIsRoad: 1;
					unsigned char bHasComplexHierarchy : 1;
					unsigned char bDontCollideWithFlyer : 1;
					unsigned char nSpecialType : 4;
					unsigned char bWetRoadReflection : 1;
				};
				struct{
					unsigned char : 2;
					unsigned char nCarmodId : 5;
					unsigned char : 1; // bUseCommonVehicleDictionary
				};
			};
			
		};
	};
	CColModel        *m_pColModel; // 20
	float             m_fDrawDistance; // 24
	struct RwObject  *m_pRwObject; // 28

	// vtable
	virtual CBaseModelInfo* DeletingDestructor(uint8_t deletingFlags);
	virtual class CAtomicModelInfo*AsAtomicModelInfoPtr();
    virtual class CDamagableModelInfo*AsDamageAtomicModelInfoPtr();
    virtual class CBaseModelInfo *AsLodAtomicModelInfoPtr();
    virtual ModelInfoType GetModelType();//=0
    virtual tTimeInfo *GetTimeInfo();
    virtual void Init();
    virtual void Shutdown();
    virtual void DeleteRwObject();//=0
    virtual unsigned int GetRwModelType();//=0
    virtual struct RwObject *CreateInstance(RwMatrix *matrix);//=0
    virtual struct RwObject *CreateInstance();//=0
    virtual void SetAnimFile(char *filename);
    virtual void ConvertAnimFileIndex();
    virtual signed int GetAnimFileIndex();

	//
	void SetTexDictionary(const char* txdName);
	void ClearTexDictionary();
	void AddTexDictionaryRef();
	void RemoveTexDictionaryRef();
	void AddRef();
	void RemoveRef();
	// initPairedModel defines if we need to set col model for time model
	void SetColModel(CColModel *colModel, bool initPairedModel);
	void Init2dEffects();
	void DeleteCollisionModel();
	// index is a number of effect (max number is (m_n2dfxCount - 1))
	C2dEffect *Get2dEffect(int index);
	void Add2dEffect(C2dEffect *effect);

    	virtual ~CBaseModelInfo() {}
	CBaseModelInfo();  // constructor
	
	bool GetIsDrawLast();
	bool HasBeenPreRendered();
	bool HasComplexHierarchy();
	bool IsBackfaceCulled();
	bool IsBreakableStatuePart();
	bool IsLod();
	bool IsRoad();
	bool IsTagModel();
	bool SwaysInWind();
	void SetHasBeenPreRendered(int bHasBeenPreRendered);
	void SetIsLod(int bIsLod);
	void SetOwnsColModel(int bOwns);
	void IncreaseAlpha();

    CVehicleModelInfo* AsVehicleModelInfoPtr() { return reinterpret_cast<CVehicleModelInfo*>(this); }
    inline CColModel* GetColModel() { return m_pColModel; }
};

VALIDATE_SIZE(CBaseModelInfo, 0x20);
