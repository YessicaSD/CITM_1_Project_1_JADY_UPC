#include "Application.h"
#include "Enemy_Missile_turret.h"
#include "ModuleStage05.h"
#include "ModuleRender.h"

Enemy_Missile_turret::Enemy_Missile_turret(int x,int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop):Enemy(x,y, hp, scoreValue,  powerupDrop)
{
	turret.PushBack({128,212,24,19});
	animation = &turret;
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	collider = App->collision->AddCollider({ x, y, 24, 19 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}
void Enemy_Missile_turret::Move()
{
	position = fixedPos + App->stage05->spawnPos;

	if (frameCount == 150 && position.x>0 && position.y>0 )
	{
		App->particles->AddParticle(App->particles->missile, { (float)position.x+5,(float)position.y-5 }, { 0,0 }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT2, 0, PARTICLE_MISSILE);
		frameCount = 0;
	}

	frameCount += 1;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy_Missile_turret::Draw1(SDL_Texture * sprites)
{
	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}
