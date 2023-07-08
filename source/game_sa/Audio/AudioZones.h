#pragma once

#include "CompressedBox.h"
#include <span>

struct tAudioZoneSphere {
    char    m_szName[8];
    int16   m_nAudioZone;
    union {
        struct {
            uint16 m_bIsActive : 1;
        };
        uint16 m_nFlags;
    };
    CVector m_vPosn;
    float   m_fRadius;
};
VALIDATE_SIZE(tAudioZoneSphere, 0x1C);

struct tAudioZoneBox {
    char          m_szName[8];
    int16         m_nAudioZone;
    union {
        struct {
            uint16 m_bIsActive : 1;
        };
        uint16 m_nFlags;
    };
    CompressedBox m_Box;
    void DrawWireFrame(CRGBA color, const CMatrix& transform) const {
        m_Box.DrawWireFrame(color, transform);
    }
};
VALIDATE_SIZE(tAudioZoneBox, 0x18);

class CAudioZones {
public:
    static int32 (&m_aActiveBoxes)[10];
    static int32 (&m_aActiveSpheres)[10];

    static uint32& m_NumActiveBoxes;
    static uint32& m_NumActiveSpheres;
    static uint32& m_NumBoxes;
    static uint32& m_NumSpheres;

    static constexpr int32 NUM_AUDIO_BOXES = 158;
    static tAudioZoneBox (&m_aBoxes)[NUM_AUDIO_BOXES];

    static constexpr int32 NUM_AUDIO_SPHERES = 3;
    static tAudioZoneSphere (&m_aSpheres)[NUM_AUDIO_SPHERES];

public:
    static void InjectHooks();

    static void Init();

    static void RegisterAudioBox(char name[8], int32 id, bool isActive, CVector min, CVector max);
    static void RegisterAudioSphere(char name[8], int32 id, bool isActive, CVector position, float radius);

    static void SwitchAudioZone(char* zoneName, bool enable);
    static void Update(bool a1, CVector posn);

    static auto GetActiveAudioBoxes() {
        return m_aBoxes | rng::views::take((size_t)m_NumBoxes);
    }
};
