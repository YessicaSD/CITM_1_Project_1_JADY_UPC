#ifndef __PARTICLE_MISSILE_H__
#define __PARTICLE_MISSILE_H__

#include "Particle.h"

class Particle_Missile : public Particle
{
public:
	
	Particle_Missile(Particle&, fPoint, fPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);
	void Move();
	/*void Draw();
*/
private:
	fPoint targetPlayerPos;
	
	
};

#endif // __PARTICLE_MISSILE_H__

