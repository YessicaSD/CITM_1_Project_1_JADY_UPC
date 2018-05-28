#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "ModulePowerups.h"
#include "Enemy_Basic.h"
#include "Enemy_Oscilator.h"
#include "Enemy_PowerDropper.h"


#define MAX_ENEMIES 100


enum ENEMY_TYPES
{
	NO_TYPE = -1,
	BASIC,
	OSCILATOR,
	POWERDROPPER,
	METALCROW,
	REDBATS,
	ROTATING_TURRET,
	PINATA,
	PINATA_SPAWNER,
	FRONT_TURRET,
	OUTDOOR_TURRET,
	MECH,
	MECH_SPAWNER,
	BIG_ASTEROID,
	MIDDLE_ASTEROID,
	LITTLE_ASTEROID,
	INDOOR_TURRET,
	INDOOR_TURRET_LASER,
	REAR_TURRET,
	MISSILE_TURRET,
	SHIP_MOTOR,
	MISSILE_LAUNCHER,
	MISSILE,
	INTERGALACTIC_F,
	IF_SPAWNER,
	MAX_ENEMY
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	iPoint speed;
	Uint32 delay;//In miliseconds
	POWERUP_TYPE pu_Type = POWERUP_TYPE:: NOPOWERUP;
	//Additional variables (help us spawn enemies with time)
	bool counting = false;
	Uint32 spawnTime;
	Enemy *pointer = nullptr;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status InputUpdate();
	update_status LogicUpdate();
	update_status RenderUpdate0();
	update_status RenderUpdate1();
	update_status RenderUpdate2();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, Uint32 delay = 0, POWERUP_TYPE powerup_type = NOPOWERUP, iPoint speed = { 0, 0 });
	Enemy* InstaSpawn(ENEMY_TYPES type, int x, int y, POWERUP_TYPE powerup_type = NOPOWERUP, iPoint speed  ={ 0, 0 });

private:

	Enemy* SpawnEnemy(const EnemyInfo& info);
	void RenderEnemy(Enemy*);

private:
	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];

public:

	SDL_Texture* nml_sprites = nullptr;
	SDL_Texture* dmg_sprites = nullptr;
	
};

#endif // __ModuleEnemies_H__
