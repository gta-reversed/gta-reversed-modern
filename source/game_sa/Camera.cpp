#include "StdInc.h"

#include "Camera.h"

#include "TaskSimpleHoldEntity.h"
#include "TaskSimpleDuck.h"
#include "Hud.h"

float& CCamera::m_f3rdPersonCHairMultY = *reinterpret_cast<float*>(0xB6EC10);
float& CCamera::m_f3rdPersonCHairMultX = *reinterpret_cast<float*>(0xB6EC14);
float& CCamera::m_fMouseAccelVertical = *reinterpret_cast<float*>(0xB6EC18);
float& CCamera::m_fMouseAccelHorzntl = *reinterpret_cast<float*>(0xB6EC1C);
bool& CCamera::m_bUseMouse3rdPerson = *reinterpret_cast<bool*>(0xB6EC2E);
bool& CCamera::bDidWeProcessAnyCinemaCam = *reinterpret_cast<bool*>(0xB6EC2D);

CCamera& TheCamera = *reinterpret_cast<CCamera*>(0xB6F028);
bool& gbModelViewer = *reinterpret_cast<bool*>(0xBA6728);
int8& gbCineyCamMessageDisplayed = *(int8*)0x8CC381; // 2
bool& gPlayerPedVisible = *(bool*)0x8CC380; // true
uint8& gCurCamColVars = *(uint8*)0x8CCB80;
float& gCurDistForCam = *(float*)0x8CCB84;
float*& gpCamColVars = *(float**)0xB6FE88;
float (&gCamColVars)[28][6] = *(float (*)[28][6])0x8CC8E0;

CCam& CCamera::GetActiveCamera() {
    return TheCamera.m_aCams[TheCamera.m_nActiveCam];
}

void CCamera::InjectHooks() {
    RH_ScopedClass(CCamera);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(GetArrPosForVehicleType, 0x50AF00);
    RH_ScopedInstall(GetPositionAlongSpline, 0x50AF80);
    RH_ScopedInstall(GetRoughDistanceToGround, 0x516B00);
    RH_ScopedInstall(InitialiseCameraForDebugMode, 0x50AF90);
    RH_ScopedInstall(ProcessObbeCinemaCameraPed, 0x50B880);
    RH_ScopedInstall(ProcessWideScreenOn, 0x50B890);
    RH_ScopedInstall(RenderMotionBlur, 0x50B8F0);
    RH_ScopedInstall(SetCameraDirectlyBehindForFollowPed_CamOnAString, 0x50BD40);
    RH_ScopedInstall(SetCameraDirectlyInFrontForFollowPed_CamOnAString, 0x50BD70);
    RH_ScopedInstall(SetCamPositionForFixedMode, 0x50BEC0);
    RH_ScopedInstall(SetFadeColour, 0x50BF00);
    RH_ScopedInstall(SetMotionBlur, 0x50BF40);
    RH_ScopedInstall(SetMotionBlurAlpha, 0x50BF80);
    RH_ScopedInstall(SetNearClipScript, 0x50BF90);
    RH_ScopedInstall(SetNewPlayerWeaponMode, 0x50BFB0);
    RH_ScopedInstall(SetRwCamera, 0x50C100);
    RH_ScopedInstall(SetWideScreenOn, 0x50C140);
    RH_ScopedInstall(SetWideScreenOff, 0x50C150);
    RH_ScopedInstall(StartCooperativeCamMode, 0x50C260);
    RH_ScopedInstall(StopCooperativeCamMode, 0x50C270);
    RH_ScopedInstall(AllowShootingWith2PlayersInCar, 0x50C280);
    RH_ScopedInstall(StoreValuesDuringInterPol, 0x50C290);
    RH_ScopedInstall(ProcessScriptedCommands, 0x516AE0);
    RH_ScopedInstall(FinishCutscene, 0x514950);
    RH_ScopedInstall(LerpFOV, 0x50D280);
    RH_ScopedInstall(UpdateAimingCoors, 0x50CB10);
    RH_ScopedInstall(SetColVarsAimWeapon, 0x50CBF0);
    RH_ScopedInstall(ClearPlayerWeaponMode, 0x50AB10);
    RH_ScopedInstall(DontProcessObbeCinemaCamera, 0x50AB40);
    RH_ScopedInstall(Enable1rstPersonCamCntrlsScript, 0x50AC00);
    RH_ScopedInstall(FindCamFOV, 0x50AD20);
    RH_ScopedInstall(GetFading, 0x50ADE0);
    RH_ScopedInstall(GetFadingDirection, 0x50ADF0);
    RH_ScopedInstall(Get_Just_Switched_Status, 0x50AE10);
    RH_ScopedInstall(GetGameCamPosition, 0x50AE50);

    RH_ScopedInstall(Constructor, 0x51A450, { .reversed = false });
    RH_ScopedInstall(InitCameraVehicleTweaks, 0x50A3B0);
    RH_ScopedInstall(ApplyVehicleCameraTweaks, 0x50A480);
    RH_ScopedInstall(CamShake, 0x50A9F0);
    RH_ScopedInstall(GetScreenRect, 0x50AB50);
    RH_ScopedInstall(Enable1rstPersonWeaponsCamera, 0x50AC10);
    RH_ScopedInstall(Fade, 0x50AC20);
    RH_ScopedInstall(Find3rdPersonQuickAimPitch, 0x50AD40, { .reversed = false });
    RH_ScopedInstall(GetCutSceneFinishTime, 0x50AD90);
    RH_ScopedInstall(GetScreenFadeStatus, 0x50AE20);
    RH_ScopedInstall(GetLookingLRBFirstPerson, 0x50AE60);
    RH_ScopedInstall(GetLookDirection, 0x50AE90);
    RH_ScopedInstall(GetLookingForwardFirstPerson, 0x50AED0);
    RH_ScopedInstall(CopyCameraMatrixToRWCam, 0x50AFA0, { .reversed = false });
    RH_ScopedInstall(CalculateMirroredMatrix, 0x50B380);
    RH_ScopedInstall(DealWithMirrorBeforeConstructRenderList, 0x50B510);
    RH_ScopedInstall(ProcessFade, 0x50B5D0);
    RH_ScopedInstall(ProcessMusicFade, 0x50B6D0, { .reversed = false });
    RH_ScopedInstall(Restore, 0x50B930);
    RH_ScopedInstall(RestoreWithJumpCut, 0x50BAB0);
    RH_ScopedInstall(SetCamCutSceneOffSet, 0x50BD20);
    RH_ScopedInstall(SetCameraDirectlyBehindForFollowPed_ForAPed_CamOnAString, 0x50BDA0, { .reversed = false });
    RH_ScopedInstall(SetCameraDirectlyInFrontForFollowPed_ForAPed_CamOnAString, 0x50BE30);
    RH_ScopedInstall(Using1stPersonWeaponMode, 0x50BFF0);
    RH_ScopedInstall(SetParametersForScriptInterpolation, 0x50C030);
    RH_ScopedInstall(SetPercentAlongCutScene, 0x50C070);
    RH_ScopedInstall(SetZoomValueFollowPedScript, 0x50C160);
    RH_ScopedInstall(SetZoomValueCamStringScript, 0x50C1B0, { .reversed = false });
    RH_ScopedInstall(UpdateTargetEntity, 0x50C360, { .reversed = false });
    RH_ScopedInstall(TakeControl, 0x50C7C0, { .reversed = false });
    RH_ScopedInstall(TakeControlNoEntity, 0x50C8B0);
    RH_ScopedInstall(TakeControlAttachToEntity, 0x50C910, { .reversed = false });
    RH_ScopedInstall(TakeControlWithSpline, 0x50CAE0);
    RH_ScopedInstall(SetCamCollisionVarDataSet, 0x50CB60);
    RH_ScopedInstall(SetNearClipBasedOnPedCollision, 0x50CB90, { .reversed = false });
    RH_ScopedInstall(SetColVarsPed, 0x50CC50);
    RH_ScopedInstall(SetColVarsVehicle, 0x50CCA0);
    RH_ScopedInstall(CameraGenericModeSpecialCases, 0x50CD30);
    RH_ScopedInstall(CameraPedModeSpecialCases, 0x50CD80);
    RH_ScopedInstall(CameraPedAimModeSpecialCases, 0x50CDA0);
    RH_ScopedInstall(CameraVehicleModeSpecialCases, 0x50CDE0);
    RH_ScopedInstall(IsExtraEntityToIgnore, 0x50CE80);
    RH_ScopedInstall(ConsiderPedAsDucking, 0x50CEB0);
    RH_ScopedInstall(ResetDuckingSystem, 0x50CEF0);
    RH_ScopedInstall(HandleCameraMotionForDucking, 0x50CFA0, { .reversed = false });
    RH_ScopedInstall(HandleCameraMotionForDuckingDuringAim, 0x50D090, { .reversed = false });
    RH_ScopedInstall(VectorMoveLinear, 0x50D160, { .reversed = false });
    RH_ScopedInstall(VectorTrackLinear, 0x50D1D0, { .reversed = false });
    RH_ScopedInstall(AddShakeSimple, 0x50D240);
    RH_ScopedInstall(InitialiseScriptableComponents, 0x50D2D0);
    RH_ScopedInstall(DrawBordersForWideScreen, 0x514860);
    RH_ScopedInstall(Find3rdPersonCamTargetVector, 0x514970, { .reversed = false });
    RH_ScopedInstall(CalculateGroundHeight, 0x514B80, { .reversed = false });
    RH_ScopedInstall(CalculateFrustumPlanes, 0x514D60, { .reversed = false });
    RH_ScopedInstall(CalculateDerivedValues, 0x5150E0, { .reversed = false });
    RH_ScopedInstall(ImproveNearClip, 0x516B20, { .reversed = false });
    RH_ScopedInstall(SetCameraUpForMirror, 0x51A560);
    RH_ScopedInstall(RestoreCameraAfterMirror, 0x51A5A0);
    RH_ScopedInstall(ConeCastCollisionResolve, 0x51A5D0, { .reversed = false });
    RH_ScopedInstall(TryToStartNewCamMode, 0x51E560, { .reversed = false });
    RH_ScopedInstall(CameraColDetAndReact, 0x520190, { .reversed = false });
    RH_ScopedInstall(CamControl, 0x527FA0, { .reversed = false });
    RH_ScopedInstall(Process, 0x52B730, { .reversed = false });
    RH_ScopedInstall(DeleteCutSceneCamDataMemory, 0x5B24A0);
    RH_ScopedInstall(LoadPathSplines, 0x5B24D0, { .reversed = false });
    RH_ScopedInstall(Init, 0x5BC520, { .reversed = false });

    RH_ScopedOverloadedInstall(ProcessVectorTrackLinear, "0", 0x50D350, void(CCamera::*)(float), { .reversed = false });
    RH_ScopedOverloadedInstall(ProcessVectorTrackLinear, "1", 0x516440, void(CCamera::*)(), {.reversed = false});
    RH_ScopedOverloadedInstall(ProcessVectorMoveLinear, "0", 0x50D430, void(CCamera::*)(float), { .reversed = false });
    RH_ScopedOverloadedInstall(ProcessVectorMoveLinear, "1", 0x5164A0, void(CCamera::*)(), { .reversed = false });
    RH_ScopedOverloadedInstall(ProcessFOVLerp, "0", 0x50D510, void(CCamera::*)(float), { .reversed = false });
    RH_ScopedOverloadedInstall(ProcessFOVLerp, "1", 0x516500, void(CCamera::*)(), { .reversed = false });
    //RH_ScopedOverloadedInstall(ProcessJiggle, "0", 0x516560, { .reversed = false });

    RH_ScopedGlobalInstall(CamShakeNoPos, 0x50A970);
}

