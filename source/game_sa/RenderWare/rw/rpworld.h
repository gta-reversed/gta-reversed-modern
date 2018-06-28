/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
/******************************************/
/*                                        */
/*    RenderWare(TM) Graphics Library     */
/*                                        */
/******************************************/

/*
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd.
 * or Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. and Canon Inc. will not, under any
 * circumstances, be liable for any lost revenue or other damages
 * arising from the use of this file.
 *
 * Copyright (c) 1999. Criterion Software Ltd.
 * All Rights Reserved.
 */

/*************************************************************************
 *
 * Filename: <C:/daily/rwsdk/include/d3d9/rpworld.h>
 * Automatically Generated on: Fri Oct 03 09:52:43 2003
 *
 ************************************************************************/

/*--- System Header Files ---*/
#include <stdarg.h>
#include <stdlib.h>

/*****************************************************************************
 Global Defines & Enums
 */

#define RWD3D9VSCONST_TRANSFORM_OFFSET  0
#define RWD3D9VSCONST_AMBIENT_OFFSET    4
#define RWD3D9VSCONST_LIGHTS_OFFSET     5

typedef enum rwD3D9VertexShaderEffectType
{
    rwD3D9VERTEXSHADEREFFECT_NONE = 0,
    rwD3D9VERTEXSHADEREFFECT_BUMPMAP = 1,
    rwD3D9VERTEXSHADEREFFECT_ENVMAP,
    rwD3D9VERTEXSHADEREFFECT_BUMPENVMAP,
    rwD3D9VERTEXSHADEREFFECT_DUAL,
    rwD3D9VERTEXSHADEREFFECT_DUALREPLICATE,
    rwD3D9VERTEXSHADEREFFECT_UVANIM,
    rwD3D9VERTEXSHADEREFFECT_DUALUVANIM,
    rwD3D9VERTEXSHADEREFFECT_NORMALMAP,
    rwD3D9VERTEXSHADEREFFECT_NORMALENVMAP,
    rwD3D9VERTEXSHADEREFFECT_CUBEMAP,
    rwD3D9VERTEXSHADEREFFECT_BUMPCUBEMAP,

    rwD3D9VERTEXSHADEREFFECT_MAX = (1 << 6),

} rwD3D9VertexShaderEffectType;


typedef enum rwD3D9VertexShaderFogMode
{
    rwD3D9VERTEXSHADERFOG_NONE = 0,
    rwD3D9VERTEXSHADERFOG_LINEAR = 1,
    rwD3D9VERTEXSHADERFOG_EXP,
    rwD3D9VERTEXSHADERFOG_EXP2,

    rwD3D9VERTEXSHADERFOG_MAX
} rwD3D9VertexShaderFogMode;

/******************************************************************************
 Global Types
 */

#if !defined(DOXYGEN)

/* This struct is used to specify the required functionality of the vertex shader */
typedef struct _rpD3D9VertexShaderDescriptor
{
    RwUInt8 numDirectionalLights : 4;
    RwUInt8 numPointLights : 4;
    RwUInt8 numSpotLights : 4;
    RwUInt8 numTexCoords : 4;

    RwUInt8 morphing : 1;
    RwUInt8 numWeights : 3;
    RwUInt8 prelit : 1;
    RwUInt8 normals : 1;
    RwUInt8 normalizeNormals : 1;
    RwUInt8 modulateMaterial : 1;
    RwUInt8 fogMode : 2;
    RwUInt8 effect : 6;

} _rpD3D9VertexShaderDescriptor;

/*
 * Offsets for the required vertex shader constants.
 * The combined transposed matrix world-view-projection is always at offset 0.
 * The ambient is always at offset 4.
 * The first light is always at offset 5.
 * 0xFF indicates that the specified constant is not used.
 */
typedef struct _rpD3D9VertexShaderDispatchDescriptor
{
    RwUInt8 offsetMaterialColor;
    RwUInt8 offsetFogRange;
    RwUInt8 offsetEffect;
    RwUInt8 offsetMorphingCoef;
    RwUInt8 offsetBoneMatrices;
    RwUInt8 pad[3];

} _rpD3D9VertexShaderDispatchDescriptor;

#endif /* !defined(DOXYGEN) */

/*
 * Vertex shader pipeline callbacks
 */

typedef struct RxD3D9ResEntryHeader RxD3D9ResEntryHeader;
typedef struct RxD3D9InstanceData RxD3D9InstanceData;
typedef struct RpMaterial RpMaterial;

/* Initialize shared components of "desc" and to prepare internal render data */

typedef RwBool (*_rxD3D9VertexShaderInstanceCallBack)(void *object,
                                                      RxD3D9ResEntryHeader *resEntryHeader,
                                                      RwBool reinstance);

typedef void (*_rxD3D9VertexShaderBeginCallBack)(void *object,
                                                 RwUInt32 type,
                                                 _rpD3D9VertexShaderDescriptor  *desc);

/* _rwD3D9VSSetActiveWorldMatrix MUST be called before using this two callbacks */

typedef RwV4d * (*_rxD3D9VertexShaderLightingCallBack)(void *object,
                                                       RwUInt32 type,
                                                       RwV4d    *shaderConstantPtr,
                                                       _rpD3D9VertexShaderDescriptor  *desc);

typedef void *(*_rxD3D9VertexShaderGetMaterialShaderCallBack)(const RpMaterial *material,
                                                              _rpD3D9VertexShaderDescriptor *desc,
                                                              _rpD3D9VertexShaderDispatchDescriptor *dispatch);


typedef void (*_rxD3D9VertexShaderMeshRenderCallBack)(RxD3D9ResEntryHeader *resEntryHeader,
                                                      RxD3D9InstanceData *instancedMesh,
                                                      const _rpD3D9VertexShaderDescriptor  *desc,
                                                      const _rpD3D9VertexShaderDispatchDescriptor *dispatch);

typedef void (*_rxD3D9VertexShaderEndCallBack)(void *object,
                                               RwUInt32 type,
                                               _rpD3D9VertexShaderDescriptor  *desc);

/****************************************************************************
 Global Types
 */


typedef struct RpMaterialChunkInfo RpMaterialChunkInfo;
typedef struct RpMaterialChunkInfo _rpMaterial;

#if (!defined(DOXYGEN))
struct RpMaterialChunkInfo
{
    RwInt32             flags;       /* Material flags - unused currently - 
                                      * for future expansion */
    RwRGBA              color;       /* Color of material. */
    RwInt32             unused;      /* Not used */
    RwBool              textured;    /* Are we textured? */
    RwSurfaceProperties surfaceProps;/* Surface properties */
};
#endif /* (!defined(DOXYGEN)) */

#if (!defined(RwMaterialAssign))
#define RwMaterialAssign(_target, _source)             \
    ( *(_target) = *(_source) )
#endif /* (!defined(RwMaterialAssign)) */

/**
 * \ingroup rpmaterial
 * \struct RpMaterial 
 * Material object. This should be 
 * considered an opaque type. Use the RpMaterial API functions to access.
 */
typedef struct RpMaterial RpMaterial;

