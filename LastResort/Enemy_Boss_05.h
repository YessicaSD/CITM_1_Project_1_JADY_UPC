#ifndef __ENEMY_BOSS_05_H__
#define __ENEMY_BOSS_05_H__

#include "Enemy.h"
#include "MovPath.h"

class ModulePlayer;

class Enemy_Boss_05 : public Enemy
{
public:
	Enemy_Boss_05(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw(SDL_Texture* sprites);

private:
	//Animations---------------------------
	Animation bossAnim;
	//Variables----------------------------
	fPoint float_position;
	fPoint speed;
	fPoint aceleration;
	int shootFrames;
	enum DirectionY {
		UP,
		DOWN
	} currentDir = UP;
};

#endif // __ENEMY_BOSS_05_H__

