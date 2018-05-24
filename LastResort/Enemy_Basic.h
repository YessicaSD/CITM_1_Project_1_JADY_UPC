#ifndef __ENEMY_BASIC_H__
#define __ENEMY_BASIC_H__

#include "Enemy.h"

class Enemy_Basic : public Enemy
{
private:
	Animation basicenemy;
	int initialY;

public:
	Enemy_Basic(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
};

#endif // __ENEMY_BASIC_H__
