#include "Enemy_Middle_Asteroid.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"

Enemy_Middle_Asteroid::Enemy_Middle_Asteroid(int x, int y, POWERUP_TYPE pu_t):Enemy(x,y,pu_t) {
	Middle_Asteroid.PushBack({ 250,334,40,39 });
	animation = &Middle_Asteroid;
	collider = App->collision->AddCollider({ x, y, 40, 39 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}

void Enemy_Middle_Asteroid::Move()
{
	//position.x -= 2;
	position.x += speed.x;
	position.y += speed.y;
}

void Enemy_Middle_Asteroid::Draw(SDL_Texture* sprites) {
	if (collider != nullptr)
		collider->SetPos(position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2);

	if (animation != nullptr)
	{
		App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2, &(animation->GetCurrentFrame()));

	}
}

void Enemy_Middle_Asteroid::OnCollision(Collider*) 
{
	App->particles->AddParticle(App->particles->MiddleAsteroidDestroy, { position.x, position.y }, { 0 ,0 }, App->particles->particlesTx, COLLIDER_IGNORE_HIT, 0);
}