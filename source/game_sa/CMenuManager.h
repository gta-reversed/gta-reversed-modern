/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector2D.h"
#include "CSprite2d.h"

// Menu entries action to perform
enum eMenuActions {   // There's many actions @0x57702E and @0x57CD88
    MENU_ACTION_NA = 0,
    MENU_ACTION_TEXT = 1,       // Some static text at the top of the page (works only on first entry)
    MENU_ACTION_BACK = 2,       // Back to previous menu
    MENU_ACTION_YES = 3,       // Used as YES in menus (also as NO, weird?)
    MENU_ACTION_NO = 4,       // Used as NO in menus  (also as YES, weird?)
    MENU_ACTION_SWITCH = 5,       // Switch to target menu
    MENU_ACTION_SKIP = 20,      // Skip this entry (unselectable)
    MENU_ACTION_BACK_PC = 55,      // Same as BACK without a extra checking (?)
};

// Type of menu entries
enum eMenuEntryType {
    MENU_ENTRY_SAVE_1 = 1,
    MENU_ENTRY_SAVE_2,
    MENU_ENTRY_SAVE_3,
    MENU_ENTRY_SAVE_4,
    MENU_ENTRY_SAVE_5,
    MENU_ENTRY_SAVE_6,
    MENU_ENTRY_SAVE_7,
    MENU_ENTRY_SAVE_8,
    MENU_ENTRY_MISSIONPACK,
    MENU_ENTRY_JOYMOUSE,
    MENU_ENTRY_BUTTON,
    MENU_ENTRY_OPTION,
};

enum eMenuPage {
    MENUPAGE_STATS = 0,
    MENUPAGE_START_GAME = 1, // New Game, Load Game, Delete Game
    MENUPAGE_BRIEF = 2,
    MENUPAGE_AUDIO_SETTINGS = 3,
    MENUPAGE_DISPLAY_SETTINGS = 4,
    MENUPAGE_MAP = 5,
    MENUPAGE_NEW_GAME_ASK = 6, // Are you sure you want to start a new game? All current game progress will be lost. Proceed?
    MENUPAGE_SELECT_GAME = 7, // Please select which new game you wish to start:
    MENUPAGE_MISSIONPACK_LOADING_ASK = 8, // // Are you sure you want to load a San Andreas Mission Pack? All current game progress will be lost. Proceed?
    MENUPAGE_LOAD_GAME = 9, // Select save file to load:
    MENUPAGE_DELETE_GAME = 10, // Select save file to delete:
    MENUPAGE_LOAD_GAME_ASK = 11, // All unsaved progress in your current game will be lost. Proceed with loading?
    MENUPAGE_DELETE_GAME_ASK = 12, // Are you sure you wish to delete this save file?
    MENUPAGE_LOAD_FIRST_SAVE = 13,
    MENUPAGE_DELETE_FINISHED = 14,
    MENUPAGE_DELETE_SUCCESSFUL = 15, // // Delete Successful. Select OK to continue.
    MENUPAGE_GAME_SAVE = 16, // Select file you wish to save to:
    MENUPAGE_SAVE_WRITE_ASK = 17, // Are you sure you wish to save?
    MENUPAGE_SAVE_DONE_1 = 18,
    MENUPAGE_SAVE_DONE_2 = 19, // Save Successful. Select OK to continue.
    MENUPAGE_GAME_SAVED = 20, // OK
    MENUPAGE_GAME_LOADED = 21, // OK
    MENUPAGE_GAME_WARNING_DONT_SAVE = 22, // Warning! One or more cheats have been activated. This may affect your save game. It is recommended that you do not save this game.
    MENUPAGE_ASK_DISPLAY_DEFAULT_SETS = 23, // Are you sure you want to reset your current settings to default?
    MENUPAGE_ASK_AUDIO_DEFAULT_SETS = 24, // Are you sure you want to reset your current settings to default?
    MENUPAGE_ASK_CONTROLLER_DEFAULT_SETS = 25, // Are you sure you want to reset your current settings to default?
    MENUPAGE_USER_TRACKS_OPTIONS = 26,
    MENUPAGE_DISPLAY_ADVANCED = 27, // DRAW DISTANCE, ...
    MENUPAGE_LANGUAGE = 28, // English, ...
    MENUPAGE_SAVE_GAME_DONE = 29, // O.K
    MENUPAGE_SAVE_GAME_FAILED = 30, // Save Unsuccessful., O.K.
    MENUPAGE_SAVE_WRITE_FAILED = 31, // Save Unsuccessful.
    MENUPAGE_SAVE_FAILED_FILE_ERROR = 32, // Load Unsuccessful. File Corrupted, Please delete.
    MENUPAGE_OPTIONS = 33, // Controller Setup, Audio Setup ...
    MENUPAGE_MAIN_MENU = 34, // Start Game, Options, Quit Game
    MENUPAGE_QUIT_GAME_ASK = 35, // Are you sure you want to quit? All progress since the last save game will be lost. Proceed?
    MENUPAGE_CONTROLLER_SETUP = 36, // CONFIGURATION, Redefine Controls ...
    MENUPAGE_REDEFINE_CONTROLS = 37, // Foot Controls, Vehicle Controls
    MENUPAGE_CONTROLS_VEHICLE_ONFOOT = 38,
    MENUPAGE_MOUSE_SETTINGS = 39,
    MENUPAGE_JOYPAD_SETTINGS = 40,
    MENUPAGE_PAUSE_MENU = 41, // Resume, START NEW GAME ...
    MENUPAGE_QUIT_GAME_2 = 42,
    MENUPAGE_EMPTY = 43
};

