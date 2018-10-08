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
		speed = { 0,-2 };
		fixedPos += speed;
		if (frameCount == 20)
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
		targetPlayerPos.x += 20;
		targetPlayerPos.y += 10;
		speed.UnitVector(targetPlayerPos, position);
		fixedPos.x += speed.x * 1.25f;
		fixedPos.y += speed.y * 1.25f;
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

	//Update the collider
	currentFrame = anim.GetCurrentFrame();
	if (collider != nullptr)//INFO: We check if the collider is nullptr because not all particles instanciate a collider
	{
		collider->SetPos((int)position.x - currentFrame.w / 2, (int)position.y - currentFrame.h / 2);
		collider->SetMeasurements(currentFrame.w, currentFrame.h);
	}
}

void Particle_Missile::Draw()
{
	if(missileState == FOLLOW)
	//Draw the particle
	App->render->BlitEx(this->texture, (int)position.x - currentFrame.w / 2, (int)position.y - currentFrame.h / 2, &anim.GetCurrentFrame(), SDL_FLIP_NONE, (AbsoluteRotation({ (int)position.x, (int)position.y }, { (int)targetPlayerPos.x, (int)targetPlayerPos.y }))*180/PI);
	else
	{
		App->render->BlitEx(this->texture, (int)position.x - currentFrame.w / 2, (int)position.y - currentFrame.h / 2, &anim.GetCurrentFrame(), SDL_FLIP_NONE, -90);
	}
}