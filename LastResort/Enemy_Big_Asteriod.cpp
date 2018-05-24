#include "Application.h"
#include "Enemy_Big_Asteriod.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
Enemy_Big_Asteroid::Enemy_Big_Asteroid(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) :Enemy(x ,y , hp, scoreValue, pu_t)
{
	BigAsteroid.PushBack({ 152,176,64,62 });
	animation = &BigAsteroid;
	collider = App->collision->AddCollider({ x, y, 64, 62 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}
void Enemy_Big_Asteroid::Move()
{
	position.x -= 3;
}
void Enemy_Big_Asteroid::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h/2);

	if (animation != nullptr)
	{
			App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h/2, &(animation->GetCurrentFrame()));
		
	}
}

void Enemy_Big_Asteroid::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->AsteroidDestroy, { position.x, position.y }, { 0 , 0 }, App->particles->particlesTx, COLLIDER_IGNORE_HIT, 0);
}
