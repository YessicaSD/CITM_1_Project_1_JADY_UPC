#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Player1.h"
#include "Player2.h"
#include "ModulePowerups.h"
#include "ModuleStage05.h"
//Enemies----------------------------
#include "Enemy.h"
#include "Enemy_Oscilator.h"
#include "Enemy_Basic.h"
#include "Enemy_PowerDropper.h"
#include "Enemy_MetalCraw.h"
#include "Enemy_RedBats.h"
#include "Enemy_RotatingTurret.h"
#include "Enemy_Pinata.h"
#include "Enemy_Pinata_Spawner.h"
#include "Enemy_FrontTurret.h"
#include "Enemy_Outdoor_turret.h"
#include "Enemy_Outdoor_Laser.h"
#include "Enemy_Mech.h"
#include "Enemy_Mech_Spawner.h"
#include "Enemy_Big_Asteriod.h"
#include "Enemy_Middle_Asteroid.h"
#include "Enemy_Little_Asteroid.h"
#include "Enemy_Indoor_turret.h"
#include "Enemy_RearTurret.h"

#define DAMAGE_FLASHING_INTERVAL 4

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	 //ALL IN 1 PNG
	nml_sprites = App->textures->Load("Assets/General/Enemies/Enemies1.png");
    dmg_sprites = App->textures->Load("Assets/General/Enemies/Enemies1_white.png");
	
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	//SPAWN WITH MARGINS (queue)---------------------------------------------------------------------
	//- Check if the enemy is inside the "spawn area (viewport + spawn margin)" to spawn it
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (App->stage05->spawnPos.x + queue[i].x < 0 + SCREEN_WIDTH + SPAWN_MARGIN_RIGHT &&
				App->stage05->spawnPos.x + queue[i].x > 0 - SPAWN_MARGIN_LEFT &&
				App->stage05->spawnPos.y + queue[i].y > 0 - SPAWN_MARGIN_UP &&
				App->stage05->spawnPos.y + queue[i].y < 0 + SCREEN_HEIGHT + SPAWN_MARGIN_DOWN)
			{
				//If we get to the position, we start counting
				if (queue[i].counting == false)
				{
					queue[i].spawnTime = SDL_GetTicks() + queue[i].delay;
					queue[i].counting = true;
				}
			}
			//If we reach the spawn time, we spawn the enemy!
			if (queue[i].counting == true && SDL_GetTicks() >= queue[i].spawnTime)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at x: %d, y: %d", queue[i].x, queue[i].y);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr)
		{
			enemies[i]->Move();
		}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->isDamaged)
			{
				if (enemies[i]->flashing_interval %2)
					enemies[i]->Draw(dmg_sprites);
				else
					enemies[i]->Draw(nml_sprites);
					
				enemies[i]->dmg_frames += 1;

				if (enemies[i]->dmg_frames > 3) {
					enemies[i]->flashing_interval += 1;
					enemies[i]->dmg_frames = 0;
				}
				if (enemies[i]->flashing_interval > DAMAGE_FLASHING_INTERVAL) {
					enemies[i]->isDamaged = false;
					enemies[i]->flashing_interval = -1;
				}

			}
			else
			{
				enemies[i]->Draw(nml_sprites);
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	//Check if the enemy is outside the "spawn area (viewport + despawn margin)" to despawn it---------------------------------------------------------------------------
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x > 0 + SCREEN_WIDTH + DESPAWN_MARGIN_RIGHT ||
				enemies[i]->position.x < 0 - DESPAWN_MARGIN_LEFT ||
				enemies[i]->position.y < 0 - DESPAWN_MARGIN_UP ||
				enemies[i]->position.y > 0 + SCREEN_HEIGHT + DESPAWN_MARGIN_DOWN)
			{
				LOG("DeSpawning enemy at x: %d, y: %d", enemies[i]->position.x, enemies[i]->position.y);
				enemies[i]->isDead = true;
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->isDead = true;
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
			queue[i].type = ENEMY_TYPES::NO_TYPE;
			queue[i].delay = 0;
			queue[i].pu_Type = POWERUP_TYPE::NOPOWERUP;
			queue[i].counting = false;
			queue[i].spawnTime = 0;
	}

	App->textures->Unload(nml_sprites);
	App->textures->Unload(dmg_sprites);

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, Uint32 delay, POWERUP_TYPE powerup_type, iPoint speed)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].delay = delay;
			queue[i].pu_Type = powerup_type;
			queue[i].speed = speed;

			ret = true;
			break;
		}
	}

	return ret;
}

