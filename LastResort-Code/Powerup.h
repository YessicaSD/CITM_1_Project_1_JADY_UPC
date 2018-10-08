#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModulePowerups.h"

struct SDL_Texture;
struct Collider;
struct ModulePlayer;

class Powerup
{
public:
	Animation* animation = nullptr ;
	Collider* collider = nullptr;
	iPoint position;
	POWERUP_TYPE type = NOPOWERUP;

public:
	Powerup(int x, int y);
	virtual ~Powerup();

	const Collider* GetCollider() const;
	virtual void OnCollision(Collider* , ModulePlayer* );
};

#endif