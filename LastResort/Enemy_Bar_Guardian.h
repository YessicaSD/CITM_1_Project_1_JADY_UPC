#ifndef __ENEMY_BAR_GUARDIAN_H__
#define __ENEMY_BAR_GUARDIAN_H__

#include "Enemy.h"

class ModulePlayer;

enum BarGuardianPhases
{
	barGuard_Up,
	barGuard_Down,
};

class Enemy_BarGuardian : public Enemy
{
public:
	Enemy_BarGuardian(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw(SDL_Texture* sprites);
	void OnCollision(Collider* c2);

private:
	BarGuardianPhases phase = barGuard_Up;
	const float moveSpeed = 0.5f;
	float accumulatedY = 0;//Helps us move the barGuardian with float speed, although it its position is iPoint and not fPoint
	bool eyeOpen = false;
	Animation eyeAnim;
	SDL_Rect topBarAnim;
	SDL_Rect botBarAnim;
	SDL_Rect backAnim;
};

#endif // __ENEMY_BAR_GUARDIAN_H__
