#include "Application.h"
#include "Enemy_Oscilator.h"
#include "ModuleCollision.h"

Enemy_Oscilator::Enemy_Oscilator(int x, POWERUP_TYPE pu_t) : Enemy(x, original_y, pu_t)
{
	Oscilator.PushBack({ 0,0,50,48 });
	Oscilator.PushBack({ 50,0,50,48 });
	Oscilator.PushBack({ 0,49,50,49 });
	Oscilator.PushBack({ 50,49,50,49 });
	Oscilator.PushBack({ 100,49,50,49 });
	Oscilator.PushBack({ 0,98,50,50 });
	Oscilator.PushBack({ 51,98,49,50 });
	Oscilator.PushBack({ 100,98,49,50 });
	Oscilator.PushBack({ 0,148,49,52 });
	Oscilator.PushBack({ 52,148,50,51 });
	Oscilator.PushBack({ 102,148,50,51 });
	Oscilator.speed = 0.02F;
	animation = &Oscilator;
	collider = App->collision->AddCollider({ 0, 0, 50, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


}

void Enemy_Oscilator::Move()
{
	
	if (going_up)
	{
	if (wave > 200.0f)
	going_up = false;
	else
	wave += 0.05f;
	}
	else
	{
	if (wave < -200.0f)
	going_up = true;
	else
	wave -= 0.05f;
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;
	
}