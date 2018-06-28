/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CClock {
public:
     static unsigned char(&daysInMonth)[12]; // static unsigned char const daysInMonth[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
     static bool &bClockHasBeenStored;
     static unsigned short &ms_Stored_nGameClockSeconds;
     static unsigned char &ms_Stored_nGameClockMinutes;
     static unsigned char &ms_Stored_nGameClockHours;
     static unsigned char &ms_Stored_nGameClockDays;
     static unsigned char &ms_Stored_nGameClockMonths;
     static unsigned char &CurrentDay;
     static unsigned short &ms_nGameClockSeconds;
     static unsigned char &ms_nGameClockMinutes;
     static unsigned char &ms_nGameClockHours;
     static unsigned char &ms_nGameClockDays;
     static unsigned char &ms_nGameClockMonth;
     static unsigned int &ms_nLastClockTick;
     static unsigned int &ms_nMillisecondsPerGameMinute;

    //! Returns number of minutes to specified hour & minute.
     static unsigned short GetGameClockMinutesUntil(unsigned char hours, unsigned char minutes);
    //! Returns true current hour is in range of two specified hours.
     static bool GetIsTimeInRange(unsigned char hourA, unsigned char hourB);
    //! Initializes clock
     static void Initialise(unsigned int milisecondsPerGameMinute);
    //! Normalizes game clock
    //! For example hour of 24 means new day and hour 1.
     static void NormaliseGameClock();
    //! Sets new day
    //! Directions (0 = one day backwards, 1 = one day forwards)
     static void OffsetClockByADay(unsigned int timeDirection);
    //! Restores a clock time
     static void RestoreClock();
    //! Sets game clock
     static void SetGameClock(unsigned char hours, unsigned char minutes, unsigned char day);
    //! Backups a clock time
     static void StoreClock();
    //! Updates a time
     static void Update();
};

//#include "meta/meta.CClock.h"
