#ifndef __POWERUP_G_H__
#define __POWERUP_G_H__

#include "Powerup.h"

struct Collider;

class Powerup_G : public Powerup
{
public:
	Powerup_G (int x, int y);
	Animation gAnim;
	void OnCollision(Collider*, ModulePlayer*);
};

#endif // __POWERUP_G_H__
