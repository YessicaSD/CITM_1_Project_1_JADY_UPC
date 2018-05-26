#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleAudio.h"
#include "ModulePowerups.h"

#include "ModuleStage05.h"


Enemy::Enemy(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t)
	: position(x, y), hp(hp), scoreValue(scoreValue), powerUp_drop(pu_t)
{
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
}
Enemy::Enemy(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t,iPoint speed)
	: position(x, y), hp(hp), scoreValue(scoreValue), powerUp_drop(pu_t),speed(speed)
{
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
}
Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{

	if (collider != nullptr)
		collider->SetPos(position.x, position.y );

	if (animation != nullptr)
		App->render->Blit(sprites, position.x , position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	//LOG("Collider %i ", collider->type);
	//Explosion type REMEMBER: Improve it for 1.0-----------------------
	App->particles->AddParticle(App->particles->g_explosion02, { (float)position.x, (float)position.y }, { 0 ,0 }, App->particles->g_explosion02.texture, COLLIDER_IGNORE_HIT, 0, PARTICLE_FOLLOW_BACKGROUND);

	//Sfx REMEMBER: Improve it for 1.0----------------------------------
	if (SDL_GetTicks() % 2)
		App->audio->ControlSFX(App->particles->g_explosion01_1sfx, PLAY_AUDIO);
	else
		App->audio->ControlSFX(App->particles->g_explosion02_1sfx, PLAY_AUDIO);
}