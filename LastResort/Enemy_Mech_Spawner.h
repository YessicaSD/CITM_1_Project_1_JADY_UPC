#ifndef __ENEMY_MECH_SPAWNER_H__
#define __ENEMY_MECH_SPAWNER_H__

#include "Enemy.h"
#include "ModuleParticles.h"

#define MAX_SPAWNED 3
#define SPAWN_FRAMES 300

class Enemy_Mech_Spawner : public Enemy
{
private:
	Animation MechAppear;
	iPoint initialPosition;
	int spawnFrames = 0;

public:
	Enemy_Mech_Spawner(int x, int y, POWERUP_TYPE pu_t);
	~Enemy_Mech_Spawner() {};
	void Move();
	void Draw(SDL_Texture* sprites);

	enum animState {
		IDLE,
		ANIMATION,
	} currentState = ANIMATION;

	Enemy* spawned[MAX_SPAWNED];

	int currentEnemies = 0;
	//int spawnFrames = 0;
	//bool isSpawning = false;

	//Times
	Uint32 lastSpawnTime = 0;
	Uint32 spawnDelay = 1000;
};

#endif // __ENEMY_MECH_SPAWNER_H__

