#ifndef __ENEMY_MECH_SPAWNER_H__
#define __ENEMY_MECH_SPAWNER_H__

#include "Enemy.h"

#define MAX_SPAWNED 3
#define SPAWN_FRAMES 300

enum animState
{
	IDLE,
	ANIMATION,
} ;

class Enemy_Mech_Spawner : public Enemy
{
private:
	Animation MechAppear;
	iPoint initialPosition;
	int spawnFrames = 0;

public:
	Enemy_Mech_Spawner(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	~Enemy_Mech_Spawner() {};
	void Move();
	void Draw1(SDL_Texture* sprites);

	animState currentState = ANIMATION;
	Enemy* spawned[MAX_SPAWNED] = {nullptr};
	int currentEnemies = 0;
	
};

#endif // __ENEMY_MECH_SPAWNER_H__

