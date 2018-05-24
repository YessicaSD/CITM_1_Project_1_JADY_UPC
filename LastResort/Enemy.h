#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModulePowerUps.h"

struct SDL_Texture;
struct Collider;


class Enemy
{



public:
	iPoint position;
	iPoint speed;//Not all enemies use this parameter to move, but its very helpful for those who do
	POWERUP_TYPE powerUp_drop;
	Animation* animation = nullptr;
	Collider* collider = nullptr;
	//Statistics---------------------
	bool isDead = false;
	float hp;
	int scoreValue;
	//Damage properties--------------
	int dmg_frames = 0;
	int flashing_interval = -1;
	bool isDamaged = false;
	

public:
	Enemy(int x, int y, POWERUP_TYPE pu_t);
	Enemy(int x, int y, POWERUP_TYPE pu_t,iPoint speed);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider*);
};

#endif // __ENEMY_H__
