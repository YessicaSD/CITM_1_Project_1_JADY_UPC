#ifndef __ENEMY_PINATA_H__
#define __ENEMY_PINATA_H__

#include "Enemy.h"
#include "MovPath.h"

class ModulePlayer;

class Enemy_Pinata : public Enemy
{
public:
	Enemy_Pinata(int x, int y, POWERUP_TYPE pu_t);
	void Move();
	void Draw(SDL_Texture* sprites);
	void CheckTarget() ;
	void CheckDirection();

private:
	//Animations---------------------------
	Animation moveAnim;
	Animation rotateAnim;
	Animation initAnim;
	//Variables---------------------------
	fPoint float_position;
	int initialY;
	int initialX;
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

#endif // __ENEMY_PINATA_H__