#if (!defined(DOXYGEN))
struct RpMaterial
{
        RwTexture           *texture; /**< texture */
        RwRGBA              color; /**< color */              
        RxPipeline          *pipeline; /**< pipeline */     
        RwSurfaceProperties surfaceProps; /**< surfaceProps */
        RwInt16             refCount;          /* C.f. rwsdk/world/bageomet.h:RpGeometry */
        RwInt16             pad;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpmaterial
 * \ref RpMaterialCallBack 
 * represents the function called from \ref RpGeometryForAllMaterials and 
 * \ref RpWorldForAllMaterials for all materials referenced by polygons in a 
 * given geometry. This function should return a pointer to the current 
 * material to indicate success. The callback may return NULL to terminate 
 * further callbacks on the materials.
 * 
 * \param  material   Pointer to the current material
 * \param  data       Pointer to developer-defined data structure.
 * 
 * \return Pointer to the current material.
 */
typedef RpMaterial *(*RpMaterialCallBack)(RpMaterial *material, void *data);

/****************************************************************************
 <macro/inline functionality
 */

#define RpMaterialAddRefMacro(_material)                            \
    (((_material)->refCount++), (_material))

#define RpMaterialAddRefVoidMacro(_material)                        \
MACRO_START                                                         \
{                                                                   \
    (_material)->refCount++;                                        \
}                                                                   \
MACRO_STOP


#define RpMaterialSetColorMacro(_material, _color)                  \
    (RwRGBAAssign(&((_material)->color), (_color)), (_material))

#define RpMaterialGetColorMacro(_material)                          \
    (&((_material)->color))

#define RpMaterialSetSurfacePropertiesMacro(_material, _surfProps)  \
    (RwSurfacePropertiesAssign(&((_material)->surfaceProps),        \
                               (_surfProps)), (_material))

#define RpMaterialGetSurfacePropertiesMacro(_material)              \
    (&((_material)->surfaceProps))

#define RpMaterialGetTextureMacro(_material)                        \
    ((_material)->texture)


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpMaterialAddRef(_material)                                 \
    RpMaterialAddRefMacro(_material)

#define RpMaterialSetColor(_material, _color)                       \
    RpMaterialSetColorMacro(_material, _color)

#define RpMaterialGetColor(_material)                               \
    RpMaterialGetColorMacro(_material)

#define RpMaterialSetSurfaceProperties(_material, _surfProps)       \
    RpMaterialSetSurfacePropertiesMacro(_material, _surfProps)

#define RpMaterialGetSurfaceProperties(_material)                   \
    RpMaterialGetSurfacePropertiesMacro(_material)

#define RpMaterialGetTexture(_material)                             \
    RpMaterialGetTextureMacro(_material)

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/*--- Automatically derived from: C:/daily/rwsdk/world/bamatlst.h ---*/
/****************************************************************************
 Global Types
 */

typedef struct RpMaterialList RpMaterialList;

#if (!defined(DOXYGEN))
struct RpMaterialList
{
    RpMaterial     **materials;
    RwInt32        numMaterials;
    RwInt32        space;
};
#endif /* (!defined(DOXYGEN)) */

/*--- Automatically derived from: C:/daily/rwsdk/world/bamesh.h ---*/

/*
 *
 * Purpose: Provide construction and enumeration facilities for meshes.
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 */

#define RPMESHGLOBAL(var)                                   \
    (RWPLUGINOFFSET(rpMeshGlobals,                          \
                    RwEngineInstance,                       \
                    meshModule.globalsOffset)->var)

#define rwPRIMTYPEOR                            \
    (rwPRIMTYPELINELIST |                       \
      rwPRIMTYPEPOLYLINE |                      \
      rwPRIMTYPETRILIST |                       \
      rwPRIMTYPETRISTRIP |                      \
      rwPRIMTYPETRIFAN   |                      \
      rwPRIMTYPEPOINTLIST)

#define rpMESHHEADERPRIMTYPEOR                  \
    (0 /* rpMESHHEADERTRILIST*/ |               \
      rpMESHHEADERTRISTRIP |                    \
      rpMESHHEADERTRIFAN  |                     \
      rpMESHHEADERLINELIST |                    \
      rpMESHHEADERPOLYLINE |                    \
      rpMESHHEADERPOINTLIST)

/****************************************************************************
 Global types
 */

/*
 * typedef for header structure listing all meshes
 * constituting a single RpGeometry or RpWorldSector
 */
typedef struct RpMeshHeader RpMeshHeader;

/**
 * \ingroup rpmesh
 * \ref RpMeshHeaderFlags
 * represents the different types of mesh.
 * \see RpMeshHeader
 */
enum RpMeshHeaderFlags
{
    /* NOTE: trilists are denoted by absence of any other
     *       primtype flags, so be careful that you test:
     *        (triListFlag == (flags&triListFlag))
     *       or:
     *        (0 == (flags&rpMESHHEADERPRIMMASK))
     *       and not:
     *        (flags&triListFlag)
     */
    rpMESHHEADERTRISTRIP  = 0x0001, /**< Render as tristrips */
    rpMESHHEADERTRIFAN    = 0x0002, /**< On PlayStation 2 these will be converted to trilists */
    rpMESHHEADERLINELIST  = 0x0004, /**< Render as linelists */
    rpMESHHEADERPOLYLINE  = 0x0008, /**< On PlayStation 2 these will be converted to linelists */
    rpMESHHEADERPOINTLIST = 0x0010, /**< Pointlists are supported only if rendered by
                                     *   custom pipelines; there is no default RenderWare
                                     *   way to render pointlists. */

