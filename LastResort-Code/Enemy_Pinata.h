#ifndef __ENEMY_PINATA_H__
#define __ENEMY_PINATA_H__

#include "Enemy.h"
#include "MovPath.h"

class ModulePlayer;

class Enemy_Pinata : public Enemy
{
public:
	Enemy_Pinata(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw1(SDL_Texture* sprites);
	void Draw2(SDL_Texture* sprites);
	void CheckTarget() ;
	void CheckDirection();

private:
	void DrawPinata(SDL_Texture* sprites);

	//Animations---------------------------
	Animation moveAnim;
	Animation rotateAnim;
	Animation initAnim;
	//Variables---------------------------
	fPoint float_position;
	iPoint fixedPos;
	fPoint speed;
	fPoint aceleration;

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
	bool drawOnLayer2 = false;
};

#endif // __ENEMY_PINATA_H__
