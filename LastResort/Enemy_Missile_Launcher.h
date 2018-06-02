#ifndef __ENEMY_MISSILE_LAUNCHER_H__
#define __ENEMY_MISSILE_LAUNCHER_H__

#include "Enemy.h"
enum missilestate
{
	IDLEM,
	LASTDOWN,
	DOWN,
	
};
class Enemy_Missile_Launcher : public Enemy
{
private:
	Animation Missile_Launcher;
	int frameCount = 0;
	int mframeCount = 0;
	int lastMissile;
	SDL_Rect shipPart;
	SDL_Rect missile;
	iPoint missilePosition[8];
	missilestate mstate;
public:
	Enemy_Missile_Launcher(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Enemy_Missile_Launcher::Draw(SDL_Texture* sprites);
};

#endif // __ENEMY_MISSILE_LAUNCHER_H__

