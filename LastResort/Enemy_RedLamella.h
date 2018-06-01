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
	void Draw(SDL_Texture* sprites);
	void CheckTarget();
	void CheckDirection();

private:
	//Animations---------------------------
	Animation moveAnim;
	Animation rotateAnim;
	Animation initAnim;
	//Variables---------------------------
	fPoint float_position;
	iPoint fixedPos;

	//int initialY;
	//int initialX;
	enum Direction {
		NONE,
		RIGHT,
		LEFT
	} currentDir = NONE, lastDir = NONE;

	enum MoveState {
		IDLE,
		FOLLOW,
		ROTATE
	} currentState = IDLE;

	MovePath pinataMov;

	bool blitEx = false;
	ModulePlayer* currentTarget = nullptr;
	ModulePlayer* lastTarget = nullptr;
};

#endif // __ENEMY_RED_LAMELLA_H__
