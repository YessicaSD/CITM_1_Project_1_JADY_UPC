#ifndef __ENEMY_INDOOR_TURRET_H__
#define __ENEMY_INDOOR_TURRET_H__

#include "Enemy.h"
#include "Rotation.h"

class Enemy_indoorTurret : public Enemy
{
public:
	Enemy_indoorTurret(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop, fPoint speed);
	void Move();
	void Draw(SDL_Texture*Tx);
	//void OnCollision(Collider*);

private:
	//Helper functions
	fPoint fixedPos;
	Animation indoorTurretAnim;
	iPoint targetPlayerPos;
	fPoint ParticleSpeed;
	fPoint fPosition;
	int frameCounter=0;


};

#endif // __ENEMY_INDOOR_TURRET_H__

