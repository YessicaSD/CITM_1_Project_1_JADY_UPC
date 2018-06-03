#include "Application.h"
#include "Particle_Missile_2.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "Rotation.h"

#define MAX_MISSILE_SPEED 1.0f

Particle_Missile_2::Particle_Missile_2(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) :Particle(p, position, speed, delay, colType, tex)
{
	this->speed = speed;
	aceleration = { 0.1f,0.1f };
	collider->SetMeasurements(8, 8);

}

void Particle_Missile_2::Move()
{

	fPoint vectorIncrease;
	fPoint PlayerPos;

	CheckTarget();

	switch (missileState)
	{
	case Particle_Missile_2::INIT:
		position += speed;
		if (frameCount == 20)
			missileState = FOLLOW;
		frameCount += 1;

		break;

	case Particle_Missile_2::FOLLOW:
		// Update player position---------------------------------------
	

		PlayerPos.x = (float)currentTarget->position.x + currentTarget->playerCenter.x;
		PlayerPos.y = (float)currentTarget->position.y + currentTarget->playerCenter.y;


		vectorIncrease.UnitVector(PlayerPos, position);

		speed.x += vectorIncrease.x * aceleration.x;

		speed.y += vectorIncrease.y * aceleration.y;


		if (speed.x > MAX_MISSILE_SPEED) {
			speed.x = MAX_MISSILE_SPEED;
		}
		else if (speed.x < -MAX_MISSILE_SPEED) {
			speed.x = -MAX_MISSILE_SPEED;
		}

		if (speed.y > MAX_MISSILE_SPEED) {
			speed.y = MAX_MISSILE_SPEED;
		}
		else if (speed.y < -MAX_MISSILE_SPEED) {
			speed.y = -MAX_MISSILE_SPEED;
		}

		//Update position----------------------------------------------

		position.x += speed.x;
		position.y += speed.y;
		break;
	}
	

	//Set the collider position
	if (collider != nullptr) {

		collider->SetPos(position.x - 8, position.y - 8);
	}
}

void  Particle_Missile_2::CheckTarget() {

	float DistancePlayer1 = position.DistanceTo({ (float)App->player1->position.x,(float)App->player1->position.y });
	float DistancePlayer2 = position.DistanceTo({ (float)App->player2->position.x,(float)App->player2->position.y });

	if (DistancePlayer1 <= DistancePlayer2) {
		if (App->player1->isActive)
			currentTarget = App->player1;
		else if (App->player2->isActive)
			currentTarget = App->player2;
	}
	else if (DistancePlayer2  < DistancePlayer1)
	{
		if (App->player2->isActive)
			currentTarget = App->player2;
		else if (App->player1->isActive)
			currentTarget = App->player1;
	}
	else
		currentTarget = App->player1;
}


void Particle_Missile_2::Draw()
{
	if (missileState == FOLLOW)
		//Draw the particle
		App->render->BlitEx(this->texture, (int)position.x -8 , (int)position.y - 8, &anim.LoopAnimation(), SDL_FLIP_HORIZONTAL, (AbsoluteRotation({ (int)position.x, (int)position.y }, { (int)currentTarget->position.x + currentTarget->playerCenter.x, currentTarget->position.y + currentTarget->playerCenter.y })) * 180 / PI);
	else
	{
		App->render->BlitEx(this->texture, (int)position.x - 8, (int)position.y - 8 , &anim.LoopAnimation(), SDL_FLIP_HORIZONTAL, -90);
	}
}