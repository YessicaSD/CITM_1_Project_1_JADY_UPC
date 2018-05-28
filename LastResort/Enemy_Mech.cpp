#include "Enemy_Mech.h"
#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleStage05.h"
#include <stdlib.h>


Enemy_Mech::Enemy_Mech(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t):Enemy(x, y, hp, scoreValue, pu_t)
{

	Mech.PushBack({0,488,28,35});
	Mech.PushBack({ 28,488,28,35 });
	Mech.PushBack({ 56,488,28,35 });
	Mech.PushBack({ 56,488,28,35 });
	Mech.PushBack({ 84,488,26,35 });
	Mech.PushBack({ 110,488,32,35 });
	Mech.speed = 0.2f;
	animation = &Mech;
	collider = App->collision->AddCollider({ x, y, 28, 35 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);

	finalPosition.x = x - App->stage05->spawnPos.x;
	finalPosition.y = y - App->stage05->spawnPos.y;
	resp = rand() % 2;

	if (resp == 0)
	{
		going_left = false;
		going_right = true;
		limit = finalPosition.x+92;
		limit_2 = finalPosition.x;
	}
	else
	{
		going_right = false;
		going_left = true;
		limit = finalPosition.x;
		limit_2 = finalPosition.x-92;
	}
		
	
};
void Enemy_Mech::Move()
{

	if (going_right)
	{
		if (finalPosition.x < limit)
		{
			finalPosition.x += 0.5f;
			if ((int)animation->GetCurrentFrameNum() == 3 && finalPosition.x < limit - 10)
				animation->current_frame = 0;
		}


		else
		{
			going_right = false;
			going_left = true;
		}
	}
	else
	{
		if (finalPosition.x > limit_2)
		{
			finalPosition.x -= 0.5f;
			if ((int)animation->GetCurrentFrameNum() == 3 && finalPosition.x > limit_2 + 10)
				animation->current_frame = 0;
		}
		else
		{
			going_right = true;
			going_left = false;
		}
	}
	position.x = App->stage05->spawnPos.x + finalPosition.x;
	position.y = App->stage05->spawnPos.y + finalPosition.y;

	if (collider != nullptr)
		collider->SetPos(position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h);
};
void Enemy_Mech::Draw(SDL_Texture* sprites)
{

	

	if (animation != nullptr)
	{
		if(going_right)
		App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h, &(animation->GetCurrentFrame()));
		if (going_left)
			App->render->BlitEx(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h, &(animation->GetCurrentFrame()));
	}
		
	
}