    rpMESHHEADERPRIMMASK  = 0x00FF, /**< All bits reserved for specifying primitive type */
    rpMESHHEADERUNINDEXED = 0x0100, /**< Topology is defined implicitly by vertex
                                     *   order, ergo the mesh contains no indices */
    rpMESHHEADERFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/*
 * Typedef for RpMeshHeaderFlags enumeration
 * representing the different types of mesh
 */
typedef enum RpMeshHeaderFlags RpMeshHeaderFlags;

typedef struct rpMeshGlobals rpMeshGlobals;

#if (!defined(DOXYGEN))
struct rpMeshGlobals
{
    RwInt16             nextSerialNum;
    RwFreeList         *triStripListEntryFreeList;
    RwUInt8             meshFlagsToPrimType[rpMESHHEADERPRIMTYPEOR];
    RwUInt8             primTypeToMeshFlags[rwPRIMTYPEOR];
};
#endif /* (!defined(DOXYGEN)) */

typedef struct RpBuildMeshTriangle RpBuildMeshTriangle;

/**
 * \ingroup rpmesh
 * \struct RpBuildMeshTriangle
 * This type represents an array of indices into
 * the object vertex array. Used during the construction
 * of tristrips.
 *
 * See API functions
 * \see RpBuildMeshGeneratePreprocessTriStrip
 * \see RpBuildMeshGenerateExhaustiveTriStrip
 * \see RpBuildMeshGenerateTrivialTriStrip
 * \see RpBuildMeshGenerateDefaultTriStrip
 * and
 * \see RpMeshSetTriStripMethod
 * \see RpMeshGetTriStripMethod
 */
struct RpBuildMeshTriangle
{
    RwUInt16            vertIndex[3]; /**< indices into object vertex
                                       *   array. */
    RpMaterial         *material;     /**< pointer to material used to
                                       *   render the mesh. */
    RwUInt16            matIndex;     /**< unique index for material used */
    RwUInt16            textureIndex; /**< unique index for texture used */
    RwUInt16            rasterIndex;  /**< unique index for raster used */
    RwUInt16            pipelineIndex;/**< unique index for pipeline used */
};

typedef struct RpBuildMesh RpBuildMesh;

/**
 * \ingroup rpmesh
 * \struct RpBuildMesh
 * This type represents a mesh ready for tri stripping.
 *
 * See API functions
 * \see RpBuildMeshGeneratePreprocessTriStrip
 * \see RpBuildMeshGenerateExhaustiveTriStrip
 * \see RpBuildMeshGenerateTrivialTriStrip
 * \see RpBuildMeshGenerateDefaultTriStrip
 * and
 * \see RpMeshSetTriStripMethod
 * \see RpMeshGetTriStripMethod
 */
struct RpBuildMesh
{
    RwUInt32            triangleBufferSize; /**< number of triangles
                                             *   space has been allocated
                                             *   for. */
    RwUInt32            numTriangles;       /**< number of triangles to be
                                             *   tristripped. */
    RpBuildMeshTriangle *meshTriangles;     /**< pointer to build mesh
                                             *   triangles. */
};

typedef struct RpMesh RpMesh;

/**
 * \ingroup rpmesh
 * \struct RpMesh
 * This type represents a single polygon mesh.
 * A mesh is defined as a collection of triangles derived from an RpGeometry
 * or RpWorldSector which have a common material.
 *
 * See API functions \see RpGeometryForAllMeshes and
 * \see RpWorldSectorForAllMeshes and
 * the corresponding function callback types:
 */
struct RpMesh
{
    RxVertexIndex      *indices;    /**< vertex indices defining the mesh */
    RwUInt32            numIndices; /**< number of vertices in mesh */
    RpMaterial         *material;   /**< pointer to material used to
                                     *   render the mesh. */
};

/**
 * \ingroup rpmesh
 * \struct RpMeshHeader
 * Header for all meshes that constitute a single RpGeometry or RpWorldSector
 */
struct RpMeshHeader
{
    RwUInt32            flags;    /**< \see RpMeshHeaderFlags */
    RwUInt16            numMeshes; /**< Number of meshes in object */
    RwUInt16            serialNum; /**< Determine if mesh has changed
                                    * since last instance */
    RwUInt32            totalIndicesInMesh; /**< Total triangle index
                                             * count in all meshes
                                             */
    RwUInt32            firstMeshOffset; /**< Offset in bytes from end this
                                          * structure RpMeshHeader
                                          * to the first mesh
                                          */
};

/**
 * \ingroup rpmesh
 * \ref RpMeshCallBack is the callback
 * function supplied to \ref RpGeometryForAllMeshes and
 * \ref RpWorldSectorForAllMeshes for all meshes in a given geometry.
 *
 * This function should return a pointer to the current mesh to indicate
 * success. The callback may return NULL to terminate further callbacks
 * on the meshes.
 *
 * \param  mesh        Pointer to the current mesh, supplied by
 *                     iterator.
 * \param  meshHeader  Pointer to the meshes header
 * \param  data        Pointer to developer-defined data structure.
 *
 * \return Returns a pointer to the current mesh if successful or NULL 
 * if an error occurred.
 */
typedef RpMesh     *(*RpMeshCallBack) (RpMesh * mesh,
                                       RpMeshHeader * meshHeader,
                                       void *pData);

/*--- Automatically derived from: C:/daily/rwsdk/world/bameshop.h ---*/

/****************************************************************************
 Defines
 */

#define RPTRISTRIPPOLYGONMAXEDGES 3

/**
 * \ingroup rpmesh
 * \ref RpTriStripMeshCallBack is the callback to generate triangle strips
 * when the triangle stripped geometries or world sectors are unlocked.
 *
 * \param buildMesh pointer to the mesh which the triangle strip will be
 *                  generated from.
 * \param data      pointer to user-supplied data to pass to the callback
 * function.
 *
 * \return a pointer to the constructed mesh header.
 *
 */
typedef RpMeshHeader *
(*RpTriStripMeshCallBack) (RpBuildMesh *buildMesh, void *data);



/****************************************************************************
 Global types
 */

typedef struct RpTriStripEdge RpTriStripEdge;

typedef struct RpTriStripPolygon RpTriStripPolygon;
/**
 * \ingroup rpmesh
 * \struct RpTriStripPolygon
 * This type represents a polygon.
 *
 * \see RpTriStripPolygonFollowStrip
 * \see RpBuildMeshGenerateTriStrip
 * \see RpTriStripMeshTunnel
 */
struct RpTriStripPolygon
{
    RwLLLink inEndLink;     /**< link for list of polygons joined by fewer than
                                 2 strip edges */
    RwLLLink inUsedLink;    /**< link for list of used polygons */
    RwLLLink inFreeLink;    /**< link for list of free polygons */
    RwUInt32 numEdges;      /**< number of edges */
    RpTriStripEdge *edges[RPTRISTRIPPOLYGONMAXEDGES];   /**< polygon edges */
    RxVertexIndex vertIndex[RPTRISTRIPPOLYGONMAXEDGES]; /**< polygon vertex 
                                                             indices */
    RwUInt32 testFrame;     /**< used to prevent a tri-strip being counted by
                                 the cost function more than once */
};

/**
 * \ingroup rpmesh
 * \struct RpTriStripEdge
 * This type represents a polygon edge which may be part of a tri-strip.
 *
 * \see RpTriStripPolygonFollowStrip
 * \see RpBuildMeshGenerateTriStrip
 * \see RpTriStripMeshTunnel
 */
struct RpTriStripEdge
{
    RwLLLink inUsedLink;        /**< link for list of used edges */      
    RwLLLink inFreeLink;        /**< link for list of free edges */
    RpTriStripPolygon *poly1;   /**< first polygon including this edge */
    RpTriStripPolygon *poly2;   /**< second polygon including this edge or NULL
                                     if this edge is only included in one */
    RxVertexIndex vert1;        /**< index of first vertex of edge */
    RxVertexIndex vert2;        /**< index of second vertex of edge */
    RwBool strip;               /**< TRUE if the edge is part of a tri-strip */
};

typedef struct RpTriStripMesh RpTriStripMesh;
/**
 * \ingroup rpmesh
 * \struct RpTriStripMesh
 * This type represents a mesh and the tri-strips it contains.
 *
 * \see RpBuildMeshGenerateTriStrip
 * \see RpTriStripMeshTunnel
 */
struct RpTriStripMesh
{
    RwUInt32 numPolygons;       /**< the number of polygons in the mesh */
    RwLinkList polygonEndList;  /**< linked list of polygons joined by fewer 
                                     than 2 strip edges. */
    RwLinkList polygonUsedList; /**< linked list of used polygons */
    RwLinkList polygonFreeList; /**< linked list of free polygons */
    RwLinkList edgeUsedList;    /**< linked list of used edges */
    RwLinkList edgeFreeList;    /**< linked list of free edges */
};

/**
 * \ingroup rpmesh
 * \ref RpTriStripMeshStripCallBack represents the callback function to
 * tri-strip a mesh.
 * 
 * \param  mesh Pointer to the mesh to tri-strip.
 * \param  data Pointer to user-supplied data.
 *
 * \return Returns a pointer to the current mesh if successful or NULL if an
 *         error occurred. 
 */
typedef RpTriStripMesh *
(*RpTriStripMeshStripCallBack) (RpTriStripMesh *mesh, void *data);

typedef struct RpTriStripData RpTriStripData;
/**
 * \ingroup rpmesh
 * \struct RpTriStripData
 * This type represents the data required by the 
 * \ref RpBuildMeshGenerateTriStrip function to tri-strip a mesh. This data must
 * be the user-supplied data passed into RpMeshSetTriStripMethod when using
 * \ref RpBuildMeshGenerateTriStrip.
 *
 * \see RpMeshGetTriStripMethod
 * \see RpMeshSetTriStripMethod
 * \see RpBuildMeshGenerateTriStrip
 * \see RpTriStripMeshTunnel
 */
struct RpTriStripData
{
    RwBool ignoreWinding;                /**< TRUE to ignore winding order */
    RpTriStripMeshStripCallBack stripCB; /**< callback to tri-strip mesh */
    void *data;                          /**< data to supply to callback */
};

/**
 * \ingroup rpmesh
 * \ref RpTriStripCostCallBack represents the callback function used by the
 * tunnelling tri-stripper to determine the cost of a tri-strip.
 * 
 * \param  startPolygon Pointer to polygon at the start of the tri-strip.
 * \param  testFrame    Value that must be written to the testFrame of all 
 *                      polygons in the tri-strip
 * \param  data         Pointer to user-supplied data.
 *
 * \return Returns the cost of the tri-strip.
 */
typedef RwUInt32
(*RpTriStripCostCallBack) (RpTriStripPolygon *startPolygon, RwUInt32 testFrame, void *data);

typedef struct RpTriStripTunnelData RpTriStripTunnelData;
/**
 * \ingroup rpmesh
 * \struct RpTriStripTunnelData
 * This type represents the data required by the 
 * \ref RpTriStripMeshTunnel function to tri-strip a mesh. This data must
 * be the user-supplied data in the RpTriStripData structure passed into
 * \ref RpMeshSetTriStripMethod as the user-supplied data when using
 * \ref RpTriStripMeshTunnel.
 *
 * \see RpMeshGetTriStripMethod
 * \see RpMeshSetTriStripMethod
 * \see RpBuildMeshGenerateTriStrip
 * \see RpTriStripMeshTunnel
 * \see RpTriStripDefaultCost
 */
struct RpTriStripTunnelData
{
    RwReal quality; /**< Values between 0.1 and 0.5 tend to be fairly quick but
        don't always give the best results. Values greater than 0.5 tend to 
        give good results useful for final artwork but can take much longer.
        Large values e.g. 5 allow the length limit to be the limiting factor
        instead. */
    RwUInt32 lengthLimit; /**< The maximum tunnel length to use. Values between
        10 and 50 tend to be fairly quick but don't always give the best
        results. Values greater than 50 tend to give good results for final
        artwork but can take much longer. Large values e.g. 10000 allow the
        quality to be the limiting factor. */
    RpTriStripCostCallBack costCB; /**< callback to determine tri-strip cost */
    void *data;                    /**< data to supply to callbacks */
};



/****************************************************************************
 Global Variables 
 */


/*--- Automatically derived from: C:/daily/rwsdk/world/bageomet.h ---*/

/*
 * Handling atomic's geometry
 * Geometry describe objects, and are the building blocks for atomics
 *
 * Copyright (c) 1998 Criterion Software Ltd.
*/


/****************************************************************************
 Defines
 */

/* Type ID */
#define rpGEOMETRY 8

/**
 * \ingroup rpgeometry
 * RpGeometryFlag
 * Geometry type flags 
 *
 * When creating a geometry, these flags can be OR'ed together to
 * specify the format along with the rpGEOMETRYTEXCOORDSETS(n) macro if more
 * than two sets of texture coordinates are required. See \ref RpGeometryCreate
 * for more details.
 *
 * \see RpGeometryCreate().
 */
enum RpGeometryFlag
{
    rpGEOMETRYTRISTRIP  = 0x00000001, /**<This geometry's meshes can be
                                          rendered as strips.
                                          \ref RpMeshSetTriStripMethod is
                                          used to change this method.*/
    rpGEOMETRYPOSITIONS = 0x00000002, /**<This geometry has positions */  
    rpGEOMETRYTEXTURED  = 0x00000004, /**<This geometry has only one set of
                                          texture coordinates. Texture
                                          coordinates are specified on a per
                                          vertex basis */
    rpGEOMETRYPRELIT    = 0x00000008, /**<This geometry has pre-light colors */
    rpGEOMETRYNORMALS   = 0x00000010, /**<This geometry has vertex normals */
    rpGEOMETRYLIGHT     = 0x00000020, /**<This geometry will be lit */
    rpGEOMETRYMODULATEMATERIALCOLOR = 0x00000040, /**<Modulate material color 
                                                      with vertex colors
                                                      (pre-lit + lit) */

