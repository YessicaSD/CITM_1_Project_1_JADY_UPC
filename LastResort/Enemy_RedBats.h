#ifndef __ENEMY_REDBATS_H__
#define __ENEMY_REDBATS_H__

#include "Enemy.h"

class Enemy_RedBats : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = SCREEN_HEIGHT / 2;
	Animation RedBats;

public:

	Enemy_RedBats(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void OnCollision(Collider*);
};
#endif // __ENEMY_REDBATS_H__