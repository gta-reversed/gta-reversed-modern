/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include "CBoundingBox.h"
#include "CColModel.h"
#include "CFileCarGenerator.h"
#include "CEntity.h"
#include "CFileObjectInstance.h"
#include "CFileMgr.h"

class  CFileLoader {
public:
     static char(&ms_line)[512]; // static char ms_line[512]

     static void InjectHooks();

    //! copy textures from dictionary to baseDictionary
     static void AddTexDictionaries(RwTexDictionary *dictionary, RwTexDictionary *baseDictionary);
     static RpAtomic *FindRelatedModelInfoCB(RpAtomic *atomic, void *data);
     static bool FinishLoadClumpFile(RwStream *stream, unsigned int modelIndex);
     static void LoadAnimatedClumpObject(char const *line);
     static bool LoadAtomicFile(RwStream *stream, unsigned int modelId);
     static void LoadAtomicFile(char const *filename);
     static RpClump *LoadAtomicFile2Return(char const *filename);
     static void LoadAudioZone(char const *line);
     static void LoadBoundingBox(unsigned char *data, CBoundingBox &outBoundBox);
     static void LoadCarGenerator(CFileCarGenerator *carGen, int iplId);
     static void LoadCarGenerator(char const *line, int iplId);
     static void LoadCarPathNode(char const *line, int objModelIndex, int pathEntryIndex, bool a4);
     static bool LoadClumpFile(RwStream *stream, unsigned int modelIndex);
     static void LoadClumpFile(char const *filename);
     static int LoadClumpObject(char const *line);
     static bool LoadCollisionFile(unsigned char *data, unsigned int dataSize, unsigned char colId);
     static void LoadCollisionFile(char const *filename, unsigned char colId);
     static bool LoadCollisionFileFirstTime(unsigned char *data, unsigned int dataSize, unsigned char colId);
     static void LoadCollisionModel(unsigned char *data, CColModel &outColModel);
     static void LoadCollisionModelVer2(unsigned char *data, unsigned int dataSize, CColModel &outColModel, char const *modelName);
     static void LoadCollisionModelVer3(unsigned char *data, unsigned int dataSize, CColModel &outColModel, char const *modelName);
     static void LoadCollisionModelVer4(void *data, unsigned int dataSize, CColModel &outColModel, char const *modelName);
     static void LoadCullZone(char const *line);
     static void LoadEntryExit(char const *line);
     static void LoadGarage(char const *line);
     static void LoadLevel(char const *filename);
     static char *LoadLine(FILESTREAM file);
     static char *LoadLine(char **outLine, int &outSize);
     static int LoadObject(char const *line);
     static CEntity *LoadObjectInstance(CFileObjectInstance *objInstance, char const *modelname);
     static CEntity *LoadObjectInstance(char const *line);
     static void LoadObjectTypes(char const *filename);
     static void LoadOcclusionVolume(char const *line, char const *filename);
     static int LoadPathHeader(char const *line, int &outPathType);
     static int LoadPedObject(char const *line);
     static void LoadPedPathNode(char const *line, int objModelIndex, int pathEntryIndex);
     static void LoadPickup(char const *line);
     static void LoadScene(char const *filename);
     static void LoadStuntJump(char const *line);
     static void LoadTXDParent(char const *line);
    //! load txd from file
     static RwTexDictionary *LoadTexDictionary(char const *filename);
     static void LoadTimeCyclesModifier(char const *line);
     static int LoadTimeObject(char const *line);
     static int LoadVehicleObject(char const *line);
     static int LoadWeaponObject(char const *line);
     static void LoadZone(char const *line);
    //! dummy function
     static void ReloadObjectTypes(char const *arg1);
     static void ReloadPaths(char const *filename);
    //! save txd to file
     static void SaveTexDictionary(RwTexDictionary *dictionary, char const *filename);
     static RpAtomic *SetRelatedModelInfoCB(RpAtomic *atomic, RpClump* clump);
     static bool StartLoadClumpFile(RwStream *stream, unsigned int modelIndex);
};

//! global variable to be used in a callback
 extern unsigned int &gAtomicModelId;

 void GetNameAndDamage(char const *nodeName, char *outName, bool &outDamage);
//! Makes a copy of atomic and adds it to clump
//! @param atomic callback atomic
//! @param data clump object (RpClump *)
//! @return callback atomic
 RpAtomic *CloneAtomicToClumpCB(RpAtomic *atomic, void *data);
//! Gets file name from a path
 char const *GetFilename(char const *filepath);
 void LoadingScreenLoadingFile(char const *filename);
//! Adds texture to the dictionary
//! @param texture callback texture
//! @param data texture dictionary (RwTexDictionary *)
//! @return callback texture
 RwTexture *AddTextureCB(RwTexture *texture, void *data);

//#include "meta/meta.CFileLoader.h"
