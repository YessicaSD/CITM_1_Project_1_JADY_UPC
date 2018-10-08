#include "Application.h"
#include "Enemy_Oscilator.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"

Enemy_Oscilator::Enemy_Oscilator(int x, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, original_y, hp, scoreValue, pu_t)
{

	//up
	Oscilator.PushBack({ 51,98,49,50 }); //8
	//Oscilator.PushBack({ 50,49,50,49 }); //5
	Oscilator.PushBack({ 100,49,50,49 }); //6
	Oscilator.PushBack({ 50,0,50,48 }); //2
	Oscilator.PushBack({ 0,0,50,48 }); //1
	Oscilator.PushBack({ 100,0,50,49 }); //3
	Oscilator.PushBack({ 0,49,50,49 });  //4
	Oscilator.PushBack({ 0,98,50,50 }); //7 //es largo
	Oscilator.PushBack({ 0,98,50,50 }); //7 //es largo
	Oscilator.PushBack({ 52,148,50,51 }); //11
	Oscilator.PushBack({ 0,98,50,50 }); //7 //es largo

	//down
	Oscilator.PushBack({ 0,49,50,49 });  //4
	Oscilator.PushBack({ 100,0,50,49 }); //3
	Oscilator.PushBack({ 0,0,50,48 }); //1
	Oscilator.PushBack({ 50,0,50,48 }); //2
	Oscilator.PushBack({ 100,49,50,49 }); //6
	Oscilator.PushBack({ 50,49,50,49 }); //5
	Oscilator.PushBack({ 51,98,49,50 }); //8
	Oscilator.PushBack({ 100,98,49,50 });//9 es largo
	Oscilator.PushBack({ 100,98,49,50 });//9 es largo
	Oscilator.PushBack({ 51,98,49,50 }); //8
	Oscilator.speed = 0.2f;
	animation = &Oscilator;
	collider = App->collision->AddCollider({ x, original_y, 50, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);


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
	
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy_Oscilator::Draw1(SDL_Texture * sprites)
{
	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}