CCamera* CCamera::Constructor() { this->CCamera::CCamera(); return this; }

// 0x51A450
CCamera::CCamera() : CPlaceable() {
    m_nShakeType = 1;
    m_bMusicFadedOut = false;
    m_matrix = reinterpret_cast<CMatrixLink*>(&m_mCameraMatrix);
    m_fDuckCamMotionFactor = 0.0f;
    m_fDuckAimCamMotionFactor = 0.0f;

    InitialiseScriptableComponents();
}

// 0x50A870
CCamera::~CCamera() {
    m_matrix = nullptr;
}

// 0x5BC520
void CCamera::Init() {
    return plugin::CallMethod<0x5BC520, CCamera*>(this);

    memset(&m_bAboveGroundTrainNodesLoaded, 0, 0xD60u);
    m_pRwCamera = nullptr;
    InitialiseScriptableComponents();
    m_bPlayerWasOnBike = false;
    m_b1rstPersonRunCloseToAWall = false;
    m_fPositionAlongSpline = 0.0f;
    m_bCameraJustRestored = false;

    for (auto& camera : m_aCams) {
        camera.Init();
    }

    m_bEnable1rstPersonCamCntrlsScript = false;
    m_bAllow1rstPersonWeaponsCamera = false;
    m_bCooperativeCamMode = false;
    m_bAllowShootingWith2PlayersInCar = true;
    m_bVehicleSuspenHigh = false;

    m_aCams[0].m_nMode = MODE_FOLLOWPED;
    m_aCams[0].m_fTargetCloseInDist = 2.0837801f - 1.85f;
    m_aCams[0].m_fMinRealGroundDist = 1.85f;
    m_aCams[0].m_fTargetZoomGroundOne = -0.55f;
    m_aCams[0].m_fTargetZoomGroundTwo = 1.5f;
    m_aCams[0].m_fTargetZoomGroundThree = 3.6f;
    m_aCams[0].m_fTargetZoomOneZExtra = 0.06f;
    m_aCams[0].m_fTargetZoomTwoZExtra = -0.1f;
    m_aCams[0].m_fTargetZoomTwoInteriorZExtra = 0.0f;
    m_aCams[0].m_fTargetZoomThreeZExtra = -0.07f;
    m_aCams[0].m_fTargetZoomZCloseIn = 0.90040702f;

    m_aCams[0].m_pCamTargetEntity = nullptr;
    m_aCams[0].m_fCamBufferedHeight = 0.0f;
    m_aCams[0].m_fCamBufferedHeightSpeed = 0.0f;
    m_aCams[0].m_bCamLookingAtVector = false;
    m_aCams[0].m_fPlayerVelocity = 0.0f;

    m_aCams[1].m_nMode = MODE_FOLLOWPED;
    m_aCams[1].m_pCamTargetEntity = nullptr;
    m_aCams[1].m_fCamBufferedHeight = 0.0f;
    m_aCams[1].m_fCamBufferedHeightSpeed = 0.0f;
    m_aCams[1].m_bCamLookingAtVector = false;
    m_aCams[1].m_fPlayerVelocity = 0.0f;

    m_aCams[2].m_pCamTargetEntity = nullptr;
    m_aCams[2].m_bCamLookingAtVector = false;
    m_aCams[2].m_fPlayerVelocity = 0.0f;

    m_bMoveCamToAvoidGeom = false;
    ClearPlayerWeaponMode();
    m_bInATunnelAndABigVehicle = false;

    m_bHeadBob = false;
    m_fFractionInterToStopMoving = 0.25f;
    m_fFractionInterToStopCatchUp = 0.75f;
    m_fGaitSwayBuffer = 0.85f;
    m_bScriptParametersSetForInterp = false;
    m_nCamShakeStart = 0;
    m_fCamShakeForce = 0.0f;
    m_nModeObbeCamIsInForCar = 30;
    m_bIgnoreFadingStuffForMusic = false;
    m_bWaitForInterpolToFinish = false;

    m_pToGarageWeAreIn = nullptr;
    m_pToGarageWeAreInForHackAvoidFirstPerson = nullptr;
    m_bPlayerIsInGarage = false;
    m_bJustCameOutOfGarage = false;

    m_fNearClipScript = 0.9f;
    m_bUseNearClipScript = false;
    m_bDoingSpecialInterp = false;
    m_bBelowGroundTrainNodesLoaded = false;

    m_nModeForTwoPlayersSeparateCars = MODE_TWOPLAYER_SEPARATE_CARS;
    m_nModeForTwoPlayersSameCarShootingAllowed = MODE_TWOPLAYER_IN_CAR_AND_SHOOTING;
    m_nModeForTwoPlayersSameCarShootingNotAllowed = MODE_BEHINDCAR;
    m_nModeForTwoPlayersNotBothInCar = MODE_TWOPLAYER;

    m_bWideScreenOn = false;
    m_fFOV_Wide_Screen = 0.0f;
    m_bRestoreByJumpCut = false;

    m_nCarZoom = 2;
    m_nPedZoom = 2;

    m_fCarZoomSmoothed = 0.0f;
    m_fCarZoomTotal = 0.0f;
    m_fCarZoomBase = 0.0f;
    m_fPedZoomSmoothed = 0.0f;
    m_fPedZoomTotal = 0.0f;
    m_fPedZoomBase = 0.0f;
    if (FindPlayerVehicle()) {
        m_pTargetEntity = FindPlayerVehicle();
    } else {
        m_pTargetEntity = FindPlayerPed();
    }
    CEntity::SafeRegisterRef(m_pTargetEntity);

    m_bInitialNodeFound = false;
    m_fScreenReductionPercentage = 0.0f;
    m_fScreenReductionSpeed = 0.0f;
    m_bWideScreenOn = false;
    m_bWantsToSwitchWidescreenOff = false;
    m_bWorldViewerBeingUsed = false;
    m_fPlayerExhaustion = 1.0f;
    m_fPedOrientForBehindOrInFront = 0.0f;

    if (!FrontEndMenuManager.m_bStartGameLoading) {
        m_bFading = false;
        CDraw::FadeValue = 0;
        m_fFadeAlpha = 0.0f;
        m_bMusicFading = false;
        m_fTimeToFadeMusic = 0.0f;
        m_fEffectsFaderScalingFactor = 0.0f;
        m_fMouseAccelVertical = 0.0015f;
    }

    if (FrontEndMenuManager.m_bStartGameLoading)
        m_fTimeToFadeMusic = 0.0f;

    m_bStartingSpline = false;
    m_nTypeOfSwitch = eSwitchType::INTERPOLATION;
    m_bUseScriptZoomValuePed = false;
    m_bUseScriptZoomValueCar = false;
    m_fPedZoomValueScript = 0.0f;
    m_fCarZoomValueScript = 0.0f;
    m_bUseSpecialFovTrain = false;
    m_fFovForTrain = 70.0f;
    m_nModeToGoTo = MODE_FOLLOWPED;
    m_bJust_Switched = false;
    m_bUseTransitionBeta = false;
    m_mCameraMatrix.SetScale(1.0f);
    m_bTargetJustBeenOnTrain = false;
    m_bInitialNoNodeStaticsSet = false;
    m_nLongestTimeInMill = 5000;
    m_nTimeLastChange = 0;
    m_bIdleOn = false;
    m_nTimeWeLeftIdle_StillNoInput = 0;
    m_nTimeWeEnteredIdle = 0;
    m_fLODDistMultiplier = 1.0f;
    m_bCamDirectlyBehind = false;
    m_bCamDirectlyInFront = false;
    m_nMotionBlur = 0;
    m_bGarageFixedCamPositionSet = false;
    SetMotionBlur(255, 255, 255, 0, 0);
    m_bCullZoneChecksOn = false;
    m_bFailedCullZoneTestPreviously = false;
    m_nCheckCullZoneThisNumFrames = 6;
    m_nZoneCullFrameNumWereAt = 0;
    m_fCameraAverageSpeed = 0.0f;
    m_fCameraSpeedSoFar = 0.0f;

    m_vecPreviousCameraPosition = CVector{};

    m_nWorkOutSpeedThisNumFrames = 4;
    m_nNumFramesSoFar = 0;
    m_bJustInitialized = true;
    m_bTransitionState = false;

    m_nTimeTransitionStart = 0;

    m_bLookingAtPlayer = true;
    m_bLookingAtVector = false;

    m_f3rdPersonCHairMultX = 0.53f;
    m_f3rdPersonCHairMultY = 0.4f;

    m_fAvoidTheGeometryProbsTimer = 0.0f;
    m_nAvoidTheGeometryProbsDirn = 0;

    gPlayerPedVisible = 1;
    m_bResetOldMatrix = true;
}

