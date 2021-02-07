/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPlaceable.h"
#include "CCam.h"
#include "CQueuedMode.h"
#include "CVector.h"
#include "RenderWare.h"
#include "CCamPathSplines.h"
#include "CMatrix.h"
#include "CVehicle.h"
#include "CRect.h"
#include "CPed.h"
#include "CGarage.h"

enum eSwitchType : unsigned short
{
    SWITCHTYPE_NONE,
    SWITCHTYPE_INTERPOLATION,
    SWITCHTYPE_JUMPCUT
};

enum eLookingDirection
{
    LOOKING_DIRECTION_UNKNOWN_1 = 0,
    LOOKING_DIRECTION_UNKNOWN_2,
    LOOKING_DIRECTION_UNKNOWN_3,
    LOOKING_DIRECTION_FORWARD,
};

enum class eGroundHeightType : std::int32_t
{
    ENTITY_BOUNDINGBOX_BOTTOM = 0, // ground height + boundingBoxMin.z of colliding entity
    EXACT_GROUND_HEIGHT = 1, // ignores height of colliding entity at position
    ENTITY_BOUNDINGBOX_TOP = 2 // ground height + boundingBoxMax.z of colliding entity
};

class CCamera : public CPlaceable {
    //PLUGIN_NO_DEFAULT_CONSTRUCTION(CCamera)
public:
    bool m_bAboveGroundTrainNodesLoaded;
    bool m_bBelowGroundTrainNodesLoaded;
    bool m_bCamDirectlyBehind;
    bool m_bCamDirectlyInFront;
    bool m_bCameraJustRestored;
    bool m_bcutsceneFinished;
    bool m_bCullZoneChecksOn;
    bool m_bFirstPersonBeingUsed;
    bool m_bJustJumpedOutOf1stPersonBecauseOfTarget;
    bool m_bIdleOn;
    bool m_bInATunnelAndABigVehicle;
    bool m_bInitialNodeFound;
    bool m_bInitialNoNodeStaticsSet;
    bool m_bIgnoreFadingStuffForMusic;
    bool m_bPlayerIsInGarage;
    bool m_bPlayerWasOnBike;
    bool m_bJustCameOutOfGarage;
    bool m_bJustInitalised;
    bool m_bJust_Switched;
    bool m_bLookingAtPlayer;
    bool m_bLookingAtVector;
    bool m_bMoveCamToAvoidGeom;
    bool m_bObbeCinematicPedCamOn;
    bool m_bObbeCinematicCarCamOn;
    bool m_bRestoreByJumpCut;
    bool m_bUseNearClipScript;
    bool m_bStartInterScript;
    bool m_bStartingSpline;
    bool m_bTargetJustBeenOnTrain;
    bool m_bTargetJustCameOffTrain;
    bool m_bUseSpecialFovTrain;
    bool m_bUseTransitionBeta;
    bool m_bUseScriptZoomValuePed;
    bool m_bUseScriptZoomValueCar;
    bool m_bWaitForInterpolToFinish;
    bool m_bItsOkToLookJustAtThePlayer;
    bool m_bWantsToSwitchWidescreenOff;
    bool m_bWideScreenOn;
    bool m_b1rstPersonRunCloseToAWall;
    bool m_bHeadBob;
    bool m_bVehicleSuspenHigh;
    bool m_bEnable1rstPersonCamCntrlsScript;
    bool m_bAllow1rstPersonWeaponsCamera;
    bool m_bCooperativeCamMode;
    bool m_bAllowShootingWith2PlayersInCar;
    bool m_bDisableFirstPersonInCar;
    unsigned short m_nModeForTwoPlayersSeparateCars;
    unsigned short m_nModeForTwoPlayersSameCarShootingAllowed;
    unsigned short m_nModeForTwoPlayersSameCarShootingNotAllowed;
    unsigned short m_nModeForTwoPlayersNotBothInCar;
    bool m_bGarageFixedCamPositionSet;
    bool m_bDoingSpecialInterPolation;
    bool m_bScriptParametersSetForInterPol;
    bool m_bFading;
    bool m_bMusicFading;
    bool m_bMusicFadedOut;
    bool m_bFailedCullZoneTestPreviously;
    bool m_bFadeTargetIsSplashScreen;
    bool m_bWorldViewerBeingUsed;
    bool m_bTransitionJUSTStarted;
    bool m_bTransitionState;
    unsigned char m_nActiveCam;
private:
    char _pad5A[2];
public:
    unsigned int m_nCamShakeStart;
    unsigned int m_nFirstPersonCamLastInputTime;
    unsigned int m_nLongestTimeInMill;
    unsigned int m_nNumberOfTrainCamNodes;
    unsigned int m_nTimeLastChange;
    unsigned int m_nTimeWeLeftIdle_StillNoInput;
    unsigned int m_nTimeWeEnteredIdle;
    unsigned int m_nTimeTransitionStart;
    unsigned int m_nTransitionDuration;
    unsigned int m_nTransitionDurationTargetCoors;
    unsigned int m_nBlurBlue;
    unsigned int m_nBlurGreen;
    unsigned int m_nBlurRed;
    unsigned int m_nBlurType;
    unsigned int m_nWorkOutSpeedThisNumFrames;
    unsigned int m_nNumFramesSoFar;
    unsigned int m_nCurrentTrainCamNode;
    unsigned int m_nMotionBlur;
    unsigned int m_nMotionBlurAddAlpha;
    unsigned int m_nCheckCullZoneThisNumFrames;
    unsigned int m_nZoneCullFrameNumWereAt;
    unsigned int m_nWhoIsInControlOfTheCamera;
    unsigned int m_nCarZoom;
    float m_fCarZoomBase;
    float m_fCarZoomTotal;
    float m_fCarZoomSmoothed;
    float m_fCarZoomValueScript;
    unsigned int m_nPedZoom;
    float m_fPedZoomBase;
    float m_fPedZoomTotal;
    float m_fPedZoomSmoothed;
    float m_fPedZoomValueScript;
    float m_fCamFrontXNorm;
    float m_fCamFrontYNorm;
    float m_fDistanceToWater;
    float m_fHeightOfNearestWater;
    float m_fFOVDuringInter;
    float m_fLODDistMultiplier;
    float m_fGenerationDistMultiplier;
    float m_fAlphaSpeedAtStartInter;
    float m_fAlphaWhenInterPol;
    float m_fAlphaDuringInterPol;
    float m_fBetaDuringInterPol;
    float m_fBetaSpeedAtStartInter;
    float m_fBetaWhenInterPol;
    float m_fFOVWhenInterPol;
    float m_fFOVSpeedAtStartInter;
    float m_fStartingBetaForInterPol;
    float m_fStartingAlphaForInterPol;
    float m_fPedOrientForBehindOrInFront;
    float m_fCameraAverageSpeed;
    float m_fCameraSpeedSoFar;
    float m_fCamShakeForce;
    float m_fFovForTrain;
    float m_fFOV_Wide_Screen;
    float m_fNearClipScript;
    float m_fOldBetaDiff;
    float m_fPositionAlongSpline;
    float m_fScreenReductionPercentage;
    float m_fScreenReductionSpeed;
    float m_fAlphaForPlayerAnim1rstPerson;
    float m_fOrientation;
    float m_fPlayerExhaustion;
    float m_fSoundDistUp;
    float m_fSoundDistUpAsRead;
    float m_fSoundDistUpAsReadOld;
    float m_fAvoidTheGeometryProbsTimer;
    unsigned short m_nAvoidTheGeometryProbsDirn;
private:
    char _pad16A[2];
public:
    float m_fWideScreenReductionAmount;
    float m_fStartingFOVForInterPol;
    CCam m_aCams[3];
    CGarage *m_pToGarageWeAreIn;
    CGarage *m_pToGarageWeAreInForHackAvoidFirstPerson;
    CQueuedMode m_PlayerMode;
    CQueuedMode m_PlayerWeaponMode;
    CVector m_vecPreviousCameraPosition;
    CVector m_vecRealPreviousCameraPosition;
    CVector m_vecAimingTargetCoors;
    CVector m_vecFixedModeVector;
    CVector m_vecFixedModeSource;
    CVector m_vecFixedModeUpOffSet;
    CVector m_vecCutSceneOffset;
    CVector m_vecStartingSourceForInterPol;
    CVector m_vecStartingTargetForInterPol;
    CVector m_vecStartingUpForInterPol;
    CVector m_vecSourceSpeedAtStartInter;
    CVector m_vecTargetSpeedAtStartInter;
    CVector m_vecUpSpeedAtStartInter;
    CVector m_vecSourceWhenInterPol;
    CVector m_vecTargetWhenInterPol;
    CVector m_vecUpWhenInterPol;
    CVector m_vecClearGeometryVec;
    CVector m_vecGameCamPos;
    CVector m_vecSourceDuringInter;
    CVector m_vecTargetDuringInter;
    CVector m_vecUpDuringInter;
    CVector m_vecAttachedCamOffset;
    CVector m_vecAttachedCamLookAt;
    float m_fAttachedCamAngle;
    RwCamera *m_pRwCamera;
    CEntity *m_pTargetEntity;
    CEntity *m_pAttachedEntity;
    CCamPathSplines m_aPathArray[4];
    bool m_bMirrorActive;
    bool m_bResetOldMatrix;
private:
    char _pad972[2];
public:
    CMatrix m_mCameraMatrix;
    CMatrix m_mCameraMatrixOld;
    CMatrix m_mViewMatrix;
    CMatrix m_mMatInverse;
    CMatrix m_mMatMirrorInverse;
    CMatrix m_mMatMirror;
    CVector m_avecFrustumNormals[4];
    CVector m_avecFrustumWorldNormals[4];
    CVector m_avecFrustumWorldNormals_Mirror[4];
    float m_fFrustumPlaneOffsets[4];
    float m_fFrustumPlaneOffsets_Mirror[4];
    CVector m_vecRightFrustumNormal; //!< unused?
    CVector m_vecBottomFrustumNormal; //!< unused?
    CVector m_vecTopFrustumNormal; //!< unused?
    float field_BF8; //!< unused?
    float m_fFadeAlpha;
    float m_fEffectsFaderScalingFactor;
    float m_fFadeDuration;
    float m_fTimeToFadeMusic;
    float m_fTimeToWaitToFadeMusic;
    float m_fFractionInterToStopMoving;
    float m_fFractionInterToStopCatchUp;
    float m_fFractionInterToStopMovingTarget;
    float m_fFractionInterToStopCatchUpTarget;
    float m_fGaitSwayBuffer;
    float m_fScriptPercentageInterToStopMoving;
    float m_fScriptPercentageInterToCatchUp;
    unsigned int m_nScriptTimeForInterPolation;
    unsigned short m_nFadeInOutFlag;
private:
    char _padC32[2];
public:
    int m_nModeObbeCamIsInForCar;
    short m_nModeToGoTo;    // see eCamMode
    short m_nMusicFadingDirection;
    short m_nTypeOfSwitch; // see eSwitchType
private:
    char _padC3E[2];
public:
    unsigned int m_nFadeStartTime;
    unsigned int m_nFadeTimeStartedMusic;
    int m_nExtraEntitiesCount;
    CEntity *m_pExtraEntity[2];
    float m_fDuckCamMotionFactor;
    float m_fDuckAimCamMotionFactor;
    float m_fTrackLinearStartTime;
    float m_fTrackLinearEndTime;
    CVector m_vecTrackLinearEndPoint;
    CVector m_vecTrackLinearStartPoint;
    bool m_bTrackLinearWithEase;
    char field_C7D;
    char field_C7E;
    char field_C7F;
    CVector m_vecTrackLinear;
    bool m_bVecTrackLinearProcessed;
    char field_C8D;
    char field_C8E;
    char field_C8F;
    float m_fShakeIntensity;
    float m_fStartShakeTime;
    float m_fEndShakeTime;
    int field_C9C;
    int m_nShakeType;
    float m_fStartZoomTime;
    float m_fEndZoomTime;
    float m_fZoomInFactor;
    float m_fZoomOutFactor;
    unsigned char m_nZoomMode;
    bool m_bFOVLerpProcessed;
    char field_CB6;
    char field_CB7;
    float m_fFOVNew;
    float m_fMoveLinearStartTime;
    float m_fMoveLinearEndTime;
    CVector m_vecMoveLinearPosnStart;
    CVector m_vecMoveLinearPosnEnd;
    bool m_bMoveLinearWithEase;
    char field_CDD;
    char field_CDE;
    char field_CDF;
    CVector m_vecMoveLinear;
    bool m_bVecMoveLinearProcessed;
    bool m_bBlockZoom;
    bool m_bCameraPersistPosition;
    bool m_bCameraPersistTrack;
    bool m_bCinemaCamera;
    char field_CF1;
    char field_CF2;
    char field_CF3;

