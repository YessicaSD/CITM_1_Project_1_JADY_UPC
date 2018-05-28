#include "Enemy_Indoor_turret.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include "Player1.h"
#include "Player2.h"
Enemy_indoorTurret::Enemy_indoorTurret(int x, int  y, float hp, int scoreValue, POWERUP_TYPE powerupDrop, iPoint speed) : Enemy( x, y, hp, scoreValue,powerupDrop,speed)
{
	indoorTurretAnim.PushBack({ 128,196,24,16 });
	animation = &indoorTurretAnim;
	collider = App->collision->AddCollider({ x, y, 24, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
	/*App->render->BlitEx();*/
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	frameCounter = 0;
}
void Enemy_indoorTurret::Move()
{
	//Turret position-------------------------------------------
	position.x = fixedPos.x + App->stage05->spawnPos.x;
	position.y = fixedPos.y + App->stage05->spawnPos.y;

	//Shoot---------------------------------------------------------------------------------------------------
	if (frameCounter == 130)
	{

		//Target player -------------------------------------------------------------------------------------------------
		if (App->player1->isActive==true && App->player2->isActive==false)
			targetPlayerPos = { App->player1->position.x,App->player1->position.y };

		else if (App->player1->isActive == false && App->player2->isActive == true)
			targetPlayerPos = {App->player2->position.x,App->player2->position.y };
	
		else
		{
			if (position.DistanceTo(App->player1->position) < position.DistanceTo(App->player2->position))
			 targetPlayerPos = { App->player1->position.x,App->player1->position.y };

			else
				targetPlayerPos = { App->player2->position.x,App->player2->position.y };
			
		}
		
		ParticleSpeed.UnitVector({ (float)targetPlayerPos.x,(float)targetPlayerPos.y }, { (float)position.x,(float)position.y});
		App->particles->AddParticle(App->particles->orangeBall, { (float)position.x,(float)position.y }, {ParticleSpeed.x,ParticleSpeed.y}, App->particles->particlesTx, COLLIDER_ENEMY_SHOT, 0, PARTICLE_FOLLOW_BACKGROUND);


		frameCounter = 0;
	}
	frameCounter += 1;

	//Set collider position
	switch(speed.x)
	{
	case 0:
		if (collider != nullptr)
			collider->SetPos(position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h);
		break;
	case 1:
		if (collider != nullptr)
			collider->SetPos(position.x - animation->GetFrame().w / 2, position.y);
		break;
	case 2:
		if (collider != nullptr)
		{
			collider->SetPos(position.x, position.y - animation->GetFrame().w / 2);
			collider->SetMeasurements(animation->GetFrame().h, animation->GetFrame().w);
		}
		break;
	case 3:
		if (collider != nullptr)
		{
			collider->SetPos(position.x - animation->GetFrame().h, position.y - animation->GetFrame().w / 2);
			collider->SetMeasurements(animation->GetFrame().h, animation->GetFrame().w);
		}
		break;
	}
}

void Enemy_indoorTurret::Draw(SDL_Texture* sprites)
{
	//Draw
	switch (speed.x)
	{
	case 0:
		if (animation != nullptr)
			App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h, &(animation->GetCurrentFrame()));
		break;
	case 1:
		if (animation != nullptr)
			App->render->BlitEx(sprites, position.x - animation->GetFrame().w / 2, position.y, &(animation->GetCurrentFrame()), SDL_FLIP_VERTICAL);
		break;
	case 2:
		if (animation != nullptr)
			App->render->BlitEx(sprites, position.x - 4, position.y - animation->GetFrame().h / 2, &(animation->GetCurrentFrame()), SDL_FLIP_NONE, 90);
		break;
	case 3:
		if (animation != nullptr)
			App->render->BlitEx(sprites, position.x - animation->GetFrame().w + 4, position.y - animation->GetFrame().h / 2, &(animation->GetCurrentFrame()), SDL_FLIP_NONE, -90);
		break;
	}
}
