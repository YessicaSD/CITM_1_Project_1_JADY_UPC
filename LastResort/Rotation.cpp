#include "Rotation.h"
#include <math.h>
#include "p2Point.h"

void LimitRotation(float &rotation)
{
	//- Limit the rotation to positive numbers
	if (rotation < 0)
	{
		rotation = 2 * PI + rotation;//We add the rotation because it's negative, so it will efectively substract it
	}
	//- Limit the rotation to one circle
	while (rotation > 2 * PI)
	{
		rotation -= 2 * PI;
	}
}

//Try to implement it with templates

//This function calculates the rotation to a point, from an origin position
//Returns -1 if the targetPos is the same as origin
float CalculateRotationToPoint(iPoint originPos, iPoint targetPos)
{
	//Fist quadrant
	if (targetPos.x > originPos.x && targetPos.y > originPos.y)
	{
		return atan(targetPos.x - originPos.x / targetPos.y - originPos.y);
	}
	//Second quadrant
	else if (targetPos.x < originPos.x && targetPos.y > originPos.y)
	{
		return PI + atan(targetPos.x - originPos.x / targetPos.y - originPos.y);
	}
	//Third quadrant
	else if (targetPos.x < originPos.x && targetPos.y < originPos.y)
	{
		return PI + atan(targetPos.x - originPos.x / targetPos.y - originPos.y);
	}
	//Fourth quadrant
	else if (targetPos.x > originPos.x && targetPos.y < originPos.y)
	{
		return 2 * PI + atan(targetPos.x - originPos.x / targetPos.y - originPos.y);
	}

	//- In line
	else if (targetPos.x == originPos.x && targetPos.y > originPos.y)
	{
		return angleValue[N];
	}
	else if (targetPos.x < originPos.x && targetPos.y == originPos.y)
	{
		return angleValue[W];
	}
	else if (targetPos.x == originPos.x && targetPos.y < originPos.y)
	{
		return angleValue[S];
	}
	else if (targetPos.x > originPos.x && targetPos.y == originPos.y)
	{
		return angleValue[E];
	}

	//Same position
	else if (targetPos.x == originPos.x && targetPos.y == originPos.y)
	{
		//If we're in the same position we return -1
		return -1;
	}
}