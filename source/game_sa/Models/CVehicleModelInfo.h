/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CClumpModelInfo.h"
#include "RenderWare.h"
#include "CVector.h"
#include "CQuaternion.h"
#include "RwObjectNameIdAssocation.h"
#include "CRGBA.h"
#include "CPool.h"

// enum by forkerer (https://github.com/forkerer/)
enum eVehicleDummies
{
    DUMMY_LIGHT_FRONT_MAIN = 0x0,
    DUMMY_LIGHT_REAR_MAIN = 0x1,
    DUMMY_LIGHT_FRONT_SECONDARY = 0x2,
    DUMMY_LIGHT_REAR_SECONDARY = 0x3,
    DUMMY_SEAT_FRONT = 0x4,
    DUMMY_SEAT_REAR = 0x5,
    DUMMY_EXHAUST = 0x6,
    DUMMY_ENGINE = 0x7,
    DUMMY_GAS_CAP = 0x8,
    DUMMY_TRAILER_ATTACH = 0x9,
    DUMMY_HAND_REST = 0xA,
    DUMMY_EXHAUST_SECONDARY = 0xB,
    DUMMY_WING_AIRTRAIL = 0xC,
    DUMMY_VEH_GUN = 0xD,
};

enum VehicleUpgradePosn {
	UPGRADE_BONNET,
	UPGRADE_BONNET_LEFT,
	UPGRADE_BONNET_RIGHT,
	UPGRADE_BONNET_DAM,
	UPGRADE_BONNET_LEFT_DAM,
	UPGRADE_BONNET_RIGHT_DAM,
	UPGRADE_SPOILER,
	UPGRADE_SPOILER_DAM,
	UPGRADE_WING_LEFT,
	UPGRADE_WING_RIGHT,
	UPGRADE_FRONTBULLBAR,
	UPGRADE_BACKBULLBAR,
	UPGRADE_LIGHTS,
	UPGRADE_LIGHTS_DAM,
	UPGRADE_ROOF,
	UPGRADE_NITRO,
};

struct  UpgradePosnDesc {
	CVector m_vPosition;
	CQuaternion m_qRotation;
	int m_nParentComponentId;
};

VALIDATE_SIZE(UpgradePosnDesc, 0x20);

class CVehicleModelInfo : public CClumpModelInfo {
public:
	RpMaterial *m_pPlateMaterial;
	char m_szPlateText[8];
	char field_30;
	unsigned char m_nPlateType;
	char m_szGameName[8];
private:
	char _pad3A[2];
public:
	unsigned int m_nVehicleType;
	float m_fWheelSizeFront;
	float m_fWheelSizeRear;
	short m_nWheelModelIndex;
	unsigned short m_nHandlingId;
	unsigned char m_nNumDoors;
	unsigned char m_nVehicleClass; // see eVehicleClass
	unsigned char m_nFlags;
	unsigned char m_nWheelUpgradeClass;
	unsigned char m_nTimesUsed;
    char field_51;
	unsigned short m_nFrq;
	union{
		unsigned int m_nCompRules;
		struct{
			unsigned int nExtraA_comp1 : 4;
			unsigned int nExtraA_comp2 : 4;
			unsigned int nExtraA_comp3 : 4;
			unsigned int nExtraA_rule : 4;
			unsigned int nExtraB_comp1 : 4;
			unsigned int nExtraB_comp2 : 4;
			unsigned int nExtraB_comp3 : 4;
			unsigned int nExtraB_rule : 4;
		} m_nCompRulesBits;
	};
	float m_fBikeSteerAngle;

	class CVehicleStructure {
	public:
		CVector m_avDummyPos[15];
		UpgradePosnDesc m_aUpgrades[18];
		RpAtomic *m_apExtras[6];
		unsigned char m_nNumExtras;
		unsigned int m_nMaskComponentsDamagable;
		static CPool<CVehicleStructure> *&m_pInfoPool;

        CVehicleStructure* Constructor();
	} *m_pVehicleStruct;

	char field_60[464];
	RpMaterial *m_apDirtMaterials[32];
	unsigned char m_anPrimaryColors[8];
	unsigned char m_anSecondaryColors[8];
	unsigned char m_anTertiaryColors[8];
	unsigned char m_anQuaternaryColors[8];
	unsigned char m_nNumColorVariations;
	unsigned char m_nLastColorVariation;
	unsigned char m_nCurrentPrimaryColor;
	unsigned char m_nCurrentSecondaryColor;
	unsigned char m_nCurrentTertiaryColor;
	unsigned char m_nCurrentQuaternaryColor;
	short m_anUpgrades[18];
	short m_anRemapTxds[4];
private:
    char _pad302[2];
public:
	class CAnimBlock *m_pAnimBlock;