// 0x50A3B0
void CCamera::InitCameraVehicleTweaks() {
    m_fCurrentTweakDistance   = 1.0f;
    m_fCurrentTweakAltitude   = 1.0f;
    m_fCurrentTweakAngle      = 0.0f;
    m_nCurrentTweakModelIndex = -1;

    if (!m_bCameraVehicleTweaksInitialized) {
        for (auto& camTweak : m_aCamTweak) {
            camTweak.m_nModelIndex = -1;
            camTweak.m_fDistance   = 1.0f;
            camTweak.m_fAltitude   = 1.0f;
            camTweak.m_fAngle      = 0.0f;
        }

        m_aCamTweak[0].m_nModelIndex = MODEL_RCGOBLIN;
        m_aCamTweak[0].m_fDistance = 1.0f;
        m_aCamTweak[0].m_fAltitude = 1.0f;
        m_aCamTweak[0].m_fAngle    = 0.178997f; // todo: magic number

        m_bCameraVehicleTweaksInitialized = true;
    }
}

// 0x50D2D0
void CCamera::InitialiseScriptableComponents() {
    m_fTrackLinearStartTime    = -1.0f;
    m_fTrackLinearEndTime      = -1.0f;
    m_fStartShakeTime          = -1.0f;
    m_fEndShakeTime            = -1.0f;
    m_fEndZoomTime             = -1.0f;
    m_fStartZoomTime           = -1.0f;
    m_fZoomInFactor            = +0.0f;
    m_fZoomOutFactor           = +0.0f;
    m_bTrackLinearWithEase     = true;
    m_nZoomMode                = 1;
    m_bMoveLinearWithEase      = true;
    m_fMoveLinearStartTime     = -1.0f;
    m_fMoveLinearEndTime       = -1.0f;
    m_bBlockZoom               = false;
    m_bCameraPersistPosition   = false;
    m_bCameraPersistTrack      = false;
    m_bVecTrackLinearProcessed = false;
    m_bVecMoveLinearProcessed  = false;
    m_bFOVLerpProcessed        = false;
}

// 0x50AF90
void CCamera::InitialiseCameraForDebugMode() {
#ifndef FINAL
    if (auto* vehicle = FindPlayerVehicle()) {
        m_aCams[2].m_vecSource = vehicle->GetPosition();
    } else if (auto* player = FindPlayerPed()) {
        m_aCams[2].m_vecSource = player->GetPosition();
    }

    m_aCams[2].m_fTrueAlpha = 0.0f;
    m_aCams[2].m_fTrueBeta  = 0.0f;
    m_aCams[2].m_nMode = eCamMode::MODE_DEBUG;
#endif
}

// 0x50A480
void CCamera::ApplyVehicleCameraTweaks(CVehicle* vehicle) {
    if (vehicle->m_nModelIndex == m_nCurrentTweakModelIndex) {
        return;
    }

    InitCameraVehicleTweaks();
    for (auto& camTweak : m_aCamTweak) {
        if (camTweak.m_nModelIndex == (int32)vehicle->m_nModelIndex) { // todo: vehicle->m_nModelIndex -> int16?
            m_fCurrentTweakDistance = camTweak.m_fDistance;
            m_fCurrentTweakAltitude = camTweak.m_fAltitude;
            m_fCurrentTweakAngle    = camTweak.m_fAngle;
            return;
        }
    }
}

// 0x50A9F0
void CCamera::CamShake(float strength, CVector from) {
    auto dist = DistanceBetweenPoints(from, GetActiveCamera().m_vecSource);
    dist = std::clamp(dist, 0.0f, 100.0f);

    float percentShakeForce = 1.0f - dist / 100.f;
    float shakeForce = (m_fCamShakeForce - float(CTimer::GetTimeInMS() - m_nCamShakeStart) / 1000.f) * percentShakeForce;

    float toShakeForce = percentShakeForce * strength * 0.35f;
    if (toShakeForce > std::clamp(shakeForce, 0.0f, 2.0f)) {
        m_fCamShakeForce = toShakeForce;
        m_nCamShakeStart = CTimer::GetTimeInMS();
    }
}

// 0x50A970
void CamShakeNoPos(CCamera* camera, float strength) {
    float oldShake = camera->m_fCamShakeForce - float(CTimer::GetTimeInMS() - camera->m_nCamShakeStart) / 1000.f;

    if (strength > std::clamp(oldShake, 0.0f, 2.0f)) {
        camera->m_fCamShakeForce = strength;
        camera->m_nCamShakeStart = CTimer::GetTimeInMS();
    }
}

// 0x50AB10
void CCamera::ClearPlayerWeaponMode() {
    m_PlayerWeaponMode.m_nMode = 0;
    m_PlayerWeaponMode.m_nMaxZoom = 1;
    m_PlayerWeaponMode.m_nMinZoom = -1;
    m_PlayerWeaponMode.m_fDuration = 0.0f;
}

// 0x50AB40
void CCamera::DontProcessObbeCinemaCamera() {
    bDidWeProcessAnyCinemaCam = false;
}

// 0x50AC00
void CCamera::Enable1rstPersonCamCntrlsScript() {
    m_bEnable1rstPersonCamCntrlsScript = true;
}

// 0x50AC10
void CCamera::Enable1rstPersonWeaponsCamera() {
    m_bAllow1rstPersonWeaponsCamera = true;
}

// 0x50AC20
void CCamera::Fade(float duration, eFadeFlag direction) {
    m_fFadeDuration = duration;
    m_bFading = true;
    m_nFadeInOutFlag = direction;
    m_nFadeStartTime = CTimer::GetTimeInMS();

    if (m_bIgnoreFadingStuffForMusic && direction != eFadeFlag::FADE_OUT)
        return;

    m_bMusicFading = true;
    m_nMusicFadingDirection = direction;

    m_fTimeToFadeMusic = std::clamp(duration * 0.3f, duration * 0.3f, duration);

    switch (direction) {
    case eFadeFlag::FADE_IN:
        m_fTimeToWaitToFadeMusic = duration - m_fTimeToFadeMusic;
        m_fTimeToFadeMusic       = std::max(0.0f, m_fTimeToFadeMusic - 0.1f);
        m_nFadeTimeStartedMusic  = CTimer::GetTimeInMS();
        break;
    case eFadeFlag::FADE_OUT:
        m_fTimeToWaitToFadeMusic = 0.0f;
        m_nFadeTimeStartedMusic  = CTimer::GetTimeInMS();
        break;
    }
}

