#ifndef __POWERUP_HOMING_H__
#define __POWERUP_HOMING_H__

#include "Powerup.h"

struct Collider;

class Powerup_Homing : public Powerup
{
public:
	Powerup_Homing(int x, int y);
	Animation homingAnim;
	void OnCollision(Collider*, ModulePlayer*);
};

#endif // __POWERUP_LASER_H
