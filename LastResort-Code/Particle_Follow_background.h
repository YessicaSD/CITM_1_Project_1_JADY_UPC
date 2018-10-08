#ifndef __PARTICLE_FOLLOW_BACKGROUND_H__
#define __PARTICLE_FOLLOW_BACKGROUND_H__

#include "Particle.h"

class Particle_Follow_background : public Particle
{
public:
	Particle_Follow_background();
	Particle_Follow_background(Particle&, fPoint, fPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);

	void Move();
	void Draw();
};

#endif // __PARTICLE_FOLLOW_BACKGROUND_H__