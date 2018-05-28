#ifndef __POWERUP_SPEED_H__
#define __POWERUP_SPEED_H__

#include "Powerup.h"

struct Collider;
struct Sfx;
class Powerup_Speed : public Powerup
{
public:
	Powerup_Speed(int x, int y);
	Animation speedAnim;
	
	void OnCollision(Collider*, ModulePlayer*);
};

#endif // __POWERUP_SPEED_H__
