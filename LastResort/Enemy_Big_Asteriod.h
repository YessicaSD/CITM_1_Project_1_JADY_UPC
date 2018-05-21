#ifndef __ENEMY_BIG_ASTERIOD_H__
#define __ENEMY_BIG_ASTERIOD_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Big_Asteriod : public Enemy
{
private:
	Animation Mech;
	fPoint finalPosition;
	bool going_right;
	bool going_left;
	SDL_Texture *LacerTex;
	int resp;
	int limit;
	int limit_2;
public:
	Enemy_Big_Asteriod(int x, int y, POWERUP_TYPE pu_t);
	~Enemy_Big_Asteriod() {};
	void Move();
};

#endif // __ENEMY_BIG_ASTERIOD_H__
