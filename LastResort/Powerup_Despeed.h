#ifndef __POWERUP_DESPEED_H__
#define __POWERUP_DESPEED_H__

#include "Powerup.h"

struct Collider;

class Powerup_despeed : public Powerup
{
public:
	Powerup_despeed(int x, int y);
	Animation despeedanim;
	void OnCollision(Collider*, ModulePlayer*);
};

#endif // __POWERUP_despeed_H__

