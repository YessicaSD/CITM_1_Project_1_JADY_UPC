#include "ParticleLaser.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleStage05.h"
#include "Player1.h"
#include "Player2.h"

Particle_Laser::Particle_Laser():Particle()
{

}

Particle_Laser::Particle_Laser(Particle& p, iPoint position, iPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) : Particle(p, position, speed, delay, colType, tex)
{
	if (App->player1->isActive == true && App->player2->isActive == false)
	{
		PlayerPosition.y = App->player1->position.y+PLAYER_Y;
	}
	else if (App->player1->isActive == false && App->player2->isActive == true)
	{
		PlayerPosition.y = App->player1->position.y + PLAYER_Y;
	}

	if (App->player2->position.y > App->player1->position.y && App->player2->isActive==true)
	{
		PlayerPosition.y = App->player2->position.y + PLAYER_Y;
	}
	else if(App->player1->position.y > App->player2->position.y && App->player1->isActive == true)
	{
		PlayerPosition.y = App->player1->position.y + PLAYER_Y;
	}
	going_up = true;
}

void Particle_Laser:: Move()
{
	if (going_up)
	{
		position.x = App->stage05->spawnPos.x + fixedPos.x;
		position.y = App->stage05->spawnPos.y + fixedPos.y;

		if (PlayerPosition.y < fixedPos.y + App->stage05->spawnPos.y)
			fixedPos.y -= speed.y;
		else
			anim.speed = 0.2;

		if (anim.GetCurrentFrameNum()==12)
		{
			going_up = false;

			if (App->player1->isActive == true && App->player2->isActive == false)
				PlayerPosition.x = App->player1->position.x;
			else if (App->player1->isActive == false && App->player2->isActive == true)
				PlayerPosition.x = App->player1->position.x;
			if (App->player2->position.y > App->player1->position.y && App->player2->isActive == true)
					PlayerPosition.x = App->player2->position.x;
			else if (App->player1->position.y > App->player2->position.y && App->player1->isActive == true)
						PlayerPosition.x = App->player1->position.x;

			if (PlayerPosition.x > position.x)
			go_right = true;
			else
				go_left = true;
		}
			
	}
	

	if (go_right && going_up == false)
	{
		position.x += speed.x;
	}
	 if(go_left && going_up == false)
		position.x -= speed.x;
};

void Particle_Laser::Draw()
{
	SDL_Rect currentFrame = anim.GetCurrentFrame();

	//Update the collider
	if (collider != nullptr)
	{
		collider->SetPos(position.x, position.y - currentFrame.h / 2);
		collider->SetMeasurements(currentFrame.w, currentFrame.h);
	}
	

	//Render
	if (going_up == true || go_left == true)
		App->render->Blit(texture, position.x, position.y - currentFrame.h / 2, &currentFrame);
	else
		App->render->BlitEx(texture, position.x, position.y - currentFrame.h / 2, &currentFrame, SDL_FLIP_HORIZONTAL);
	
}