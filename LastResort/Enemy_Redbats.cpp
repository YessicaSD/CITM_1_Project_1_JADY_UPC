#include "Application.h"
#include "Enemy_RedBats.h"
#include "ModuleCollision.h"

Enemy_RedBats::Enemy_RedBats(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	RedBats.PushBack({ 156,0,27,29 });
	RedBats.PushBack({ 190,0,27,18 });
	RedBats.PushBack({ 223,10,26,10 });
	RedBats.PushBack({ 256,5,26,19 });
	RedBats.PushBack({ 156,30,26,29 });
	RedBats.PushBack({ 189,35,26,19 });
	RedBats.PushBack({ 221,39,27,10 });
	RedBats.PushBack({ 256,34,28,21 });
	RedBats.speed = 0.09f;
	animation = &RedBats;
	collider = App->collision->AddCollider({ 0, 0, 27, 25 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;
	
}

void Enemy_RedBats::Move()
{

	if (going_up)
	{
		if (wave > 1.5f)
			going_up = false;
		else
			wave += 0.08f;
	}
	else
	{
		if (wave < -1.5f)
			going_up = true;
		else
			wave -= 0.08f;
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;

}