	static class CLinkedUpgradeList{
	public:
		short m_anUpgrade1[30];
		short m_anUpgrade2[30];
		unsigned int m_nLinksCount;
		// add upgrade with components upgrade1 and upgrade2
		void AddUpgradeLink(std::int16_t upgrade1, std::int16_t upgrade2);
		// find linked upgrade for this upgrade. In this case upgrade param could be upgrade1 or 
		// upgrade2
        std::int16_t FindOtherUpgrade(std::int16_t upgrade);
	} &ms_linkedUpgrades;

	// vehicle components description tables
	// static RwObjectNameIdAssocation ms_vehicleDescs[12];
	static RwObjectNameIdAssocation** ms_vehicleDescs;

	// remap texture
	static RwTexture *ms_pRemapTexture;
	// vehiclelights128 texture
	static RwTexture *ms_pLightsTexture;
	// vehiclelightson128 texture
	static RwTexture *ms_pLightsOnTexture;
	
	// color of currently rendered car
	// static unsigned char ms_currentCol[4];
	static unsigned char *ms_currentCol;

	// number of wheel upgrades available
	// tatic short ms_numWheelUpgrades[4];
	static short *ms_numWheelUpgrades;

	// wheels upgrades data
	// static short ms_upgradeWheels[15][4];
	static short *ms_upgradeWheels;

	// lights states for currently rendered car
	// static char *ms_lightsOn[4];
	static char *ms_lightsOn;

	// extras ids for next-spawned car
	// static char ms_compsUsed[2];
	static char *ms_compsUsed;
    static char *ms_compsToUse;

	// vehicle colours from carcols.dat
	// static CRGBA ms_vehicleColourTable[128];
	static CRGBA *ms_vehicleColourTable;

    static void InjectHooks();

    virtual void SetClump(RpClump* clump) override;

    void SetClump_Reversed(RpClump* clump);

