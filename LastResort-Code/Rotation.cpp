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

//TO DO: Implement it with templates

//This function calculates the rotation to a point, from an origin position
//Returns -1 if the targetPos is the same as origin
float AbsoluteRotation(iPoint originPos, iPoint targetPos)
{
	//Fist quadrant
	if (targetPos.x > originPos.x && targetPos.y > originPos.y)
	{
		return atan((double)(targetPos.y - originPos.y) / (double)(targetPos.x - originPos.x));
	}
	//Second quadrant
	else if (targetPos.x < originPos.x && targetPos.y > originPos.y)
	{
		return PI + atan((double)(targetPos.y - originPos.y) / (double)(targetPos.x - originPos.x));
	}
	//Third quadrant
	else if (targetPos.x < originPos.x && targetPos.y < originPos.y)
	{
		return PI + atan((double)(targetPos.y - originPos.y) / (double)(targetPos.x - originPos.x));
	}
	//Fourth quadrant
	else if (targetPos.x > originPos.x && targetPos.y < originPos.y)
	{
		return 2 * PI + atan((double)(targetPos.y - originPos.y) / (double)(targetPos.x - originPos.x));
	}

	//- In line
	else if (targetPos.x == originPos.x && targetPos.y > originPos.y)
	{
		return angleValue[S];
	}
	else if (targetPos.x < originPos.x && targetPos.y == originPos.y)
	{
		return angleValue[W];
	}
	else if (targetPos.x == originPos.x && targetPos.y < originPos.y)
	{
		return angleValue[N];
	}
	else if (targetPos.x > originPos.x && targetPos.y == originPos.y)
	{
		return angleValue[E];
	}

	//Same position
	else if (targetPos.x == originPos.x && targetPos.y == originPos.y)
	{
		//If we're in the same position we return E
		return angleValue[E];
	}
}

//This function has a series of if statatements that do the following
//First if  --> Finds the rotation we want to go to
//Second if --> Determines which distance from the currentRotation to the targetRotation is shorter
//Third if  --> Go to that direction, until we get at it
void RotateTo(float targetRotation, float &currentRotation, float speed)
{
	//We create a variable that's going to store the opposite rotation from the targetRotation
	float oppositeRotation;

	//Check if the target rotation is down or one of the lower diagonals
	if (targetRotation == angleValue[S] || targetRotation == angleValue[SE] || targetRotation == angleValue[SW])
	{
		oppositeRotation = targetRotation + PI;
		//Check which way is shorter
		if (currentRotation <= oppositeRotation && currentRotation > targetRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation < targetRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation > oppositeRotation)
		{
			//Move counterclock
			currentRotation += speed;
		}
	}

	//Check if the target rotation is up or one of the upper diagonals
	else if (targetRotation == angleValue[N] || targetRotation == angleValue[NE] || targetRotation == angleValue[NW])
	{
		oppositeRotation = targetRotation - PI;
		//Check which way is shorter
		if (currentRotation > targetRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation <= oppositeRotation)
		{
			//Move clockwise
			currentRotation -= speed;
		}
		else if (currentRotation < targetRotation && currentRotation > oppositeRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
	}

	//Check if the target rotation is left
	else if (targetRotation == angleValue[W])
	{
		//Check which way is shorter
		if (currentRotation == 0 || currentRotation > targetRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation < targetRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
	}

	//Check if the target rotation is right
	else if (targetRotation == angleValue[E])
	{
		oppositeRotation = angleValue[W];
		//Check which way is shorter
		if (currentRotation <= oppositeRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation > oppositeRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
	}
}

int GetNearestAngle(float currentRotation)
{
	const int divisions = 16;//number of enums in Angle
	const float angleSeparation = (2 * PI) / (2 * divisions);//2 * divisions because we need to divide every angle in half

	//- Start with the exception (E). We need an or because you can end up in this case if you increase the rotation to 2PI or we decrease it to 0
	if (currentRotation >= angleValue[E] - angleSeparation || currentRotation < 0 + angleSeparation)
	{
		return E;
	}

	//- Then go through all the other cases
	for (int i = E + 1; i < divisions; ++i)
	{
		if (currentRotation >= angleValue[i] - angleSeparation && currentRotation < angleValue[i] + angleSeparation)
		{
			return i;
		}
	}

	//In case that it didn't return anything before, we'll return the E position, just so that we don't get an error (this should never execute)
	LOG("Angle to render not found, returning east direction.");
	return E;
}