// 0x50AD20
float CCamera::FindCamFOV() {
    return m_aCams[m_nActiveCam].m_fFOV;
}

// 0x50AD40
float CCamera::Find3rdPersonQuickAimPitch() {
    return plugin::CallMethodAndReturn<float, 0x50AD40, CCamera*>(this);

    const auto& cam = m_aCams[m_nActiveCam];
    const auto radians = DegreesToRadians(cam.m_fFOV / 2.0f);
    const auto tan1  = std::tan(radians) * (0.5f - m_f3rdPersonCHairMultY + 0.5f - m_f3rdPersonCHairMultY) * (1.0f / CDraw::ms_fAspectRatio);
    const auto atan1 = std::atan2(tan1, 1.0f);
    const auto pitch = atan1 + cam.m_fVerticalAngle;
    return -pitch;
}

// 0x50AD90
uint32 CCamera::GetCutSceneFinishTime() {
    auto& cam = m_aCams[m_nActiveCam];
    if (cam.m_nMode == eCamMode::MODE_FLYBY) {
        return cam.m_nFinishTime;
    }

    cam = m_aCams[(m_nActiveCam + 1) % 2];
    if (cam.m_nMode == eCamMode::MODE_FLYBY) {
        return cam.m_nFinishTime;
    }

    return 0;
}

// 0x50ADE0
bool CCamera::GetFading() const {
    return m_bFading;
}

// TODO: eFadingDirection
// 0x50ADF0
int32 CCamera::GetFadingDirection() const {
    if (m_bFading)
        return m_nFadeInOutFlag == eFadeFlag::FADE_OUT;
    else
        return 2;
}

// 0x50AE10
bool CCamera::Get_Just_Switched_Status() const {
    return m_bJust_Switched;
}

// 0x50AE20
eNameState CCamera::GetScreenFadeStatus() const {
    if (m_fFadeAlpha == 0.0f) {
        return NAME_DONT_SHOW;
    }
    if (m_fFadeAlpha == 255.0f) {
        return NAME_FADE_IN;
    }

    return NAME_SHOW;
}

// 0x50AE50
CVector* CCamera::GetGameCamPosition() {
    return &m_vecGameCamPos;
}

// 0x50AE60
bool CCamera::GetLookingLRBFirstPerson() {
    return m_aCams[m_nActiveCam].m_nMode == eCamMode::MODE_1STPERSON
        && m_aCams[m_nActiveCam].m_nDirectionWasLooking != LOOKING_DIRECTION_FORWARD;
}

// 0x50AED0
bool CCamera::GetLookingForwardFirstPerson() {
    return m_aCams[m_nActiveCam].m_nMode == eCamMode::MODE_1STPERSON
        && m_aCams[m_nActiveCam].m_nDirectionWasLooking == LOOKING_DIRECTION_FORWARD;
}

// 0x50AE90
int32 CCamera::GetLookDirection() {
    const auto& cam = m_aCams[m_nActiveCam];
    if (cam.m_nMode != eCamMode::MODE_CAM_ON_A_STRING &&
        cam.m_nMode != eCamMode::MODE_1STPERSON &&
        cam.m_nMode != eCamMode::MODE_BEHINDBOAT &&
        cam.m_nMode != eCamMode::MODE_FOLLOWPED ||
        (cam.m_nDirectionWasLooking == LOOKING_DIRECTION_FORWARD)
    ) {
        return LOOKING_DIRECTION_FORWARD;
    }

    return cam.m_nDirectionWasLooking; // todo: unsigned/signed
}

// 0x50AF00
void CCamera::GetArrPosForVehicleType(eVehicleType type, int32& arrPos) {
    switch (type) {
    case VEHICLE_TYPE_MTRUCK:
        arrPos = 0;
        break;
    case VEHICLE_TYPE_QUAD:
        arrPos = 1;
        break;
    case VEHICLE_TYPE_HELI:
        arrPos = 2;
        break;
    case VEHICLE_TYPE_PLANE:
        arrPos = 4;
        break;
    case VEHICLE_TYPE_BOAT:
        arrPos = 3;
        break;
    default:
        break;
    }
}

// 0x50AF80
float CCamera::GetPositionAlongSpline() const {
    return m_fPositionAlongSpline;
}

// 0x516B00
float CCamera::GetRoughDistanceToGround() {
    return m_aCams[m_nActiveCam].m_vecSource.z - CalculateGroundHeight(eGroundHeightType::ENTITY_BOUNDINGBOX_BOTTOM);
}

// 0x50AFA0
void CCamera::CopyCameraMatrixToRWCam(bool bUpdateMatrix) {
    return plugin::CallMethod<0x50AFA0, CCamera*, bool>(this, bUpdateMatrix);
}

// 0x50B380
void CCamera::CalculateMirroredMatrix(CVector posn, float mirrorV, CMatrix *camMatrix, CMatrix* mirrorMatrix) {
    mirrorMatrix->GetPosition() = camMatrix->GetPosition() - posn * 2 * (DotProduct(posn, camMatrix->GetPosition()) - mirrorV);

    const CVector fwd = camMatrix->GetForward() - posn * 2 * DotProduct(posn, camMatrix->GetForward());
    mirrorMatrix->GetForward() = fwd;

    const CVector up = camMatrix->GetUp() - posn * 2 * DotProduct(posn, camMatrix->GetUp());
    mirrorMatrix->GetUp() = up;

    mirrorMatrix->GetRight() = CVector{
        up.y * fwd.z - up.z * fwd.y,
        up.z * fwd.x - up.x * fwd.z,
        up.x * fwd.y - up.y * fwd.x
    };
}

// 0x50B510
void CCamera::DealWithMirrorBeforeConstructRenderList(bool bActiveMirror, CVector mirrorNormal, float mirrorV, CMatrix* matMirror) {
    m_bMirrorActive = bActiveMirror;

    if (!bActiveMirror)
        return;

    if (matMirror)
        m_mMatMirror = *matMirror;
    else
        CalculateMirroredMatrix(mirrorNormal, mirrorV, &m_mCameraMatrix, &m_mMatMirror);

    m_mMatMirrorInverse = Invert(m_mMatMirror);
}

/// III/VC leftover
// 0x50B8F0
void CCamera::RenderMotionBlur() {
    if (m_nBlurType) {
        // CMBlur::MotionBlurRender(); // todo: Add CMBlur::MotionBlurRender is NOP, 0x71D700
    }
}

// 0x50B930
void CCamera::Restore() {
    m_bLookingAtPlayer = true;
    m_bLookingAtVector = false;
    m_nTypeOfSwitch = eSwitchType::INTERPOLATION;
    m_bUseNearClipScript = false;
    m_nModeObbeCamIsInForCar = 30;
    m_fPositionAlongSpline = 0.0f;
    m_bStartingSpline = false;
    m_bScriptParametersSetForInterp = false;
    m_nWhoIsInControlOfTheCamera = 0;

    CVehicle* vehicle = FindPlayerVehicle();
    CPlayerPed* player = FindPlayerPed();

    if (vehicle) {
        m_nModeToGoTo = MODE_CAM_ON_A_STRING;
        CEntity::SafeCleanUpRef(m_pTargetEntity);
        m_pTargetEntity = vehicle;
    } else {
        m_nModeToGoTo = MODE_FOLLOWPED;
        CEntity::SafeCleanUpRef(m_pTargetEntity);
        m_pTargetEntity = player;
    }
    CEntity::SafeRegisterRef(m_pTargetEntity);

    switch (player->m_nPedState) {
    case PEDSTATE_ENTER_CAR:
    case PEDSTATE_CARJACK:
    case PEDSTATE_OPEN_DOOR:
        m_nModeToGoTo = MODE_CAM_ON_A_STRING;
        break;
    }

    if (player->m_nPedState == PEDSTATE_EXIT_CAR) {
        m_nModeToGoTo = MODE_FOLLOWPED;

        CEntity::SafeCleanUpRef(m_pTargetEntity);
        m_pTargetEntity = player;
        CEntity::SafeRegisterRef(m_pTargetEntity);
    }

    CEntity::ClearReference(m_pAttachedEntity);

    m_bEnable1rstPersonCamCntrlsScript = false;
    m_bAllow1rstPersonWeaponsCamera = false;
    m_bUseScriptZoomValuePed = false;
    m_bUseScriptZoomValueCar = false;
    m_fAvoidTheGeometryProbsTimer = 0.0f;
    m_bStartInterScript = true;
    m_bCameraJustRestored = true;
}

