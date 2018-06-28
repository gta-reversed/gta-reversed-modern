/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CDate {
public:
    int seconds;
    int minutes;
    int hours;
    int day;
    int month;
    int year;

     CDate();

     bool operator<(CDate const &rhs);
     bool operator==(CDate const &rhs);
     bool operator>(CDate const &rhs);

     void PopulateDateFields(char const &seconds, char const &minutes, char const &hours, char const &day, char const &month, short year);
};

VALIDATE_SIZE(CDate, 0x18);

//#include "meta/meta.CDate.h"
