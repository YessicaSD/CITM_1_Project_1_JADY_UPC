#ifndef __ModulePowerups_H__
#define __ModulePowerups_H__

#include "Module.h"

#define MAX_POWERUPS 20

//MODULE POWERUPS EXPLANATION------------------------------------------------
//This module follows the structure of the module enemies
//But it doesn't spawn. It only moves, renders and despawns powerups
//Because powerups are directly spawned via AddPowerup when an enemy dies

struct Mix_Chunk;

enum POWERUP_TYPE
{
	NOPOWERUP = -1,
	SPEED,
	DESPEED,
	LASER,
	HOMING,
	GROUND,
	MAX_POWERUP
};

class Powerup;

//We don't need x and y positions on powerupinfo (as opposed to enemy info) because we won't be checking their positions to spawn them
struct SDL_Texture;

class ModulePowerups : public Module
{
public:
	ModulePowerups();
	~ModulePowerups();

	bool Start();
	update_status LogicUpdate();//We grab all our powerups and we render them
	update_status RenderUpdate2();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddPowerup(int, int, POWERUP_TYPE);
	Mix_Chunk * speedSFX = nullptr;
	Mix_Chunk * getPowerupSFX = nullptr;

private:
	//We don't need a queue, because we'll render the powerups as soon as AddCollider gets called
	Powerup* powerups[MAX_POWERUPS];
	SDL_Texture* powerupTx = nullptr;
	const float moveSpeed = 1;
};
#endif