#ifndef __ENEMY_RED_LAMELLA_H__
#define __ENEMY_RED_LAMELLA_H__

#include "Enemy.h"
#include "MovPath.h"

class ModulePlayer;

class Enemy_RedLamella: public Enemy
{
public:
	Enemy_RedLamella(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw1(SDL_Texture* sprites);
	void CheckTarget();
	bool CheckDirection();

private:
	//Animations---------------------------
	Animation moveAnim;
	Animation rotateAnim;
	//Variables---------------------------
	fPoint float_position;
	fPoint speed;
	fPoint aceleration;
	ModulePlayer* currentTarget = nullptr;
	ModulePlayer* lastTarget = nullptr;
	MovePath pinataMov;

	bool blitEx = false;
	bool runAway = false;
	int currentFrames = 0;
	int runAwayFrames = 0;


	enum DirectionX {
		RIGHT,
		LEFT
	} currentDirX = LEFT, lastDirX = LEFT;

	enum MoveState {
		FOLLOW,
		ROTATE,
	} currentState = FOLLOW;


	
};

#endif // __ENEMY_RED_LAMELLA_H__
