#ifndef __ENEMY_BAR_GUARDIAN_H__
#define __ENEMY_BAR_GUARDIAN_H__

#include "Enemy.h"

enum BarGuardianPhases
{
	barGuard_Up,
	barGuard_Down,
	barGuard_Transition,
};

enum EyePhases
{
	closed,
	open,
	opening,
	closing
};

class Enemy_BarGuardian : public Enemy
{
public:
	Enemy_BarGuardian(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	~Enemy_BarGuardian();
	void Move();
	void Draw(SDL_Texture* sprites);

private:
	BarGuardianPhases phase = barGuard_Up;
	EyePhases eyePhase = closed;
	const float moveSpeed = 0.5f;
	float accumulatedY = 0;//Helps us move the barGuardian with float speed, although it its position is iPoint and not fPoint
	Animation closingEye;
	Animation openingEye;
	Animation eyeOpen;
	Animation eyeClosed;
	SDL_Rect topBarAnim;
	SDL_Rect botBarAnim;
	SDL_Rect backAnim;
	Collider* topBarCol = nullptr;
	Collider* botBarCol = nullptr;
	int transitionCounter = 0;
	int eyeCounter = 0;
	iPoint topBarPos;
	iPoint botBarPos;
	int shotCounter = 0;
};

#endif // __ENEMY_BAR_GUARDIAN_H__