    rpGEOMETRYTEXTURED2 = 0x00000080, /**<This geometry has at least 2 sets of
                                          texture coordinates. */

    /*
     * These above flags were stored in the flags field in an RwObject, they
     * are now stored in the flags file of the RpGeometry.
     */

    rpGEOMETRYNATIVE            = 0x01000000,
    rpGEOMETRYNATIVEINSTANCE    = 0x02000000,

    rpGEOMETRYFLAGSMASK         = 0x000000FF,
    rpGEOMETRYNATIVEFLAGSMASK   = 0x0F000000,

    rpGEOMETRYFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpGeometryFlag RpGeometryFlag;

/* Multi texture coordinate format specifier for RpGeometryCreate() */
#define rpGEOMETRYTEXCOORDSETS(_num) ((_num & 0xff) << 16)

/**
 * \ingroup rpgeometry
 * RpGeometryLockMode
 * Geometry lock flags 
 */
enum RpGeometryLockMode
{
    rpGEOMETRYLOCKPOLYGONS   =   0x01, /**<Lock the polygons (triangle list) */
    rpGEOMETRYLOCKVERTICES   =   0x02, /**<Lock the vertex positional data */
    rpGEOMETRYLOCKNORMALS    =   0x04, /**<Lock the vertex normal data */
    rpGEOMETRYLOCKPRELIGHT   =   0x08, /**<Lock the pre-light values */
    rpGEOMETRYLOCKTEXCOORDS  =   0x10, /**<Lock the texture coordinates set 1*/
    rpGEOMETRYLOCKTEXCOORDS1 =   0x10, /**<Lock the texture coordinates set 1*/
    rpGEOMETRYLOCKTEXCOORDS2 =   0x20, /**<Lock the texture coordinates set 2*/
    rpGEOMETRYLOCKTEXCOORDS3 =   0x40, /**<Lock the texture coordinates set 3*/
    rpGEOMETRYLOCKTEXCOORDS4 =   0x80, /**<Lock the texture coordinates set 4*/
    rpGEOMETRYLOCKTEXCOORDS5 = 0x0100, /**<Lock the texture coordinates set 5*/
    rpGEOMETRYLOCKTEXCOORDS6 = 0x0200, /**<Lock the texture coordinates set 6*/
    rpGEOMETRYLOCKTEXCOORDS7 = 0x0400, /**<Lock the texture coordinates set 7*/
    rpGEOMETRYLOCKTEXCOORDS8 = 0x0800, /**<Lock the texture coordinates set 8*/
    rpGEOMETRYLOCKTEXCOORDSALL = 0x0ff0, /**<Lock all texture coordinate sets*/
    rpGEOMETRYLOCKALL        = 0x0fff, /**<Combination of all the above */

    rpGEOMETRYLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpGeometryLockMode RpGeometryLockMode;

/* Convenience macro for generating a tex coord lock flag */
#define rpGEOMETRYLOCKTEXCOORDSIDX(_idx) (rpGEOMETRYLOCKTEXCOORDS1 << (_idx))


/****************************************************************************
 Global Types
 */

typedef struct rpGeometryGlobals rpGeometryGlobals;

#if (!defined(DOXYGEN))
struct rpGeometryGlobals
{
        RwFreeList         *geomFreeList;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpgeometry
 * \struct RpGeometry 
 * Geometry object. This should be considered an opaque type. 
 * Use the RpGeometry API functions to access.
 */
typedef struct RpGeometry RpGeometry;

/**
 * \ingroup rpmorphtarget
 * \struct RpMorphTarget 
 * Morph target -- vertex positions and normals. 
 * This should be considered an opaque type. 
 * Use RpMorphTarget API functions to access.
 */
typedef struct RpMorphTarget RpMorphTarget;

#if (!defined(DOXYGEN))
struct RpMorphTarget
{
        RpGeometry *parentGeom; 
        RwSphere   boundingSphere;
        RwV3d      *verts;
        RwV3d      *normals;
};
#endif /* (!defined(DOXYGEN)) */

typedef struct RpTriangle RpTriangle;

/**
 * \ingroup rpgeomtry
 * \struct RpTriangle 
 * This type represents a triangle in a geometry specified 
 * by three indices into the geometry's vertex list (vertIndex)
 * together with an  index in to the geometry's 
 * material list (matIndex) (see API function \ref RpGeometryGetTriangles)
 */
struct RpTriangle
{
    RwUInt16            vertIndex[3];   /**< vertex indices */
    RwUInt16            matIndex;       /**< Index into material list */
};

#if (!defined(DOXYGEN))
struct RpGeometry
{
    RwObject            object;     /* Generic type */

    RwUInt32            flags;      /* Geometry flags */

    RwUInt16            lockedSinceLastInst; /* What has been locked since we last instanced - for re-instancing */
    RwInt16             refCount;   /* Reference count (for keeping track of atomics referencing geometry) */

    RwInt32             numTriangles; /* Quantity of various things (polys, verts and morph targets) */
    RwInt32             numVertices;
    RwInt32             numMorphTargets;
    RwInt32             numTexCoordSets;

    RpMaterialList      matList;

    RpTriangle         *triangles;  /* The triangles */

    RwRGBA             *preLitLum;  /* The pre-lighting values */

    RwTexCoords        *texCoords[rwMAXTEXTURECOORDS]; /* Texture coordinates */

    RpMeshHeader       *mesh;   /* The mesh - groups polys of the same material */

    RwResEntry         *repEntry;       /* Information for an instance */

    RpMorphTarget      *morphTarget;    /* The Morph Target */
};

typedef struct RpGeometryChunkInfo RpGeometryChunkInfo;
typedef struct RpGeometryChunkInfo _rpGeometry;

struct RpGeometryChunkInfo
{
    RwInt32             format;  /* Compression flags and number of texture coord sets */

    RwInt32             numTriangles;
    RwInt32             numVertices;

    RwInt32             numMorphTargets;
};
#endif /* (!defined(DOXYGEN)) */

/* Callbacks */

/**
 * \ingroup rpgeometry
 * \ref RpGeometryCallBack represents the simple callback function for the \ref RpGeometry object.
 * The callback may return NULL to terminate further callbacks on 
 * the geometry.
 * 
 * \param  geometry   Pointer to the current geometry, supplied by iterator.
 * \param  data       Pointer to developer-defined data structure.
 *
 * \return Pointer to the current geometry, or NULL If not found.
 */
typedef RpGeometry *(*RpGeometryCallBack)(RpGeometry *geometry, void *data);

/**
 * \ingroup rpgeometry
 * \ref RpGeometrySortByMaterialCallBack 
 * \ref RpGeometrySortByMaterialCallBack is used by
 * \ref RpGeometrySortByMaterial in order to preserve the validity of plugin
 * data when the vertices in an \ref RpGeometry are sorted (and some possibly
 * duplicated).
 *
 * A vertex map table is provided to the callback - this contains, for each
 * vertex in the new geometry, the index of the corresponding vertex in the
 * original geometry.
 *
 * \param  oldGeom           Pointer to the source geometry.
 * \param  newGeom           Pointer to the new, sorted geometry.
 * \param  remapTable        Pointer to the vertex map table
 * \param  numberOfEntries   Number of vertices in the new 
 *                           geometry (size of the map table)
 */
typedef void (*RpGeometrySortByMaterialCallBack)(const RpGeometry *oldGeom,
                                                 RpGeometry *newGeom,
                                                 RwUInt16 *remapTable,
                                                 RwUInt16 numberOfEntries);

/****************************************************************************
 Defines
 */

/* Type ID */
#define rpWorldSector 0xff     /* Not a true 'type'! */

#define rpMINDISTANCEBETWEENVERTICES (RwReal)(0.0001)

#define RPV3DFROMVERTEXNORMAL(v, n) \
    (v).x = (((RwReal)((n).x)) * ( (RwReal)(1.0/128))); \
    (v).y = (((RwReal)((n).y)) * ( (RwReal)(1.0/128))); \
    (v).z = (((RwReal)((n).z)) * ( (RwReal)(1.0/128)))

/****************************************************************************
 Global types
 */

typedef struct RpVertexNormal RpVertexNormal;

#if (!defined(DOXYGEN))
struct RpVertexNormal
{
    RwInt8          x;
    RwInt8          y;
    RwInt8          z;
    RwUInt8         pad; /* pad character to force alignment */
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpworldsector
 * \struct RpWorldSector
 * World Sector object. This should be
 * considered an opaque type. Use the RpWorldSector API functions to access.
 */
typedef struct RpWorldSector RpWorldSector;

#if (!defined(DOXYGEN))
struct RpWorldSector
{
    RwInt32                 type;

