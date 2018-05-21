#include "Enemy_Mech.h"
#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleRender.h"

Enemy_Mech::Enemy_Mech(int x, int y, POWERUP_TYPE pu_t):Enemy(x,y,pu_t)
{
	Mech.PushBack({0,488,28,35});
	Mech.PushBack({ 28,488,28,35 });
	Mech.PushBack({ 56,488,28,35 });
	Mech.PushBack({ 84,488,26,35 });
	Mech.PushBack({ 110,488,32,35 });
	Mech.speed = 0.2f;
	animation = &Mech;
	collider = App->collision->AddCollider({ x, y + 3, 24, 17 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
};
void Enemy_Mech::Move()
{

};
void Enemy_Mech::Draw(SDL_Texture* sprites)
{

	if (collider != nullptr)
		collider->SetPos(position.x-animation->GetFrame().w/2, position.y-animation->GetFrame().h);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h, &(animation->GetCurrentFrame()));
}