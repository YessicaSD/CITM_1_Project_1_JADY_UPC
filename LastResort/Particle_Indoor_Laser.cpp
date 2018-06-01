#include "Particle_Indoor_Laser.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleStage05.h"

Particle_Indoor_Laser::Particle_Indoor_Laser(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) :Particle(p, position, speed, delay, colType, tex)
{
	
	idleAnimation=p.anim.GetFrame() ;
	animation = { 221,0,0,6 };
	
	
}
void Particle_Indoor_Laser::Move()
{
	position.x = App->stage05->spawnPos.x + fixedPos.x;
	position.y = App->stage05->spawnPos.y + fixedPos.y;
	if (stateLaser != DECREASE)
	{
		fixedPos += speed;
		
	}

	if (stateLaser == INCREASE)
	{
		
		if (animation.x > idleAnimation.x)
		{
			animation.x -= labs(speed.x);
			animation.w += labs(speed.x);
		}
		else
		{
			stateLaser = IDLE;
		}
	}
	if (stateLaser == IDLE)
	{
		if (speed.x > 0)
		{
			if (position.x >= App->stage05->spawnPos.x + 850)
				stateLaser = DECREASE;
		}
		else
		{
			if (position.x <= App->stage05->spawnPos.x + 620)
				stateLaser = DECREASE;
		}
		
	}
	if (stateLaser == DECREASE)
	{
		if(animation.w>0)
		animation.w -= labs(speed.x);
	}

	if (collider != nullptr)
	{
		if (speed.x > 0)
		collider->SetPos((int)position.x-animation.w, (int)position.y);
		else
			collider->SetPos((int)position.x , (int)position.y);
		
		collider->SetMeasurements(animation.w, animation.h);
	}
}
void Particle_Indoor_Laser::Draw()
{
	if (speed.x > 0)
		App->render->Blit(texture,position.x-animation.w,position.y,&animation);
	else
		App->render->BlitEx(texture, position.x, position.y, &animation);
}