    RpTriangle              *triangles;             /* Triangles */

    RwV3d                   *vertices;              /* Vertex positions */
    RpVertexNormal          *normals;               /* Vertex normals */

    RwTexCoords             *texCoords[rwMAXTEXTURECOORDS]; /* Texture coordinates */

    RwRGBA                  *preLitLum;             /* Pre lit luminances */

    /* Pointer to memory allocated for vertex and poly pointers */
    RwResEntry              *repEntry;

    /* Atomics in this sectors */
    /* The pointers are frigged so they look like they are pointing to
       Atomics when they are pointing to here */
    RwLinkList              collAtomicsInWorldSector;       /* Coll priority */

    /* Lights in an atomic sector */
    RwLinkList              lightsInWorldSector;

    /* Outer bounding box of sector based on BSP planes */
    RwBBox                  boundingBox;

    /* Bounding box tightly enclosing geometry */
    RwBBox                  tightBoundingBox;

    /* The mesh which groups same material triangles together */
    RpMeshHeader            *mesh;

    /* The WorldSector object pipeline for this WorldSector */
    RxPipeline    *pipeline;

    /* Material list window base
     * (triangles in a given sector can "see"
     * the 256 materials from
     * MatList[matListWindowBase] -> MatList[matListWindowBase + 255])
     */
    RwUInt16                matListWindowBase;

    RwUInt16                numVertices;            /* Num vertices */
    RwUInt16                numTriangles;           /* Num triangles */
    RwUInt16                pad;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpworldsector
 * \ref RpWorldSectorCallBack
 * represents the function called from \ref RpWorldForAllWorldSectors,
 * \ref RpAtomicForAllWorldSectors and \ref RpLightForAllWorldSectors for all
 * world sectors in a given world or world sectors a given atomic or light lies
 * in. This function should return a pointer to the current world sector to
 * indicate success. The callback may return NULL to terminate further
 * callbacks on the atomic or light.
 *
 * \param  sector   Pointer to the current world sector
 * \param  data     Pointer to developer-defined data structure.
 *
 * \return Pointer to the current world sector.
 *
 */
typedef RpWorldSector *(*RpWorldSectorCallBack)(RpWorldSector *worldSector, void *data);

typedef struct RpSector RpSector;

#if (!defined(DOXYGEN))
struct RpSector
{
    RwInt32                 type;
};

/* NOTE: The left and right pointers can point to an RpPlaneSector or
 *       an RpWorldSector
 * This is determined what the type is via the type value
 */

typedef struct RpPlaneSector RpPlaneSector;

struct RpPlaneSector
{
    RwInt32                 type;

    RwReal                  value;
    RpSector                *leftSubTree;   /* Sector 'left' (less) of the plane */
    RpSector                *rightSubTree;  /* Sector 'right' (more) of the plane */
    RwReal                  leftValue;
    RwReal                  rightValue;
};
#endif /* (!defined(DOXYGEN)) */

/*--- Automatically derived from: C:/daily/rwsdk/world/balight.h ---*/

/*
 * Lighting 3D objects.
 * Lights are used to illuminate atomics and worlds
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 */


/****************************************************************************
 Defines
 */

/* Binary Light */
typedef struct RpLightChunkInfo RpLightChunkInfo;
typedef struct RpLightChunkInfo _rpLight;

#if (!defined(DOXYGEN))
struct RpLightChunkInfo
{
        RwReal              radius; /**< radius */
        RwReal              red; /**< red */
        RwReal              green; /**< green */
        RwReal              blue; /**< blue */
        RwReal              minusCosAngle; /**< minusCosAngle */
        RwUInt32            typeAndFlags; /**< typeAndFlags */
};
#endif /* (!defined(DOXYGEN)) */

/* Type ID */
#define rpLIGHT 3

/* Beyond this the lights must be positioned */
#define rpLIGHTPOSITIONINGSTART 0x80

/**
 * \ingroup rplight
 * \ref RpLightType are
 * light sub types.  This type represents the different 
 * types of light source that can be created using the API function \ref RpLightCreate.  
 * Note that lights of types rpLIGHTPOINT, rpLIGHTSPOT and rpLIGHTSPOTSOFT have linear 
 * intensity fall-off with distance from the source, reducing to zero at the light's radius:*/
enum RpLightType
{
    rpNALIGHTTYPE = 0,

    /* These don't take part in the tie mechanism (no position) */
    rpLIGHTDIRECTIONAL, /**<Directional Light */
    rpLIGHTAMBIENT, /**<Ambient Light */

    /* These do take part in the tie mechanism (do have position) */
    rpLIGHTPOINT = rpLIGHTPOSITIONINGSTART, /**<Point Light */
    rpLIGHTSPOT, /**<Spot Light */
    rpLIGHTSPOTSOFT, /**<Soft Spot Light */
    rpLIGHTTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpLightType RpLightType;

#define rpLIGHTMINCONEANGLE ((RwReal)0.0f)

#if (defined(XBOX_DRVMODEL_H))
#define rpLIGHTMAXCONEANGLE (rwPIOVER2)
#elif (defined(OPENGL_DRVMODEL_H))
#define rpLIGHTMAXCONEANGLE (rwPIOVER2)
#elif (defined(GCN_DRVMODEL_H))
#define rpLIGHTMAXCONEANGLE (rwPIOVER2)
#elif (defined(D3D8_DRVMODEL_H))
#define rpLIGHTMAXCONEANGLE (rwPIOVER2)
#elif (defined(D3D9_DRVMODEL_H))
#define rpLIGHTMAXCONEANGLE (rwPIOVER2)
#else
#define rpLIGHTMAXCONEANGLE (rwPI)
#endif

/*************/

/*** FLAGS ***/

/*************/

/**
 * \ingroup rplight
 * \ref RpLightFlag defines what geometry is influenced by the light. 
 * The bit-field RpLightFlag specifies the options available for controlling the scope 
 * of a light source (see API function \ref RpLightSetFlags):*/
enum RpLightFlag
{
    rpLIGHTLIGHTATOMICS = 0x01, /**<The light source illuminates all atomics in a world */
    rpLIGHTLIGHTWORLD = 0x02, /**<The light source illuminates all static geometry in a world */
    rpLIGHTFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpLightFlag RpLightFlag;

/* rpLIGHTPRIVATENOCHROMA - turns on optimisations to do with
 *                          lights which are a shade of grey
 */
enum rpLightPrivateFlag
{
    rpLIGHTPRIVATENOCHROMA = 0x01,
    rpLIGHTPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum rpLightPrivateFlag rpLightPrivateFlag;

/*********************/

/**
 * \ingroup rplight
 * \struct RpLight 
 * Light object. This should be 
 * considered an opaque type. Use the RpLight API functions to access.
 */
typedef struct RpLight RpLight;

#if (!defined(DOXYGEN))
struct RpLight
{
        RwObjectHasFrame    object; /**< object */
        RwReal              radius; /**< radius */
        RwRGBAReal          color; /**< color */  /* Light color */
        RwReal              minusCosAngle; /**< minusCosAngle */  
        RwLinkList          WorldSectorsInLight; /**< WorldSectorsInLight */
        RwLLLink            inWorld; /**< inWorld */
        RwUInt16            lightFrame; /**< lightFrame */
        RwUInt16            pad;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rplight
 * \ref RpLightCallBack 
 * represents the function called from \ref RpWorldForAllLights and 
 * \ref RpWorld SectorForAllLights for all lights in a given world or world 
 * sector. This function should return a pointer to the current light to 
 * indicate success. The callback may return NULL to terminate further 
 * callbacks on the world sector.
 *
 * \param  light  Pointer to the current light in the world 
 *                sector.
 * \param  data   Pointer to developer-defined data structure.
 *
 * \return Pointer to the current light.
 */
typedef RpLight    *(*RpLightCallBack) (RpLight * light, void *data);

typedef struct RpLightTie RpLightTie;

/**
 * \ingroup rplight
 * \struct RpLightTie
 *
 * RpLightTie is a linked list of lights inside world sectors. These are
 * created when frame hierarchies are updated as part of an \ref RwCameraBeginUpdate.
 * This is used for determining which lights influence a world sector and the atomics inside it.
 * Creation and destruction of RpLightTies is internal to the world plugin.
 */
struct RpLightTie
{
    /* Information for an atomic sector */
    RwLLLink            lightInWorldSector; /**< Lights IN this ATOMIC SECTOR */
    RpLight            *light;              /**< A pointer to a light */

