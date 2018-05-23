#include "Application.h"
#include "ParticleGMissile.h"
#include "Particle.h"
#include "ModuleStage05.h"
#include "Player1.h"
#include "Player2.h"


Particle_G_Missile::Particle_G_Missile(Particle& p, iPoint position, Uint32 delay, COLLIDER_TYPE colType):Particle(p, position, delay, colType)
{


}

void Particle_G_Missile::Move() {

};

void Particle_G_Missile::Draw()
{
	if (going_up == true || go_left == true)
		App->render->Blit(texture, position.x, position.y - anim.GetCurrentFrame().h / 2, &anim.GetFrame());
	else
		App->render->BlitEx(texture, position.x, position.y - anim.GetCurrentFrame().h / 2, &anim.GetFrame(), SDL_FLIP_HORIZONTAL);

}