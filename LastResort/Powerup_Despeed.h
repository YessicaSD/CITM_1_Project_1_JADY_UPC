#ifndef __POWERUP_DESPEED_H__
#define __POWERUP_DESPEED_H__

#include "Powerup.h"

struct Collider;
//struct Sfx;

class Powerup_SlowDown : public Powerup
{
public:
	Powerup_SlowDown(int x, int y);
	Animation DespeedAnim;

	void OnCollision(Collider*, ModulePlayer*);
};

#endif // __POWERUP_SPEED_H__