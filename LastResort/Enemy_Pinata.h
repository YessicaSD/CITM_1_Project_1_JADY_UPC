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

private:
	//Animations---------------------------
	Animation moveAnim;
	Animation rotateAnim;
	Animation initAnim;
	//Variables---------------------------
	enum Direction {
		STILL,
		RIGHT,
		LEFT
	} currentDir = STILL, lastDir = STILL;

	enum Move_States {
		INIT,
		FOLLOW,
		ROTATE
	} currentState = INIT;

	MovePath pinataMov;
	bool checkTarget = false;
	bool checkDirection = false;
	bool blitEx = false;
	ModulePlayer* currentTarget = nullptr;
	ModulePlayer* lastTarget = nullptr;
};

#endif // __ENEMY_PINATA_H__
