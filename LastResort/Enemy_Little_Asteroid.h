#ifndef __ENEMY_LITTLE_ASTERIOD_H__
#define __ENEMY_LITTLE_ASTERIOD_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Little_Asteroid : public Enemy
{
private:
	Animation LittleAsteroid;
	fPoint fposition;
public:
	Enemy_Little_Asteroid(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop, fPoint speed);
	~Enemy_Little_Asteroid() {};
	void Move();
	void Draw(SDL_Texture* sprites);
	void OnCollision(Collider*);

};

#endif // __ENEMY_LITTLE_ASTERIOD_H__

