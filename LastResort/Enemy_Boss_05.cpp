#include "Application.h"
#include "ModuleAudio.h"
#include "Enemy_Boss_05.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include "ModuleUI.h"
#include <stdlib.h>

#define MAX_BOSS_SPEED 0.7f
#define BOOS_SHOOT_FRAMES 220
#define DESTROY_FRAMES 30
#define ARMOR_EXPLOSIOM_FRAMES 15

Enemy_Boss_05::Enemy_Boss_05(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{

	//Position--------------------------------------

	speed = { 0.0f, 0.0f };
	aceleration = { 0.0f, 0.01f };
	float_position = { 0.0f, 13.0f };
	//Animations------------------------------------
	metalArmorTexPos = { 717 ,0 };
	metalArmorPos = { -81, -86 };

	for (int i = 0; i < 4; ++i) {
		bossAnim.PushBack({ 525 + i * 48, 202,48,48 });
	}
	bossAnim.speed = 0.2f;

	//Add collider--------------------------------
	collider = App->collision->AddCollider({ x - 20, y - 20, 40, 40 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}


void Enemy_Boss_05::OnCollision(Collider* collider) {

	App->ui->stageclear = true;
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

	//Shoot particle-----------------------------------------------
	if (shootFrames > BOOS_SHOOT_FRAMES) {
		shootFrames = 0;
		App->audio->ControlAudio( App->particles->bossShot_sfx, PLAY_AUDIO);
		App->particles->AddParticle(App->particles->bossShot, { (float)position.x- 35 ,  (float)position.y}, { 0,0 }, App->particles->particlesTx, COLLIDER_IGNORE_HIT, 0.0f ,PARTICLE_BOSS);
	}



	if (App->stage05->cameraMovement.currentMov == 24) {
	
		if (initframes > 180) {

			if (destroyFrames > DESTROY_FRAMES && destroyedParts < 6) {
				++destroyedParts;
				destroyFrames = 0;
			}
			else {
				++destroyFrames;
			}

			if (destroyFrames == ARMOR_EXPLOSIOM_FRAMES) {
				AddExplosions();
			}
			
			++shootFrames;
		}
		else {
			++initframes;
		}
	}


	//Set the collider position
	if (collider != nullptr) {

		collider->SetPos(position.x - 24, position.y - 24);
	}
}

void Enemy_Boss_05::AddExplosions() {

	fPoint pos;

	pos.x = metalArmorPos.x + (int)fixedPos.x + App->stage05->spawnPos.x + armorWeight;
	pos.y = metalArmorPos.y + (int)fixedPos.y + App->stage05->spawnPos.y;

	switch (destroyedParts)
	{
	case 0:
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y +77}, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 0.0f, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 93 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 0.0f, PARTICLE_FOLLOW_WORLD);
		break;
	case 1:
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 0, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 +13 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 300, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 4 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 0, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 5 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 100, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 6 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 400, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13*2 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 50, PARTICLE_FOLLOW_WORLD); 
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13*3 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 100, PARTICLE_FOLLOW_WORLD);
		break;
	case 2:
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 250, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 350, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 4 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 500, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 5 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 50, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 6 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 400, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 2 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 150, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 3 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 50, PARTICLE_FOLLOW_WORLD);

		break;
	case 3:
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 600, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 120, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 4 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 300, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 5 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 50, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 6 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 400, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 2 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 200, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 37 + 13 * 3 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 300, PARTICLE_FOLLOW_WORLD);
		break;
	case 4:
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 24 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 300, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 24 + 13 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 120, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 24 + 13 * 4 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 300, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 24 + 13 * 5 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 50, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 24 + 13 * 6 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 100, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 24 + 13 * 2 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 350, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 24 + 13 * 3 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 450, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 24 + 13 * 8 }, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 150, PARTICLE_FOLLOW_WORLD);
		App->particles->AddParticle(App->particles->g_explosion02, { pos.x + 16.0f,  pos.y + 24 + 13 * 7}, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 300, PARTICLE_FOLLOW_WORLD);
		break;
	}


}


void Enemy_Boss_05::Draw0(SDL_Texture* sprites)
{

	//Draw------------------------------------------------------------------

	App->render->Blit(sprites, position.x - 24, position.y - 24, &bossAnim.LoopAnimation());

}

void Enemy_Boss_05::Draw1(SDL_Texture* sprites)
{
	armorWeight = destroyedParts * 32;

	SDL_Rect metalArmor = { metalArmorTexPos.x + armorWeight ,metalArmorTexPos.y,151 - armorWeight,156 };
	//Draw------------------------------------------------------------------

	App->render->Blit(sprites, metalArmorPos.x + (int)fixedPos.x + App->stage05->spawnPos.x + armorWeight, metalArmorPos.y + (int)fixedPos.y + App->stage05->spawnPos.y, &metalArmor);

}