	// destroying vehiclelights textures
	static void ShutdownLightTexture();
	// find remap texture with name
	static RwTexture *FindTextureCB(char  const* name);
	// start using special finding callback
	static void UseCommonVehicleTexDicationary();
	// stop using special finding callback
	static void StopUsingCommonVehicleTexDicationary();
	// set new parent frame for object. Data is actually RwFrame *
	static RpAtomic *MoveObjectsCB(RwObject *object, void *data);
	// this is used to disable _dam atomic and "enable" _ok atomic at vehicle model setup. Data is 
	// unused
	static RpAtomic *HideDamagedAtomicCB(RpAtomic *atomic, void *data);
	// hide all atomics with state data (data is actually unsigned char)
	static RpAtomic *HideAllComponentsAtomicCB(RpAtomic *atomic, void *data);
	// check if material has alpha. Boolean result is stored to data (data is actually bool *)
	static RpMaterial *HasAlphaMaterialCB(RpMaterial *material, void *data);
	// setup atomic renderer. Data is unused
	static RpAtomic *SetAtomicRendererCB(RpAtomic *atomic, void *data);
	// setup heli renderer. Data is unused
	static RpAtomic *SetAtomicRendererCB_RealHeli(RpAtomic *atomic, void *data);
	// setup plane renderer. Data is unused
	static RpAtomic *SetAtomicRendererCB_Plane(RpAtomic *atomic, void *data);
	// setup boat renderer. Data is unused
	static RpAtomic *SetAtomicRendererCB_Boat(RpAtomic *atomic, void *data);
	// setup heli renderer. Data is unused
	static RpAtomic *SetAtomicRendererCB_Heli(RpAtomic *atomic, void *data);
	// setup train renderer. Data is unused
	static RpAtomic *SetAtomicRendererCB_Train(RpAtomic *atomic, void *data);
	// setup model render callbacks
	void SetAtomicRenderCallbacks();
	// setup objects flag. Data is actually flag (unsigned short)
	static RwObject *SetAtomicFlagCB(RwObject *object, void *data);
	// clear all atomic flag. Data is actually flag (unsigned short)
	static RwObject *ClearAtomicFlagCB(RwObject *object, void *data);
	// set component flags
	void SetVehicleComponentFlags(RwFrame *component, unsigned int flags);
	// get wheel position. Wheel is wheel id [0-3]. Local - get local offset (if false it will get 
	// world position)
	void GetWheelPosn(int wheel, CVector &outVec, bool local);
	// get component local offset. Component is a frame hierarchy id. Returns true if component present
	bool GetOriginalCompPosition(CVector &outVec, int component);
	// get vehicle extra with rules. Returns extra id.
	int ChooseComponent();
	// get vehicle second extra with rules. Returns extra id.
	int ChooseSecondComponent();
	// check if upgrade is available
	bool IsUpgradeAvailable(VehicleUpgradePosn upgrade);
	// change colors and settings of material according to vehicle color and lights states.  Data 
	// contains pointer to restore entries
	RpMaterial *SetEditableMaterialsCB(RpMaterial *material, void *data);
	// execute SetEditableMaterialsCB(RpMaterial *, void *) for atomic materials and also remove
	// vehicle window if needed. Data contains pointer to restore entries
	RpAtomic *SetEditableMaterialsCB(RpAtomic *atomic, void *data);
	// execute SetEditableMaterialsCB(RpAtomic *, void *) for atomics in clump. This one is called
	// before vehicle rendering
	void SetEditableMaterials(RpClump *clump);
	// reset materials settings. This one is called after vehicle rendering
	void ResetEditableMaterials(RpClump *clump);
	// set current vehicle colour for model
	void SetVehicleColour(unsigned char prim, unsigned char sec, unsigned char tert, 
		unsigned char quat);
	// get color for car. variationShift determines how many color variations to skip. 
	// For example, 1 will simply give you next color variation.
	void ChooseVehicleColour(unsigned char &prim, unsigned char &sec, unsigned char &tert, 
		unsigned char &quat, int variationShift);
	// get num remaps in this model
	int GetNumRemaps();
	// add remap to model. Txd is id of tex dictionary.
	void AddRemap(int txd);
	// adds wheel upgrade. This one is called from LoadVehicleUpgrades()
	static void AddWheelUpgrade(int wheelSetNumber, int modelId);
	// gets num upgrades for this set
	static int GetNumWheelUpgrades(int wheelSetNumber);
	// gets whell upgrade
	static void GetWheelUpgrade(int wheelSetNumber, int wheelUpgradeNumber);
	// do nothing
	static void DeleteVehicleColourTextures();
	// loads 'white' texture
	static void LoadEnvironmentMaps();
	// unloads 'white' texture
	static void ShutdownEnvironmentMaps();
	// gets mat effect of this material. Data is actually int *
	static RpMaterial *GetMatFXEffectMaterialCB(RpMaterial *material, void *data);
	// sets mat effect for this meterial. Data is actually int
	static RpMaterial *SetEnvironmentMapCB(RpMaterial *material, void *data);
	// sets environment map intensity. Data is acually unsigned int
	static RpMaterial *SetEnvMapCoeffCB(RpMaterial *material, void *data);
	// do nothing
	static RpAtomic *SetRenderPipelinesCB(RpAtomic *atomic, void *data);
	// setups rendering pipelines for atomics in model (CCustomCarEnvMapPipeline::CustomPipeAtomicSetup)
	void SetRenderPipelines();
	// gets car plate text
	// return m_plateText[0] != '\0' ? m_plateText : NULL;
	char *GetCustomCarPlateText();
	// sets plate text
	void SetCustomCarPlateText(char *text);
	// gets max number of passengers for model
	static int GetMaximumNumberOfPassengersFromNumberOfDoors(int modelId);
	// remove some unused materials in model?
	void ReduceMaterialsInVehicle();
	// setup lights states for currenly rendered vehicle
	void SetupLightFlags(class CVehicle *vehicle);
	// move all objects from data (it is actually RwFrame *) to frame
	static RwFrame *CollapseFramesCB(RwFrame *frame, void *data);
	// setup vehicle model components
	void PreprocessHierarchy();
	// setup environment map for atomic's materials. Data is actually int and it represents effect id
	static RpAtomic *SetEnvironmentMapAtomicCB(RpAtomic *atomic, void *data);
	// setup environment map intensity for atomic with data (unsigned int)
	static RpAtomic *SetEnvMapCoeffAtomicCB(RpAtomic *atomic, void *data);
	// setup custom plate
	void SetCarCustomPlate();
	// disable environment map effect on model
	void DisableEnvMap();
	// setup environment map intensity for model
	void SetEnvMapCoeff(float coeff);
    // get num doors in this model
    int GetNumDoors();
	static void AssignRemapTxd(const char* name, std::int16_t txdSlot);
};

VALIDATE_SIZE(CVehicleModelInfo::CVehicleStructure, 0x314);
VALIDATE_SIZE(CVehicleModelInfo, 0x308);
