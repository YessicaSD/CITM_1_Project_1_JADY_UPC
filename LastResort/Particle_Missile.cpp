#include "Application.h"
#include "Particle_Missile.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "Rotation.h"
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

	position.x = (float)App->stage05->spawnPos.x + fixedPos.x;
	position.y = (float)App->stage05->spawnPos.y + fixedPos.y;

	//if (speed.y <= -0.9f && (anim.GetCurrentFrameNum() > 3 || anim.GetCurrentFrameNum() < 2))
	//{
	//	anim.current_frame = 2;
	//}
	//else if (speed.x >= 1.0f && (int)anim.GetCurrentFrameNum() > 1)
	//{
	//	anim.current_frame = 0;
	//}
	//else if (speed.x <= -0.9 && (anim.GetCurrentFrameNum() < 4 || anim.GetCurrentFrameNum() > 5))
	//{
	//	anim.current_frame = 4;
	//}
	//else if (speed.y <= 0.9 && (anim.GetCurrentFrameNum() < 6 || anim.GetCurrentFrameNum() > 7)) //DOWN
	//{
	//	anim.current_frame = 6;
	//}

}

void Particle_Missile::Draw()
{
	SDL_Rect currentFrame = anim.GetCurrentFrame();

	//Update the collider
	if (collider != nullptr)//INFO: We check if the collider is nullptr because not all particles instanciate a collider
	{
		collider->SetPos((int)position.x - currentFrame.w / 2, (int)position.y - currentFrame.h / 2);
		collider->SetMeasurements(currentFrame.w, currentFrame.h);
	}

	//Draw the particle
	App->render->BlitEx(this->texture, (int)position.x - currentFrame.w / 2, (int)position.y - currentFrame.h / 2, &currentFrame, SDL_FLIP_NONE, (AbsoluteRotation({ (int)position.x, (int)position.y }, { (int)targetPlayerPos.x, (int)targetPlayerPos.y }))*180/PI);
}