    /* Information for a atomic */
    RwLLLink            WorldSectorInLight; /**< Atomic sectors HOLDING this Light */
    RpWorldSector      *sect;               /**< A pointer to a world sector */
};

/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d9/D3D9lights.h ---*/
/*
 * typedef for struct RpD3D9AttenuationParams
 */
typedef struct RpD3D9AttenuationParams RpD3D9AttenuationParams;
/**
 * \ingroup rplightd3d9
 * \struct RpD3D9AttenuationParams
 *  This type represents the attenuation model of a spot or point light.
 */
struct RpD3D9AttenuationParams
{
    RwReal constant;    /**< Constant attenuation coefficient */
    RwReal linear;      /**< Linear attenuation coefficient */
    RwReal quadratic;   /**< Quadratic attenuation coefficient */
};

/*--- Automatically derived from: C:/daily/rwsdk/world/baclump.h ---*/

/*
 * Clump and atomic handling.
 * Clumps and atomics are the movable rendered objects in the world
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 */


/****************************************************************************
 Defines
 */

/****************************** Object type ID ******************************/

/* Type IDs */

#define rpATOMIC 1
#define rpCLUMP 2

/* Interpolator flags */
enum RpInterpolatorFlag
{
    rpINTERPOLATORDIRTYINSTANCE = 0x01,
    rpINTERPOLATORDIRTYSPHERE = 0x02,
    rpINTERPOLATORNOFRAMEDIRTY = 0x04,
    rpINTERPOLATORFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpInterpolatorFlag rpInterpolatorFlag;

/**
 * \ingroup rpatomic
 * The bit-field type RpAtomicFlag specifies the options available for
 * controlling the behavior of atomics. See API function \ref RpAtomicSetFlags.
 *
 * \see RpAtomicSetFlags
 * \see RpAtomicGetFlags
 * \see RpWorldSectorForAllCollisionAtomics
 */

enum RpAtomicFlag
{
    rpATOMICCOLLISIONTEST = 0x01, /**<A generic collision flag to indicate
                                   * that the atomic should be considered
                                   * in collision tests.
                                   */
    rpATOMICRENDER = 0x04,      /**<The atomic is rendered if it is
                                 * in the view frustum.
                                 */

    rpATOMICFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicFlag RpAtomicFlag;

/**
 * \ingroup rpatomic
 * \ref RpAtomicSetGeomFlag defines how an atomic references a new geometry
 *
 * \see RpAtomicSetGeometry
 */
enum RpAtomicSetGeomFlag
{
    rpATOMICSAMEBOUNDINGSPHERE = 0x01, /**<The bounding-sphere for the
                                        * new geometry is assumed to be the
                                        * same as the old one, if any, and
                                        * should not be recalculated.
                                        */

    rpATOMICSETGEOMFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicSetGeomFlag RpAtomicSetGeomFlag;

enum RpAtomicPrivateFlag
{
    rpATOMICPRIVATEWORLDBOUNDDIRTY = 0x01,
    rpATOMICPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicPrivateFlag rpAtomicPrivateFlag;


/**
 * \ingroup rpatomic
 * \struct RpAtomic
 * Atomic Geometry object. This should be
 * considered an opaque type. Use the RpAtomic API functions to access.
 */
typedef struct RpAtomic RpAtomic;

/**
 * \ingroup rpinterpolator
 * \struct RpInterpolator
 * Morph Target Interpolator.
 * This should be considered an opaque type.
 * Use the RpInterpolator API functions to access.
 */
typedef struct RpInterpolator RpInterpolator;

#if (!defined(DOXYGEN))
struct RpInterpolator
{
        RwInt32             flags; /**< flags */
        RwInt16             startMorphTarget; /**< startMorphTarget */
        RwInt16             endMorphTarget; /**< endMorphTarget */
        RwReal              time; /**< time */
        RwReal              recipTime; /**< recipTime */
        RwReal              position; /**< position */
};
#endif /* (!defined(DOXYGEN)) */

/* More callbacks */

/**
 * \ingroup rpclump
 * \struct RpClump
 * Clump Geometry object. This should be
 * considered an opaque type. Use the RpClump API functions to access.
 */
typedef struct RpClump RpClump;

/**
 * \ingroup rpclump
 * RpClumpCallBack represents the function called from 
 * \ref RwCameraForAllClumpsInFrustum when a clump lies inside the current 
 * camera's view frustum. It is also the callback type used with
 * \ref RpWorldForAllClumps. 
 *
 * This function should return a pointer to the current clump to indicate 
 * success. The callback may return NULL to terminate further callbacks on 
 * the clumps.
 *
 * \param  clump   Pointer to the current clump, supplied by
 *                 iterator.
 * \param  data    Pointer to developer-defined data structure.
 *
 * \return Pointer to the current clump.
 *
 * \see RpWorldForAllClumps
 * \see RpClumpGetCallBack
 * \see RpClumpSetCallBack
 * \see RwCameraForAllClumpsInFrustum
 */
typedef RpClump    *(*RpClumpCallBack) (RpClump * clump, void *data);

#if (!defined(DOXYGEN))
struct RpClump
{
        RwObject            object;

        /* Information about all the Atomics */
        RwLinkList          atomicList;

        /* Lists of lights and cameras */
        RwLinkList          lightList;
        RwLinkList          cameraList;

        /* The clump in a world */
        RwLLLink            inWorldLink;

        /* Clump frustum callback */
        RpClumpCallBack     callback;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpatomic
 * \ref RpAtomicCallBackRender represents the function called from
 * \ref RpAtomicRender when the specified atomic
 * lies inside the current camera's view frustum. The default callback
 * initiates execution of the atomic rendering pipeline. This function should
 * return a pointer to the atomic to indicate success.
 *
 * \param  atomic   Pointer to the current atomic, supplied by
 *                  iterator.
 *
 * \return Returns a pointer to the atomic to indicate success.
 *
 * \see RpAtomicRender
 */

typedef RpAtomic   *(*RpAtomicCallBackRender) (RpAtomic * atomic);

#if (!defined(DOXYGEN))
struct RpAtomic
{
    RwObjectHasFrame    object;

    /* Information for an instance */
    RwResEntry         *repEntry;

    /* Triangles making the object */
    RpGeometry         *geometry;

    /* Interpolated bounding sphere (in object space and world space) */
    RwSphere            boundingSphere;
    RwSphere            worldBoundingSphere;

    /* Connections to other atomics */
    RpClump            *clump;
    RwLLLink            inClumpLink;

    /* callbacks */
    RpAtomicCallBackRender renderCallBack;

    /* Interpolation animation pointer */
    RpInterpolator      interpolator;

    /* Counter for checks of "render has occurred already" */
    RwUInt16            renderFrame;
    RwUInt16            pad;

    /* Connections to sectors */
    RwLinkList          llWorldSectorsInAtomic;

    /* The Atomic object pipeline for this Atomic */
    RxPipeline         *pipeline;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpatomic
 * \ref RpAtomicCallBack represents the function called from \ref RpWorldSectorForAllAtomics and
 * \ref RpClumpForAllAtomics for all atomics in a given world sector or clump.
 * This function should return a pointer to the current atomic to indicate
 * success. The callback may return NULL to terminate further callbacks on
 * the world sector.
 *
 * \param  atomic   Pointer to the current atomic, supplied by
 *                  iterator.
 * \param  data     Pointer to developer-defined data structure.
 *
 * \return Returns a pointer to the current atomic
 */
typedef RpAtomic   *(*RpAtomicCallBack) (RpAtomic * atomic, void *data);

typedef struct RpTie RpTie;

/**
 * \ingroup rpatomic
 * \struct RpTie
 *
 * RpTie is a linked list of atomics inside world sectors. These are
 * created when frame hierarchies are updated as part of an \ref RwCameraBeginUpdate.
 * This is used for frustum culling atomics by world sector.
 * Creation and destruction of RpTies is internal to the world plugin.
 */
struct RpTie
{
    /* Information for an atomic sector */
    RwLLLink            lAtomicInWorldSector; /**< Atomics IN this ATOMIC SECTOR */
    RpAtomic           *apAtom;               /**< An atomic */

