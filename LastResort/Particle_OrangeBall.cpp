#include "Application.h"
#include "Particle.h"
#include "Particle_OrangeBall.h"
#include "ModuleStage05.h"

Particle_OrangeBall::Particle_OrangeBall() : Particle()
{

}

Particle_OrangeBall::Particle_OrangeBall(Particle& p) : Particle(p)
{
	//fixedPos = p.initialPosition;
}

void Particle_OrangeBall::Move()
{
	initialPosition.x += speed.x;
	initialPosition.y += speed.y;
	position = initialPosition + App->stage05->spawnPos;
	//fixedPos.x += speed.x;
	//fixedPos.y += speed.y;
	//position = fixedPos + App->stage05->spawnPos;
};

void Particle_OrangeBall::Draw()
{
	SDL_Rect currentFrame = anim.GetCurrentFrame();
	App->render->Blit(texture, position.x - currentFrame.w / 2, position.y - currentFrame.h / 2, &currentFrame);
}