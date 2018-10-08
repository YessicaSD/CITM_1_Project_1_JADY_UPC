#ifndef __ENEMY_OSCILATOR_H__
#define __ENEMY_OSCILATOR_H__

#include "Enemy.h"

class Enemy_Oscilator : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up=true;
	int original_y = SCREEN_HEIGHT/2 -20;
	Animation Oscilator;

public:

	Enemy_Oscilator(int x, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw1(SDL_Texture * sprites);
};

#endif // __ENEMY_OSCILATOR_H__
