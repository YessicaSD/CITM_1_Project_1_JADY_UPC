#ifndef __PARTICLE_LASER_H__
#define __PARTICLE_LASER_H__

#include "Particle.h"

class Particle_Laser : public Particle
{
private:
	Animation LaserAnim;
	int initialY;
	fPoint PlayerPosition;
	bool going_up;
	bool go_right;
	bool go_left;
public:

	Particle_Laser();
	/*~Particle_Laser() {

		if (collider != nullptr)
			collider->to_delete = true;
	};*/
	Particle_Laser(Particle& p);
	void Move();
};

#endif // __PARTICLE_LASER_H__
