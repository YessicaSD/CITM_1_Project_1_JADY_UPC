#include "Application.h"
#include "Particle.h"
#include "Particle_Follow_background.h"
#include "ModuleStage05.h"

Particle_Follow_background::Particle_Follow_background() : Particle()
{

}

Particle_Follow_background::Particle_Follow_background(Particle& p, iPoint position, iPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) : Particle(p, position, speed, delay, colType, tex)
{

}

void Particle_Follow_background::Move()
{
	fixedPos.x -= 4;
	fixedPos.y -= 4;
	position = App->stage05->spawnPos + fixedPos;
};

void Particle_Follow_background::Draw()
{
	SDL_Rect currentFrame = anim.GetCurrentFrame();
	collider->SetPos(position.x, position.y);
	App->render->Blit(texture, position.x - currentFrame.w / 2, position.y - currentFrame.h / 2, &currentFrame);
}