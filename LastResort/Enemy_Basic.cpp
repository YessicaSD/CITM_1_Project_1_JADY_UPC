#include "Application.h"
#include "Enemy_Basic.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"

Enemy_Basic::Enemy_Basic(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	for (int i=0;i<=96;i+=32)
	{
		basicenemy.PushBack({ i,200,32,16 });
	}
	basicenemy.speed = 0.12f;

	animation = &basicenemy;

	collider = App->collision->AddCollider({ x, y, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
	fixedY = y - App->stage05->spawnPos.y;//We get the y position
}

void Enemy_Basic::Move()
{

	position.x -= 1;
	position.y = fixedY + App->stage05->spawnPos.y;//We fix the y position to be the same as the background
}

