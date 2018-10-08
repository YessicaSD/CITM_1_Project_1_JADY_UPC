#ifndef __PARTICLE_FIREBALL_H__
#define __PARTICLE_FIREBALL_H__

#include "Particle.h"

//Similar to Particle_Follow_background but has a pivot point on the left and a smaller collider

class Particle_Fireball : public Particle
{
public:
	Particle_Fireball();
	Particle_Fireball(Particle&, fPoint, fPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);

	void Move();
	void Draw();
};

#endif // __PARTICLE_FIREBALL_H__