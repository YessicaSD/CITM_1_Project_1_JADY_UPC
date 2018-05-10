#ifndef __ENEMY_PINATA_H__
#define __ENEMY_PINATA_H__

#include "Enemy.h"

class Enemy_Pinata : public Enemy
{
public:
	Enemy_Pinata(int x, int y, POWERUP_TYPE pu_t);
	void Move();

private:
	Animation moveLeftAnim;
	Animation moveRightAnim;
	Animation rotateAnim;
	Animation deathAnim;//Pilots drop off this enemy
	int moveSpeed;
};

#endif // __ENEMY_PINATA_H__
