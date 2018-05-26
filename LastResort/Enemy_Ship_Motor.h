#ifndef __ENEMY_SHIP_MOTOR_H__
#define __ENEMY_SHIP_MOTOR_H__

#include "Enemy.h"

class Enemy_Ship_Motor : public Enemy
{
private:
	
	Animation Ship_Motor;
	int i, j;
	SDL_Rect Ship_Part;
	enum  state
	{
		OPEN, 
		CLOSE,

	}stateMotor=CLOSE;
	int frameCount=0;
	Enemy* MissileLaunch;

public:

	Enemy_Ship_Motor(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw(SDL_Texture*);
	void OnCollision(Collider*);
};
#endif // __ENEMY_SHIP_THING_H__