// 0x50BAB0
void CCamera::RestoreWithJumpCut() {
    m_bRestoreByJumpCut = true;
    m_bLookingAtPlayer = true;
    m_bLookingAtVector = false;
    m_nTypeOfSwitch = eSwitchType::JUMPCUT;
    m_nWhoIsInControlOfTheCamera = 0;
    m_fPositionAlongSpline = 0.0f;
    m_bStartingSpline = false;
    m_bUseNearClipScript = false;
    m_nModeObbeCamIsInForCar = 30;
    m_bScriptParametersSetForInterp = false;

    CVehicle* vehicle = FindPlayerVehicle();
    CPlayerPed* player = FindPlayerPed();

    if (vehicle) {
        m_nModeToGoTo = MODE_CAM_ON_A_STRING;
        CEntity::SafeCleanUpRef(m_pTargetEntity);
        m_pTargetEntity = vehicle;
    } else {
        m_nModeToGoTo = MODE_FOLLOWPED;
        CEntity::SafeCleanUpRef(m_pTargetEntity);
        m_pTargetEntity = player;
    }
    CEntity::SafeRegisterRef(m_pTargetEntity);

    switch (player->m_nPedState) {
    case PEDSTATE_ENTER_CAR:
    case PEDSTATE_CARJACK:
    case PEDSTATE_OPEN_DOOR:
        m_nModeToGoTo = MODE_CAM_ON_A_STRING;
        break;
    }

    if (player->m_nPedState == PEDSTATE_EXIT_CAR) {
        m_nModeToGoTo = MODE_FOLLOWPED;

        CEntity::SafeCleanUpRef(m_pTargetEntity);
        m_pTargetEntity = player;
        CEntity::SafeRegisterRef(m_pTargetEntity);
    }

    if (!m_bCooperativeCamMode) {
        m_bUseScriptZoomValuePed = false;
        m_bUseScriptZoomValueCar = false;
        return;
    }

    CPlayerPed* player0 = FindPlayerPed(0);
    CPlayerPed* player1 = FindPlayerPed(1);

    if (!player0) {
        m_bUseScriptZoomValuePed = false;
        m_bUseScriptZoomValueCar = false;
        return;
    }

    if (!player1) {
        m_bUseScriptZoomValuePed = false;
        m_bUseScriptZoomValueCar = false;
        return;
    }

    CEntity::SafeCleanUpRef(m_pTargetEntity);

    if (!player0->IsInVehicle() || !player1->IsInVehicle()) {
        m_nModeToGoTo = m_nModeForTwoPlayersNotBothInCar;
        m_pTargetEntity = player0;
        CEntity::SafeRegisterRef(m_pTargetEntity);

        m_bUseScriptZoomValuePed = false;
        m_bUseScriptZoomValueCar = false;
        return;
    }

    if (player0->m_pVehicle == player1->m_pVehicle) {
        if (m_bAllowShootingWith2PlayersInCar) {
            m_nModeToGoTo = m_nModeForTwoPlayersSameCarShootingAllowed;
        } else {
            m_nModeToGoTo = m_nModeForTwoPlayersSameCarShootingNotAllowed;
        }
    } else {
        m_nModeToGoTo = m_nModeForTwoPlayersSeparateCars;
    }

    m_pTargetEntity = player0->m_pVehicle;
    CEntity::SafeRegisterRef(m_pTargetEntity);

    m_bUseScriptZoomValuePed = false;
    m_bUseScriptZoomValueCar = false;
}

// 0x50BD20
void CCamera::SetCamCutSceneOffSet(const CVector& offset) {
    m_vecCutSceneOffset = offset;
}

// 0x50BD40
void CCamera::SetCameraDirectlyBehindForFollowPed_CamOnAString() {
    m_bCamDirectlyBehind = true;
    CPed* player = FindPlayerPed();
    if (player) {
        m_fPedOrientForBehindOrInFront = CGeneral::GetATanOfXY(player->GetForward().x, player->GetForward().y);
    }
}

// 0x50BD70
void CCamera::SetCameraDirectlyInFrontForFollowPed_CamOnAString() {
    m_bCamDirectlyInFront = true;
    CPed* player = FindPlayerPed();
    if (player != nullptr) {
        m_fPedOrientForBehindOrInFront = CGeneral::GetATanOfXY(player->GetForward().x, player->GetForward().y);
    }
}

// unused
// 0x50BDA0
void CCamera::SetCameraDirectlyBehindForFollowPed_ForAPed_CamOnAString(CPed* targetPed) {
    return plugin::CallMethod<0x50BDA0, CCamera*, CPed*>(this, targetPed);
}

// 0x50BE30
void CCamera::SetCameraDirectlyInFrontForFollowPed_ForAPed_CamOnAString(CPed* targetPed) {
    if (!targetPed) {
        return;
    }

    m_bLookingAtPlayer = false;
    m_pTargetEntity = targetPed;

    CCam& camera = GetActiveCamera();
    CEntity::SafeCleanUpRef(camera.m_pCamTargetEntity);

    camera.m_pCamTargetEntity = targetPed;
    camera.m_pCamTargetEntity->RegisterReference(camera.m_pCamTargetEntity);

    m_bCamDirectlyInFront = true;
    m_fPedOrientForBehindOrInFront = CGeneral::GetATanOfXY(targetPed->GetForward().x, targetPed->GetForward().y);
}

// 0x50BEC0
void CCamera::SetCamPositionForFixedMode(const CVector* fixedModeSource, const CVector* fixedModeUpOffset) {
    m_vecFixedModeSource = *fixedModeSource;
    m_vecFixedModeUpOffSet = *fixedModeUpOffset;
    m_bGarageFixedCamPositionSet = false;
}

// 0x50BF00
void CCamera::SetFadeColour(uint8 red, uint8 green, uint8 blue) {
    m_bFadeTargetIsSplashScreen = false;
    if (red == 2 && green == 2 && blue == 2) {
        m_bFadeTargetIsSplashScreen = true;
    }

    CDraw::FadeRed   = red;
    CDraw::FadeGreen = green;
    CDraw::FadeBlue  = blue;
}

// TODO: eBlurType
// 0x50BF40
void CCamera::SetMotionBlur(uint8 red, uint8 green, uint8 blue, int32 value, uint32 blurType) {
    m_nBlurRed    = red;
    m_nBlurGreen  = green;
    m_nBlurBlue   = blue;
    m_nBlurType   = blurType;
    m_nMotionBlur = value;
}

// 0x50BF80
void CCamera::SetMotionBlurAlpha(int32 alpha) {
    m_nMotionBlurAddAlpha = alpha;
}

// 0x50BF90
void CCamera::SetNearClipScript(float nearClip) {
    m_fNearClipScript = nearClip;
    m_bUseNearClipScript = true;
}

// 0x50BFB0
void CCamera::SetNewPlayerWeaponMode(eCamMode mode, int16 maxZoom, int16 minZoom) {
    m_PlayerWeaponMode.m_nMode     = mode;
    m_PlayerWeaponMode.m_nMinZoom  = minZoom;
    m_PlayerWeaponMode.m_nMaxZoom  = maxZoom;
    m_PlayerWeaponMode.m_fDuration = 0.0f;
}

// 0x50BFF0
bool CCamera::Using1stPersonWeaponMode() const {
    switch (m_PlayerWeaponMode.m_nMode) {
    case MODE_SNIPER:
    case MODE_M16_1STPERSON:
    case MODE_ROCKETLAUNCHER:
    case MODE_ROCKETLAUNCHER_HS:
    case MODE_HELICANNON_1STPERSON:
    case MODE_CAMERA:
    case MODE_AIMWEAPON_ATTACHED:
        return true;
    default:
        return false;
    }
}

// 0x50C030
void CCamera::SetParametersForScriptInterpolation(float interpolationToStopMoving, float interpolationToCatchUp, uint32 timeForInterpolation) {
    m_nScriptTimeForInterpolation = timeForInterpolation;
    m_bScriptParametersSetForInterp = true;
    m_fScriptPercentageInterToStopMoving = interpolationToStopMoving / 100.0f;
    m_fScriptPercentageInterToCatchUp = interpolationToCatchUp / 100.0f;
}

// 0x50C070
void CCamera::SetPercentAlongCutScene(float percent) {
    auto& cam = m_aCams[m_nActiveCam];
    if (cam.m_nMode == eCamMode::MODE_FLYBY) {
        cam.m_fTimeElapsedFloat = (float)cam.m_nFinishTime * percent / 100.0f;
        return;
    }

    cam = m_aCams[(m_nActiveCam + 1) % 2];
    if (cam.m_nMode == eCamMode::MODE_FLYBY) {
        cam.m_fTimeElapsedFloat = (float)cam.m_nFinishTime * percent / 100.0f;
        return;
    }
}

