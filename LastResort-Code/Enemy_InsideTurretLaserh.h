#ifndef __ENEMY_INSIDE_TURRET_LASER_H__
#define __ENEMY_INSIDE_TURRET_LASER_H__

#include "Enemy.h"

class Enemy_Inside_Turret_Laser : public Enemy
{
private:
	Animation turret;
	int framecount;
public:
	Enemy_Inside_Turret_Laser(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop, fPoint speed);
	void Move();
	void Draw2(SDL_Texture* sprites);

};

#endif // __ENEMY_INSIDE_TURRET_LASER_H__
