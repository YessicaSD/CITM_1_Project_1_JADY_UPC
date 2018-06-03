#ifndef __ENEMY_OUTDOOR_TURRET_H__
#define __ENEMY_OUTDOOR_TURRET_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Outdoor_turret : public Enemy
{
private:
	Animation OutdoorTurretAnim;
	iPoint initalPosition;
	Uint32 StartTime;
	
public:
	Enemy_Outdoor_turret(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw1(SDL_Texture * sprites);
};

#endif // __ENEMY_OUTDOOR_TURRET_H__

