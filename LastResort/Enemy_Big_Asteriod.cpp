#include "Enemy_Big_Asteriod.h"
Enemy_Big_Asteroid::Enemy_Big_Asteroid(int x, int y, POWERUP_TYPE pu_t) :Enemy(x,y, pu_t)
{
	BigAsteroid.PushBack({ 152,176,64,62 });
	animation = &BigAsteroid;
}
void Enemy_Big_Asteroid::Move()
{
	position.x -= 1;
}