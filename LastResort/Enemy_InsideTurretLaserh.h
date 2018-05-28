#ifndef __ENEMY_INSIDE_TURRET_LASER_H__
#define __ENEMY_INSIDE_TURRET_LASER_H__

#include "Enemy.h"

class Enemy_Inside_Turret_Laser : public Enemy
{
private:
	Animation turret;

public:
	Enemy_Inside_Turret_Laser(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
};

#endif // __ENEMY_INSIDE_TURRET_LASER_H__
