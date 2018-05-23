#ifndef __PARTICLE_ORANGE_BALL_H__
#define __PARTICLE_ORANGE_BALL_H__

#include "Particle.h"

class Particle_OrangeBall : public Particle
{
public:
	Particle_OrangeBall();
	Particle_OrangeBall(Particle&, iPoint);

	void Move();
	void Draw();
};

#endif // __PARTICLE_ORANGE_BALL_H__