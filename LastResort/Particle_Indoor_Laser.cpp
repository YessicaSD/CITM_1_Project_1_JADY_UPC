#include "Particle_Indoor_Laser.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleStage05.h"

Particle_Indoor_Laser::Particle_Indoor_Laser(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) :Particle(p, position, speed, delay, colType, tex)
{
	idleAnimation=p.anim.GetFrame() ;
	animation = { 221,0,0,6 };
	LOG("ANIM.X %i", anim.GetCurrentFrame().x);
	
}
void Particle_Indoor_Laser::Move()
{
	if (stateLaser != DECREASE)
	{
		fixedPos += speed;
		position.x = App->stage05->spawnPos.x + fixedPos.x;
		position.y = App->stage05->spawnPos.y + fixedPos.y;
	}

	if (stateLaser == INCREASE)
	{
		LOG("ANIM.X %i", anim.GetCurrentFrame().x);
		if (animation.x > idleAnimation.x)
		{
			animation.x -= 1;
			animation.w += 1;
		}
		else
		{
			stateLaser = IDLE;
		}
	}
	if (stateLaser == IDLE)
	{

	}
}
void Particle_Indoor_Laser::Draw()
{
	if (speed.x > 0)
		App->render->Blit(texture,position.x-animation.w,position.y,&animation);
	else
		App->render->BlitEx(texture, position.x, position.y, &animation);
}