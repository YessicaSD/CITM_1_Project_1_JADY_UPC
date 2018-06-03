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
	void Draw0(SDL_Texture* sprites);
	void Draw1(SDL_Texture* sprites);
	void OnCollision(Collider* collider);
	void AddExplosions();

private:
	//Animations---------------------------
	Animation bossAnim;
	iPoint metalArmorPos;
	iPoint metalArmorTexPos;
	

	//Variables----------------------------
	fPoint initPos;
	fPoint float_position;
	fPoint speed;
	fPoint aceleration;
	int initframes = 0;
	int shootFrames;
	int destroyedParts = 0;
	int destroyFrames = 0;
	int armorWeight;

	enum DirectionY {
		UP,
		DOWN
	} currentDir = UP;
};

#endif // __ENEMY_BOSS_05_H__

