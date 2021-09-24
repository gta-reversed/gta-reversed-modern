/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Font.h"

enum eMenuType : uint8 {
    MENU_TYPE_DEFAULT,
    MENU_TYPE_GRID,
};

class tMenuPanel {
public:
    char m_anUsedCarColors[64];
    eMenuType m_nType;
    char m_aaacRowTitles[4][12][10];
    char _pad1[3];
    int32 m_aadwNumberInRowTitle[4][12];
    int32 m_aadw2ndNumberInRowTitle[4][12];
    char m_aacColumnHeaders[4][10];
    char m_acTitle[10];
    bool m_abRowSelectable[12];
    bool m_abRowAlreadyBought[12];
    eFontAlignment m_anColumnAlignment[4];
    eFontAlignment m_anColumnHeaderAlignment[4];
    char m_nNumRows;
    char m_nNumColumns;
    bool m_abColumnInteractive[4];
    float m_afColumnWidth[4];
    CVector2D m_vPosn;
    bool m_bColumnBackground;
    char m_nSelectedRow;
    char m_nAcceptedRow;
    char _pad2;
};

VALIDATE_SIZE(tMenuPanel, 0x418);

class CMenuSystem {
public:
    static bool* MenuInUse;
    static uint16& CurrentMenuInUse;
    static uint16& num_menus_in_use; // name from Android PDB

    static void ActivateItems(uint8 panelId, bool item1, bool item2, bool item3, bool item4, bool item5, bool item6, bool item7, bool item8, bool item9, bool item10, bool item11, bool item12);
    static void ActivateOneItem(uint8 panelId, uint8 rowId, bool enable);

    // Returns panel Id
    static uint8 CreateNewMenu(eMenuType type, char* pTitle, float posX, float posY, float width, char columns, bool interactive, bool background, eFontAlignment alignment);

    static char CheckForAccept(uint8 panelId);
    static char CheckForSelected(uint8 panelId);
    static void Initialise();
    static void Process(uint8 panelId);
    static tMenuPanel* InputStandardMenu(uint8 panelId);
    static tMenuPanel* InputGridMenu(uint8 panelId);
    static void DisplayStandardMenu(uint8 panelId, bool bBrightFont);
    static void DisplayGridMenu(uint8 panelId, bool bBrightFont);
    static void HighlightOneItem(uint8 panelId, uint8 itemId, bool bHighlight = true);
    static tMenuPanel** InsertMenu(uint8 panelId, uint8 columnId, char* pTitle, char* str1, char* str2, char* str3, char* str4, char* str5, char* str6, char* str7, char* str8, char* str9, char* str10, char* str11, char* str12);
    static tMenuPanel* InsertOneMenuItem(uint8 panelId, uint8 columnId, uint8 rowId, char* str);
    static tMenuPanel* InsertOneMenuItemWithNumber(uint8 panelId, uint8 columnId, uint8 rowId, char* str, int32 number1, int32 number2);
    static void SetActiveMenuItem(uint8 panelId, char rowId);
    static void SetColumnHeader(uint8 panelId, uint8 columnId, char* str);
    static void SetColumnOrientation(uint8 panelId, uint8 columnId, eFontAlignment alignment);
    static void SetColumnWidth(uint8 panelId, uint8 columnId, uint16 width);
    static void SetDPadInput(uint8 panelId, bool bEnable);
    static void SetHeaderOrientation(uint8 panelId, uint8 columnId, eFontAlignment alignment);
    static void SwitchOffMenu(uint8 panelId);
};

extern tMenuPanel** MenuNumber; // tMenuPanel MenuNumber[2]
