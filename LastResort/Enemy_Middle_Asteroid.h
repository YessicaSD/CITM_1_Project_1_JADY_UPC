#ifndef __ENEMY_MIDDLE_ASTEROID_H__
#define __ENEMY_MIDDLE_ASTEROID_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Middle_Asteroid : public Enemy
{
private:
	Animation Middle_Asteroid;
	fPoint finalPosition;



public:
	Enemy_Middle_Asteroid(int x, int y, POWERUP_TYPE pu_t);
	
	void Move();
	void Draw(SDL_Texture* sprites);
	
	void OnCollision(Collider*);
};

#endif // __ENEMY_MIDDLE_ASTEROID_H__