//Gets deleted if you instaspawn in a position that's different to the camera
Enemy* ModuleEnemies::InstaSpawn(ENEMY_TYPES type, int x, int y, POWERUP_TYPE powerup_type,  iPoint speed)
{
	EnemyInfo enemyInfo;
	enemyInfo.type = type;
	enemyInfo.x = x;
	enemyInfo.y = y;
	enemyInfo.speed = speed;
	enemyInfo.delay = 0;
	enemyInfo.pu_Type = powerup_type;
	return SpawnEnemy(enemyInfo);
}

Enemy* ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::BASIC:
			enemies[i] = new Enemy_Basic(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 1, 100, info.pu_Type);
			break;
		case ENEMY_TYPES::OSCILATOR:
			enemies[i] = new Enemy_Oscilator(info.x + App->stage05->spawnPos.x, 5, 100, info.pu_Type);
			break;
		case ENEMY_TYPES::POWERDROPPER:
			enemies[i] = new Enemy_PowerDropper(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 1, 100, info.pu_Type);
			break;
		case ENEMY_TYPES::METALCROW:
			enemies[i] = new Enemy_MetalCraw(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 50, 1000, info.pu_Type);
			break;
		case  ENEMY_TYPES::REDBATS:
			enemies[i] = new Enemy_RedBats(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 1, 100, info.pu_Type);
			break;
		case ENEMY_TYPES::ROTATING_TURRET:
			enemies[i] = new Enemy_RotatingTurret(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 12, 200, info.pu_Type);
			break;
		case ENEMY_TYPES::PINATA:
			enemies[i] = new Enemy_Pinata(info.x, info.y, 1, 200, info.pu_Type);
			break;
		case ENEMY_TYPES::PINATA_SPAWNER:
			enemies[i] = new Enemy_Pinata_Spawner(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 5, 200, info.pu_Type);
			break;
		case ENEMY_TYPES::FRONT_TURRET:
			enemies[i] = new Enemy_FrontTurret(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 5, 200, info.pu_Type);
			break;
		case ENEMY_TYPES::OUTDOOR_TURRET:
			enemies[i] = new Enemy_Outdoor_turret(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 15, 300, info.pu_Type);
			break;
		case ENEMY_TYPES::MECH:
			enemies[i] = new Enemy_Mech(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 3, 300, info.pu_Type);
			break;
		case ENEMY_TYPES::MECH_SPAWNER:
			enemies[i] = new Enemy_Mech_Spawner(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 1, 0, info.pu_Type);
			break;
		case ENEMY_TYPES::BIG_ASTEROID:
			enemies[i] = new Enemy_Big_Asteroid(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 5, 100, info.pu_Type);
			break;
		case ENEMY_TYPES::MIDDLE_ASTEROID:
			enemies[i] = new Enemy_Middle_Asteroid(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 1, 100, info.pu_Type);
			break;
		case ENEMY_TYPES::LITTLE_ASTEROID:
			enemies[i] = new Enemy_Little_Asteroid(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 1, 100, info.pu_Type, info.speed);
			break;
		case ENEMY_TYPES::INDOOR_TURRET:
			enemies[i] = new Enemy_indoorTurret(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 7, 300, info.pu_Type, info.speed);
			break;
		case ENEMY_TYPES::REAR_TURRET:
			enemies[i] = new Enemy_RearTurret(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, 150, 500, info.pu_Type);
			break;
		}
		return enemies[i];
	}
	return nullptr;
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->collider == c1)
		{
			//Rest hp to enemies depending on the collider's damage
			enemies[i]->hp -= c2->damage;  
			//If enemy dies-----------------------------------------
			if (enemies[i]->hp <= 0)
			{
				//---Give out points------------------------
				if (c2->type == COLLIDER_PLAYER_1_SHOT) {
					App->player1->score += enemies[i]->scoreValue;
				}
				else if (c2->type == COLLIDER_PLAYER_2_SHOT) {
					App->player2->score += enemies[i]->scoreValue;
				}
				//---Drop powerup---------------------------
				if (enemies[i]->powerUp_drop != NOPOWERUP) {
					App->powerups->AddPowerup( enemies[i]->position.x, enemies[i]->position.y, enemies[i]->powerUp_drop);
				}
				//---Delete enemy---------------------------
				enemies[i]->isDead = true;
				enemies[i]->OnCollision(c2);
				delete enemies[i];
				enemies[i] = nullptr;
			}
			//If enemy does not die only change its sprite to white
			else  if  (enemies[i]->isDamaged == false && enemies[i]->flashing_interval == -1) {
				enemies[i]->isDamaged = true;
				enemies[i]->flashing_interval = 0;
			}
			break; //TEST 
		}
	}
}
