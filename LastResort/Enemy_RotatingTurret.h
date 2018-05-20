#ifndef __ENEMY_ROTATING_TURRET_H__
#define __ENEMY_ROTATING_TURRET_H__

#include "Enemy.h"

class Enemy_RotatingTurret : public Enemy
{
public:
	Enemy_RotatingTurret(int, int, POWERUP_TYPE);
	void Move();
	void Draw(SDL_Texture*);

private:
	Animation rotatingTurretAnim;
	iPoint targetPlayerPos;
	float rotation;
	iPoint fixedPos;
};

#endif // __ENEMY_ROTATING_TURRET_H__
