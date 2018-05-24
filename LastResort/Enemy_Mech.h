#ifndef __ENEMY_MECH_H__
#define __ENEMY_MECH_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Mech : public Enemy
{
private:
	Animation Mech;
	fPoint finalPosition;
	bool going_right;
	bool going_left;
	int resp;
	int limit;
	int limit_2;
	

public:
	Enemy_Mech(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	~Enemy_Mech() {};
	void Move();
	void Draw(SDL_Texture* sprites);
};

#endif // __ENEMY_MECH_H__
