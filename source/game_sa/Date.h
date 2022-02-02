/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CDate {
public:
    int32 seconds;
    int32 minutes;
    int32 hours;
    int32 day;
    int32 month;
    int32 year;

    CDate();

    bool operator<(CDate const& rhs);
    bool operator==(CDate const& rhs);
    bool operator>(CDate const& rhs);

    void PopulateDateFields(char const& seconds, char const& minutes, char const& hours, char const& day, char const& month, int16 year);
};

VALIDATE_SIZE(CDate, 0x18);
