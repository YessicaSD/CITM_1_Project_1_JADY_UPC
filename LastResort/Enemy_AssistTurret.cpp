#include "Application.h"
#include "Enemy_AssistTurret.h"
#include "ModuleStage05.h"
#include "ModuleRender.h"

Enemy_Assist_Turret::Enemy_Assist_Turret(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop) :Enemy(x, y, hp, scoreValue, powerupDrop)
{
	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 5; ++i) {
			initAnim.PushBack({ 868 + i*24, 34 + j*24,24,24 });
		}
	}
	initAnim.speed = 0.3f;

	for (int i = 0; i < 4; ++i) {
		turretAnim.PushBack({ 868 + i * 24, 82 ,24,24 });
	} 
	turretAnim.speed = 0.3f;

	for (int i = 0; i < 5; ++i) {
		fireAnim.PushBack({ 868 + i * 24, 106 ,24,24 });
	} 
	fireAnim.speed = 0.2f;

	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	collider = App->collision->AddCollider({ x - 10, y - 10, 20, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}
void Enemy_Assist_Turret::Move()
{
	position = fixedPos + App->stage05->spawnPos;

	switch (state)
	{
	case Enemy_Assist_Turret::INIT:
		break;
	case Enemy_Assist_Turret::NORMAL:

		if (frameCount == 300)
		{
			App->particles->AddParticle(App->particles->missile, { (float)position.x + 5,(float)position.y - 5 }, { 0,0 }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT2, 0, PARTICLE_MISSILE);
			isShooting = true;
			frameCount = 0;
		}

		frameCount += 1;

		break;
	}

	if (collider != nullptr)
		collider->SetPos(position.x - 10, position.y - 10);
}

void Enemy_Assist_Turret::Draw1(SDL_Texture * sprites)
{

	SDL_Rect currentAnim;
	switch (state)
	{
	case Enemy_Assist_Turret::INIT:
		currentAnim = initAnim.GetFrameEx();
		if (initAnim.finished == true) {
			state = NORMAL;
		}
		break;
	case Enemy_Assist_Turret::NORMAL:
		currentAnim = turretAnim.LoopAnimation();
		break;
	}
	if (isShooting == true) {
		App->render->Blit(sprites, position.x - 12, position.y - 12 - 8, &fireAnim.GetFrameEx());
		if (fireAnim.finished == true) {
			fireAnim.Reset();
			isShooting = false;
		}
	}

	App->render->Blit(sprites, position.x - 12, position.y - 12, &currentAnim);
}
