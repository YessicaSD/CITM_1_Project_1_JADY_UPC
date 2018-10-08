#ifndef __ENEMY_BASIC_H__
#define __ENEMY_BASIC_H__

#include "Enemy.h"

class Enemy_Basic : public Enemy
{
private:
	Animation basicenemy;
	int fixedY;

public:
	Enemy_Basic(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw1(SDL_Texture * sprites);
};

#endif // __ENEMY_BASIC_H__
