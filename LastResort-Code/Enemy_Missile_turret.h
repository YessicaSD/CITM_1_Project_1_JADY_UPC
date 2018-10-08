#ifndef __ENEMY_MISSILE_TURRET_H__
#define __ENEMY_MISSILE_TURRET_H__

#include "Enemy.h"

class Enemy_Missile_turret : public Enemy
{
private:
	Animation turret;
	iPoint fixedPos;

public:

	Enemy_Missile_turret(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	int frameCount;
	void Move();
	void Draw1(SDL_Texture * sprites);
};

#endif // __ENEMY_OSCILATOR_H__
