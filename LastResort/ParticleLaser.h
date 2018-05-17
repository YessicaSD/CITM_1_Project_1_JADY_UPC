#ifndef __PARTICLE_LASER_H__
#define __PARTICLE_LASER_H__

#include "Particle.h"

class Particle_Laser : public Particle
{
private:
	Animation LaserAnim;
	int initialY;

public:
	Particle_Laser() {};
	Particle_Laser(Particle& p);
	void Move();
};

#endif // __PARTICLE_LASER_H__
