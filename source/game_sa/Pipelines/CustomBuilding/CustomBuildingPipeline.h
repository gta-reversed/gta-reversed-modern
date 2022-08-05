#pragma once

class CCustomBuildingPipeline {
public:
    static RxPipeline*& ObjPipeline;

public:
    static void InjectHooks();

    static bool CreatePipe();
    static void DestroyPipe();
    static RpAtomic* CustomPipeAtomicSetup(RpAtomic* atomic);
    static RxPipeline* CreateCustomObjPipe();
};
