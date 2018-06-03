#ifndef __PARTICLE_MISSILE_2_H__
#define __PARTICLE_MISSILE_2_H__

#include "Particle.h"

class ModulePlayer;
class Particle_Missile_2 : public Particle
{
public:

	Particle_Missile_2(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex);
	void Move();
	void Draw();
	void  CheckTarget();
private:
	ModulePlayer *currentTarget = nullptr;
	fPoint speed;
	fPoint aceleration;
	int frameCount;
	enum state
	{
		INIT,
		FOLLOW,

	}missileState = INIT;
	

};

#endif // __PARTICLE_MISSILE_2_H__

