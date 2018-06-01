#ifndef __ModuleUnit_H__
#define __ModuleUnit_H__

//---------------------------------MODULE UNIT EXPLANATION-------------------------------------
//---------------------------------------------------------------------------------------------
//This module takes care of the unit behaviour in the game.
//---------------------------------------------------------------------------------------------
//The unit has 5 distinct phases
//- Rotating: default state. Unit rotates around the player ship
//- Throwing: if you charge the unit, it will be launched respective to its position with the player ship
//- Following terrain: activated when orange unit collides. Unit follows the terrain
//- Bouncing on terrain: activated when blue unit collides. Unit bounces on terrain
//- Returning: unit returns to the center of the player
//- Positioning: unit positions itself from the center of the player to the rotation it had
//----------------------------------------ROTATION---------------------------------------------
//The unit rotates in 2 different ways:
//- Around the player ship, which changes its position. We'll call this rotation "orbit"
//- Around its own center, which changes where it aims. We'll call this rotation "turn around"
//- It also has an animation simulating a rotation on the sphere part. We'll call this "spin"
//- ORBIT
//  - The unit rotates around the player's ship we point to with playerToFollow.
//  - The unit will always orbit to the opposite direction to where we're going.
//	  For example, if we move to the right it will rotate to the left.
//  - The unit can rotate clock wise or counter clock wise.
//  - It will rotate in the way which it has to travel less distance to get to its target position.
//  - If the distance is the same counter clock wise and clock wise, it will prioritize rotatating counter clock wise.
//- TURN AROUND
//  - The unit has 16 different axis or places where it can aim.
//  - The unit will turn around twice as fast as it orbits around the player ship,
//    which means that if the unit is on the right side of the ship and we move to the right, when it is just above the ship, the unit will already be pointing towards the left.
//- SPIN
//  - The unit has 8 different sprites for each of its axis
//  - We created a struct called "SpinAnimation" which will store the 8 different sprites for the 16 different places where it can aim
//    (basically its the same as the animation class but it allows us to have better control over its animations)

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModulePlayer.h"
#include "Rotation.h"

#define SPIN_FRAMES 8
#define UNIT_AXIS 16

struct SDL_Texture;
struct Collider;

enum UnitPhase
{
	rotating = 0,
	throwing,
	followingTerrain,
	bouncingOnTerrain,
	returning,
	positioning
};

enum FollowingTerrainDirection
{
	FTD_notFollowing = 0,
	FTD_up,
	FTD_down,
	FTD_right,
	FTD_left
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

	//Inherited functions from Module class
	bool Start();
	update_status LogicUpdate();
	update_status RenderUpdate2();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

	//Change color
	void MakeUnitBlue();
	void MakeUnitOrange();

private:
	//Unit phases (executed inside update)
	void Rotating();//Here we'll check for input, rotate the unit, and render it
	void Throwing();
	void FollowingTerrain();
	void BouncingOnTerrain();
	void Returning();
	void Positioning();

	//Collision phases (collision behaves differenly depending on which phase it is)
	void OnCollisionThrowing(Collider*, Collider*);
	void OnCollisionFollowingTerrain(Collider*, Collider*);
	void OnCollisionBouncingOnTerrain(Collider*, Collider*);

	//Return conditions (a series of conditions that make the unit return, so that it never gets stuck for too much time)
	void CheckPlayerClose();
	void CheckHitHeavyEnemy(Collider*, Collider*);
	void CheckOutOfScreen();
	void CheckReturnTime();

	//Following terrain
	bool ColliderIsOnLeft();//Returns true if collider to follow is on the left of the unit
	bool ColliderIsOnRight();//Returns true if collider to follow is on the right of the unit
	bool ColliderIsAbove();//Returns true if collider to follow is above of the unit
	bool ColliderIsBellow();//Returns true if collider to follow is bellow of the unit


	//Trail VFX (sprite that follows the unit when it is throwing, followingTerrain, bouncingOnTerrain or returning)
	void PlaceTrailOnUnit();
	void TrailLogic();
	void TrailRender();

