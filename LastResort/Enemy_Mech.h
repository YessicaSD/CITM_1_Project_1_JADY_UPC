#ifndef __ENEMY_MECH_H__
#define __ENEMY_MECH_H__

#include "Enemy.h"
#include "ModuleParticles.h"
class Enemy_Mech : public Enemy
{
private:
	Animation Mech;
	int initialY;
	int position_y;
	int position_x;
	Uint32 StartTime;
	Uint32 CurrentTime;

	SDL_Texture *LacerTex;
public:
	Enemy_Mech(int x, int y, POWERUP_TYPE pu_t);
	~Enemy_Mech() {};
	void Move();
	void Draw(SDL_Texture* sprites);
};

#endif // __ENEMY_MECH_H__
