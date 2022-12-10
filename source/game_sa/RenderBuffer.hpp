#pragma once

#include <Base.h>
#include <rwcore.h>

namespace RenderBuffer {
void InjectHooks();

/*!
* @addr 0x708290
* @brief Start storing vertices. Must be followed by `StopStoring()`
* If there isn't enough space in the buffer for the
* specified amount of vertices/indices the buffer is
* rendered out first.
*
* @param     nIndicesNeeded  No. of indices that will be stored
* @param     nVerticesNeeded No. of vertices that will be stored
* @param out pFirstIndex     Pointer to the first unused index in the buffer
* @param out pFirstVertex    Pointer to the first unused vertex in the buffer
*/
void StartStoring(
    int32 nIndicesNeeded,
    int32 nVerticesNeeded,
    RwImVertexIndex*& pFirstIndex,
    RwIm3DVertex*& pFirstVertex
);

/*!
* @addr 0x7077A0
* @brief Must be enclosed by a `StartStoring()` operation
*/
void StopStoring();

/*!
* @addr 0x707800
* @brief Render out the contents of the temporary buffers as a trilist.
* Frequently inlined!
*/
void RenderStuffInBuffer();

/*!
* @addr 0x707790
* @brief Reset the index/vertex buffer stored counters.
* Frequently inlined!
*/
void ClearRenderBuffer();
}; // namespace RenderBuffer
