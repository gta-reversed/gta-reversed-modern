/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
/***************************************************************************
 *                                                                         *
 * Module  : rperror.h                                                     *
 *                                                                         *
 * Purpose : Used to generate error codes                                  *
 *                                                                         *
 **************************************************************************/

/****************************************************************************
 Defines
 */

#define RWECODE(a,b) a,

enum rwPLUGIN_ERRENUM
{
    rwPLUGIN_ERRENUMLAST = RWFORCEENUMSIZEINT
};

typedef enum rwPLUGIN_ERRENUM rwPLUGIN_ERRENUM;
