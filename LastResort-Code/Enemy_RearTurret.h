#ifndef __ENEMY_REAR_TURRET_H__
#define __ENEMY_REAR_TURRET_H__

#include "Enemy.h"

enum rearTurretMovement
{
	move_static,
	move_forward,
	move_backward
};

class Enemy_RearTurret : public Enemy
{
private:
	//Animation
	SDL_Rect rearTurretRect;

	//Movement
	rearTurretMovement rearTurretMov = move_static;
	iPoint fixedPos;
	int frameCounter = 0;
	const int frameLimitStatic = 10;
	const int frameLimitMove   =  4;
	
	//Shooting
	void rearTurretShoot();
	const float shootSpeed = 3;
	int timesMovedForward = 0;

public:
	Enemy_RearTurret(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw0(SDL_Texture * sprites);
};

#endif // __ENEMY_BASIC_H__