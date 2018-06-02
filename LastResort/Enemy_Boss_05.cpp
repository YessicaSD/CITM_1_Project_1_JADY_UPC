#include "Application.h"
#include "Enemy_Boss_05.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include <stdlib.h>

#define MAX_BOSS_SPEED 1

Enemy_Boss_05::Enemy_Boss_05(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	renderLayer = 0;

	shootFrames = rand() % 120 + 120;

	//Position--------------------------------------

	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y +14;
	speed = { 0.0f, 0.0f };
	aceleration = { 0.0f, 0.05f };

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
	switch (currentDir)
	{
	case Enemy_Boss_05::UP:

		if (float_position.x  < 0) {
			speed.y -= aceleration.y;
		}
		else if (float_position.x >= 0) {
			speed.y += aceleration.y;
		}

		if (speed.y >= 0.0f) {
			currentDir = DOWN;
		}

		break;
	case Enemy_Boss_05::DOWN:

		if (float_position.x  < 0) {
			speed.y += aceleration.y;
		}
		else if (float_position.x >= 0) {
			speed.y -= aceleration.y;
		}
		if (speed.y >= 0.0f) {
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

	float_position.x += speed.x;
	float_position.y += speed.y;

	position = { (int)fixedPos.x + float_position.x, (int)float_position.y + fixedPos.x };

	//Set the collider position
	if (collider != nullptr) {

		collider->SetPos(position.x - 12, position.y - 12);
	}
}

void Enemy_Boss_05::Draw(SDL_Texture* sprites)
{

	//Draw------------------------------------------------------------------

	App->render->Blit(sprites, position.x - 24, position.y - 24, &bossAnim.LoopAnimation());

}