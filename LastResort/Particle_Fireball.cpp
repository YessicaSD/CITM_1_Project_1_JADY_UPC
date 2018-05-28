#include "Application.h"
#include "Particle.h"
#include "Particle_Fireball.h"
#include "ModuleStage05.h"

Particle_Fireball::Particle_Fireball() : Particle()
{

}

Particle_Fireball::Particle_Fireball(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) : Particle(p, position, speed, delay, colType, tex)
{

}

void Particle_Fireball::Move()
{
	fixedPos.x += speed.x;
	fixedPos.y += speed.y;

	position.x = (float)App->stage05->spawnPos.x + fixedPos.x;
	position.y = (float)App->stage05->spawnPos.y + fixedPos.y;

	//Update collider
	currentFrame = anim.GetCurrentFrame();
	if (collider != nullptr)//INFO: We check if the collider is nullptr because not all particles instanciate a collider
	{
		collider->SetPos((int)position.x, (int)position.y - currentFrame.h / 2);
	}
};

void Particle_Fireball::Draw()
{
	//Render
	App->render->Blit(texture, (int)position.x, (int)position.y - currentFrame.h / 2, &currentFrame);
}