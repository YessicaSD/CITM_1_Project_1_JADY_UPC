#ifndef __ENEMY_SHIP_MOTOR_H__
#define __ENEMY_SHIP_MOTOR_H__

#include "Enemy.h"

class Enemy_Ship_Motor : public Enemy
{
private:
	
	Animation Ship_Thing;

public:

	Enemy_Ship_Motor(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	/*void Move();
	void OnCollision(Collider*);*/
};
#endif // __ENEMY_SHIP_THING_H__