// 0x50C100
void CCamera::SetRwCamera(RwCamera* camera) {
    m_pRwCamera = camera;
    m_mViewMatrix.Attach(&camera->viewMatrix, false);
}

// 0x50C140
void CCamera::SetWideScreenOn() {
    m_bWideScreenOn = true;
    m_bWantsToSwitchWidescreenOff = false;
}

// 0x50C150
void CCamera::SetWideScreenOff() {
    m_bWantsToSwitchWidescreenOff = m_bWideScreenOn;
}

// 0x50C160
void CCamera::SetZoomValueFollowPedScript(int16 zoomMode) {
    switch (zoomMode) {
    case 1:
        m_fPedZoomValueScript = 1.50f;
        break;
    case 2:
        m_fPedZoomValueScript = 2.90f;
        break;
    default:
        m_fPedZoomValueScript = 0.25f;
    }
    m_bUseScriptZoomValuePed = true;
}

// zoomMode : 0- ZOOM_ONE , 1- ZOOM_TWO , 2- ZOOM_THREE
// 0x50C1B0
void CCamera::SetZoomValueCamStringScript(int16 zoomMode) {
    return plugin::CallMethod<0x50C1B0, CCamera*, int16>(this, zoomMode);

    static constexpr float ZOOM_ONE_DISTANCE_ptr[]   = { +1.0f, +1.4f, +0.65f, 1.90f, +6.49f }; // 0x8CC3F4
    static constexpr float ZOOM_TWO_DISTANCE_ptr[]   = { +6.0f, +6.0f, +15.9f, 15.9f, +15.0f }; // 0x8CC408
    static constexpr float ZOOM_THREE_DISTANCE_ptr[] = { -1.0f, -0.2f, -3.20f, 0.05f, -2.41f }; // 0x8CC3E0

    auto entity = m_aCams[0].m_pCamTargetEntity;
    if (entity->m_nStatus == STATUS_SIMPLE) {
        int32 arrPos = 0;
        auto appearance = static_cast<eVehicleType>(entity->AsVehicle()->GetVehicleAppearance());
        GetArrPosForVehicleType(appearance, arrPos);
        switch (zoomMode) {
        case 1:
            m_fCarZoomValueScript = ZOOM_ONE_DISTANCE_ptr[arrPos];
            break;
        case 2:
            m_fCarZoomValueScript = ZOOM_TWO_DISTANCE_ptr[arrPos];
            break;
        default:
            m_fCarZoomValueScript = ZOOM_THREE_DISTANCE_ptr[arrPos];
            break;
        }
        m_bUseScriptZoomValueCar = true;
        return;
    }

    SetZoomValueFollowPedScript(zoomMode);
}

// 0x50C260
void CCamera::StartCooperativeCamMode() {
    m_bCooperativeCamMode = true;
    CGameLogic::n2PlayerPedInFocus = eFocusedPlayer::NONE;
}

// 0x50C270
void CCamera::StopCooperativeCamMode() {
    m_bCooperativeCamMode = false;
    CGameLogic::n2PlayerPedInFocus = eFocusedPlayer::NONE;
}

// 0x50C280
void CCamera::AllowShootingWith2PlayersInCar(bool bAllow) {
    m_bAllowShootingWith2PlayersInCar = bAllow;
}

// 0x50C290
void CCamera::StoreValuesDuringInterPol(CVector* sourceDuringInter, CVector* targetDuringInter, CVector* upDuringInter, float* FOVDuringInter) {
    m_vecSourceDuringInter = *sourceDuringInter;
    m_vecTargetDuringInter = *targetDuringInter;
    m_vecUpDuringInter     = *upDuringInter;
    m_fFOVDuringInter      = *FOVDuringInter;

    auto dist = sourceDuringInter - m_vecTargetDuringInter;
    m_fBetaDuringInterPol = CGeneral::GetATanOfXY(dist.x, dist.y);

    float distOnGround = dist.Magnitude2D();
    m_fAlphaDuringInterPol = CGeneral::GetATanOfXY(distOnGround, dist.z);
}

// 0x50C360
void CCamera::UpdateTargetEntity() {
    plugin::CallMethod<0x50C360, CCamera*>(this);
}

// 0x50C7C0
void CCamera::TakeControl(CEntity* target, eCamMode modeToGoTo, eSwitchType switchType, int32 whoIsInControlOfTheCamera) {
    plugin::CallMethod<0x50C7C0, CCamera*, CEntity*, eCamMode, eSwitchType, int32>(this, target, modeToGoTo, switchType, whoIsInControlOfTheCamera);
}

// 0x50C8B0
void CCamera::TakeControlNoEntity(const CVector* fixedModeVector, eSwitchType switchType, int32 whoIsInControlOfTheCamera) {
    if (whoIsInControlOfTheCamera == 2 && m_nWhoIsInControlOfTheCamera == 1)
        return;

    m_nWhoIsInControlOfTheCamera = whoIsInControlOfTheCamera;
    m_bLookingAtVector           = true;
    m_nModeToGoTo                = MODE_FIXED;
    m_bLookingAtPlayer           = false;
    m_vecFixedModeVector         = *fixedModeVector;
    m_nTypeOfSwitch              = switchType;
    m_bStartInterScript          = true;
}

// 0x50C910
void CCamera::TakeControlAttachToEntity(CEntity* target, CEntity* attached, CVector* attachedCamOffset, CVector* attachedCamLookAt, float attachedCamAngle, eSwitchType switchType, int32 whoIsInControlOfTheCamera) {
    plugin::CallMethod<0x50C910, CCamera*, CEntity*, CEntity*, CVector*, CVector*, float, eSwitchType, int32>(this, target, attached, attachedCamOffset, attachedCamLookAt, attachedCamAngle, switchType, whoIsInControlOfTheCamera);
}

// 0x50CAE0
void CCamera::TakeControlWithSpline(eSwitchType switchType) {
    m_bLookingAtPlayer = false;
    m_bLookingAtVector = false;
    m_bCutsceneFinished = false;
    m_nModeToGoTo = MODE_FLYBY;
    m_nTypeOfSwitch = switchType;
    m_bStartInterScript = true;
}

// 0x50CB10
void CCamera::UpdateAimingCoors(const CVector& aimingTargetCoors) {
    m_vecAimingTargetCoors = aimingTargetCoors;
}

// 0x515BD0
void CCamera::UpdateSoundDistances() {
    plugin::CallMethod<0x515BD0, CCamera*>(this);
}

// unused
// 0x50CB90
void CCamera::SetNearClipBasedOnPedCollision(float arg2) {
    plugin::CallMethod<0x50CB90, CCamera*, float>(this, arg2);
}

// TODO: eAimingType
// 0x50CBF0
void CCamera::SetColVarsAimWeapon(int32 aimingType) {
    switch (aimingType) {
    case 0:
        CCamera::SetCamCollisionVarDataSet(0);
        break;
    case 1:
        CCamera::SetCamCollisionVarDataSet(1);
        break;
    case 2:
        CCamera::SetCamCollisionVarDataSet(2);
        break;
    case 3:
        CCamera::SetCamCollisionVarDataSet(3);
        break;
    default:
        return;
    }
}

// 0x50CC50
void CCamera::SetColVarsPed(ePedType pedType, int32 nCamPedZoom) {
    const int32 camColVars = [=] {
        switch (pedType) {
        case PED_TYPE_PLAYER1:
            return nCamPedZoom + 3;
        case PED_TYPE_PLAYER2:
            return nCamPedZoom + 6;
        default:
            return 0;
        }
    }();

    if (camColVars != gCurCamColVars) {
        gCurCamColVars = camColVars;
        gCurDistForCam = 1.0f;
        gpCamColVars = gCamColVars[camColVars];
    }
}

// 0x50CD30
void CCamera::CameraGenericModeSpecialCases(CPed* targetPed) {
    m_nExtraEntitiesCount = 0;

    if (!targetPed) {
        return;
    }

    auto* taskHold = static_cast<CTaskSimpleHoldEntity*>(targetPed->GetIntelligence()->GetTaskHold(false));
    if (!taskHold || !taskHold->m_pEntityToHold) {
        return;
    }

    m_pExtraEntity[m_nExtraEntitiesCount++] = targetPed;
}

// 0x50CD80
void CCamera::CameraPedModeSpecialCases() {
    CCollision::bCamCollideWithVehicles = true;
    CCollision::bCamCollideWithObjects  = true;
    CCollision::bCamCollideWithPeds     = true;
}

// 0x50CDA0
void CCamera::CameraPedAimModeSpecialCases(CPed* ped) {
    CameraPedModeSpecialCases();

    if (ped->IsInVehicle()) {
        m_pExtraEntity[m_nExtraEntitiesCount++] = ped->m_pVehicle;
    }
}

