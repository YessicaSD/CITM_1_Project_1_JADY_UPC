#include "Application.h"
#include "Particle.h"
#include "Particle_OrangeBall.h"
#include "ModuleStage05.h"

Particle_OrangeBall::Particle_OrangeBall() : Particle()
{

}

Particle_OrangeBall::Particle_OrangeBall(Particle& p, iPoint position, Uint32 delay) : Particle(p, position, delay)
{

}

void Particle_OrangeBall::Move()
{
	fixedPos.x -= 4;
	fixedPos.y -= 4;
	position = App->stage05->spawnPos + fixedPos;
};

void Particle_OrangeBall::Draw()
{
	SDL_Rect currentFrame = anim.GetCurrentFrame();
	collider->SetPos(position.x, position.y);
	App->render->Blit(texture, position.x - currentFrame.w / 2, position.y - currentFrame.h / 2, &currentFrame);
}