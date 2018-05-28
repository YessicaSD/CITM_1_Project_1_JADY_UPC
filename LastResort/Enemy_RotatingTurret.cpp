#include "Application.h"
#include "Enemy_RotatingTurret.h"
#include "ModuleCollision.h"
#include <math.h>
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "Rotation.h"
#include "ModuleAudio.h"

Enemy_RotatingTurret::Enemy_RotatingTurret(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Animation
	rotatingTurretAnim.PushBack({ 332,  0, 26, 27 });// 0 = E
	rotatingTurretAnim.PushBack({ 412, 27, 26, 27 });// 1 = ESE
	rotatingTurretAnim.PushBack({ 358,  0, 26, 27 });// 2 = SE
	rotatingTurretAnim.PushBack({ 384,  0, 26, 27 });// 3 = SSE
	rotatingTurretAnim.PushBack({ 410,  0, 26, 27 });// 4 = S
	rotatingTurretAnim.PushBack({ 359, 27, 26, 27 });// 5 = SSW
	rotatingTurretAnim.PushBack({ 436,  0, 26, 27 });// 6 = SW
	rotatingTurretAnim.PushBack({ 255, 27, 26, 27 });// 7 = WSW
	rotatingTurretAnim.PushBack({ 281, 27, 26, 27 });// 8 = W
	rotatingTurretAnim.PushBack({ 385, 27, 26, 27 });// 9 = WNW
	rotatingTurretAnim.PushBack({ 307, 27, 26, 27 });//10 = NW
	rotatingTurretAnim.PushBack({ 333, 27, 26, 27 });//11 = NNW
	rotatingTurretAnim.PushBack({ 254,  0, 26, 27 });//12 = N
	rotatingTurretAnim.PushBack({ 438, 27, 26, 27 });//13 = NNE
	rotatingTurretAnim.PushBack({ 280,  0, 26, 27 });//14 = NE
	rotatingTurretAnim.PushBack({ 305,  0, 26, 27 });//15 = ENE
	animation = &rotatingTurretAnim;
	//Position
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	//Collider
	collider = App->collision->AddCollider({ x, y, 26, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
}

void Enemy_RotatingTurret::Move()
{
	//Logic--------------------------------------------------------------------
	//- Lock position
	position = App->stage05->spawnPos + fixedPos;

	//- Select the player we need to aim to
	if(App->player1->isActive == true && App->player2->isActive == true)
	{
		//-- Check which one is at less distance
		if (sqrt(pow(position.x - App->player1->position.x, 2) + pow(position.y - App->player1->position.y, 2)) <=
			sqrt(pow(position.x - App->player2->position.x, 2) + pow(position.y - App->player2->position.y, 2)))
		{
			targetPlayerPos = App->player2->position;
		}
		else
		{
			targetPlayerPos = App->player1->position;
		}
	}

	else if (App->player1->isActive == true && App->player2->isActive == false)
	{
		targetPlayerPos = App->player1->position;
	}

	else if (App->player1->isActive == false && App->player2->isActive == true)
	{
		targetPlayerPos = App->player2->position;
	}

	//- Calculate rotation
	rotation = AbsoluteRotation(position, targetPlayerPos);

	//- Shoot
	if(frameCounter >= 122)
	{
		ShootBall({ (float)position.x, (float)position.y }, { cosf(rotation), sinf(rotation)});
		ShootBall({ (float)position.x, (float)position.y }, { cosf(rotation + shootSeparation), sinf(rotation + shootSeparation) });
		ShootBall({ (float)position.x, (float)position.y }, { cosf(rotation - shootSeparation), sinf(rotation - shootSeparation) });
		frameCounter = 0;
	}
	else
	{
		frameCounter++;
	}

	pushBackNumber = GetNearestAngle(rotation);

	//Update collider
	collider->SetPos(position.x + spriteXOffset[pushBackNumber], position.y + spriteYOffset[pushBackNumber]);
}

void Enemy_RotatingTurret::Draw(SDL_Texture* sprites)
{
	//Blit
	App->render->Blit(sprites, position.x + spriteXOffset[pushBackNumber], position.y + spriteYOffset[pushBackNumber], &rotatingTurretAnim.ReturnFrame(pushBackNumber));
}

void Enemy_RotatingTurret::ShootBall(fPoint position, fPoint speed)
{
	//Shoot
	App->particles->AddParticle(
		App->particles->orangeBall,
		{ position },
		{ speed },
		App->particles->particlesTx,
		COLLIDER_TYPE::COLLIDER_ENEMY_SHOT,
		0,
		PARTICLE_TYPE::PARTICLE_FOLLOW_BACKGROUND);
}

void Enemy_RotatingTurret::OnCollision(Collider* collider2)
{
	//Make the ship part fall if it is killed
	App->stage05->rotatingTurretsKilled++;

	//Explosion type REMEMBER: Improve it for 1.0-----------------------
	App->particles->AddParticle(App->particles->g_explosion02, { (float)position.x, (float)position.y }, { 0, 0 }, App->particles->g_explosion02.texture, COLLIDER_IGNORE_HIT, 0);

	//Sfx REMEMBER: Improve it for 1.0----------------------------------
	if (SDL_GetTicks() % 2)
	{
		App->audio->ControlAudio(App->particles->g_explosion01_1sfx, PLAY_AUDIO);
	}
	else
	{
		App->audio->ControlAudio(App->particles->g_explosion02_1sfx, PLAY_AUDIO);
	}
}