// 0x50CDE0
void CCamera::CameraVehicleModeSpecialCases(CVehicle* vehicle) {
    float speed = vehicle->m_vecMoveSpeed.Magnitude();

    const auto slow = speed <= 0.2f;
    CCollision::relVelCamCollisionVehiclesSqr = slow ? 0.1f : 1.0f;
    CCollision::bCamCollideWithVehicles = true;
    CCollision::bCamCollideWithPeds     = slow;
    CCollision::bCamCollideWithObjects  = slow;

    if (vehicle->m_pTrailer) {
        m_pExtraEntity[m_nExtraEntitiesCount++] = vehicle->m_pTrailer;
    }
}

// 0x50CE80
bool CCamera::IsExtraEntityToIgnore(CEntity* entity) {
    if (m_nExtraEntitiesCount <= 0) {
        return false;
    }

    for (auto& extraEntity : m_pExtraEntity) {
        if (extraEntity == entity) {
            return true;
        }
    }

    return false;
}

// 0x420C40
bool CCamera::IsSphereVisible(const CVector& origin, float radius, RwMatrix* transformMatrix) {
    return plugin::CallMethodAndReturn<bool, 0x420C40, CCamera*, const CVector&, float, RwMatrix*>(this, origin, radius, transformMatrix);
}

// 0x420D40
bool CCamera::IsSphereVisible(const CVector& origin, float radius) {
    return plugin::CallMethodAndReturn<bool, 0x420D40, CCamera*, const CVector&, float>(this, origin, radius);
}

// 0x50CEB0
bool CCamera::ConsiderPedAsDucking(CPed* ped) {
    auto task = ped->GetIntelligence()->GetTaskDuck(true);
    return task && ped->bIsDucking && !task->m_bIsAborting;
}

// 0x50CEF0
void CCamera::ResetDuckingSystem(CPed* ped) {
    m_fDuckCamMotionFactor    = 0.0f;
    m_fDuckAimCamMotionFactor = 0.0f;
    if (!ped)
        return;

    auto* task = ped->GetIntelligence()->GetTaskDuck(true);
    if (!task)
        return;

    if (!ped->bIsDucking || task->m_bIsAborting)
        return;

    float factor;
    if (ped->m_vecMoveSpeed.Magnitude() <= 0.000001f)
        factor = 0.3f - 1.0f;
    else
        factor = 0.3f - 0.5f;

    m_fDuckCamMotionFactor    = factor;
    m_fDuckAimCamMotionFactor = -0.35f;
}

// arg5 always used as false
// 0x50CFA0
void CCamera::HandleCameraMotionForDucking(CPed* ped, CVector* source, CVector* targPosn, bool arg5) {
    plugin::CallMethod<0x50CFA0, CCamera*, CPed*, CVector*, CVector*, bool>(this, ped, source, targPosn, arg5);
}

// arg5 always used as false
// 0x50D090
void CCamera::HandleCameraMotionForDuckingDuringAim(CPed* ped, CVector* source, CVector* targPosn, bool arg5) {
    plugin::CallMethod<0x50D090, CCamera*, CPed*, CVector*, CVector*, bool>(this, ped, source, targPosn, arg5);
}

// 0x50D160
void CCamera::VectorMoveLinear(CVector* moveLinearPosnEnd, CVector* moveLinearPosnStart, float duration, bool bMoveLinearWithEase) {
    plugin::CallMethod<0x50D160, CCamera*, CVector*, CVector*, float, bool>(this, moveLinearPosnEnd, moveLinearPosnStart, duration, bMoveLinearWithEase);
}

// 0x50D1D0
void CCamera::VectorTrackLinear(CVector* trackLinearStartPoint, CVector* trackLinearEndPoint, float duration, bool bEase) {
    plugin::CallMethod<0x50D1D0, CCamera*, CVector*, CVector*, float, bool>(this, trackLinearStartPoint, trackLinearEndPoint, duration, bEase);
}

// 0x516400
void CCamera::AddShake(float duration, float a2, float a3, float a4, float a5) {
    return AddShakeSimple(duration, 1, 1.0f);
}

// 0x50D240
void CCamera::AddShakeSimple(float duration, int32 type, float intensity) {
    m_fShakeIntensity = intensity;
    m_nShakeType = type;
    m_fStartShakeTime = static_cast<float>(CTimer::GetTimeInMS());
    m_fEndShakeTime = m_fStartShakeTime + duration;
}

// 0x50D280
void CCamera::LerpFOV(float zoomInFactor, float zoomOutFactor, float timeLimit, bool bEase) {
    m_fStartZoomTime = static_cast<float>(CTimer::GetTimeInMS());
    m_fEndZoomTime = static_cast<float>(CTimer::GetTimeInMS()) + timeLimit;

    m_nZoomMode = bEase; // TODO: Rename
    m_fZoomInFactor = zoomInFactor;
    m_fZoomOutFactor = zoomOutFactor;
}

// 0x50B5D0
void CCamera::ProcessFade() {
    if (!m_bFading) {
        return;
    }

    float fadeAlpha = 0.0f;

    if (m_nFadeInOutFlag == eFadeFlag::FADE_OUT) {
        m_fFadeDuration == 0.0f
            ? (m_fFadeAlpha += 0.0f)
            : (m_fFadeAlpha -= CTimer::GetTimeStepInSeconds() / m_fFadeDuration * 255.0f);

        if (m_fFadeAlpha > 0.0f) {
            CDraw::FadeValue = static_cast<uint8>(m_fFadeAlpha);
            return;
        }

        m_bFading = false;
    } else {
        if (m_nFadeInOutFlag == eFadeFlag::FADE_OUT) { // stupid, why not use a switch instead?
            CDraw::FadeValue = static_cast<uint8>(m_fFadeAlpha);
            return;
        }

        if (m_fFadeAlpha >= 255.0f) {
            m_bFading = false;
        }

        fadeAlpha = 255.0f;

        m_fFadeDuration == 0.0f
            ? (m_fFadeAlpha += 255.0f)
            : (m_fFadeAlpha += CTimer::GetTimeStepInSeconds() / m_fFadeDuration * 255.0f);

        if (m_fFadeAlpha < 255.0f) {
            CDraw::FadeValue = static_cast<uint8>(m_fFadeAlpha);
            return;
        }
    }

    m_fFadeAlpha = fadeAlpha;
    CDraw::FadeValue = static_cast<uint8>(m_fFadeAlpha);
}

// 0x50B6D0
void CCamera::ProcessMusicFade() {
    return plugin::CallMethod<0x50B6D0, CCamera*>(this);

    if (!m_bMusicFading)
        return;

    if (m_fTimeToWaitToFadeMusic <= 0.0f) {
        if (m_nModeToGoTo == MODE_TOPDOWN) {
            if (m_fTimeToFadeMusic > 0.0f)
                m_fEffectsFaderScalingFactor = CTimer::GetTimeStepInSeconds() / m_fTimeToFadeMusic + m_fEffectsFaderScalingFactor;
            else
                m_fEffectsFaderScalingFactor = 1.0f;

            if (m_fEffectsFaderScalingFactor >= 1.0f) {
                m_bMusicFadedOut = false;
                m_bMusicFading = false;
                m_fEffectsFaderScalingFactor = 1.0f;
            }
        } else if (m_nFadeInOutFlag == eFadeFlag::FADE_IN) {
            if (m_fEffectsFaderScalingFactor <= 0.0f) {
                m_bMusicFadedOut = true;
                m_bMusicFading = false;
                m_fEffectsFaderScalingFactor = 0.0f;
            }

            if (m_fTimeToFadeMusic > 0.0f)
                m_fEffectsFaderScalingFactor = m_fEffectsFaderScalingFactor - CTimer::GetTimeStepInSeconds() / m_fTimeToFadeMusic;
            else
                m_fEffectsFaderScalingFactor = 0.0f;

            if (m_fEffectsFaderScalingFactor <= 0.0f)
                m_fEffectsFaderScalingFactor = 0.0f;
        }
    } else {
        m_fTimeToWaitToFadeMusic = m_fTimeToWaitToFadeMusic - CTimer::GetTimeStepInSeconds();
    }

    if (!AudioEngine.IsLoadingTuneActive()) {
        AudioEngine.SetMusicFaderScalingFactor(m_fEffectsFaderScalingFactor);
        AudioEngine.SetEffectsFaderScalingFactor(m_fEffectsFaderScalingFactor);
    }
}

// unused, empty
// 0x50B880
void CCamera::ProcessObbeCinemaCameraPed() {
    // NOP
}

//
void CCamera::ProcessObbeCinemaCameraPlane() {
    assert(0);
}

//
void CCamera::ProcessObbeCinemaCameraTrain() {
    assert(0);
}

