#include "Enemy_Little_Asteroid.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

Enemy_Little_Asteroid::Enemy_Little_Asteroid(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t, fPoint speed) : Enemy(x, y, hp, scoreValue, pu_t, speed)
{
	LittleAsteroid.PushBack({ 0,557,32,28 });
	LittleAsteroid.PushBack({ 32,557,31,26 });
	LittleAsteroid.PushBack({ 63,557,31,26 });
	LittleAsteroid.PushBack({ 94,557,31,28 });
	LittleAsteroid.PushBack({ 125,557,32,26 });
	LittleAsteroid.PushBack({ 0,585,32,29 });
	LittleAsteroid.PushBack({ 32,583,32,30 });
	LittleAsteroid.PushBack({ 64,583,32,31 });
	LittleAsteroid.PushBack({ 97,585,31,28 });
	LittleAsteroid.speed = 0.2;
	animation = &LittleAsteroid;
	collider = App->collision->AddCollider({ x, y, 31, 28}, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
	fposition.x = (float)position.x;
	fposition.y = (float)position.y;
	App->audio->ControlAudio(App->enemies->AsteroirdAppearSfx, PLAY_AUDIO);
}

void Enemy_Little_Asteroid::Move()
{
	fposition += speed;
	position.x = (int)fposition.x;
	position.y = (int)fposition.y;


	if (collider != nullptr)
		collider->SetPos(position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2);
}
void Enemy_Little_Asteroid::Draw(SDL_Texture* sprites)
{
	if (animation != nullptr)
	{
		App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2, &(animation->GetCurrentFrame()));

	}
}
void Enemy_Little_Asteroid::OnCollision(Collider*)
{
	App->particles->AddParticle(App->particles->littleAsteroidDestroy, { (float)position.x, (float)position.y }, { 0 , 0 }, App->particles->particlesTx, COLLIDER_IGNORE_HIT, 0);
}