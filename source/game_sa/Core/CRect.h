/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector2D.h"

/* CRect class describes a rectangle.

	A(left;top)_____________________
	|                               |
	|                               |
	|                               |
	|_________________B(right;bottom)
	
*/

class  CRect
{
public:
	float left;          // x1
	float bottom;        // y1
	float right;         // x2
	float top;           // y2

	CRect(float left, float top, float right, float bottom);
	CRect();

	bool IsFlipped();
	void Restrict(CRect const& restriction);
	void Resize(float resizeX, float resizeY);
	bool IsPointInside(CVector2D const& point);
	bool IsCircleInside(CVector2D const& circleCenter, float circleRadius);
	void SetFromCenter(float x, float y, float size);
	void GetCenter(float *x, float *y);
	void StretchToPoint(float x, float y);
};

VALIDATE_SIZE(CRect, 0x10);