// 0x50B890
void CCamera::ProcessWideScreenOn() {
    if (m_bWantsToSwitchWidescreenOff) {
        m_bWantsToSwitchWidescreenOff = false;
        m_bWideScreenOn = false;
        m_fWideScreenReductionAmount = 0.0f;
        m_fScreenReductionPercentage = 0.0f;
        m_fFOV_Wide_Screen = 0.0f;
    } else {
        m_fWideScreenReductionAmount = 1.0f;
        m_fScreenReductionPercentage = 30.0f;
        m_fFOV_Wide_Screen = m_aCams[m_nActiveCam].m_fFOV * 0.3f;
    }
}

// 0x516440
void CCamera::ProcessVectorTrackLinear() {
    plugin::CallMethod<0x516440, CCamera*>(this);
}

// 0x50D350
void CCamera::ProcessVectorTrackLinear(float ratio) {
    plugin::CallMethod<0x50D350, CCamera*, float>(this, ratio);
}

//
void CCamera::ProcessObbeCinemaCameraBoat() {
    assert(0);
}

//
void CCamera::ProcessObbeCinemaCameraCar() {
    assert(0);
}

//
void CCamera::ProcessObbeCinemaCameraHeli() {
    assert(0);
}

// 0x50D430
void CCamera::ProcessVectorMoveLinear(float ratio) {
    plugin::CallMethod<0x50D430, CCamera*, float>(this, ratio);
}

// 0x516500
void CCamera::ProcessFOVLerp() {
    plugin::CallMethod<0x516500, CCamera*>(this);
}

// 0x50D510
void CCamera::ProcessFOVLerp(float ratio) {
    plugin::CallMethod<0x50D510, CCamera*, float>(this, ratio);
}

// 0x5164A0
void CCamera::ProcessVectorMoveLinear() {
    plugin::CallMethod<0x5164A0, CCamera*>(this);
}

// unused
// 0x51A6F0
void CCamera::ProcessShake() {
    plugin::CallMethod<0x51A6F0, CCamera*>(this);
}

// shakeIntensity not used
// 0x516560
CVector* CCamera::ProcessShake(float intensity) {
    return plugin::CallMethodAndReturn<CVector*, 0x516560, CCamera*, float>(this, intensity);
}

// inlined - 0x52B845
// 0x516AE0
void CCamera::ProcessScriptedCommands() {
    ProcessVectorMoveLinear();
    ProcessVectorTrackLinear();
    ProcessFOVLerp();
}

// 0x52B730
void CCamera::Process() {
    plugin::CallMethod<0x52B730, CCamera*>(this);
}

// 0x514860
void CCamera::DrawBordersForWideScreen() {
    CRect rect;
    GetScreenRect(&rect);
    if (m_nBlurType == MOTION_BLUR_NONE  || m_nBlurType == MOTION_BLUR_LIGHT_SCENE) {
        m_nMotionBlurAddAlpha = 80;
    }
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(NULL));
    CSprite2d::DrawRect({ -5.f, -5.f,     SCREEN_WIDTH + 5.f, rect.top         }, { 0, 0, 0, 255 });
    CSprite2d::DrawRect({ -5.f, rect.bottom, SCREEN_WIDTH + 5.f, SCREEN_HEIGHT + 5.f }, { 0, 0, 0, 255 });
}

// 0x514950
void CCamera::FinishCutscene() {
    SetPercentAlongCutScene(100.0f);
    m_fPositionAlongSpline = 1.0f;
    m_bCutsceneFinished = true;
}

// 0x514970
void CCamera::Find3rdPersonCamTargetVector(float range, CVector source, CVector* pCamera, CVector* pPoint) {
    plugin::CallMethod<0x514970, CCamera*, float, CVector, CVector*, CVector*>(this, range, source, pCamera, pPoint);
}

// 0x514B80
float CCamera::CalculateGroundHeight(eGroundHeightType type) {
    return plugin::CallMethodAndReturn<float, 0x514B80, CCamera*, eGroundHeightType>(this, type);
}

// 0x514D60
void CCamera::CalculateFrustumPlanes(bool bForMirror) {
    plugin::CallMethod<0x514D60, CCamera*, bool>(this, bForMirror);
}

// 0x5150E0
void CCamera::CalculateDerivedValues(bool bForMirror, bool bOriented) {
    return plugin::CallMethod<0x5150E0, CCamera*, bool, bool>(this, bForMirror, bOriented);
}

// 0x516B20
void CCamera::ImproveNearClip(CVehicle* vehicle, CPed* ped, CVector* source, CVector* targPosn) {
    return plugin::CallMethod<0x516B20, CCamera*, CVehicle*, CPed*, CVector*, CVector*>(this, vehicle, ped, source, targPosn);
}

static CMatrix& preMirrorMat = *(CMatrix*)0xB6FE40;

// 0x51A560
void CCamera::SetCameraUpForMirror() {
    preMirrorMat = m_mCameraMatrix;
    m_mCameraMatrix = m_mMatMirror;
    CopyCameraMatrixToRWCam(true);
    CalculateDerivedValues(true, false);
}

// 0x51A5A0
void CCamera::RestoreCameraAfterMirror() {
    SetMatrix(preMirrorMat);
    CopyCameraMatrixToRWCam(true);
    CalculateDerivedValues(false, false);
}

// 0x51A5D0
bool CCamera::ConeCastCollisionResolve(CVector* source, CVector* center, CVector* pVecOut, float radius, float arg5, float* pFloatOut) {
    return plugin::CallMethodAndReturn<bool, 0x51A5D0, CCamera*, CVector*, CVector*, CVector*, float, float, float*>(this, source, center, pVecOut, radius, arg5, pFloatOut);
}

// 0x51E560
bool CCamera::TryToStartNewCamMode(int32 camSequence) {
    return plugin::CallMethodAndReturn<bool, 0x51E560, CCamera*, int32>(this, camSequence);
}

// 0x520190
void CCamera::CameraColDetAndReact(CVector* source, CVector* target) {
    plugin::CallMethod<0x520190, CCamera*, CVector*, CVector*>(this, source, target);
}

// 0x527FA0
void CCamera::CamControl() {
    plugin::CallMethod<0x527FA0, CCamera*>(this);
}

// 0x5B24A0
void CCamera::DeleteCutSceneCamDataMemory() {
    for (auto& splines : m_aPathArray) {
        delete splines.m_pArrPathData;
        splines.m_pArrPathData = nullptr;
    }
}

// 0x5B24D0
void CCamera::LoadPathSplines(FILE* file) {
    plugin::CallMethod<0x5B24D0, CCamera*>(this);
}

// 0x50AB50
void CCamera::GetScreenRect(CRect* rect) {
    rect->left  = 0.0f;
    rect->right = SCREEN_WIDTH;

    if (m_bWideScreenOn) {
        rect->top = (float)(RsGlobal.maximumHeight / 2)          * m_fScreenReductionPercentage / 100.f - SCREEN_SCALE_Y(22.0f);
        rect->bottom    = SCREEN_HEIGHT - (RsGlobal.maximumHeight / 2) * m_fScreenReductionPercentage / 100.f - SCREEN_SCALE_Y(14.0f);
    } else {
        rect->top = 0.0f;
        rect->bottom    = SCREEN_HEIGHT;
    }
}

// 0x50CB60
void CCamera::SetCamCollisionVarDataSet(int32 index) {
    if (index == gCurCamColVars) {
        return;
    }

    gCurCamColVars = index;
    gCurDistForCam = 1.0f;
    gpCamColVars   = gCamColVars[index];
}

// 0x50CCA0
void CCamera::SetColVarsVehicle(eVehicleType vehicleType, int32 camVehicleZoom) {
    switch (vehicleType) {
        case VEHICLE_TYPE_AUTOMOBILE:
        case VEHICLE_TYPE_PLANE:
            SetCamCollisionVarDataSet(camVehicleZoom + 9);
            return;
        case VEHICLE_TYPE_MTRUCK:
            SetCamCollisionVarDataSet(camVehicleZoom + 12);
            return;
        case VEHICLE_TYPE_QUAD:
            SetCamCollisionVarDataSet(camVehicleZoom + 15);
            return;
        case VEHICLE_TYPE_HELI:
            SetCamCollisionVarDataSet(camVehicleZoom + 18);
            return;
        case VEHICLE_TYPE_BOAT:
            SetCamCollisionVarDataSet(camVehicleZoom + 21);
            return;
        case VEHICLE_TYPE_TRAIN:
            SetCamCollisionVarDataSet(camVehicleZoom + 24);
            return;
    }
}

// 0x515BC0
void CCamera::StartTransitionWhenNotFinishedInter(eCamMode currentCamMode) {
    m_bDoingSpecialInterp = true;
    StartTransition(currentCamMode);
}

// 0x515200
void CCamera::StartTransition(eCamMode currentCamMode) {
    plugin::CallMethod<0x515200, CCamera*, eCamMode>(this, currentCamMode);
}
