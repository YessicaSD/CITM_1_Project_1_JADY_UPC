#include "Application.h"
#include "Particle.h"
#include "Particle_OrangeBall.h"
#include "ModuleStage05.h"

Particle_OrangeBall::Particle_OrangeBall() : Particle()
{

}

Particle_OrangeBall::Particle_OrangeBall(Particle& p) : Particle(p)
{

}

void Particle_OrangeBall::Move()
{
	fixedPos.x += 5;
	fixedPos.y += 5;
	position = App->stage05->spawnPos + fixedPos;
};

void Particle_OrangeBall::Draw()
{
	SDL_Rect currentFrame = anim.GetCurrentFrame();
	collider->SetPos(position.x, position.y);
	App->render->Blit(texture, position.x - currentFrame.w / 2, position.y - currentFrame.h / 2, &currentFrame);
}