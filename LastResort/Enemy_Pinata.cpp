#include "Application.h"
#include "Enemy_Pinata.h"
#include "ModuleCollision.h"

Enemy_Pinata::Enemy_Pinata(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	//Push backs
	//basicenemy.speed = 0.12f;

	//animation = &basicenemy;

	//Add collider
	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_Pinata::Move()
{
	//Move

	//Update collider
}