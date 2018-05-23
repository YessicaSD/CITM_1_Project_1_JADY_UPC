#ifndef __PARTICLE_G_MISSILE_H__
#define __PARTICLE_G_MISSILE_H__

#include "Particle.h"

class Particle_G_Missile : public Particle
{
private:
	Animation LaserAnim;
	int initialY;
	fPoint PlayerPosition;
	bool going_up;
	bool go_right;
	bool go_left;
public:

	Particle_G_Missile(Particle&, iPoint, iPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);
	void Move();
	void Draw();
};

#endif // __PARTICLE_G_MISSILE_H__

