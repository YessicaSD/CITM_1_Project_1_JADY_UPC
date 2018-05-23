#ifndef __PARTICLE_LASER_H__
#define __PARTICLE_LASER_H__

#include "Particle.h"

class Particle_Laser : public Particle
{
public:
	Particle_Laser();
	/*~Particle_Laser() {

		if (collider != nullptr)
			collider->to_delete = true;
	};*/
	Particle_Laser(Particle&, iPoint);
	void Move();
	void Draw();

private:
	Animation LaserAnim;
	fPoint PlayerPosition;
	bool going_up;
	bool go_right;
	bool go_left;
};

#endif // __PARTICLE_LASER_H__
