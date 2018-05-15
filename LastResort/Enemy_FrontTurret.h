#ifndef __ENEMY_FRONT_TURRET_H__
#define __ENEMY_FRONT_TURRET_H__

#include "Enemy.h"

class Enemy_FrontTurret : public Enemy
{
public:
	Enemy_FrontTurret(int x, int y, POWERUP_TYPE pu_t);
	void Move();

private:
	Animation frontTurretAnim;
	int initialY;
	int initialX;
};

#endif // __ENEMY_FRONT_SHIP_TURRET_H__