#ifndef __ENEMY_MECH_SPAWNER_H__
#define __ENEMY_MECH_SPAWNER_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Mech_Spawner : public Enemy
{
private:
	Animation MechSpawner;
	iPoint initialPosition;
	
public:
	Enemy_Mech_Spawner(int x, int y, POWERUP_TYPE pu_t);
	~Enemy_Mech_Spawner() {};
	void Move();
	
};

#endif // __ENEMY_MECH_SPAWNER_H__