enum eMenuTexture {
    MENUTEX_RADIO_TEXTURES_BEGIN,
    MENUTEX_ARROW = MENUTEX_RADIO_TEXTURES_BEGIN,
    MENUTEX_RADIO_PLAYBACK,
    MENUTEX_RADIO_KROSE,
    MENUTEX_RADIO_KDST,
    MENUTEX_RADIO_BOUNCE,
    MENUTEX_RADIO_SFUR,
    MENUTEX_RADIO_RLS,
    MENUTEX_RADIO_RADIOX,
    MENUTEX_RADIO_CSR,
    MENUTEX_RADIO_KJAH,
    MENUTEX_RADIO_MASTERSOUND,
    MENUTEX_RADIO_WCTR,
    MENUTEX_RADIO_TPLAYER,
    MENUTEX_RADIO_TEXTURES_END,

    MENUTEX_BACKGROUND_TEXTURES_BEGIN = MENUTEX_RADIO_TEXTURES_END,
    MENUTEX_BACK2 = MENUTEX_BACKGROUND_TEXTURES_BEGIN,
    MENUTEX_BACK3,
    MENUTEX_BACK4,
    MENUTEX_BACK5,
    MENUTEX_BACK6,
    MENUTEX_BACK7,
    MENUTEX_BACK8,
    MENUTEX_MAP,
    MENUTEX_BACKGROUND_TEXTURES_END,

    MENUTEX_BACK8_TEXTURES_BEGIN = MENUTEX_BACKGROUND_TEXTURES_END,
    MENUTEX_BACK8_TOP = MENUTEX_BACK8_TEXTURES_BEGIN,
    MENUTEX_BACK8_RIGHT,
    MENUTEX_BACK8_TEXTURES_END,

    MENUTEX_MOUSE_TEXTURES_BEGIN = MENUTEX_BACK8_TEXTURES_END,
    MENUTEX_MOUSE = MENUTEX_MOUSE_TEXTURES_BEGIN,
    MENUTEX_CROSSHAIR,
    MENUTEX_MOUSE_TEXTURES_END,

    MENUTEX_TEXTURE_COUNT = MENUTEX_MOUSE_TEXTURES_END
};

struct  CMenuPageButton {
    unsigned char m_nActionType; // Unknown if signed or signed, but it does only '==' comparisions, so it's safe to use unsigned (moar numbers)
    char m_szName[8];
    char m_nType;
    char m_nTargetMenu;
private:
    char _padB;
public:
    short m_nPosnX;
    short m_nPosnY;
    char m_nAlign;
};

VALIDATE_SIZE(CMenuPageButton, 0x12);

struct  CMenuPage {
    char m_szTitleName[8];
    char m_nPrevMenu;
    char m_nStartingButton;
    CMenuPageButton m_aButtons[12];
};

VALIDATE_SIZE(CMenuPage, 0xE2);

