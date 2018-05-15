#include "Application.h"
#include "Enemy_Pinata.h"
#include "Enemy_Pinata_Spawner.h"
#include "ModuleCollision.h"

Enemy_Pinata_Spawner::Enemy_Pinata_Spawner(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	//Add collider--------------------------
	collider = App->collision->AddCollider({ x, y, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_Pinata_Spawner::Move()
{

}