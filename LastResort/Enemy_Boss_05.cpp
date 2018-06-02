#include "Application.h"
#include "Enemy_Boss_05.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include <stdlib.h>


Enemy_Boss_05::Enemy_Boss_05(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	renderLayer = 0;

	shootFrames = rand() % 120 + 120;

	//Position--------------------------------------

	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	speed = { -1.0f, 0.0f };
	aceleration = { 0.1f, 0.1f };

	//Animations------------------------------------

	for (int i = 0; i < 4; ++i) {
		bossAnim.PushBack({ 525 + i * 48, 202,48,48 });
	}
	bossAnim.speed = 0.3f;

	//Add collider--------------------------------
	collider = App->collision->AddCollider({ x - 20, y - 20, 40, 40 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}


//Movement-------------------------------------------------------------

void Enemy_Boss_05::Move()
{

	if (collider != nullptr)
		collider->SetPos(position.x - 20, position.y - 20);
}

void Enemy_Boss_05::Draw(SDL_Texture* sprites)
{
	SDL_Rect currentAnim;

	//Draw------------------------------------------------------------------

	App->render->Blit(sprites, position.x - 24, position.y - 24, &currentAnim);

}