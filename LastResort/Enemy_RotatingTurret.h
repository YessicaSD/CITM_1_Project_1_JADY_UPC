#ifndef __ENEMY_ROTATING_TURRET_H__
#define __ENEMY_ROTATING_TURRET_H__

#include "Enemy.h"

class Enemy_RotatingTurret : public Enemy
{
public:
	Enemy_RotatingTurret(int x, int y, POWERUP_TYPE pu_t);
	void Move();

private:
	Animation rotatingTurretAnim;
	iPoint targetPlayerPos;
	int rotation;
};

#endif // __ENEMY_ROTATING_TURRET_H__
