#ifndef __ENEMY_INTERGSLSCTIC_F_H__
#define __ENEMY_INTERGSLSCTIC_F_H__

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
	fPoint speed;
	fPoint aceleration;
	int shootFrames;
};

#endif // __ENEMY_INTERGSLSCTIC_F_H__

