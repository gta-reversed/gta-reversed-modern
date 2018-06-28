/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

/**
 * Double linked list item base class
 *
 * You should inherit this class to use it in List_c lists!
 */
class  ListItem_c
{
protected:
	ListItem_c *next;
	ListItem_c *prev;

protected:
	ListItem_c(void);
	~ListItem_c(void);

friend class List_c;
};
