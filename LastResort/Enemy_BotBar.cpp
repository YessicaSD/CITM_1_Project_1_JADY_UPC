#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "Enemy_BotBar.h"
#include "ModuleStage05.h"

Enemy_BotBar::Enemy_BotBar(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Animation-------------------------------------
	barAnim = { 265, 460, 32, 128 };
	//Render layer----------------------------------
	renderLayer = 0;
	//Collider--------------------------------------
	collider = App->collision->AddCollider({ x - barAnim.w / 2, y - barAnim.h / 2, barAnim.w, barAnim.h }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}

void Enemy_BotBar::Move()
{
	//Move
	position = fixedPos + App->stage05->spawnPos;
	//Set the collider position
	collider->SetPos(position.x - barAnim.w / 2, position.y - barAnim.h / 2);
}

void Enemy_BotBar::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x - barAnim.w / 2, position.y - barAnim.h / 2, &barAnim);
}