#ifndef __ENEMY_MISSILE_H__
#define __ENEMY_MISSILE_H__

#include "Enemy.h"

class Enemy_Missile : public Enemy
{
private:
	Animation Missile;
	fPoint speed;
	

public:
	Enemy_Missile(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw1(SDL_Texture* sprites);
};

#endif // __ENEMY_MISSILE_LAUNCHER_H__