    /* Information for a atomic */
    RwLLLink            lWorldSectorInAtomic; /**< Atomic sectors HOLDING this atomic */
    RpWorldSector      *worldSector;          /**< A world sector */
};

typedef struct RpClumpChunkInfo RpClumpChunkInfo;
typedef struct RpClumpChunkInfo _rpClump;

#if (!defined(DOXYGEN))
struct RpClumpChunkInfo
{
    RwInt32             numAtomics;
    RwInt32             numLights;
    RwInt32             numCameras;
};

#endif /* (!defined(DOXYGEN)) */

/*
 * World handling.
 * World give objects scope, and provide a mechanism for
 * efficiency static object rendering.
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 *
 */

/****************************************************************************
 Defines
 */

/* Type ID */
#define rpWORLD 7

/* RpWorld private flags (in RwObject) */
enum RpWorldPrivateFlag
{
    rpWORLDSINGLEMALLOC = 0x01,
    rpWORLDPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpWorldPrivateFlag RpWorldPrivateFlag;

/**
 * \ingroup rpworldsub
 * The bit-field type \ref RpWorldFlag specifies the options available
 * for creating the static geometry component of a world (see API function \ref RpWorldSetFlags):
 */
enum RpWorldFlag
{
    rpWORLDTRISTRIP  = 0x01, /**<This world's meshes can be rendered
                                 as tri strips */
    rpWORLDPOSITIONS = 0x02, /**<This world has positions */
    rpWORLDTEXTURED  = 0x04, /**<This world has only one set of texture coordinates */
    rpWORLDPRELIT    = 0x08, /**<This world has luminance values */
    rpWORLDNORMALS   = 0x10, /**<This world has normals */
    rpWORLDLIGHT     = 0x20, /**<This world will be lit */
    rpWORLDMODULATEMATERIALCOLOR = 0x40,
                             /**<Modulate material color with vertex colors
                                 (pre-lit + lit) */
    rpWORLDTEXTURED2 = 0x80, /**<This world has 2 or more sets of texture coordinates */

    /*
     * These above flags were stored in the flags field in an RwObject, they
     * are now stored in the flags file of the RpWorld.
     */

    rpWORLDNATIVE               = 0x01000000,
    rpWORLDNATIVEINSTANCE       = 0x02000000,

    rpWORLDFLAGSMASK            = 0x000000FF,
    rpWORLDNATIVEFLAGSMASK      = 0x0F000000,

    rpWORLDSECTORSOVERLAP       = 0x40000000,

    rpWORLDFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpWorldFlag RpWorldFlag;

/* Multi texture coordinate format specifier */
#define rpWORLDTEXCOORDSETS(_num)  ((_num & 0xff) << 16)

/* Maximum depth of BSP tree */
#define rpWORLDMAXBSPDEPTH 64

/****************************************************************************
 Global types
 */

/**
 * \ingroup rpworldsub
 *
 * A pluginID is a unique identifiers for a plugin. This is a list of the IDs for
 * RpWorld plugin, which is not just one plugin, but a collection of plugins
 * that extend RenderWare Graphics Core. See \ref RwEngineRegisterPlugin
 *
 */
enum RwCriterionWorldID
{
    /* Guard value that should not be used. */
    rwID_NAWORLDID = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x00),

    /* The valid plugin IDs */
    /**< RpMaterial pluginID */
    rwID_MATERIALMODULE      = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x01),
    /**< RpMesh pluginID */
    rwID_MESHMODULE          = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x02),
    /**< RpGeometry pluginID */
    rwID_GEOMETRYMODULE      = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x03),
    /**< RpClump pluginID */
    rwID_CLUMPMODULE         = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x04),
    /**< RpLight pluginID */
    rwID_LIGHTMODULE         = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x05),
    /* Not used */
    rwID_COLLISIONMODULE     = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x06),
    /**< RpWorld pluginID */
    rwID_WORLDMODULE         = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x07),
    /* Not used */
    rwID_RANDOMMODULE        = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x08),
    /**< PluginID for RpWorld's objects */
    rwID_WORLDOBJMODULE      = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x09),
    /**< RpWorldSector pluginID */
    rwID_SECTORMODULE        = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0A),
    /**< Binary RpWorld pluginID */
    rwID_BINWORLDMODULE      = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0B),
    /**< RpWorld pipeline pluginID */
    rwID_WORLDPIPEMODULE     = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0D),
    /**< Binary RpMesh pluginID */
    rwID_BINMESHPLUGIN       = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0E),
    /**< RpWorld device pluginID */
    rwID_RXWORLDDEVICEMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0F),
    /**< PluginID for platform specific serialization data */
    rwID_NATIVEDATAPLUGIN    = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x10),
    /**< \if xbox Vertex format pluginID \endif */
    /**< \if gcn  Vertex format pluginID \endif */
    rwID_VERTEXFMTPLUGIN     = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x11),
    rwCRITERIONWORLDIDFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwCriterionWorldID RwCriterionWorldID;

/**
 * \ingroup rpworldsub
 * \ref RpWorldRenderOrder
 * represents the options available for
 * the rendering order of world sectors in the camera's view frustum (see
 * API function \ref RpWorldSetRenderOrder).
 */
enum RpWorldRenderOrder
{
    rpWORLDRENDERNARENDERORDER = 0,
    rpWORLDRENDERFRONT2BACK,  /**<Renders nearest sectors first */
    rpWORLDRENDERBACK2FRONT, /**<Renders furthest sectors first */
    rpWORLDRENDERORDERFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpWorldRenderOrder RpWorldRenderOrder;

/**
 * \ingroup rpworldsector
 * \ref RpWorldSectorCallBackRender represents the function called from
 * \ref RpWorldSectorRender when the specified world sector lies inside the
 * current camera's view frustum. The default callback initiates execution of
 * the world sector rendering pipeline. This function should return a pointer
 * to the world sector to indicate success
 *
 * \param  worldSector   Pointer to the world sector to be
 *                       rendered
 *
 * \return Pointer to the world sector.
 *
 */
typedef RpWorldSector *(*RpWorldSectorCallBackRender) (RpWorldSector *
                                                       worldSector);

/**
 * \ingroup rpworldsub
 * \struct RpWorld
 * World object. This should be considered an opaque type.
 * Use the RpWorld API functions to access.
 */
typedef struct RpWorld RpWorld;

#if (!defined(DOXYGEN))
struct RpWorld
{
    RwObject            object;

    RwUInt32            flags;

    RpWorldRenderOrder  renderOrder;

    /* Materials */
    RpMaterialList      matList;

    /* The world stored as a BSP tree */
    RpSector           *rootSector;

    /* The number of texture coordinate sets in each sector */
    RwInt32             numTexCoordSets;

    /* Render frame used when last rendered */
    RwInt32             numClumpsInWorld;
    RwLLLink           *currentClumpLink;

    /* All the clumps in the world */
    RwLinkList          clumpList;

    /* All of the lights in the world */
    RwLinkList          lightList;

    /* Directional lights in the world */
    RwLinkList          directionalLightList;

    /* The worlds origin offset */
    RwV3d               worldOrigin;

    /* Bounding box around the whole world */
    RwBBox              boundingBox;

    /* The callbacks functions */
    RpWorldSectorCallBackRender renderCallBack;

    RxPipeline         *pipeline;
};
#endif /* (!defined(DOXYGEN)) */

/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d9/d3d9usage.h ---*/
/****************************************************************************
 Global Types
 */

/**
 * \ingroup worldextensionsd3d9
 * RpD3D9GeometryUsageFlag represents the options available to inform
 * RWD3D9 about the future usage of a specific geometry.
 * The usage flags may be set via \ref RpD3D9GeometrySetUsageFlags.
 */
enum RpD3D9GeometryUsageFlag
{
    rpD3D9GEOMETRYUSAGE_DYNAMICPOSITIONS  =     0x02,   /**<Positions will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICNORMALS    =     0x04,   /**<Normals will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICPRELIT     =     0x08,   /**<Prelight information will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDS  =     0x10,   /**<The 1st set of texture coordinates will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDS1 =     0x10,   /**<The 1st set of texture coordinates will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDS2 =     0x20,   /**<The 2nd set of texture coordinates will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDS3 =     0x40,   /**<The 3rd set of texture coordinates will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDS4 =     0x80,   /**<The 4th set of texture coordinates will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDS5 =   0x0100,   /**<The 5th set of texture coordinates will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDS6 =   0x0200,   /**<The 6th set of texture coordinates will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDS7 =   0x0400,   /**<The 7th set of texture coordinates will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDS8 =   0x0800,   /**<The 8th set of texture coordinates will be locked and changed every frame. */
    rpD3D9GEOMETRYUSAGE_DYNAMICTEXCOORDSALL = 0x0ff0,   /**<All sets of texture coordinates will be locked and changed every frame. */

    rpD3D9GEOMETRYUSAGE_DYNAMICMASK       =   0x0fff,   /**<Mask for finding dynamic information. */

    rpD3D9GEOMETRYUSAGE_CREATETANGENTS    =  0x10000,   /**<Per-vertex tangents are going to be used for this geometry. */

