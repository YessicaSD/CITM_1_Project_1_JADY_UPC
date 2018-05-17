#include "Application.h"
#include "Enemy_RedBats.h"
#include "ModuleCollision.h"

Enemy_RedBats::Enemy_RedBats(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	RedBats.PushBack({ 150,0,27,29 });
	RedBats.PushBack({ 176,0,25,30 });
	RedBats.PushBack({ 202,0,26,29 });
	RedBats.PushBack({ 228,0,26,29 });
	RedBats.PushBack({ 150,30,26,29 });
	RedBats.PushBack({ 176,29,26,29 });
	RedBats.PushBack({ 202,29,26,29 });
	RedBats.PushBack({ 228,29,26,29 });
	RedBats.speed = 0.09f;
	animation = &RedBats;
	collider = App->collision->AddCollider({ x, y, 27, 25 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
	original_y = y;
	
}

void Enemy_RedBats::Move()
{

	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.08f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.08f;
	}

	position.y = int(float(original_y) + (18.0f * sinf(wave)));
	position.x -= 2;

}