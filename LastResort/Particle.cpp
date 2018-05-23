#include "Particle.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"
#include "ModuleStage05.h"
#include "ModuleParticles.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(Particle& p, iPoint position, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex)
{
	this->anim = p.anim;
	this->position = position;
	this->speed = p.speed;
	this->collision_fx = p.collision_fx;
	this->born = SDL_GetTicks() + delay;
	this->life = p.life;
	this->texture = tex;
	this->fixedPos = position - App->stage05->spawnPos;
	if (p.collision_fx != nullptr) { this->collision_fx = p.collision_fx; }
	if (colType != COLLIDER_NONE) { this->collider = App->collision->AddCollider({ this->position.x, this->position.y ,this->anim.GetCurrentFrame().w, this->anim.GetCurrentFrame().h }, colType, (Module*)App->particles);
	}
}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::CheckParticleDeath()
{
	//1- Check if its his "life" time has passed
	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
		{
			return true;
		}
	}

	//2- Check if its animation has finished
	else
	{
		if (anim.Finished())
		{
			return true;
		}
	}

	//3- Check if it out of the screen margins
	if (position.x >  SCREEN_WIDTH + DESPAWN_MARGIN_RIGHT ||
		position.x < 0 - DESPAWN_MARGIN_LEFT ||
		position.y > SCREEN_HEIGHT + DESPAWN_MARGIN_DOWN ||
		position.y < 0 - DESPAWN_MARGIN_UP)
	{
		return true;
	}

	//4- Return false it is shouldn't die (passes all the cases)
	return false;
}

void Particle::Move()
{
	position.x += speed.x;
	position.y += speed.y;
}

void Particle::Draw()
{
	//Update the collider
	if (collider != nullptr)
	{
		collider->SetPos(position.x, position.y - anim.GetFrame().h / 2);
		collider->SetMeasurements(anim.GetFrame().w, anim.GetFrame().h);
	}

	//Draw the particle
	App->render->Blit(texture, position.x - anim.GetCurrentFrame().w / 2, position.y - anim.GetCurrentFrame().h / 2, &anim.GetFrame());
}