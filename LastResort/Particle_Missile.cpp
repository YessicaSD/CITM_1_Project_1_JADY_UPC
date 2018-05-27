#include "Application.h"
#include "Particle_Missile.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
Particle_Missile::Particle_Missile(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) :Particle(p, position, speed, delay, colType, tex)
{
	
	fixedPos.x = position.x -(float)App->stage05->spawnPos.x ;
	fixedPos.y = position.y -(float)App->stage05->spawnPos.y ;
	
}

void Particle_Missile::Move() 
{

	
	if (missileState == UP)
	{
		speed = { 0,-1 };
		fixedPos += speed;
		if (frameCount == 40)
			missileState = FOLLOW;
		frameCount += 1;
	}
	if (missileState == FOLLOW)
	{
		if (App->player1->isActive == true && App->player2->isActive == false)
			targetPlayerPos = { (float)App->player1->position.x,(float)App->player1->position.y };

		else if (App->player1->isActive == false && App->player2->isActive == true)
			targetPlayerPos = { (float)App->player2->position.x,(float)App->player2->position.y };

		else
		{

			if (position.DistanceTo({ (float)App->player1->position.x,(float)App->player1->position.y }) < position.DistanceTo({ (float)App->player2->position.x, (float)App->player2->position.y }))
				targetPlayerPos = { (float)App->player1->position.x,(float)App->player1->position.y };

			else
				targetPlayerPos = { (float)App->player2->position.x,(float)App->player2->position.y };

		}
		speed.UnitVector(targetPlayerPos, position);
		fixedPos += speed;

	}

	if (speed.y <= -0.9f && anim.GetCurrentFrameNum() > 3 || anim.GetCurrentFrameNum() < 2)
	{
		anim.current_frame = 2;
	}

	position.x = (float)App->stage05->spawnPos.x + fixedPos.x;
	position.y = (float)App->stage05->spawnPos.y + fixedPos.y;

}