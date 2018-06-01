#ifndef __PARTICLE_INDOOR_LASER_H__
#define __PARTICLE_INDOOR_LASER_H__

#include "Particle.h"

class Particle_Indoor_Laser : public Particle
{
public:
	
	Particle_Indoor_Laser(Particle&, fPoint, fPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);

	/*void Move();
	void Draw();*/
};

#endif // __PARTICLE_INDOOR_LASER_H__