    struct {
        int m_nModelIndex;
        float m_fDistance;
        float m_fAltitude;
        float m_fAngle;
    } m_aCamTweak[5];

    bool m_bCameraVehicleTweaksInitialized;
private:
    char _padD45[3];
public:
    float m_fCurrentTweakDistance;
    float m_fCurrentTweakAltitude;
    float m_fCurrentTweakAngle;
    int m_nCurrentTweakModelIndex;
    // the following are unused?
    int field_D58;
    int field_D5C;
    int field_D60;
    int field_D64;
    int field_D68;
    int field_D6C;
    int field_D70;
    int field_D74;

     static float &m_f3rdPersonCHairMultY;
     static float &m_f3rdPersonCHairMultX;
     static float &m_fMouseAccelVertical;
     static float &m_fMouseAccelHorzntl;
     static bool &m_bUseMouse3rdPerson;
    /* virtual functions */

    // vtable function #0 (destructor)

    /* virtual functions - end */

     static CCam& GetActiveCamera();

     void AddShakeSimple(float duration, int type, float intensity);
     void AllowShootingWith2PlayersInCar(bool bAllowShootingWith2PlayersInCar);
     void ApplyVehicleCameraTweaks(CVehicle *vehicle);
     void AvoidTheGeometry(CVector const *arg2, CVector const *arg3, CVector *arg4, float FOV);
     void CalculateDerivedValues(bool bForMirror, bool bOriented);
     void CalculateFrustumPlanes(bool bForMirror);
     float CalculateGroundHeight(eGroundHeightType type);
     void CalculateMirroredMatrix(CVector posn, float MirrorV, CMatrix *CamMat, CMatrix *MirrorMat);
     void CamControl();
     void CamShake(float arg2, float x, float y, float z);
     char CameraColDetAndReact(CVector *source, CVector *target);
     void CameraGenericModeSpecialCases(CPed *targetPed);
     void CameraPedAimModeSpecialCases(CPed *targPed);
    //! unused
     void CameraPedModeSpecialCases();
     void CameraVehicleModeSpecialCases(CVehicle *targVehicle);
     void ClearPlayerWeaponMode();
     bool ConeCastCollisionResolve(CVector *source, CVector *center, CVector *pVecOut, float radius, float arg5, float *pFloatOut);
    //! unused
     bool ConsiderPedAsDucking(CPed *ped);
     void CopyCameraMatrixToRWCam(bool bUpdateMatrix);
     void DealWithMirrorBeforeConstructRenderList(bool bActiveMirror, CVector MirrorNormal, float MirrorV, CMatrix *matMirror);
     void DeleteCutSceneCamDataMemory();
     void DrawBordersForWideScreen();
    //! unused
     void Enable1rstPersonCamCntrlsScript();
    //! unused
     void Enable1rstPersonWeaponsCamera();
     void Fade(float fadeDuration, short FadeInOutFlag);
     void Find3rdPersonCamTargetVector(float range, CVector source, CVector *pCamera, CVector *pPoint);
     float Find3rdPersonQuickAimPitch();
     float FindCamFOV();
     void FinishCutscene();
     void GetArrPosForVehicleType(int type, int *arrPos);
     unsigned int GetCutSceneFinishTime();
     bool GetFading();
     int GetFadingDirection();
     CVector *GetGameCamPosition();
     signed int GetLookDirection();
     bool GetLookingForwardFirstPerson();
     bool GetLookingLRBFirstPerson();
     float GetPositionAlongSpline();
     float GetRoughDistanceToGround();
     signed int GetScreenFadeStatus();
     void GetScreenRect(CRect *pRect);
     bool Get_Just_Switched_Status();
    //! arg5 always used as false
     void HandleCameraMotionForDucking(CPed *ped, CVector *source, CVector *targPosn, bool arg5);
    //! arg5 always used as false
     void HandleCameraMotionForDuckingDuringAim(CPed *ped, CVector *source, CVector *targPosn, bool arg5);
     void ImproveNearClip(CVehicle *pVehicle, CPed *pPed, CVector *source, CVector *targPosn);
     void Init();
     void InitCameraVehicleTweaks();
     int InitialiseScriptableComponents();
     bool IsExtraEntityToIgnore(CEntity *entity);
     bool IsItTimeForNewcam(int CamSequence, int StartTime);
     bool IsSphereVisible(CVector const& origin, float radius, RwMatrixTag *transformMatrix);
     bool IsSphereVisible(CVector const& origin, float radius);
     void LerpFOV(float zoomInFactor, float zoomOutFactor, float timelimit, bool bEase);
     void LoadPathSplines(int pFile);
     void Process();
     void ProcessFOVLerp(float ratio);
     void ProcessFOVLerp();
     void ProcessFade();
     void ProcessMusicFade();
     void ProcessObbeCinemaCameraBoat();
     void ProcessObbeCinemaCameraCar();
     void ProcessObbeCinemaCameraHeli();
    //! unused, empty
     unsigned int ProcessObbeCinemaCameraPed();
     void ProcessObbeCinemaCameraPlane();
     void ProcessObbeCinemaCameraTrain();
    //! unused
     void ProcessScriptedCommands();
    //! JiggleIntensity not used
     void ProcessShake(float JiggleIntensity);
     void ProcessShake();
     void ProcessVectorMoveLinear(float ratio);
     void ProcessVectorMoveLinear();
     void ProcessVectorTrackLinear(float ratio);
     void ProcessVectorTrackLinear();
     void ProcessWideScreenOn();
     void RenderMotionBlur();
     void ResetDuckingSystem(CPed *ped);
     void Restore();
     void RestoreCameraAfterMirror();
     void RestoreWithJumpCut();
     void SetCamCutSceneOffSet(CVector const *cutsceneOffset);
     void SetCamPositionForFixedMode(CVector const *fixedModeSource, CVector const *fixedModeUpOffset);
     void SetCameraDirectlyBehindForFollowPed_CamOnAString();
    //! unused
     void SetCameraDirectlyBehindForFollowPed_ForAPed_CamOnAString(CPed *targetPed);
     void SetCameraUpForMirror();
     void SetFadeColour(unsigned char Red, unsigned char Green, unsigned char Blue);
     void SetMotionBlur(int Red, int Green, int Blue, int value, int Blurtype);
     void SetMotionBlurAlpha(int Alpha);
    //! unused
     void SetNearClipBasedOnPedCollision(float arg2);
     void SetNearClipScript(float NearClip);
     void SetNewPlayerWeaponMode(short mode, short maxZoom, short minZoom);
     void SetParametersForScriptInterpolation(float InterpolationToStopMoving, float InterpolationToCatchUp, unsigned int TimeForInterPolation);
     void SetPercentAlongCutScene(float percent);
     void SetRwCamera(RwCamera *rwcamera);
     void SetWideScreenOff();
     void SetWideScreenOn();
    //! zoomMode : 0- ZOOM_ONE , 1- ZOOM_TWO , 2- ZOOM_THREE
     void SetZoomValueCamStringScript(short zoomMode);
    //! zoomMode : value between 0 - 2
     void SetZoomValueFollowPedScript(short zoomMode);
     void StartCooperativeCamMode();
    //! currentCamMode : see eCamMode
     void StartTransition(short currentCamMode);
    //! unused , see eCamMode
     void StartTransitionWhenNotFinishedInter(short currentCamMode);
    //! unused
     void StopCooperativeCamMode();
     void StoreValuesDuringInterPol(CVector *SourceDuringInter, CVector *TargetDuringInter, CVector *UpDuringInter, float *FOVDuringInter);
    //! TypeOfSwitch : see eSwitchType
    //! ModeToGoTo : see eCamMode
     void TakeControl(CEntity *target, short ModeToGoTo, short TypeOfSwitch, int WhoIsInControlOfTheCamera);
    //! TypeOfSwitch : see eSwitchType
     void TakeControlAttachToEntity(CEntity *target, CEntity *attached, CVector *AttachedCamOffset, CVector *AttachedCamLookAt, float AttachedCamAngle, short TypeOfSwitch, int WhoIsInControlOfTheCamera);
    //! TypeOfSwitch : see eSwitchType
     void TakeControlNoEntity(CVector const *FixedModeVector, short TypeOfSwitch, int WhoIsInControlOfTheCamera);
    //! TypeOfSwitch : see eSwitchType
     void TakeControlWithSpline(short TypeOfSwitch);
     bool TryToStartNewCamMode(int CamSequence);
     void UpdateAimingCoors(CVector const *AimingTargetCoors);
     void UpdateSoundDistances();
     void UpdateTargetEntity();
     bool Using1stPersonWeaponMode();
     void VectorMoveLinear(CVector *MoveLinearPosnEnd, CVector *MoveLinearPosnStart, float duration, bool bMoveLinearWithEase);
     bool VectorMoveRunning();
     void VectorTrackLinear(CVector *TrackLinearStartPoint, CVector *TrackLinearEndPoint, float duration, bool bEase);
     bool VectorTrackRunning();
     inline RwMatrix* GetRwMatrix() { return RwFrameGetMatrix(RwCameraGetFrame(m_pRwCamera)); }

    //! unused
     static void DontProcessObbeCinemaCamera();
     static void SetCamCollisionVarDataSet(int index);
     static void SetColVarsAimWeapon(int aimingType);
     static void SetColVarsPed(int pedtype, int nCamPedZoom);
     static void SetColVarsVehicle(int vehicletype, int CamVehicleZoom);
};

VTABLE_DESC(CCamera, 0x8630E8, 1);

VALIDATE_SIZE(CCamera, 0xD78);

 extern CCamera &TheCamera;
 extern bool& gbModelViewer;

//#include "meta/meta.CCamera.h"
