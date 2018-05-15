#include "Application.h"
#include "Enemy_Basic.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"

Enemy_Basic::Enemy_Basic(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	for (int i=0;i<=96;i+=32)
	{
		basicenemy.PushBack({ i,200,32,16 });
	}
	basicenemy.speed = 0.12f;

	animation = &basicenemy;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	initialY = y - App->stage05->shipPos.y;//We get the y position (considering we are getting it from ship position)
}

void Enemy_Basic::Move()
{

	position.x -= 1;
	//To fix the position in y to be the same as the spaceship
	position.y = initialY + App->stage05->shipPos.y;
}

