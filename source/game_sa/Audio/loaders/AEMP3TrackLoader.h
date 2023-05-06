#pragma once
#include "AETrackLoader.h"

class AEMP3TrackLoader : public CAETrackLoader {
public:
    static void InjectHooks();

    AEMP3TrackLoader();
    ~AEMP3TrackLoader();

    bool Initialise();
    bool LoadStreamPackTable(void);
    bool LoadTrackLookupTable(void);
    tTrackInfo* GetTrackInfo(uint32 trackId);

    // Checks for DVD stream.
    bool IsCurrentAudioStreamAvailable();
};
