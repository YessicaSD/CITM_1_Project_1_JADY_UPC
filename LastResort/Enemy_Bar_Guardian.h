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
	const int moveSpeed = 1;
	bool eyeOpen = false;
	Animation eyeAnim;
	SDL_Rect topBarAnim;
	SDL_Rect botBarAnim;
	SDL_Rect backAnim;
};

#endif // __ENEMY_BAR_GUARDIAN_H__
