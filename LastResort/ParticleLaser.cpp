#include "ParticleLaser.h"
#include "Particle.h"
#include "Application.h"
#include "ModuleStage05.h"
#include "Player1.h"
#include "Player2.h"
Particle_Laser::Particle_Laser(Particle& p) : Particle(p)
{
	if (App->player1->isActive == true && App->player2->isActive == false)
	{
		PlayerPosition.y = App->player1->position.y;
	}
	else if (App->player1->isActive == false && App->player2->isActive == true)
	{
		PlayerPosition.y = App->player1->position.y;
	}

	if (App->player2->position.y > App->player1->position.y && App->player2->isActive==true)
	{
		
		PlayerPosition.y = App->player2->position.y;
	}
	else if(App->player1->position.y > App->player2->position.y && App->player1->isActive == true)
	{
		PlayerPosition.y = App->player1->position.y;
	}
	going_up = true;

	
}
void Particle_Laser:: Move() {
	if (going_up)
	{
		position.x = App->stage05->spawnPos.x + initialPosition.x;
		if (PlayerPosition.y < position.y)
			position.y -= speed.y;
		else
			anim.speed = 0.3;
		if (anim.Finished())
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



}
