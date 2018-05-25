#include "Enemy_Indoor_turret.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
Enemy_indoorTurret::Enemy_indoorTurret(int x, int  y, float hp, int scoreValue, POWERUP_TYPE powerupDrop, iPoint speed) : Enemy( x, y, hp, scoreValue,powerupDrop,speed)
{
	indoorTurretAnim.PushBack({ 128,196,24,16 });
	animation = &indoorTurretAnim;
	collider = App->collision->AddCollider({ x, y, 24, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
	/*App->render->BlitEx();*/
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
}
void Enemy_indoorTurret::Move()
{
	position.x = fixedPos.x + App->stage05->spawnPos.x;
	position.y = fixedPos.y + App->stage05->spawnPos.y;
}
void Enemy_indoorTurret::Draw(SDL_Texture* sprites)
{
	//Up turrot 
	if (speed.x == 0)
	{
		if (collider != nullptr)
			collider->SetPos(position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2);

		if (animation != nullptr)
			App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2, &(animation->GetCurrentFrame()));
	}
	// Down 
	if (speed.x==1)
	{

		if (collider != nullptr)
			collider->SetPos(position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2);

		if (animation != nullptr)
			App->render->BlitEx(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2, &(animation->GetCurrentFrame()),SDL_FLIP_VERTICAL);
	}
}
