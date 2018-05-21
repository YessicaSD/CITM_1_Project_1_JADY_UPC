#ifndef __ENEMY_PINATA_SPAWNER_H__
#define __ENEMY_PINATA_SPAWNER_H__

#include "Enemy.h"


#define MAX_SPAWNED 3
#define SPAWN_FRAMES 300

class Enemy;

class Enemy_Pinata_Spawner : public Enemy
{
public:
	Enemy_Pinata_Spawner(int x, int y, POWERUP_TYPE pu_t);
	void Move();
	void Draw(SDL_Texture* sprites);

private:
	iPoint fixedPos;
	Animation openAnim;//Pilots drop off this enemy

	enum animState {
		IDLE,
		OPEN,
	} currentState = IDLE;

	Enemy* spawned[MAX_SPAWNED];
	int currentEnemies = 0;
	int spawnFrames = 0;
	bool isSpawning = false;
};

#endif // __ENEMY_PINATA_SPAWNER_H__

