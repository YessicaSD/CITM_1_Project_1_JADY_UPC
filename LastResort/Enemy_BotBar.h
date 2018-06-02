#ifndef __ENEMY_BOT_BAR_H__
#define __ENEMY_BOT_BAR_H__

#include "Enemy.h"

class Enemy_BotBar : public Enemy
{
public:
	Enemy_BotBar(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw(SDL_Texture* sprites);

private:
	SDL_Rect barAnim;
};

#endif // __ENEMY_BOT_BAR_H__