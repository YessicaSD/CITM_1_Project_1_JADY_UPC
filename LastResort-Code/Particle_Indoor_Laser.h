#ifndef __PARTICLE_INDOOR_LASER_H__
#define __PARTICLE_INDOOR_LASER_H__

#include "Particle.h"
enum state
{
	INCREASE,
	DECREASE, 
	IDLE,
};
class Particle_Indoor_Laser : public Particle
{
public:
	
	Particle_Indoor_Laser(Particle&, fPoint, fPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);

	void Move();
	state stateLaser=INCREASE;
	SDL_Rect idleAnimation;
	SDL_Rect animation;
	void Draw();
	int frameCount;
};

#endif // __PARTICLE_INDOOR_LASER_H__
