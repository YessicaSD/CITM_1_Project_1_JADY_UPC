#ifndef __ENEMY_BIG_ASTERIOD_H__
#define __ENEMY_BIG_ASTERIOD_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Big_Asteroid : public Enemy
{
private:
	Animation BigAsteroid;
	fPoint finalPosition;
	bool going_right;
	bool going_left;
	SDL_Texture *LacerTex;
	int resp;
	int limit;
	int limit_2;
public:
	Enemy_Big_Asteroid(int x, int y, POWERUP_TYPE pu_t);
	~Enemy_Big_Asteroid() {};
	void Move();
};

#endif // __ENEMY_BIG_ASTERIOD_H__
