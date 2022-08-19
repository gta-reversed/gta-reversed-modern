#include "StdInc.h"

#include "Checkpoint.h"
#include "3dMarkers.h"

// 0x725C00
void CCheckpoint::Render() {
    plugin::CallMethod<0x725C00, CCheckpoint*>(this);
}
