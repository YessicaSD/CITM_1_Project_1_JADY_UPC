#include "Application.h"
#include "Enemy_Oscilator.h"
#include "ModuleCollision.h"

Enemy_Oscilator::Enemy_Oscilator(int x, POWERUP_TYPE pu_t) : Enemy(x, original_y, pu_t)
{


	//down
	Oscilator.PushBack({ 50,49,50,49 }); //5
	Oscilator.PushBack({ 51,98,49,50 }); //8
	Oscilator.PushBack({ 100,98,49,50 });//9 es largo
	Oscilator.PushBack({ 102,148,50,51 }); //12
	Oscilator.PushBack({ 51,98,49,50 }); //8
	

	//up
	Oscilator.PushBack({ 50,49,50,49 }); //5
	Oscilator.PushBack({ 100,49,50,49 }); //6
	Oscilator.PushBack({ 50,0,50,48 }); //2
	Oscilator.PushBack({ 0,0,50,48 }); //1
	Oscilator.PushBack({ 0,98,50,50 }); //7 //es largo
	Oscilator.PushBack({ 100,0,50,49 }); //3
	Oscilator.PushBack({ 0,49,50,49 });  //4
	Oscilator.PushBack({ 0,0,50,48 }); //1
	Oscilator.PushBack({ 50,0,50,48 }); //2


	Oscilator.speed = 0.2f;
	animation = &Oscilator;
	collider = App->collision->AddCollider({ x, original_y, 50, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


}

void Enemy_Oscilator::Move()
{
	
	if (going_up)
	{
		if (wave > 1.0f)
		going_up = false;
		else
		wave += 0.05f;
	}
	else
	{
	if (wave < -1.0f)
	going_up = true;
	else
	wave -= 0.05f;
	}

	position.y = int((float(original_y) + (60.0f * sinf(wave))));
	position.x -= 2;
	
}