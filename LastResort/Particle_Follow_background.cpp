#include "Application.h"
#include "Particle.h"
#include "Particle_Follow_background.h"
#include "ModuleStage05.h"

Particle_Follow_background::Particle_Follow_background() : Particle()
{

}

Particle_Follow_background::Particle_Follow_background(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) : Particle(p, position, speed, delay, colType, tex)
{

}

void Particle_Follow_background::Move()
{
	fixedPos.x += speed.x;
	fixedPos.y += speed.y;

	position.x = (float)App->stage05->spawnPos.x + fixedPos.x;
	position.y = (float)App->stage05->spawnPos.y + fixedPos.y;
};

void Particle_Follow_background::Draw()
{
	SDL_Rect currentFrame = anim.GetCurrentFrame();

	//Update collider
	if(collider != nullptr)//INFO: We check if the collider is nullptr because not all particles instanciate a collider
	{
		collider->SetPos((int)position.x - currentFrame.w / 2, (int)position.y - currentFrame.h / 2);
	}	

	//Render
	App->render->Blit(texture, (int)position.x - currentFrame.w / 2, (int)position.y - currentFrame.h / 2, &currentFrame);
}