class  CMenuManager {
public:
    char field_0;
    char field_1[3];
    float               m_fStatsScrollSpeed;
    char field_8;
    char field_9[23];
    char field_20;
    bool                m_bHudOn;
    char field_22[2];
    int                 m_nRadarMode;
    char field_28[4];
    int                 m_nTargetBlipIndex; // blip script handle
    char field_30;
    char field_31;
    bool                m_bDontDrawFrontEnd;
    bool                m_bActivateMenuNextFrame;
    bool                m_bMenuAccessWidescreen;
    char field_35;
    char field_36[2];
    int field_38;
    int                 m_nBrightness;
    float               m_fDrawDistance;
    bool                m_bShowSubtitles;
    char field_45[4];
    char field_49;
    bool                m_bMapLegend;
    bool                m_bWidescreenOn;
    bool                m_bFrameLimiterOn;
    bool                m_bRadioAutoSelect;
    char field_4E;
    char                m_nSfxVolume;
    char                m_nRadioVolume;
    bool                m_bRadioEq;
    char                m_nRadioStation;
    char field_53;
    int                 m_nSelectedMenuItem;
    char field_58;
    char drawRadarOrMap;
    char field_5A;
    char        m_bAllStreamingStuffLoaded;
    bool                m_bMenuActive;
    char doGameReload;
    char field_5E;
    char isSaveDone;
    bool                m_bLoadingData;
    char field_61[3];
    float               m_fMapZoom;
    float               m_fMapBaseX;
    float               m_fMapBaseY;
    CVector2D           m_vMousePos;
    char field_78;
    char field_79[3];
    int titleLanguage;
    int textLanguage;
    char                m_nLanguage;
    char                m_nPreviousLanguage;
    char field_86[2];
    int field_88;
    bool                m_bLanguageChanged;
    char field_8D[3];
    int field_90;
    int field_94;
    char               *m_pJPegBuffer; //!< +0x98  \see JPegCompress file
    char  field_9C[16];
    int field_AC;
    char                m_nRadioMode;
    char invertPadX1;
    char invertPadY1;
    char invertPadX2;
    char invertPadY2;
    char swapPadAxis1;
    char swapPadAxis2;
    char field_B7;
    bool                m_bDrawMouse;
    char field_B9[3];
    int                 m_nMousePosLeft;
    int                 m_nMousePosTop;
    bool                m_bMipMapping;
    bool                m_bTracksAutoScan;
    short field_C6;
    int                 m_nAppliedAntiAliasingLevel;
    int                 m_nAntiAliasingLevel;
    char                m_nController;
    char field_D1[3];
    int                 m_nAppliedResolution;
    int                 m_nResolution;
    int field_DC;
    int mousePosLeftA;
    int mousePosTopA;
    bool                m_bSavePhotos;
    bool                m_bMainMenuSwitch;
    char                m_nPlayerNumber;
    char field_EB;
    int field_EC;
    int field_F0;
    char field_F4;
    char field_F5[3];
    //union{
    //	struct{
    CSprite2d           m_apTextures[25];
    //	};
    //	struct{
    //		CSprite2d m_apRadioSprites[13];
    //		CSprite2d m_apBackgroundTextures[8];
    //		CSprite2d m_apAdditionalBackgroundTextures[2];
    //		CSprite2d m_apMouseTextures[2];
    //	};
    //};
    bool                m_bTexturesLoaded;
    unsigned char       m_nCurrentMenuPage;
    char field_15E;
    unsigned char       m_bSelectedSaveGame;
    char field_160;
    char field_161;
    char                m_szMpackName[8];
    char field_16A[6486];
    int field_1AC0;
    int field_1AC4;
    int field_1AC8;
    int field_1ACC;
    int field_1AD0;
    int field_1AD4;
    int field_1AD8;
    short field_1ADC;
    bool                m_bChangeVideoMode;
    char field_1ADF;
    int field_1AE0;
    int field_1AE4;
    char field_1AE8;
    char field_1AE9;
    char field_1AEA;
    bool                m_bScanningUserTracks;
    int field_1AEC;
    char field_1AF0;
    char field_1AF1;
    char field_1AF2;
    char field_1AF3;
    int field_1AF4;
    int field_1AF8;
    int field_1AFC;
    int field_1B00;
    int field_1B04;
    char field_1B08;
    char field_1B09;
    char field_1B0A;
    char field_1B0B;
    int field_1B0C;
    char field_1B10;
    char field_1B11;
    char field_1B12;
    char field_1B13;
    char field_1B14;
    char field_1B15;
    char field_1B16;
    char field_1B17;
    int EventToDo;
    int field_1B1C;
    unsigned char       m_nTexturesRound;
    unsigned char       m_nNumberOfMenuOptions;
    short field_1B22;
    int field_1B24;
    char field_1B28;
    char field_1B29;
    short field_1B2A;
    int field_1B2C;
    int field_1B30;
    short field_1B34;
    short field_1B36;
    int field_1B38;
    char field_1B3C;
    char field_1B3D;
    char field_1B3E;
    char field_1B3F;
    int field_1B40;
    char field_1B44;
    char field_1B45;
    short field_1B46;
    int field_1B48;
    int field_1B4C;
    char                m_nBackgroundSprite;
    char field_1B51;
    short field_1B52;
    int field_1B54;
    int field_1B58;
    char field_1B5C;
    char field_1B5D;
    short field_1B5E;
    int field_1B60;
    int field_1B64;
    int field_1B68;
    int field_1B6C;
    int field_1B70;
    int field_1B74;

    static int& nLastMenuPage;

    static bool& bInvertMouseX;
    static bool& bInvertMouseY;

public:
    static void InjectHooks();
    CMenuManager();
    ~CMenuManager();

    void CheckForMenuClosing();
    void ProcessFileActions();
    void ProcessStreaming(char bImmediately);
    void UserInput();
    void Process();
    void DrawWindow(const CRect& coords, const char* pKey, unsigned char nColour, CRGBA backColor, bool Unused, bool bBackground);
    char SwitchToNewScreen(char page);
    void SaveSettings();
    char InitialiseChangedLanguageSettings(char a2);
    void ScrollRadioStations(char numStations);
    void ProcessMissionPackNewGame();
    signed int DoSettingsBeforeStartingAGame();
    char SetDefaultPreferences(eMenuPage page);
    char PrintMap();
    char PrintStats();
    char PrintBriefs();
    char DrawControllerSetupScreen();
};

VALIDATE_SIZE(CMenuManager, 0x1B78);

extern CMenuManager &FrontEndMenuManager;