	//Other helper functions
	void UpdateUnitColliders();

public:
	fPoint position;
	ModulePlayer* playerToFollow = nullptr;//Ship it has to follow
	Collider* unitCol = nullptr;
	float currentOrbit;
	float currentTurnAround;
	float power = 0;
	UnitPhase unitPhase = UnitPhase::rotating;

private:	
	//Rotating
	//- Orbit
	float targetOrbit;//The orbit rotation we want the unit to be in
	bool orbiting;//A bool that indicates if we can make the unit orbit
	int radius = 31;
	const float orbitSpeed = 3.141592 / 27;//The speed at which the unit rotates around the player ship
	//- Turn around
	bool turningAround;//A bool that indicates if we can make the unit turn around
	int turnAroundToRender;
	const float turnAroundSpeed = orbitSpeed * 2;
	//- Spin
	float currentSpinFrame;
	const float spinSpeed = 0.2f;
	SpinAnimation spinAnimation[UNIT_AXIS];// There is an animation for each direction of the unit
	//									  E, ESE,  SE, SSE,   S, SSW,  SW, WSW,   W, WNW,  NW, NNW,   N, NNE,  NE, ENE
	int spriteXDifferences[UNIT_AXIS] = { 8,   8,   8,   8,   8,   9,  13,  14,  14,  14,  13,   9,   8,   8,   8,   8 };//Sprite differences in x, helps us keep the unit centered on its trajectory
	int spriteYDifferences[UNIT_AXIS] = { 8,   8,   8,   8,   8,   8,   8,   8,   8,   9,  13,  15,  14,  15,  13,   9 };//Sprite differences in y, helps us keep the unit centered on its trajectory

	//Shooting
	const float unitProjectileSpeed = 6;//6= pixels it moves each frame
	//									    E, ESE,  SE, SSE,   S, SSW,  SW, WSW,   W, WNW,  NW, NNW,   N, NNE,  NE, ENE
	int shotPosXDifferences[UNIT_AXIS] = { 15,  14,  12,   6,   0,  -5, -11, -13, -14, -13, -11,  -6,   0,   6,  11,  14 };//Helps us position the unit projectile at the top of its antenas
	int shotPosYDifferences[UNIT_AXIS] = {  0,   7,  12,  14,  15,  14,  12,   6,   0,  -6, -11, -14, -14, -13, -10,  -6 };//Helps us position the unit projectile at the top of its antenas
	bool locked = false;

	//Throwing
	const float powerSpeed = 0.02f;
	Uint32 shootTime;
	const float throwingSpeed = 7;
	Animation chargeAnim;
	SDL_Rect chargeFrame;
	int chargeXOffset[15] = { 18, 16, 16, 14, 14, 16, 16, 15, 15, 14, 14, 23, 23, 21, 21 };//INFO: 15 = number of sprites in the charging animation
	int chargeYOffset[15] = { 18, 16, 16, 14, 14, 16, 16, 15, 15, 13, 13, 23, 23, 21, 21 };
	Animation throwAnim;
	SDL_Rect throwFrame;
	Collider* hitDetectionLeft;
	Collider* hitDetectionRight;
	Collider* hitDetectionUp;
	Collider* hitDetectionDown;
	const int sphereDiameter = 16;//The sphere part of the unit

	//Following terrain
	FollowingTerrainDirection followTerrainDir = FTD_notFollowing;
	Collider* colliderToFollow = nullptr;
	int followTerrainSpeed = 4;

	//Bouncing on terrain
	fPoint throwSpeed;

	//Returning
	const float returningSpeed = 7;
	//Return conditions
	const int returnMargin = 80;

	//Positioning
	const float positioningSpeed = 7;

	//Textures
	SDL_Texture* unitTx = nullptr;
	SDL_Texture* blueUnitTx = nullptr;
	SDL_Texture* orangeUnitTx = nullptr;
	SDL_Texture* throwUnitTx = nullptr;
	SDL_Texture* throwUnitOrangeTx = nullptr;
	SDL_Texture* throwUnitBlueTx = nullptr;

	//Trail
	iPoint trailPos[4];
	iPoint lastUnitPos;
	float trailRotation[4] = {0};
	SDL_Rect trailAnim[4];
	const float trailRotationSpeed = PI / 16;//16 axis, but it gets rendered every 2 frames
	bool renderTrail;
	int trailFrameCounter = 0;
};
#endif