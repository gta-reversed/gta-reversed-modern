#pragma once

// Helper for loading col binary files

#include "CompressedVector.h"
#include "Vector.h"
#include "Sphere.h"
#include "Box.h"

// Based on https://gtamods.com/wiki/Collision_File

// The term `Face` and `Tri` are interchangable. (Mean the same thing)

namespace ColHelpers {
// Top-most header for every file
struct FileHeader {
    char fourcc[4]{}; // Not null terminated. Either: COLL, COL2, COL3, COL4
    uint32 size{};
    char modelName[22]{};
    uint16 modelId{};
};
VALIDATE_SIZE(FileHeader, 0x20);

struct TSurface {
    uint8 material, flag, brightness, light;
};

struct TBox : CBox {
    TSurface surface{};

    operator CColBox() const {
        return { *(CBox*)this, surface.material, surface.flag, surface.light };
    }
};

namespace V1 {
    using TVector = CVector;
    using TVertex = TVector;


    struct TSphere {
        // Unfortunately can't use CSphere, because `center` and `radius` are swapped
        float    radius{};
        TVector  center{};
        TSurface surface{};

        operator CColSphere() const {
            return { {center, radius}, surface.material, surface.flag, surface.light };
        }
    };

    struct TFace {
        uint32 a{}, b{}, c{};
        TSurface surface{};

        operator CColTriangle() {
            return { (uint16)a, (uint16)b, (uint16)c, surface.material, surface.light };
        }
    };

    struct TBounds {
        // Unfortunately can't use CSphere, because `center` and `radius` are swapped
        struct {
            float    radius{};
            TVector  center{};

            operator CSphere() const { return { center, radius }; } // Implicitly convert to an actual CSphere
        } sphere;
        CBoundingBox box{};
    };

    // Version specific header after FileHeader
    struct Header {
        TBounds bounds{};
    };
};
namespace V2 {
    using TVertex = CompressedVector;

    struct TSphere : CSphere {
        TSurface surface{};
    };

    struct TBounds {
        CSphere      sphere{};
        CBoundingBox box{};
    };

    struct TFaceGroup {
        CBoundingBox bb{};
        uint16       start{}, end{}; // First and last vertex index
    };

    struct TFace {
        uint16 a{}, b{}, c{};
        uint8  material{}, light{};
    };

    // Version specific header after FileHeader
    struct Header {
        TBounds bounds{};

        uint16 nSpheres{}, nBoxes{}, nFaces{}, nLines{};

        // Quote from https://gtamods.com/wiki/Collision_File :
        // 1 - collision uses cones instead of lines(flag forced to false by engine upon loading)
        // 2 - not empty(collision model has spheres or boxes or a mesh)
        // 8 - has face groups(if not empty)
        // 16 - has shadow mesh(col 3)
        uint32 flags{};

        uint32 offSpheres{}, offBoxes{}, offLines{}, offVerts{}, offFaces{}, offPlanes{};
    };
    VALIDATE_SIZE(Header, 0x4C);
};
namespace V3 {
    using namespace V2; // Inhert all other stuff

    // Header for V3
    struct Header : V2::Header {
        uint32 nShdwFace{};
        uint32 offShdwVert{}, offShdwFace{};
    };
};
namespace V4 {
    using namespace V3; // Inhert all other stuff

    // Header for V4
    struct Header : V3::Header {
        uint32 unk{};
    };
};
};
