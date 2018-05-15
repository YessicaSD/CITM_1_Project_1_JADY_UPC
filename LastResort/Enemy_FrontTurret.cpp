#include "Application.h"
#include "Enemy_FrontTurret.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"

Enemy_FrontTurret::Enemy_FrontTurret(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	//Animation-----------------------------------------------
	frontTurretAnim.PushBack({120, 458, 32, 24});
	frontTurretAnim.speed = 1;
	frontTurretAnim.loop = true;
	animation = &frontTurretAnim;
	//Collider------------------------------------------------
	collider = App->collision->AddCollider({ x, y, 32, 24}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//Positions-----------------------------------------------
	initialX = x - (int)App->stage05->spawnPos.x;//We get the x position
	initialY = y - (int)App->stage05->spawnPos.y;//We get the y position
}

void Enemy_FrontTurret::Move()
{
	//We move the turret with the background
	position.x = (int)App->stage05->spawnPos.x + initialX;
	position.y = (int)App->stage05->spawnPos.y + initialY;
}

