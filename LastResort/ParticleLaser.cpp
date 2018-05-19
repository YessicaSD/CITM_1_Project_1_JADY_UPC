#include "ParticleLaser.h"
#include "Particle.h"
#include "Application.h"

#include "Player1.h"
#include "Player2.h"
Particle_Laser::Particle_Laser(Particle& p) : Particle(p)
{
	if (App->player2->position.y > App->player1->position.y && App->player2->IsActive==true)
	{
		PlayerPosition.x = App->player2->position.x;
		PlayerPosition.y = App->player2->position.y;
	}
	else
	{
		PlayerPosition.x = App->player1->position.x;
		PlayerPosition.y = App->player1->position.y;
	}
	
	
}
void Particle_Laser:: Move() {
	if (PlayerPosition.y<position.y)
		position.y -= speed.y;

	if (PlayerPosition.x > position.x )
	{
		position.x += speed.x;
	}
	else if(PlayerPosition.x < position.x)
		position.x -= speed.x;



}
