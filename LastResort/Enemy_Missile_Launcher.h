#ifndef __ENEMY_MISSILE_LAUNCHER_H__
#define __ENEMY_MISSILE_LAUNCHER_H__

#include "Enemy.h"

class Enemy_Missile_Launcher : public Enemy
{
private:
	Animation Missile_Launcher;
	iPoint fixedPos2;
	
public:
	Enemy_Missile_Launcher(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
};

#endif // __ENEMY_MISSILE_LAUNCHER_H__

