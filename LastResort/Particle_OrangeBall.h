#ifndef __PARTICLE_ORANGE_BALL_H__
#define __PARTICLE_ORANGE_BALL_H__

#include "Particle.h"

class Particle_OrangeBall : public Particle
{
public:
	Particle_OrangeBall();
	Particle_OrangeBall(Particle& p);

	void Move();
	void Draw();

private:
	iPoint fixedPos;
};

#endif // __PARTICLE_ORANGE_BALL_H__