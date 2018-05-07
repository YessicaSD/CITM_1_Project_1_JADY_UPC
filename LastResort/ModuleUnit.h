#ifndef __ModuleUnit_H__
#define __ModuleUnit_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModulePlayer.h"

//MODULE UNIT BASIC EXPLANATION
//---------------------------------------------------------------------------------------------
//This module takes care of the unit behaviour in the game.
//The unit rotates in 2 different ways:
//- Around the player ship, which changes its position. We'll call this rotation "orbit"
//- Around its own center, which changes where it aims. We'll call this rotation "turn around"
//It also has an animation simulating a rotation on the sphere part. We'll call this "spin"
//---------------------------------------------------------------------------------------------
//CONSIDERATIONS
//- The rotations are mesured in radians, not in degrees
//-	It's very important to note that the y coordinates are inverted.
//	So for example if a 45º angle would instead really be 315º angle.
//---------------------------------------------------------------------------------------------
//ORBIT
//- The unit rotates around the player's ship we point to with playerToFollow.
//-	The unit will always orbit to the opposite direction to where we're going.
//	For example, if we move to the right it will rotate to the left.
//- The unit can rotate clock wise or counter clock wise.
//- It will rotate in the way which it has to travel less distance to get to its target position.
//- If the distance is the same counter clock wise and clock wise, it will prioritize rotatating counter clock wise.
//TURN AROUND
//- The unit has 16 different axis or places where it can aim.
//- The unit will turn around twice as fast as it orbits around the player ship,
//	which means that if the unit is on the right side of the ship and we move to the right, when it is just above the ship, the unit will already be pointing towards the left.
//SPIN
//- The unit has 8 different sprites for each of its axis
//-	We created a struct called "SpinAnimation" which will store the 8 different sprites for the 16 different places where it can aim
//	(basically its the same as the animation class but it allows us to have better control on its animations)

#define SPIN_FRAMES 8
#define UNIT_AXIS 16

struct SDL_Texture;
struct Collider;

enum Angle
{
	//S (south), N (north), E (east), W (west)
	E = 0, ESE, SE, SSE, S, SSW, SW, WSW, W, WNW, NW, NNW, N, NNE, NE, ENE
};

enum UnitType
{
	orange = 0,
	blue
};

enum UnitPhase
{
	rotating = 0,
	trowing,
	returning
};

struct SpinAnimation
{
	SDL_Rect frame [SPIN_FRAMES];
};

class ModuleUnit : public Module
{
public:
	ModuleUnit();
	~ModuleUnit();

	bool Start();
	update_status Update();//Here we'll check for input, rotate the unit, and render it
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

	void Rotating();
	void Throwing();
	void Returning();

	void RotateTo(float, float&, float);//This function increases a rotation until it reaches its target rotation
	void LimitRotation(float &);//This function limits a rotation to positive numbers and 2*PI radians
	int TurnAroundToRender();//This function will return an angle depending on where the unit is pointing to

public:
	fPoint position;
	ModulePlayer* playerToFollow = nullptr;//Ship it has to follow
	UnitType type;
	Collider* unitCol = nullptr;
	float currentOrbit;
	float currentTurnAround;

	float angleValue[UNIT_AXIS];//The value of each angle

private:
	const float PI = 3.141592;
	const float orbitSpeed = 3.141592 / 27;//The speed at which the unit rotates around the player ship
	const float turnAroundSpeed = orbitSpeed * 2;
	const float spinSpeed = 0.2f;
	const float unitProjectileSpeed = 6;//6= pixels it moves each frame

	float currentSpinFrame;
	float targetOrbit;//The orbit rotation we want the unit to be in
	int turnAroundToRender;
	bool orbiting;//A bool that indicates if we can make the unit orbit
	bool turningAround;//A bool that indicates if we can make the unit turn around
	const float radius = 31;
	const float angleSeparation = PI / 16;//The separation between the angles (helps us calculate which animation we have to play)
										 //   E, ESE,  SE, SSE,   S, SSW,  SW, WSW,   W, WNW,  NW, NNW,   N, NNE,  NE, ENE
	int spriteXDifferences[UNIT_AXIS] =  {    8,   8,   8,   8,   8,   9,  13,  14,  14,  14,  13,   9,   8,   8,   8,   8 };//Sprite differences in x, helps us keep the unit centered on its trajectory
	int spriteYDifferences[UNIT_AXIS] =  {    8,   8,   8,   8,   8,   8,   8,   8,   8,   9,  13,  15,  14,  15,  13,   9 };//Sprite differences in y, helps us keep the unit centered on its trajectory
	int shotPosXDifferences[UNIT_AXIS] = {   15,  14,  12,   6,   0,  -5, -11, -13, -14, -13, -11,  -6,   0,   6,  11,  14 };//Helps us position the unit projectile at the top of its antenas
	int shotPosYDifferences[UNIT_AXIS] = {    0,   7,  12,  14,  15,  14,  12,   6,   0,  -6, -11, -14, -14, -13, -10,  -6 };//Helps us position the unit projectile at the top of its antenas
	SDL_Texture* unitTx = nullptr;
	SpinAnimation spinAnimation[UNIT_AXIS];//There is an animation for each direction of the unit

	//Shooting
	SDL_Texture* throwUnitTx = nullptr;
	float power = 0;
	const float powerSpeed = 0.01f;
	UnitPhase unitPhase = UnitPhase::rotating;
	Uint32 shootTime;
	const int throwSpeed = 5;

};
#endif