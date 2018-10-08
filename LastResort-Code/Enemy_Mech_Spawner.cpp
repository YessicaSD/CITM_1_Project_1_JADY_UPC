#include "Application.h"
#include "ModuleEnemies.h"
#include "Enemy_Mech_Spawner.h"
#include "Particle.h"
#include "ModuleStage05.h"

Enemy_Mech_Spawner::Enemy_Mech_Spawner(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t ) : Enemy(x, y, hp, scoreValue, pu_t)
{
	for (uint i = 0; i < MAX_SPAWNED; ++i)
	{
		spawned[i] = nullptr;
	};

	MechAppear.PushBack({ 0,0,0,0 });
	MechAppear.PushBack({ 0,523,32,34 });
	MechAppear.PushBack({ 32,523,32,34 });
	MechAppear.PushBack({ 32,523,32,34 });
	MechAppear.PushBack({ 64,523,32,34 });
	MechAppear.PushBack({ 96,523,31,34 });
	MechAppear.PushBack({ 127,523,31,34 });
	MechAppear.PushBack({ 110,488,32,34 });
	MechAppear.loop = true;
	MechAppear.speed = 0.1f;
	animation = &MechAppear;

	

	initialPosition.x = x - App->stage05->spawnPos.x;
	initialPosition.y = y - App->stage05->spawnPos.y;

	//It doesn't have a collider because it doesn't need to collide with anything

	
}

void Enemy_Mech_Spawner::Move()
{
	position.x = App->stage05->spawnPos.x + initialPosition.x;
	position.y = App->stage05->spawnPos.y + initialPosition.y;


	currentEnemies = 0;
	for (int i = 0; i < MAX_SPAWNED; ++i) {

		if (spawned[i] != nullptr && spawned[i]->isDead == false )
		{
			currentEnemies += 1;
		}
		else
		{
			spawned[i] = nullptr;
		}
	}

	if (currentEnemies < 3)
	{
		currentState = ANIMATION;
		animation->speed = 0.1f;
	}

	if (currentState == ANIMATION)
	{
		if ((int)animation->GetCurrentFrameNum() == 7)
		{
			for (int i = 0; i < 3; ++i)
			{
				if (spawned[i] == nullptr)
				{
					spawned[i] = App->enemies->InstaSpawn(ENEMY_TYPES::MECH, initialPosition.x, initialPosition.y);
					break;
				}
			}
			animation->current_frame = 0;
			currentState = IDLE;
			animation->speed = 0.0f;
		}
	}


	
};

void Enemy_Mech_Spawner::Draw1(SDL_Texture* sprites)
{
		if (animation != nullptr)
		{
				App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h, &(animation->GetCurrentFrame()));
		
		}

};

	