    rpD3D9GEOMETRYUSAGEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT

};
typedef enum RpD3D9GeometryUsageFlag RpD3D9GeometryUsageFlag;

/**
 * \ingroup worldextensionsd3d9
 * RpD3D9WorldSectorUsageFlag represents the options available to inform
 * RWD3D9 about the future usage of a specific world sector.
 * The usage flags may be set via \ref RpD3D9WorldSectorSetUsageFlags.
 */
enum RpD3D9WorldSectorUsageFlag
{
    rpD3D9WORLDSECTORUSAGE_CREATETANGENTS    =  0x10000,   /**<Per-vertex tangents are going to be used for this world sector. */

    rpD3D9WORLDSECTORUSAGEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT

};
typedef enum RpD3D9WorldSectorUsageFlag RpD3D9WorldSectorUsageFlag;

/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d9/D3D9pipe.h ---*/
/****************************************************************************
 Global Defines
 */
#define RWD9DOBJECTGETTYPE(_object) (*((RwUInt8 *)(_object)))

#define RWD9DOBJECTISGEOMETRY(_object) (RWD9DOBJECTGETTYPE(_object) == (RwUInt8)rpGEOMETRY)
#define RWD9DOBJECTISATOMIC(_object) (RWD9DOBJECTGETTYPE(_object) == (RwUInt8)rpATOMIC)
#define RWD9DOBJECTISWORLDSECTOR(_object) (RWD9DOBJECTGETTYPE(_object) == (RwUInt8)-1)

/****************************************************************************
 Global Types
 */

typedef struct RxD3D9ResEntryHeader RxD3D9ResEntryHeader;
/**
 * \ingroup worldextensionsd3d9
 * \struct RxD3D9ResEntryHeader
 * This structure contains D3D9 resource specific components.
 */
struct RxD3D9ResEntryHeader
{
    RwUInt32    serialNumber;   /**< The mesh headers serial number */

    RwUInt32    numMeshes;      /**< The number of meshes */

    void        *indexBuffer;   /**< Index buffer */

    RwUInt32    primType;       /**< Primitive type */

    RxD3D9VertexStream vertexStream[RWD3D9_MAX_VERTEX_STREAMS];   /**< Vertex streams */

    RwBool      useOffsets;      /**< Use vertex buffer offsets when setting the streams */

    void        *vertexDeclaration;   /**< Vertex declaration */

    RwUInt32    totalNumIndex;  /**< Total number of indices. Needed for
                                     reinstancing, not for rendering */

    RwUInt32    totalNumVertex; /**< Total number of vertices. Needed for
                                     reinstancing, not for rendering */
};

/* This is what I keep in memory as part of the instance data setup */
typedef struct RxD3D9InstanceData RxD3D9InstanceData;
/**
 * \ingroup worldextensionsd3d9
 * \struct RxD3D9InstanceData
 * This structure contains D3D9 resource specific components.
 */
struct RxD3D9InstanceData
{
    RwUInt32        numIndex;       /**< Number of indices. Needed for
                                         reinstancing, not for rendering */

    RwUInt32        minVert;        /**< The vertex index where the
                                         meshes vertices begin. Needed for
                                         reinstancing, not for rendering */

    RpMaterial      *material;      /**< The material for this instanced data */

    RwBool          vertexAlpha;    /**< The prelight data contains alpha */

    void            *vertexShader;   /**< Vertex shader */

    RwUInt32        baseIndex;      /**< Needed if we share the vertex buffer */

    RwUInt32        numVertices;    /**< Number of vertices in the vertex buffer */

    RwUInt32        startIndex;     /**< Location in the index array to start
                                         reading vertices. */

    RwUInt32        numPrimitives;  /**< Number of primitives to render */
};

/**
 * \ingroup worldextensionsd3d9
 * \ref RxD3D9AllInOneInstanceCallBack callback function.
 * 
 * \param object Pointer to the object.
 * \param resEntryHeader Pointer to \ref RxD3D9ResEntryHeader.
 * \param reinstance Boolean whether to reinstance.
 *
 * \return TRUE if successful, FALSE otherwise.
 *
 * \see RxD3D9AllInOneSetInstanceCallBack
 * \see RxD3D9AllInOneGetInstanceCallBack
 * \see RxNodeDefinitionGetD3D9AtomicAllInOne
 * \see RxNodeDefinitionGetD3D9WorldSectorAllInOne
 */
typedef RwBool (*RxD3D9AllInOneInstanceCallBack)(void *object,
                                                 RxD3D9ResEntryHeader *resEntryHeader,
                                                 RwBool reinstance);

/**
 * \ingroup worldextensionsd3d9
 * \ref RxD3D9AllInOneReinstanceCallBack callback function.
 * 
 * \param object Pointer to the object.
 * \param resEntry Pointer to \ref RxD3D9ResEntryHeader.
 * \param instanceCallback Pointer to \ref RxD3D9AllInOneInstanceCallBack.
 *
 * \return TRUE if successful, FALSE otherwise.
 *
 * \see RxD3D9AllInOneSetReinstanceCallBack
 * \see RxD3D9AllInOneGetReinstanceCallBack
 * \see RxNodeDefinitionGetD3D9AtomicAllInOne
 * \see RxNodeDefinitionGetD3D9WorldSectorAllInOne
 */
typedef RwBool (*RxD3D9AllInOneReinstanceCallBack)(void *object,
                                                   RwResEntry *resEntry,
                                                   RxD3D9AllInOneInstanceCallBack instanceCallback);

/**
 * \ingroup worldextensionsd3d9
 * \ref RxD3D9AllInOneLightingCallBack callback function.
 * 
 * \param object Void pointer to the object.
 *
 * \see RxD3D9AllInOneSetLightingCallBack
 * \see RxD3D9AllInOneGetLightingCallBack
 * \see RxNodeDefinitionGetD3D9AtomicAllInOne
 * \see RxNodeDefinitionGetD3D9WorldSectorAllInOne
 */
typedef void (*RxD3D9AllInOneLightingCallBack)(void *object);

/**
 * \ingroup worldextensionsd3d9
 * \ref RxD3D9AllInOneRenderCallBack callback function.
 * 
 * \param repEntry Pointer to a resource entry.
 * \param object Pointer to a object that the resource entry belongs to.
 * \param type rpATOMIC or rwSECTORATOMIC.
 * \param flags \ref RpGeometryFlag's or \ref RpWorldFlag's.
 *
 * \see RxD3D9AllInOneSetRenderCallBack
 * \see RxD3D9AllInOneGetRenderCallBack
 * \see RxNodeDefinitionGetD3D9AtomicAllInOne
 * \see RxNodeDefinitionGetD3D9WorldSectorAllInOne
 */
typedef void (*RxD3D9AllInOneRenderCallBack)(RwResEntry *repEntry,
                                             void *object,
                                             RwUInt8 type,
                                             RwUInt32 flags);


/*--- Automatically derived from: C:/daily/rwsdk/world/babinwor.h ---*/
/****************************************************************************
 Global types
 */

/* Binary Representation
 *
 */
typedef struct RpWorldChunkInfoSector RpWorldSectorChunkInfo;
typedef struct RpWorldChunkInfoSector _rpWorldSector;

#if (!defined(DOXYGEN))
struct RpWorldChunkInfoSector
{
    RwInt32 matListWindowBase;
    RwInt32 numTriangles;
    RwInt32 numVertices;
    RwV3d inf;
    RwV3d sup;
    RwBool collSectorPresent;   /* unused but retains same struct size */
    RwBool unused;
};


typedef struct RpPlaneSectorChunkInfo RpPlaneSectorChunkInfo;
typedef struct RpPlaneSectorChunkInfo _rpPlaneSector;

struct RpPlaneSectorChunkInfo
{
    RwInt32 type;
    RwReal value;    
    RwBool leftIsWorldSector;
    RwBool rightIsWorldSector;
    RwReal leftValue;
    RwReal rightValue;
};

typedef struct RpWorldChunkInfo RpWorldChunkInfo;
typedef struct RpWorldChunkInfo _rpWorld;

struct RpWorldChunkInfo
{
    RwBool rootIsWorldSector;

    RwV3d invWorldOrigin;

    RwInt32 numTriangles;
    RwInt32 numVertices;
    RwInt32 numPlaneSectors;
    RwInt32 numWorldSectors;
    RwInt32 colSectorSize;    

    RwInt32 format;  /* Flags about the world */

    /* Added in 34003 */
    RwBBox  boundingBox;
};

typedef struct rpWorldChunkInfo34000 rpWorldChunkInfo34000;

struct rpWorldChunkInfo34000
{
    RwBool rootIsWorldSector;

    RwV3d invWorldOrigin;

    RwSurfaceProperties surfaceProps;

    RwInt32 numTriangles;
    RwInt32 numVertices;
    RwInt32 numPlaneSectors;
    RwInt32 numWorldSectors;
    RwInt32 colSectorSize;    

    RwInt32 format;  /* Flags about the world */
};
#endif /* (!defined(DOXYGEN)) */
