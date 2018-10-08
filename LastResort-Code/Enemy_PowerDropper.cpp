#include "Application.h"
#include "Enemy_PowerDropper.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"

Enemy_PowerDropper::Enemy_PowerDropper(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
		dropper.PushBack({ 0,218,32,26 });
		dropper.PushBack({ 32,218,30,26 });
		dropper.PushBack({ 32,218,30,26 });
		dropper.PushBack({ 62,218,32,26 });
		dropper.PushBack({ 94,218,32,26 });
		dropper.speed = 0.2f;
	animation = &dropper;

	collider = App->collision->AddCollider({ x, y, 32, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
	original_y = y;
}

void Enemy_PowerDropper::Move()
{
	
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.06f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.06f;
	}

	position.y = int(float(original_y) + (20.0f * sinf(wave)));
	position.x -= 3;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy_PowerDropper::Draw1(SDL_Texture * sprites)
{
	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}
