#include "Application.h"
#include "ModuleEnemies.h"
#include "Enemy_IF_Spawner.h"
#include "Enemy_Pinata.h"
#include "ModuleStage05.h"
#include "ModuleCollision.h"


Enemy_IF_Spawner::Enemy_IF_Spawner(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	renderLayer = 2;

	for (uint i = 0; i < MAX_SPAWNED; ++i) {
		spawned[i] = nullptr;
	}

	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;

	//Rects------------------------------------------------

	insideCore = { 525,170,192,32 }; 
	spawnDoor = { 525,144,128,26 };

	//Add collider----------------------------------------
	collider = App->collision->AddCollider({ x - 96, y+ 32, 192, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);

}

void Enemy_IF_Spawner::Move()
{
	//Update position-------------------------------------------
	position = App->stage05->spawnPos + fixedPos;

	if (collider != nullptr) {
		collider->SetPos(position.x - -96, position.y + 32);
	}
	


	//Enemies Spawning------------------------------------------
	currentEnemies = 0;

	for (int i = 0; i < MAX_SPAWNED; ++i)
	{
		if (spawned[i] != nullptr && spawned[i]->isDead == false)
		{
			currentEnemies += 1;
		}
	}

	if (currentEnemies < 3 && spawnFrames > SPAWN_FRAMES - 60)
	{
		currentState = OPEN;
	}

	if (currentEnemies < MAX_SPAWNED && spawnFrames > SPAWN_FRAMES)
	{
		for (int i = 0; i < MAX_SPAWNED; ++i)
		{
			if (spawned[i] == nullptr)
			{
				spawned[i] = App->enemies->InstaSpawn(INTERGALACTIC_F, position.x, position.y);
				spawnFrames = 0;
				break;
			}
		}
	}

	for (int i = 0; i < MAX_SPAWNED; ++i)
	{
		if (spawned[i] != nullptr && spawned[i]->isDead == true)
		{
			spawned[i] = nullptr;
		}
	}

	if (currentEnemies != 3) {
		spawnFrames += 1;
	}
}

void Enemy_IF_Spawner::Draw(SDL_Texture* sprites) {

	App->render->Blit(sprites, position.x -64, position.y - 15, &spawnDoor);
	App->render->Blit(sprites, position.x - 96, position.y +32, &insideCore);

}                   
