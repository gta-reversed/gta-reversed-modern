/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "RenderWare.h"
#include "CRGBA.h"
#include "CEntity.h"

enum eCoronaType
{
    CORONATYPE_SHINYSTAR,
    CORONATYPE_HEADLIGHT,
    CORONATYPE_MOON,
    CORONATYPE_REFLECTION,
    CORONATYPE_HEADLIGHTLINE,
    CORONATYPE_HEX,
    CORONATYPE_CIRCLE,
    CORONATYPE_RING,
    CORONATYPE_STREAK,
    CORONATYPE_TORUS,
    CORONATYPE_NONE
};

enum eCoronaFlareType : unsigned char
{
    FLARETYPE_NONE,
    FLARETYPE_SUN,
    FLARETYPE_HEADLIGHTS
};

class CRegisteredCorona {
public:
	CVector m_vPosn;
	unsigned int m_dwId;    // Should be unique for each corona. Address or something
	RwTexture *m_pTexture; // Pointer to the actual texture to be rendered
	float m_fSize; 
	float m_fAngle;      // left from III&VC
	float m_fFarClip;       // How far away this corona stays visible
	float m_fNearClip;      // How far away is the z value pulled towards camera.
	float m_fHeightAboveGround; 
	float m_fFadeSpeed;     // The speed the corona fades in and out
	CRGBA m_Color;
	unsigned char m_nFadeState;     // Intensity that lags behind the given intenisty and fades out if the LOS is blocked
	unsigned char m_bRegisteredThisFrame;   // Has this corona been registered by game code this frame
    eCoronaFlareType m_nFlareType;
	unsigned char m_bUsesReflection;    
	unsigned char m_bCheckObstacles : 1;     // Do we check the LOS or do we render at the right Z value -> bLOSCheck
	unsigned char m_bOffScreen : 1;          // Set by the rendering code to be used by the update code
	unsigned char m_bJustCreated;            // If this corona has been created this frame we won't delete it (It hasn't had the time to get its OffScreen cleared)
	unsigned char m_bFlashWhileFading : 1;   // Does the corona fade out when closer to cam
	unsigned char m_bOnlyFromBelow : 1;      // This corona is only visible if the camera is below it
	unsigned char m_bReflectionDelay : 1;    // this corona Has Valid Height Above Ground
	unsigned char m_bDrawWithWhiteCore : 1;  // This corona rendered with a small white core.
	unsigned char m_bAttached : 1;           // This corona is attached to an entity.
	CEntity *m_pAttachedTo;

	void Update();
};

VALIDATE_SIZE(CRegisteredCorona, 0x3C);