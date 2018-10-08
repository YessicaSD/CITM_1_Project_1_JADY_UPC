#ifndef __ENEMY_INTERGSLSCTIC_F_H__
#define __ENEMY_INTERGSLSCTIC_F_H__

#include "Enemy.h"
#include "MovPath.h"

class ModulePlayer;

class Enemy_Intergalactic_F : public Enemy
{
public:
	Enemy_Intergalactic_F(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw0(SDL_Texture* sprites);
	void CheckTarget();
	void CheckDirection();

private:
	//Animations---------------------------
	Animation moveRAnim;
	Animation moveLAnim;
	Animation rotateRAnim;
	Animation rotateLAnim;
	Animation shotAnim;

	//Variables---------------------------
	fPoint float_position;
	int shootFrames;
	int currentFrames = 0;
	bool isShooting = false;

	enum Direction {
		NONE,
		RIGHT,
		LEFT
	} currentDir = RIGHT, lastDir = RIGHT;

	enum MoveState {
		MOVE,
		ROTATE
	} currentState = MOVE;

	MovePath enemyMov;
	ModulePlayer* currentTarget = nullptr;
	ModulePlayer* lastTarget = nullptr;
};

#endif // __ENEMY_INTERGSLSCTIC_F_H__

