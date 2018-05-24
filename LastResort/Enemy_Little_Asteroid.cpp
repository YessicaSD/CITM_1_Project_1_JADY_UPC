#include "Enemy_Little_Asteroid.h"
#include "ModuleRender.h"
#include "Application.h"
Enemy_Little_Asteroid::Enemy_Little_Asteroid(int x, int y, POWERUP_TYPE pu_t,iPoint speed) :Enemy(x, y, pu_t,speed)
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
}

void Enemy_Little_Asteroid::Move()
{
	position += speed;
}
void Enemy_Little_Asteroid::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2);

	if (animation != nullptr)
	{
		App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2, &(animation->GetCurrentFrame()));

	}
}
void Enemy_Little_Asteroid::OnCollision(Collider*)
{

}