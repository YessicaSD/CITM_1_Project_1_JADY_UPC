#ifndef __ENEMY_ROTATING_TURRET_H__
#define __ENEMY_ROTATING_TURRET_H__

#include "Enemy.h"
#include "Rotation.h"

class Enemy_RotatingTurret : public Enemy
{
public:
	Enemy_RotatingTurret(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw1(SDL_Texture*);
	void OnCollision(Collider*);

private:
	//Helper functions
	void ShootBall(fPoint position, fPoint speed);

	Animation rotatingTurretAnim;
	iPoint targetPlayerPos;
	float rotation;
	iPoint fixedPos;

	//					     E,  ESE,   SE,  SSE,    S,  SSW,   SW,  WSW,    W,  WNW,   NW,  NNW,    N,  NNE,   NE,  ENE
	int spriteXOffset[16]{ -10,  -11,  -10,  -10,  -11,  -11,  -13,  -13,  -13,  -13,  -12,  -12,  -11,  -11,  -10,  -10 };
	int spriteYOffset[16]{ -13,  -12,  -12,  -11,  -10,  -11,  -11,  -11,  -11,  -11,  -12,  -14,  -14,  -14,  -14,  -14 };

	const float shootSpeeed = 4;
	const float shootSeparation = 2 * PI / 32;
	int frameCounter;
	int pushBackNumber;
};

#endif // __ENEMY_ROTATING_TURRET_H__
