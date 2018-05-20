#ifndef __ENEMY_PINATA_SPAWNER_H__
#define __ENEMY_PINATA_SPAWNER_H__

#include "Enemy.h"


#define MAX_SPAWNED 3
#define SPAWN_FRAMES 180

class Enemy_Pinata;

class Enemy_Pinata_Spawner : public Enemy
{
public:
	Enemy_Pinata_Spawner(int x, int y, POWERUP_TYPE pu_t);
	void Move();

private:
	iPoint fixedPos;
	Animation openAnim;//Pilots drop off this enemy

	enum animState {
		IDLE,
		FOLLOW,
		ROTATE
	} currentState = IDLE;

	Enemy_Pinata* enemies[MAX_SPAWNED];
	int currentEnemies = 0;
	int spawnFrames = SPAWN_FRAMES;
	bool isSpawning = false;
};

#endif // __ENEMY_PINATA_SPAWNER_H__

