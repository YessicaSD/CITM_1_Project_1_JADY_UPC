#include "Application.h"
#include "Enemy_Boss_05.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include <stdlib.h>

#define MAX_BOSS_SPEED 0.7f

Enemy_Boss_05::Enemy_Boss_05(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	renderLayer = 0;

	shootFrames = rand() % 120 + 120;

	//Position--------------------------------------

	speed = { 0.0f, 0.0f };
	aceleration = { 0.0f, 0.01f };
	float_position = { 0.0f, 13.0f };
	//Animations------------------------------------

	for (int i = 0; i < 4; ++i) {
		bossAnim.PushBack({ 525 + i * 48, 202,48,48 });
	}
	bossAnim.speed = 0.2f;

	//Add collider--------------------------------
	collider = App->collision->AddCollider({ x - 20, y - 20, 40, 40 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}


//Movement-------------------------------------------------------------

void Enemy_Boss_05::Move()
{

	switch (currentDir)
	{
	case Enemy_Boss_05::UP:

		if (float_position.y  < 0) {
			speed.y += aceleration.y;
		}
		else if (float_position.y >= 0) {
			speed.y -= aceleration.y;
		}

		if (float_position.y < -14.0f) {
			currentDir = DOWN;
		}

		break;
	case Enemy_Boss_05::DOWN:

		if (float_position.y  < 0) {
			speed.y -= aceleration.y;
		}
		else if (float_position.y >= 0) {
			speed.y += aceleration.y;
		}

		if (float_position.y > 14.0f) {
			currentDir = UP;
		}
		break;
	}


	if (speed.y > MAX_BOSS_SPEED) {
		speed.y = MAX_BOSS_SPEED;
	}
	else if (speed.y < -MAX_BOSS_SPEED) {
		speed.y = -MAX_BOSS_SPEED;
	}

	//Update position----------------------------------------------

	float_position.y += speed.y;

	position = { (int)( fixedPos.x + float_position.x + App->stage05->spawnPos.x), (int)(fixedPos.y + float_position.y + App->stage05->spawnPos.y)};

	//Set the collider position
	if (collider != nullptr) {

		collider->SetPos(position.x - 24, position.y - 24);
	}
}

void Enemy_Boss_05::Draw(SDL_Texture* sprites)
{

	//Draw------------------------------------------------------------------

	App->render->Blit(sprites, position.x - 24, position.y - 24, &bossAnim.LoopAnimation());

}