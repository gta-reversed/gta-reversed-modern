/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CFont.h"

enum eMenuType : unsigned char {
    MENU_TYPE_DEFAULT,
    MENU_TYPE_GRID,
};

class tMenuPanel {
public:
    char m_anUsedCarColors[64];
    eMenuType m_nType;
    char m_aaacRowTitles[4][12][10];
    char _pad1[3];
    int m_aadwNumberInRowTitle[4][12];
    int m_aadw2ndNumberInRowTitle[4][12];
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
    static unsigned short& CurrentMenuInUse;
    static unsigned short& num_menus_in_use; // name from Android PDB

    static void ActivateItems(unsigned char panelId, bool item1, bool item2, bool item3, bool item4, bool item5, bool item6, bool item7, bool item8, bool item9, bool item10, bool item11, bool item12);
    static void ActivateOneItem(unsigned char panelId, unsigned char rowId, bool enable);

    // Returns panel Id
    static unsigned char CreateNewMenu(eMenuType type, char* pTitle, float posX, float posY, float width, char columns, bool interactive, bool background, eFontAlignment alignment);

    static char CheckForAccept(unsigned char panelId);
    static char CheckForSelected(unsigned char panelId);
    static void Initialise();
    static void Process(unsigned char panelId);
    static tMenuPanel* InputStandardMenu(unsigned char panelId);
    static tMenuPanel* InputGridMenu(unsigned char panelId);
    static void DisplayStandardMenu(unsigned char panelId, bool bBrightFont);
    static void DisplayGridMenu(unsigned char panelId, bool bBrightFont);
    static void HighlightOneItem(unsigned char panelId, unsigned char itemId, bool bHighlight = true);
    static tMenuPanel** InsertMenu(unsigned char panelId, unsigned char columnId, char* pTitle, char* str1, char* str2, char* str3, char* str4, char* str5, char* str6, char* str7, char* str8, char* str9, char* str10, char* str11, char* str12);
    static tMenuPanel* InsertOneMenuItem(unsigned char panelId, unsigned char columnId, unsigned char rowId, char* str);
    static tMenuPanel* InsertOneMenuItemWithNumber(unsigned char panelId, unsigned char columnId, unsigned char rowId, char* str, int number1, int number2);
    static void SetActiveMenuItem(unsigned char panelId, char rowId);
    static void SetColumnHeader(unsigned char panelId, unsigned char columnId, char* str);
    static void SetColumnOrientation(unsigned char panelId, unsigned char columnId, eFontAlignment alignment);
    static void SetColumnWidth(unsigned char panelId, unsigned char columnId, unsigned short width);
    static void SetDPadInput(unsigned char panelId, bool bEnable);
    static void SetHeaderOrientation(unsigned char panelId, unsigned char columnId, eFontAlignment alignment);
    static void SwitchOffMenu(unsigned char panelId);
};

extern tMenuPanel** MenuNumber; // tMenuPanel MenuNumber[2]
