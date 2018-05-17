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
#include "Enemy_FrontTurret.h"
#include "Enemy_Outdoor_turret.h"
#include "Enemy_Outdoor_Laser.h"

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
	 ; //ALL IN 1 PNG
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

	//SPAWN WITHOUT MARGINS (instaQueue)-------------------------------------------------------------
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (instaQueue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (App->stage05->spawnPos.x + instaQueue[i].x < 0 + SCREEN_WIDTH &&
				App->stage05->spawnPos.x + instaQueue[i].x > 0 &&
				App->stage05->spawnPos.y + instaQueue[i].y > 0 &&
				App->stage05->spawnPos.y + instaQueue[i].y < 0 + SCREEN_HEIGHT)
			{
				SpawnEnemy(instaQueue[i]);
				instaQueue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at x: %d, y: %d", instaQueue[i].x, instaQueue[i].y);
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

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {

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
			else {
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
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
	App->textures->Unload(nml_sprites);
	App->textures->Unload(dmg_sprites);

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, Uint32 delay, POWERUP_TYPE powerup_type)
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
			ret = true;
			break;
		}
	}

	return ret;
}

bool ModuleEnemies::InstaSpawn(ENEMY_TYPES type, int x, int y, POWERUP_TYPE powerup_type)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (instaQueue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			instaQueue[i].type = type;
			instaQueue[i].x = x;
			instaQueue[i].y = y;
			instaQueue[i].pu_Type = powerup_type;
			ret = true;
			break;
		}
	}

	return ret;
}

//Gets deleted if you instaspawn in a position that's different to the camera
//bool ModuleEnemies::InstaSpawn(ENEMY_TYPES type, int x, int y, POWERUP_TYPE powerup_type)
//{
//	EnemyInfo enemyInfo;
//	enemyInfo.type = type;
//	enemyInfo.x = x;
//	enemyInfo.y = y;
//	enemyInfo.delay = 0;
//	enemyInfo.pu_Type = powerup_type;
//	SpawnEnemy(enemyInfo);
//
//	return true;
//}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::BASIC:
			enemies[i] = new Enemy_Basic(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 100;
			enemies[i]->hp = 1;
			break;
		case ENEMY_TYPES::OSCILATOR:
			enemies[i] = new Enemy_Oscilator(info.x + App->stage05->spawnPos.x, info.pu_Type);
			enemies[i]->scoreValue = 100;
			enemies[i]->hp = 5;
			break;
		case ENEMY_TYPES::POWERDROPPER:
			enemies[i] = new Enemy_PowerDropper(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 100;
			enemies[i]->hp = 1;
			break;
		case ENEMY_TYPES::METALCROW:
			enemies[i] = new Enemy_MetalCraw(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 1000;
			enemies[i]->hp = 50;
			break;
		case  ENEMY_TYPES::REDBATS:
			enemies[i] = new Enemy_RedBats(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 100;
			enemies[i]->hp = 1;
			break;
		case ENEMY_TYPES::ROTATING_TURRET:
			enemies[i] = new Enemy_RotatingTurret(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 200;
			enemies[i]->hp = 50;
			break;
		case ENEMY_TYPES::PINATA:
			enemies[i] = new Enemy_Pinata(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 200;
			enemies[i]->hp = 50;
			break;
		case ENEMY_TYPES::PINATA_SPAWNER:
			enemies[i] = new Enemy_Pinata(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 200;
			enemies[i]->hp = 50;
			break;
		case ENEMY_TYPES::FRONT_TURRET:
			enemies[i] = new Enemy_FrontTurret(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 200;
			enemies[i]->hp = 5;
			break;
		case ENEMY_TYPES::OUTDOOR_TURRET:
			enemies[i] = new Enemy_Outdoor_turret(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 300;
			enemies[i]->hp = 15;
			break;
			case ENEMY_TYPES::OUTDOOR_LASER:
			enemies[i] = new Enemy_Outdoor_Laser(info.x + App->stage05->spawnPos.x, info.y + App->stage05->spawnPos.y, info.pu_Type);
			enemies[i]->scoreValue = 0;
			enemies[i]->hp = 10000;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
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
				//---Delete enemie--------------------------
				enemies[i]->OnCollision(c2);
				delete enemies[i];
				enemies[i] = nullptr;
			}
			//If enemy does not die only change its sprite to white
			else  if  (enemies[i]->isDamaged == false && enemies[i]->flashing_interval == -1) {
				enemies[i]->isDamaged = true;
				enemies[i]->flashing_interval = 0;
			}
		}
	}
}
