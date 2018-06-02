#ifndef __ENEMY_TOP_BAR_H__
#define __ENEMY_TOP_BAR_H__

#include "Enemy.h"

class Enemy_TopBar : public Enemy
{
public:
	Enemy_TopBar(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw(SDL_Texture* sprites);

private:
	SDL_Rect barAnim;
};

#endif // __ENEMY_TOP_BAR_H__