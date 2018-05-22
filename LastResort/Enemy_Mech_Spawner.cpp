#include "Enemy_Mech_Spawner.h"
#include "Particle.h"
#include "ModuleStage05.h"

Enemy_Mech_Spawner::Enemy_Mech_Spawner(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	MechSpawner.PushBack({ 152,156,24,20 });
	animation = &MechSpawner;
	initialPosition.x = x - App->stage05->spawnPos.x;
	initialPosition.y = y - App->stage05->spawnPos.y;
	collider = App->collision->AddCollider({ x, y + 3, 24, 17 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
	//Particle ------------------------------------------------------------------------



}

void Enemy_Mech_Spawner::Move()
{
	position.x = App->stage05->spawnPos.x + initialPosition.x;
	position.y = App->stage05->spawnPos.y + initialPosition.y;
	
}


