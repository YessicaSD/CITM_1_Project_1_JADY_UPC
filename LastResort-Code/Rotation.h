#ifndef __ROTATION_H__
#define __ROTATION_H__

#include "p2Point.h"

//-------------------------------------ROTATION------------------------------------------------
//- This script holds helpful values to calculate any rotation in the game
//INFO:
//- The rotations are mesured in radians, not in degrees
//-	It's very important to note that the y coordinates are inverted.
//	So for example if a 45� angle would instead really be 315� angle.
//- Abreviations: S (south), N (north), E (east), W (west)

float const PI = 3.141592;

enum Angle
{
	E = 0,
	ESE,
	SE,
	SSE,
	S,
	SSW,
	SW,
	WSW,
	W,
	WNW,
	NW,
	NNW,
	N,
	NNE,
	NE,
	ENE
};

float const angleValue[16]
{
	2 * PI,
	PI / 8,
	PI / 4,
	3 * PI / 8,
	PI / 2,
	5 * PI / 8,
	3 * PI / 4,
	7 * PI / 8,
	PI,
	9 * PI / 8,
	5 * PI / 4,
	11 * PI / 8,
	3 * PI / 2,
	13 * PI / 8,
	7 * PI / 4,
	15 * PI / 8
};

void LimitRotation(float &);
float AbsoluteRotation(iPoint, iPoint);
void RotateTo(float, float&, float);//Increases a rotation until it reaches its target rotation
int GetNearestAngle(float); //Returns one of the 16 enum values corresponding to the angle it is

#endif //__ROTATION_H__