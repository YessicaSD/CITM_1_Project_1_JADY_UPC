#ifndef __ENEMY_BIG_ASTERIOD_H__
#define __ENEMY_BIG_ASTERIOD_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Big_Asteroid : public Enemy
{
private:
	Animation BigAsteroid;
public:
	Enemy_Big_Asteroid(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	~Enemy_Big_Asteroid() {};
	void Move();
	void Draw1(SDL_Texture* sprites);
	void OnCollision(Collider*);
};

#endif // __ENEMY_BIG_ASTERIOD_H__
