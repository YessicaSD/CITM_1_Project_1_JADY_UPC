#ifndef __ENEMY_IF_SPAWNER_H__
#define __ENEMY_IF_SPAWNER_H__

#include "Enemy.h"


#define MAX_SPAWNED 5
#define SPAWN_FRAMES 180

class Enemy;

class Enemy_IF_Spawner : public Enemy
{
public:
	Enemy_IF_Spawner(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw2(SDL_Texture* sprites);

private:
	SDL_Rect insideCore;
	SDL_Rect spawnDoor;

	//Pilots drop off this enemy

	enum animState {
		IDLE,
		OPEN,
	} currentState = IDLE;

	Enemy* spawned[MAX_SPAWNED] = {nullptr};
	int currentEnemies = 0;
	int spawnFrames = 0;
	bool isSpawning = false;
};

#endif // __ENEMY_IF_SPAWNER_H__


