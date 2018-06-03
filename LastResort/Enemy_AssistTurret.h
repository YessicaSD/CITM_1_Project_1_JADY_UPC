#ifndef __ENEMY_ASSIST_TURRET_H__
#define __ENEMY_ASSIST_TURRET_H__

#include "Enemy.h"

class Enemy_Assist_Turret : public Enemy
{
private:
	Animation turret;
	iPoint fixedPos;
	int frameCount;

public:

	Enemy_Assist_Turret(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw1(SDL_Texture * sprites);
};

#endif // __ENEMY_ASSIST_TURRET_H__

